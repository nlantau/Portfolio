# nlantau, 2020-11-05
"""
This script automates the process of structuring a folder.

A menu will give the user the option to move and/or remove
files.

The user must pass the absolut path to the desired directory.

> Move:
If the extension of the file found in the passed directory
matches a key of the dictionary FILE_TYPE, the file will be
moved to a subfolder with the name of the FILE_TYPE value.

> Remove:
If the extension of the file found in the passed directory
matches a key of the dictionary FILES_TO_REMOVE, the file will be
removed from the passed directory.


"""

import os
import sys
import re

# Use Case: Downloads folder
FILE_TYPE = {
    ".py": "1_Python_Scripts",
    ".bin": "4_Binaries",
    ".txt": "8_Text_Files",
    ".java": "1_Java_Files",
    ".jar": "1_Java_Files",
    ".c": "1_C_Source_Files",
    ".h": "1_C_Header_Files",
    ".pdf": "5_PDFs",
    ".docx": "5_Word_Docs",
    ".dotx": "5_Word_Docs",
    ".pptx": "5_Power_Points",
    ".ppt": "5_Power_Points",
    ".zip": "4_ZIP_files",
    ".mp3": "9_mp3_files",
    ".dmg": "4_DMG_and_ISO_install",
    ".csv": "4_CSV_Files",
    ".png": "3_PNG_Files",
    ".jpg": "3_JPG_Files",
    ".svg": "3_SVG_Files",
    ".fzpz": "1_Fritzing_Files",
    ".json": "5_JSON_Files",
    ".sh": "1_Shell_Scripts",
    ".bash": "1_Shell_Scripts",
    ".efi": "4_Binaries",
    ".iso": "4_DMG_and_ISO_install",
    ".ino": "11_Arduino",
}
"""
# Use Case: Print Screens and Screen Recordings
FILE_TYPE = {".png": "1_Print_Screens", ".mov": "2_Screen_Recordings"}
"""

FILES_TO_REMOVE = [
    ".pkl",
    ".srt",
    ".ics",
    ".crdownload",
    "colors",
    ".ttf",
    ".woff",
    ".woff2",
    ".reg",
    ".theme",
    ".conf",
    ".terminal",
    ".xrdb",
    "scheme",
    ".yml",
    ".html",
    ".config",
    ".tex",
    "_0",
    ".toml",
    ".ini",
    ".class",
    ".mkv",
    ".ttc",
    ".css",
    ".mp4",
    ".xml",
]


def get_list_of_current_directory(path: str) -> str:
    return os.listdir(path)


def separate_files_and_directories(list_of_dir: list, path: str) -> list:
    """ Create directories for each file type
        in current directory """

    os.chdir(path)
    files = []

    for _file in list_of_dir:
        if re.search(r"[.*]", _file):
            files.append(_file)
    return files


def mkdir_(files: list, path: str) -> str:
    """ Iterates over the list of files
        and checks if the file extension matches
        any key in FILE_TYPE.

        If the file extension is in FILE_TYPE,
        create folder and/or move file """

    # Make sure we're in the current directory
    os.chdir(path)
    # Count amount of moved files
    counter = 0

    for _file in files:
        for k, v in FILE_TYPE.items():
            if _file.endswith(k):
                move_file(_file, path, v)
                counter += 1
    return counter


def remove_file(files: list, path: str) -> str:
    """ Iterates over the list of files
        and checks if the file extension matches
        any key in FILES_TO_REMOVE.

        If the file extension is in FILES_TO_REMOVE
        the file is removed """

    # Count amount of removed files
    counter = 0

    for _file in files:
        for el in FILES_TO_REMOVE:
            if _file.endswith(el):
                try:
                    os.remove(_file)
                    counter += 1
                except (FileNotFoundError, IOError):
                    print(f"> Error removing: {_file}")
    return counter


def move_file(_file: str, path: str, v: str) -> None:
    """ Creates directory if it does not exist
        Moves file to directory specified in FILE_TYPE """

    if not os.path.exists(path + r"/" + v):
        os.mkdir(path + r"/" + v)
    if os.path.exists(path + r"/" + v):
        os.rename(path + r"/" + _file, path + r"/" + v + r"/" + _file)


def menu() -> int:
    """ Print simply menu to STDOUT """

    print("> Enter choice: ")
    print("> 1. Only Move files")
    print("> 2. Only Remove files")
    print("> 3. Remove and Move files")


def main(path: str) -> None:
    """ Main function caller of the script """

    print(f"> Path passed: {path}")

    # Check writability
    if os.access(path, os.W_OK):
        print(f"> You're allowed to modify {path}")

        menu()
        while (choice := input("> Enter choice: ")) not in ["1", "2", "3"]:
            menu()

        # Get CWD and store it as 'path'
        os.chdir(path)
        path = os.getcwd()

        files = separate_files_and_directories(
            get_list_of_current_directory(path), path
        )
        if choice == "1" or choice == "3":
            # Make directories if needed and move files
            print("> Moving files...")
            nbr_of_files = mkdir_(files, path)
            print(f"> Files moved: {nbr_of_files}")

        if choice == "2" or choice == "3":
            print("> Removing files...")
            nbr_of_removes = remove_file(files, path)
            print(f"> Files removed: {nbr_of_removes}")
    else:
        print(f"> You're NOT allowed to modify {path}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"{' Need to pass the absolut path ':-^50}")
    try:
        folder_to_sort = sys.argv[1]
        main(folder_to_sort)
    except (IndexError, IOError, FileNotFoundError):
        print(r"> Example: /Users/nlantau/Downloads/")
