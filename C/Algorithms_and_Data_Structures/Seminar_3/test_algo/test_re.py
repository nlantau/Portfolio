# nlantau, 2020-12-15
try:
    import re
    import os
    import platform
except ImportError:
    print("You suck")
    raise IndentationError


def regex_positive_lookbehind():
    # Data to test regex on
    data = os.path.join(os.path.dirname(__file__), r"../../AoC/14.txt")

    # Read data and save it as one string
    with open(data, "r") as r:
        t_string = " ".join(r.read().splitlines())

    # Regex patterns
    val_ad = re.compile(r"(?<=\]\s=)\s(?P<VA>\d+)")
    mem_ad = re.compile(r"(?<=\[)(?P<MA>\d+)(?=\])")
    bin_str = re.compile(r"(?P<bin>[X10]{36})(?=\s\w+)")

    # Apply regex patterns to 'findall()' and 'search()'
    # findall(): Since we're looking for multiple VA and MA
    # search() : Since we're looking for one binary string
    val_ad_matches = val_ad.findall(t_string)
    mem_ad_matches = mem_ad.findall(t_string)
    bin_str_match = bin_str.findall(t_string)

    # Parse VA and MA to integers
    val_ad_matches = map(int, val_ad_matches)
    mem_ad_matches = map(int, mem_ad_matches)

    # Print result
    # print(t_string)
    print("Value addresses :", end=" ")
    print(*val_ad_matches, sep=", ")
    print("Memory addresses:", end=" ")
    print(*mem_ad_matches, sep=", ")
    print(f"Binary string   :", end=" ")
    print(*bin_str_match, sep=", ")


def main():
    regex_positive_lookbehind()


if __name__ == "__main__":
    if platform.system() == "Darwin":
        os.system("clear")
    else:
        try:
            os.system("cls")
        except Exception:
            print("> Did not manage to clear your damn terminal...")
    print(f"{' NEW ':.^30}\n")
    main()
    print("\n")