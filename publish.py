"""
双平台发布：博客园 + Halo。仓库是唯一真理来源。

用法：
  python3 publish.py              # 预览变更
  python3 publish.py --go         # 新增+修改+删文 (草稿)
  python3 publish.py --go --live  # 新增+修改+删文 (正式发布)
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
HALO_CATEGORY = "3defca91-7105-43e9-92c9-67e9b32a1ed2"

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
    return os.path.splitext(os.path.basename(rel))[0].replace(" ", "-").lower()


class Cnblogs:
    key = "cnblogs"
    name = "博客园"

    def __init__(self):
        self.api = xmlrpc.client.ServerProxy(CNBLOGS_API)

    def create(self, fpath, draft):
        content = {
            "title": title_from_path(os.path.relpath(fpath, BASE)),
            "description": "<pre>" + open(fpath).read() + "</pre>",
            "categories": ["[随笔分类]算法竞赛"],
        }
        return self.api.metaWeblog.newPost("snyxz", CNBLOGS_USER, CNBLOGS_TOKEN, content, not draft)

    def update(self, postid, fpath, draft):
        content = {
            "title": title_from_path(os.path.relpath(fpath, BASE)),
            "description": "<pre>" + open(fpath).read() + "</pre>",
            "categories": ["[随笔分类]算法竞赛"],
        }
        return self.api.metaWeblog.editPost(str(postid), CNBLOGS_USER, CNBLOGS_TOKEN, content, not draft)

    def delete(self, postid):
        return self.api.blogger.deletePost("", str(postid), CNBLOGS_USER, CNBLOGS_TOKEN, True)


class Halo:
    key = "halo"
    name = "Halo"

    def __init__(self):
        self.headers = {
            "Authorization": f"Bearer {HALO_TOKEN}",
            "Content-Type": "application/json",
        }

    def _get_full(self, name):
        """从列表 API 找到单篇文章的 post+content"""
        r = requests.get(f"{HALO_API}/posts?size=200", headers=self.headers)
        for it in r.json().get("items", []):
            if it["post"]["metadata"]["name"] == name:
                return it["post"], it.get("content", {"raw": "<p></p>", "content": "", "rawType": "HTML"})
        raise ValueError(f"文章 {name} 未找到")

    def _publish(self, name):
        requests.put(f"{HALO_API}/posts/{name}/publish", headers=self.headers)

    def create(self, fpath, draft):
        name = str(uuid.uuid4())
        title = title_from_path(os.path.relpath(fpath, BASE))
        slug = slug_from_path(os.path.relpath(fpath, BASE))
        code = open(fpath).read()

        body = {
            "post": {
                "apiVersion": "content.halo.run/v1alpha1",
                "kind": "Post",
                "metadata": {"name": name, "annotations": {"content.halo.run/permalink-pattern": "/archives/{slug}"}},
                "spec": {
                    "title": title, "slug": slug, "deleted": False, "publish": not draft,
                    "pinned": False, "allowComment": True, "visible": "PUBLIC", "priority": 0,
                    "excerpt": {"autoGenerate": True, "raw": ""},
                    "categories": [HALO_CATEGORY], "tags": [], "htmlMetas": [],
                    "owner": "snyxz", "template": "", "cover": "",
                },
            },
            "content": {"raw": f"<pre>{code}</pre>", "content": "", "rawType": "HTML"},
        }
        r = requests.post(f"{HALO_API}/posts", headers=self.headers, json=body)
        r.raise_for_status()
        name = r.json()["metadata"]["name"]
        if not draft:
            self._publish(name)
        return name

    def delete(self, name):
        post, content = self._get_full(name)
        post["spec"]["deleted"] = True
        body = {"post": post, "content": content}
        r = requests.put(f"{HALO_API}/posts/{name}", headers=self.headers, json=body)
        r.raise_for_status()

    def update(self, name, fpath, draft):
        post, content = self._get_full(name)
        title = title_from_path(os.path.relpath(fpath, BASE))
        code = open(fpath).read()

        post["spec"]["title"] = title
        post["spec"]["publish"] = not draft
        post["metadata"]["annotations"]["content.halo.run/permalink-pattern"] = "/archives/{slug}"
        content["raw"] = f"<pre>{code}</pre>"

        body = {"post": post, "content": content}
        r = requests.put(f"{HALO_API}/posts/{name}", headers=self.headers, json=body)
        r.raise_for_status()
        if not draft:
            self._publish(name)


def main():
    go_mode   = "--go" in sys.argv
    live_mode = "--live" in sys.argv
    draft = not live_mode
    tag   = "发布" if live_mode else "草稿"

    platforms = []
    if CNBLOGS_TOKEN:
        platforms.append(Cnblogs())
    if HALO_TOKEN:
        platforms.append(Halo())

    if not platforms:
        print("请设置 CNBLOGS_TOKEN 和/或 HALO_TOKEN")
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
        elif any(not record[rel].get(p.key) for p in platforms):
            modified_files.append(rel)

    # 仓库已删的文件 → 同步删除平台文章
    for rel in record:
        if rel not in current:
            deleted_keys.append(rel)

    # ── 预览 ──
    if not go_mode:
        print(f"新增  {len(new_files)} 篇")
        for f in new_files: print(f"  + {f}")
        print(f"修改  {len(modified_files)} 篇")
        for f in modified_files: print(f"  ~ {f}")
        print(f"删除  {len(deleted_keys)} 篇")
        for f in deleted_keys: print(f"  - {f}")
        print(f"\n平台: {', '.join(p.name for p in platforms)}")
        print(f"模式: {tag}")
        if new_files or modified_files:
            print("确认后执行: python3 publish.py --go")
        else:
            print("没有变更。")
        return

    # ── 删除 ──
    for rel in deleted_keys:
        for p in platforms:
            pid = record[rel].get(p.key)
            if not pid:
                continue
            try:
                p.delete(pid)
                record[rel].pop(p.key, None)
                print(f"[删除-{p.name}] {rel}")
            except Exception as e:
                print(f"[删除失败-{p.name}] {rel}: {e}")
            time.sleep(3)
        # 所有平台 ID 都清掉了才删除记录
        if set(record[rel].keys()) <= {"hash"}:
            del record[rel]

    # ── 新增 ──
    for rel in new_files:
        entry = {"hash": hash_file(current[rel])}
        for p in platforms:
            try:
                pid = p.create(current[rel], draft)
                entry[p.key] = pid
                print(f"[{tag}-{p.name}] {rel} → {pid}")
            except Exception as e:
                print(f"[失败-{p.name}] {rel}: {e}")
            time.sleep(3)
        record[rel] = entry

    # ── 修改/补发 ──
    for rel in modified_files:
        entry = record[rel]
        entry["hash"] = hash_file(current[rel])
        for p in platforms:
            pid = entry.get(p.key)
            if not pid:
                try:
                    pid = p.create(current[rel], draft)
                    entry[p.key] = pid
                    print(f"[补发-{p.name}] {rel} → {pid}")
                except Exception as e:
                    print(f"[补发失败-{p.name}] {rel}: {e}")
            else:
                try:
                    p.update(pid, current[rel], draft)
                    print(f"[更新-{p.name}] {rel} → {pid}")
                except Exception as e:
                    print(f"[更新失败-{p.name}] {rel}: {e}")
            time.sleep(3)

    json.dump(record, open(SAVE, "w"), indent=2, ensure_ascii=False)
    print(f"\n{'✅'.join(p.name for p in platforms)} 完成。请 git commit published.json。")


if __name__ == "__main__":
    main()
