# nlantau, 2020-11-12
"""
Test module to execute C program multiple times
"""
import sys
import os
import time
import random
import subprocess
import regex as re
from colorama import Fore, Back, Style


# Hard Coded paths (because I can)
root = r"/Users/nlantau/docs/GitHub/DT256CHT20/Seminar_1/"
# numb_path = root + r"C/output_sorted/"
numb_path = root + r"numb_files_WSL/"
# numb_path = root + r"deviation_test/"
bin_path = root + r"C/"
res_file = root + r"Results/"
shell_command = r"/usr/bin/time"
shell_flag = r"-p"


def progress(count, total, status=""):
    bar_len = 54
    filled_len = int(round(bar_len * count / float(total)))
    percents = round(100.0 * count / float(total), 1)
    bar = f"{Fore.GREEN}={Fore.RESET}" * filled_len + "-" * (bar_len - filled_len)

    print(
        f"[{bar}] {percents:<5}% {count:>3}/{total:<3} File: {Fore.YELLOW}{status:<15}{Fore.RESET}",
        end="\r",
        flush=True,
    )


def run_C_program(bin_name: str) -> list:
    """ Runs C program with each textfile
        Looks for STDERR from C file
        Saves results in res list
        returns res """

    res = []
    try:
        if os.path.exists(c_file := os.path.abspath(root + r"C/./" + bin_name)):
            for i, path in enumerate(os.listdir(numb_path)):
                progress(i, len(os.listdir(numb_path)) - 1, status=path)
                result = subprocess.run(
                    [c_file, numb_path + path], stderr=subprocess.PIPE, text=True,
                )
                res.append(result.stderr.strip("\n"))
            return res
        else:
            print(f"\n\n> {Fore.RED}ERROR{Fore.RESET}: {bin_name} does not exist\n")
            print("> Stopping program\n\n")
            raise SystemExit
    except PermissionError:
        print(
            f"\n\n> {Fore.RED}ERROR{Fore.RESET}: Don't have permission to use {bin_name}\n"
        )
        print("> Make sure you proviced correct name for C-binary\n")
        print("> Stopping program\n\n")
        raise SystemExit


def save_to_file(results: list, res_file_name: str):
    """ If res_file_name does not exist, create the
        file and write Size,Seconds and column names
        for the CSV file. Else, simple append resulting data
        to the CSV file """

    if not os.path.exists(res_file + res_file_name):
        with open(res_file + res_file_name, "w") as creator:
            creator.write("Size,Seconds\n")

    try:
        with open(res_file + res_file_name, "a") as writer:
            for line in results:
                writer.writelines(line + "\n")
        print(f"\n> Results appended to {Fore.CYAN}{res_file_name}{Fore.RESET}\n")
    except FileNotFoundError:
        print("> File not found", file=sys.stderr)
        raise SystemExit
    except Exception as e:
        print("> Exception raised", file=sys.stderr)
        print(e)
        raise SystemExit


def print_progress(bin_name: str, res_file_name, iterations: int):
    """ Print pretty progress to user """

    print(f"\n\n{' Test started ':-^56}\n")
    info = [
        f"> Running C binary     : {Fore.CYAN}{bin_name}{Fore.RESET}",
        f"> Saving results in    : {Fore.CYAN}{res_file_name}{Fore.RESET}",
        f"> Iterations registered: {Fore.CYAN}{iterations}{Fore.RESET}\n",
    ]
    for i, line in enumerate(info):
        for ch in line:
            print(f"{ch}", end="", flush=True)
            time.sleep(0.01)
            #time.sleep(random.random() / 10)
        print()

    loading_spinner()


def loading_spinner():
    # Print loading spinner
    for _ in range(10):
        for i in ["-", "\\", "|", "/"]:
            print(f" Loading... {i}", end="\r")
            time.sleep(0.05)


def main(bin_name: str, res_file_name: str, iterations: int):
    print_progress(bin_name, res_file_name, iterations)
    for i in range(iterations):

        print(
            f"> Iteration: {Fore.BLUE}{i+1}{Fore.RESET} of {Fore.BLUE}{iterations}{Fore.RESET}"
        )
        results = run_C_program(bin_name)
        save_to_file(results, res_file_name)
        print()

    print(f"\n{' Test Done ':-^56}\n")
    info = f"> Results stored in: {Fore.GREEN}{res_file + res_file_name}{Fore.RESET}\n\n"
    for ch in info:
        print(f"{ch}", end="", flush=True)
        time.sleep(0.01)
        #time.sleep(random.random() / 10)


if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("> Need to provide name of C binary and name of results textfile")
        print("> ex: 'python tester.py qs_reca QS_Rec_10iter.CSV <iterations>' ")
        raise SystemExit
    else:
        try:
            parsed_argv = int(sys.argv[3])
            main(sys.argv[1], sys.argv[2], parsed_argv)
        except ValueError:
            print(
                f"> {Fore.RED}ERROR{Fore.RESET}: 3rd arg needs to be an integer",
                file=sys.stderr,
            )
            raise SystemExit
