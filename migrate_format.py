"""迁移 published.json 从旧格式到新格式（postid → cnblogs）"""
import json, os

BASE = os.path.dirname(os.path.abspath(__file__))
SAVE = os.path.join(BASE, "published.json")

old = json.load(open(SAVE))
new = {}

for rel, entry in old.items():
    if isinstance(entry, dict):
        new[rel] = {
            "hash": entry["hash"],
            "cnblogs": entry.get("cnblogs", entry.get("postid", "")),
            "halo": entry.get("halo", ""),
        }

json.dump(new, open(SAVE, "w"), indent=2, ensure_ascii=False)
print(f"迁移完成：{len(new)} 条记录")
