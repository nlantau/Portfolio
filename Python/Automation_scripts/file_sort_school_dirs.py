# nlantau, 2020-11-06
"""
This script will place files in folders based
on what letters the file name contains

"""
import os
import sys
import regex as re

# TODO: Complete script

# Use case: School
FILE_STRUCTURE = {
    0: "0_Study_Guide",
    1: "1_Litterature",
    2: "2_Lectures",
    3: "3_Exercises",
    4: "4_Assignments",
    5: "5_Reports",
    6: "6_Labs",
    7: "7_PDFs",
    8: "8_Old_Exams",
    9: "9_Formulas",
    10: "10_Other",
}


def subfolders(path: str) -> None:
    """ Creates sutable subfolders """

    file_count = 0
    for k, v in FILE_STRUCTURE.items():
        if os.path.exists(path + r"/" + v):
            continue
        else:
            os.mkdir(path + r"/" + v)
            file_count += 1
    print(f"> Directories created: {file_count}")


def find_files_regex(path: str) -> list:
    """ Finds files containing regex pattern
        Needs to have a flattened directory """

    file_count = 0

    for name in os.listdir(path):
        if re.search(r"\b(lec)", name.lower()):
            print(name)
            move_file(name, path, FILE_STRUCTURE[2])
            file_count += 1
        elif re.search(r"\b(exerc)", name.lower()):
            print(name)
            move_file(name, path, FILE_STRUCTURE[3])
            file_count += 1
        elif re.search(r"\b(study)", name.lower()):
            print(name)
            move_file(name, path, FILE_STRUCTURE[0])
            file_count += 1
        elif re.search(r"\b(assign)", name.lower()):
            print(name)
            move_file(name, path, FILE_STRUCTURE[4])
            file_count += 1
        elif re.search(r"\b(formu)", name.lower()):
            print(name)
            move_file(name, path, FILE_STRUCTURE[9])
            file_count += 1
    print(f"> Files moved: {file_count}")


def move_file(_file: str, path: str, v: str) -> None:
    """ Creates directory if it does not exist
        Moves file to directory specified in FILE_TYPE """

    if not os.path.exists(path + r"/" + v):
        os.mkdir(path + r"/" + v)
    if os.path.exists(path + r"/" + v):
        os.rename(path + r"/" + _file, path + r"/" + v + r"/" + _file)


def menu():
    print(f"\n{' File Sort Based on Part of Name ':-^60}\n")
    print("> 1. Give me a file structure without moving any files")
    print("> 2. Give me a file structure depending on files in directory")


def main(path: str):
    choice = 0
    while True:
        if choice == 1 or choice == 2:
            break
        if choice == 3:
            raise SystemExit
        menu()
        try:
            choice = int(input(">>> "))
        except ValueError:
            continue
    if choice == 1:
        subfolders(path)
    elif choice == 2:
        find_files_regex(path)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("> Need to pass path")
    elif os.path.exists(path := sys.argv[1]):
        main(path)
