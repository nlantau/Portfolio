# nlantau, 2020-11-05
"""
Takes all files in all subdirectories and places
them in chosen directory
"""

import os
import sys


def walk_directories(path: str) -> None:
    file_count = 0
    dirs_count = 0
    for root, dirs, files in os.walk(path, topdown=False):
        for name in files:
            os.rename(os.path.join(root, name), path + r"/" + name)
            file_count += 1
        for name in dirs:
            os.rmdir(os.path.join(root, name))
            dirs_count += 1
    print(f"> Files flattened: {file_count}")
    print(f"> Directories removed: {dirs_count}")


def main(path: str) -> None:
    walk_directories(path)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("> Please pass in path")
        sys.exit(1)
    elif os.path.exists(path := sys.argv[1]):
        print(f"> Path entered: {path}")

        # Prevent flattening close to root
        if len(path) > 20:
            main(path)
