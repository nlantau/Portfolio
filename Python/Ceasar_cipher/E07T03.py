# nlantau, 2020-07-12
""" Frequency analysis """

from timer import timer


def read_txt_file(filename):
    with open(filename, "r") as reader:
        return reader.read()


def create_dict():
    return {
        k: v for (k, v) in zip([chr(97 + k) for k in range(26)], [0 for x in range(26)])
    }


@timer
def find_frequency(alpha_dict: dict, text: str) -> dict:
    for letter in text:
        if letter.isalpha():
            alpha_dict[letter] += 1
    return alpha_dict


def analyze_freq(filename: str) -> dict:
    text: str = read_txt_file(filename).lower()

    # Create dict; key : letters, value : 0
    alpha_dict_zero = create_dict()

    # Analyze frequency of each letter. Increase value by occurence
    alpha_dict_freq = find_frequency(alpha_dict_zero, text)

    return alpha_dict_freq


if __name__ == "__main__":
    pass

