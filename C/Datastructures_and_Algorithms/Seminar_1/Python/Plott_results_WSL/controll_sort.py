# nlantau, 2020-11-19
"""
This module will go through textfiles containing integers
and check if it is sorted

It will also compare occurences in both files, to make sure
that all the original numbers exists in the sorted file
"""

import os
import sys
from colorama import Fore, Style


root = r"/mnt/c/Github/DT256CHT20/C/output_sorted/"
numbs_dir = r"/mnt/c/GitHub/DT256CHT20/"


def compare_occurences(sorted_file, unsorted_file) -> bool:
    """ Read the unsorted file and compare with
        the sorted file
    """

    sorted_dict = {k: 0 for k in sorted_file}
    original_dict = {k: 0 for k in unsorted_file}

    for n in sorted_file:
        sorted_dict[n] += 1

    for n in unsorted_file:
        original_dict[n] += 1

    print({k: original_dict[k] for k in set(original_dict) - set(sorted_dict)})
    print({k: sorted_dict[k] for k in set(sorted_dict) - set(original_dict)})

    return sorted_dict == original_dict


def read_sorted_file(path: str) -> list:
    """ Read the supposedly sorted file
        Append to list
        Send to check_order to see if it
        is sorted
        return list if it is sorted """

    try:
        with open(path, "r") as reader:
            target = [int(i.strip()) for i in reader.readlines()]
            err = check_order(target)
            if len(err) >= 1:
                print(f"> {Fore.RED}Errors found at{Fore.RESET}")
                for k, v in err.items():
                    print(f"> Line number {k} value {v}")

                print(*("\n" for _ in range(3)))
                raise SystemExit
            else:
                print(f"> Sorted: {Fore.GREEN}Check{Fore.RESET}")
                return target
    except ValueError as v:
        print("> Value error", file=sys.stderr)
    except Exception as e:
        print("> Error ", file=sys.stderr)


def check_order(numbers: list) -> dict:
    """ Compare n < n + 1
        If error, save line number
        Return error list with line
        numbers and their values """

    error_list = {}
    temp = 0

    for i in range(len(numbers) - 1):
        if numbers[i] > numbers[i + 1]:
            error_list[i + 1] = numbers[i]

    return error_list


def read_original_unsorted_file(path: str) -> list:
    """ Read original unsorted file
        and return as a list """
    try:
        with open(path, "r") as reader:
            return [int(i.strip()) for i in reader.readlines()]
    except Exception as e:
        print(f"> Something went wrong with the unsorted file", file=sys.stderr)


def main(path, original):
    print(*("\n" for _ in range(3)))
    print(f'{Fore.GREEN}{" RESULT ":-^27}{Fore.RESET}\n')

    checked_list = read_sorted_file(path)
    original_list = read_original_unsorted_file(original)
    is_equal = compare_occurences(checked_list, original_list)

    if is_equal:
        print(f"> Occurence: {Fore.GREEN} Check {Fore.RESET}")
    else:
        print(f"> Occurence: {Fore.RED} Fail {Fore.RESET}")

    print(*("\n" for _ in range(3)))


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("> Need to provide path sorted file and original file")
        print(
            "> Example: python controll_sort.py sorted_textfile.txt original_textfile.txt"
        )
        raise SystemExit
    elif os.path.exists(path := os.path.abspath(root + sys.argv[1])):
        if os.path.exists(original := os.path.abspath(numbs_dir + sys.argv[2])):
            main(path, original)
        else:
            print(f"> {original} not found")
    else:
        print(f"\n> {Fore.RED}ERROR{Fore.RESET} File does not exist...")
        print("> Stopping program\n")
        raise SystemExit
