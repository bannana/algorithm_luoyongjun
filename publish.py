"""
双平台发布脚本：博客园 + Halo，检测 .cpp 文件变更，自动同步。
仓库是唯一真理来源，平台多余文章自动清理。

published.json 格式:
  "1/1.1e1-约瑟夫问题.cpp": {"hash":"...", "cnblogs":"20848330", "halo":"uuid"}

用法：
  python3 publish.py                     # 预览变更
  python3 publish.py --go                # 新增+修改
  python3 publish.py --go --allow-delete # 新增+修改+删除(含平台孤儿清理)
  python3 publish.py --go --live         # 正式发布
"""
import json
import hashlib
import os
import sys
import time
import uuid
import xmlrpc.client

import requests

# ===== 配置 =====
CNBLOGS_TOKEN = os.environ.get("CNBLOGS_TOKEN", "")
CNBLOGS_USER  = os.environ.get("CNBLOGS_USER", "snyxz")
CNBLOGS_API   = "https://rpc.cnblogs.com/metaweblog/snyxz"

HALO_TOKEN = os.environ.get("HALO_TOKEN", "")
HALO_API   = os.environ.get("HALO_API", "https://hecloud.top/apis/api.console.halo.run/v1alpha1")
HALO_CATEGORY = os.environ.get("HALO_CATEGORY", "3defca91-7105-43e9-92c9-67e9b32a1ed2")

BASE = os.path.dirname(os.path.abspath(__file__))
SAVE = os.path.join(BASE, "published.json")
# ==================


def hash_file(path):
    with open(path, "rb") as f:
        return hashlib.md5(f.read()).hexdigest()


def scan_files():
    result = {}
    for root, dirs, names in os.walk(BASE):
        dirs[:] = [d for d in dirs if d != ".git"]
        for name in names:
            if name.endswith(".cpp"):
                rel = os.path.relpath(os.path.join(root, name), BASE)
                result[rel] = os.path.join(root, name)
    return dict(sorted(result.items()))


def title_from_path(rel):
    stem = os.path.splitext(os.path.basename(rel))[0]
    folder = os.path.basename(os.path.dirname(rel))
    if "-" in stem:
        parts = stem.split("-", 1)
        return f"[第{folder}章 {parts[0]}] {parts[1]}"
    return f"[第{folder}章] {stem}"


def slug_from_path(rel):
    stem = os.path.splitext(os.path.basename(rel))[0]
    return stem.replace(" ", "-").lower()


# ══════════════════════════════════════════════
#  博客园
# ══════════════════════════════════════════════

class Cnblogs:
    key = "cnblogs"

    def __init__(self):
        if not CNBLOGS_TOKEN:
            raise RuntimeError("未设置 CNBLOGS_TOKEN 环境变量")
        self.api = xmlrpc.client.ServerProxy(CNBLOGS_API)

    def all_ids(self):
        """返回平台上所有算法竞赛文章的 postid 集合"""
        ids = set()
        try:
            posts = self.api.metaWeblog.getRecentPosts("snyxz", CNBLOGS_USER, CNBLOGS_TOKEN, 200)
            for p in posts:
                cats = p.get("categories", [])
                if any("算法竞赛" in c for c in cats):
                    ids.add(p["postid"])
        except Exception as e:
            print(f"[警告] 博客园获取文章列表失败: {e}")
        return ids

    def create(self, fpath, draft):
        content = {
            "title": title_from_path(os.path.relpath(fpath, BASE)),
            "description": "<pre>" + open(fpath).read() + "</pre>",
            "categories": ["[随笔分类]算法竞赛"],
        }
        return self.api.metaWeblog.newPost("snyxz", CNBLOGS_USER, CNBLOGS_TOKEN, content, draft)

    def update(self, postid, fpath, draft):
        content = {
            "title": title_from_path(os.path.relpath(fpath, BASE)),
            "description": "<pre>" + open(fpath).read() + "</pre>",
            "categories": ["[随笔分类]算法竞赛"],
        }
        return self.api.metaWeblog.editPost(str(postid), CNBLOGS_USER, CNBLOGS_TOKEN, content, draft)

    def delete(self, postid):
        return self.api.blogger.deletePost("", str(postid), CNBLOGS_USER, CNBLOGS_TOKEN, True)


# ══════════════════════════════════════════════
#  Halo
# ══════════════════════════════════════════════

class Halo:
    key = "halo"

    def __init__(self):
        if not HALO_TOKEN:
            raise RuntimeError("未设置 HALO_TOKEN 环境变量")
        self.headers = {
            "Authorization": f"Bearer {HALO_TOKEN}",
            "Content-Type": "application/json",
        }

    def all_ids(self):
        """返回平台上所有未删除文章的 name/UUID 集合"""
        ids = set()
        try:
            r = requests.get(f"{HALO_API}/posts?size=200", headers=self.headers)
            for it in r.json().get("items", []):
                if not it["post"]["spec"].get("deleted"):
                    ids.add(it["post"]["metadata"]["name"])
        except Exception as e:
            print(f"[警告] Halo 获取文章列表失败: {e}")
        return ids

    def _get_post(self, name):
        r = requests.get(f"{HALO_API}/posts/{name}", headers=self.headers)
        r.raise_for_status()
        return r.json()

    def create(self, fpath, draft):
        name = str(uuid.uuid4())
        title = title_from_path(os.path.relpath(fpath, BASE))
        slug = slug_from_path(os.path.relpath(fpath, BASE))
        code = open(fpath).read()

        body = {
            "post": {
                "apiVersion": "content.halo.run/v1alpha1",
                "kind": "Post",
                "metadata": {
                    "name": name,
                    "annotations": {"content.halo.run/permalink-pattern": "/archives/{slug}"},
                },
                "spec": {
                    "title": title, "slug": slug,
                    "deleted": False, "publish": not draft,
                    "pinned": False, "allowComment": True,
                    "visible": "PUBLIC", "priority": 0,
                    "excerpt": {"autoGenerate": True, "raw": ""},
                    "categories": [HALO_CATEGORY], "tags": [], "htmlMetas": [],
                    "owner": "snyxz", "template": "", "cover": "",
                },
            },
            "content": {"raw": f"<pre>{code}</pre>", "content": "", "rawType": "HTML"},
        }
        r = requests.post(f"{HALO_API}/posts", headers=self.headers, json=body)
        r.raise_for_status()
        result = r.json()
        name = result["metadata"]["name"]
        if not draft:
            requests.put(f"{HALO_API}/posts/{name}/publish", headers=self.headers)
        return name

    def update(self, name, fpath, draft):
        old = self._get_post(name)
        title = title_from_path(os.path.relpath(fpath, BASE))
        code = open(fpath).read()

        old["post"]["spec"]["title"] = title
        old["post"]["spec"]["publish"] = not draft
        old["post"]["metadata"]["annotations"]["content.halo.run/permalink-pattern"] = "/archives/{slug}"
        old["content"]["raw"] = f"<pre>{code}</pre>"

        r = requests.put(f"{HALO_API}/posts/{name}", headers=self.headers, json=old)
        r.raise_for_status()
        if not draft:
            requests.put(f"{HALO_API}/posts/{name}/publish", headers=self.headers)

    def delete(self, name):
        old = self._get_post(name)
        old["post"]["spec"]["deleted"] = True
        r = requests.put(f"{HALO_API}/posts/{name}", headers=self.headers, json=old)
        r.raise_for_status()


# ══════════════════════════════════════════════
#  主逻辑
# ══════════════════════════════════════════════

def main():
    go_mode      = "--go" in sys.argv
    allow_delete = "--allow-delete" in sys.argv
    live_mode    = "--live" in sys.argv

    draft = not live_mode
    tag   = "发布" if live_mode else "草稿"

    platforms = []
    if CNBLOGS_TOKEN:
        platforms.append(("博客园", Cnblogs()))
    else:
        print("[跳过] 博客园 — 未设 CNBLOGS_TOKEN")
    if HALO_TOKEN:
        platforms.append(("Halo", Halo()))
    else:
        print("[跳过] Halo — 未设 HALO_TOKEN")

    if not platforms:
        print("没有可用平台，请设置 CNBLOGS_TOKEN 和/或 HALO_TOKEN")
        sys.exit(1)

    record = {}
    if os.path.exists(SAVE):
        record = json.load(open(SAVE))

    current = scan_files()
    new_files = []
    modified_files = []
    deleted_keys = []

    for rel, fpath in current.items():
        h = hash_file(fpath)
        if rel not in record:
            new_files.append(rel)
        elif record[rel].get("hash") != h:
            modified_files.append(rel)
        else:
            need_catchup = any(
                not record[rel].get(p.key) for _, p in platforms
            )
            if need_catchup:
                modified_files.append(rel)

    for rel in record:
        if rel not in current:
            deleted_keys.append(rel)

    # ── 检查平台孤儿（平台有但 published.json 没有）──
    orphans = {}
    if allow_delete:
        for pname, p in platforms:
            valid_ids = set()
            for rel, entry in record.items():
                pid = entry.get(p.key)
                if pid:
                    valid_ids.add(pid)
            remote_ids = p.all_ids()
            orphan_ids = remote_ids - valid_ids
            if orphan_ids:
                orphans[pname] = orphan_ids

    # ── 预览模式 ──
    if not go_mode:
        print(f"新增  {len(new_files)} 篇")
        for f in new_files:
            print(f"  + {f}")
        print(f"修改  {len(modified_files)} 篇")
        for f in modified_files:
            print(f"  ~ {f}")
        print(f"删除  {len(deleted_keys)} 篇  (需 --allow-delete)")
        for f in deleted_keys:
            print(f"  - {f}")
        if orphans:
            for pname, ids in orphans.items():
                print(f"孤儿  {len(ids)} 篇 on {pname}  (需 --allow-delete)")
        else:
            print("孤儿  0 篇 (平台与仓库一致)")
        print(f"\n平台: {', '.join(p[0] for p in platforms)}")
        if new_files or modified_files or (deleted_keys and allow_delete) or orphans:
            print(f"确认后执行: python3 publish.py --go")
        else:
            print("没有变更。")
        return

    # ── 执行模式 ──

    # 平台孤儿清理
    for pname, p in platforms:
        if pname not in orphans:
            continue
        for pid in orphans[pname]:
            try:
                p.delete(pid)
                print(f"[清理孤儿-{pname}] {pid}")
            except Exception as e:
                print(f"[清理孤儿失败-{pname}] {pid}: {e}")
            time.sleep(0.5)

    # 删除仓库已删除的文件
    if deleted_keys and not allow_delete:
        print(f"[跳过删除] {len(deleted_keys)} 篇，加 --allow-delete 才删")
    else:
        for rel in deleted_keys:
            for pname, p in platforms:
                pid = record[rel].get(p.key)
                if not pid:
                    continue
                try:
                    p.delete(pid)
                    record[rel].pop(p.key, None)
                    print(f"[删除-{pname}] {rel}")
                except Exception as e:
                    print(f"[删除失败-{pname}] {rel}: {e}")
            if set(record[rel].keys()) <= {"hash"}:
                del record[rel]

    # 新增
    for rel in new_files:
        entry = {"hash": hash_file(current[rel])}
        for pname, p in platforms:
            try:
                pid = p.create(current[rel], draft)
                entry[p.key] = pid
                print(f"[{tag}-{pname}] {rel} → {pid}")
            except Exception as e:
                print(f"[失败-{pname}] {rel}: {e}")
            time.sleep(1.5)
        record[rel] = entry

    # 修改（含补发）
    for rel in modified_files:
        entry = record[rel]
        entry["hash"] = hash_file(current[rel])
        for pname, p in platforms:
            pid = entry.get(p.key)
            if not pid:
                try:
                    pid = p.create(current[rel], draft)
                    entry[p.key] = pid
                    print(f"[补发-{pname}] {rel} → {pid}")
                except Exception as e:
                    print(f"[补发失败-{pname}] {rel}: {e}")
            else:
                try:
                    p.update(pid, current[rel], draft)
                    print(f"[更新-{pname}] {rel} → {pid}")
                except Exception as e:
                    print(f"[更新失败-{pname}] {rel}: {e}")
            time.sleep(1.5)

    json.dump(record, open(SAVE, "w"), indent=2, ensure_ascii=False)
    print("\n完成。请把 published.json 一起 git commit。")


if __name__ == "__main__":
    main()
