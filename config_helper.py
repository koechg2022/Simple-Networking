#!/usr/bin/env python3

import os

def print_tree(start_path, prefix="", ignore=None):
    if ignore is None:
        ignore = [".git"]
    entries = sorted(os.listdir(start_path))
    # Filter out ignored entries before counting
    entries = [entry for entry in entries if entry not in ignore]
    entries_count = len(entries)
    for i, entry in enumerate(entries):
        path = os.path.join(start_path, entry)
        connector = "└── " if i == entries_count - 1 else "├── "
        print(prefix + connector + entry)
        if os.path.isdir(path):
            extension = "    " if i == entries_count - 1 else "│   "
            print_tree(path, prefix + extension, ignore)

if __name__ == "__main__":
    print(".")
    print_tree("./", ignore=[".git", "build", "config_helper.py", ".gitignore"])
