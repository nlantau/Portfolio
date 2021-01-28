# nlantau, 2020-07-11
""" Caesar Cipher """

import re
from timer import timer


@timer
def encrypt_msg(string, offset):
    encrypted = ""
    for char in string:
        if char != " " and char.islower():
            encrypted += "".join(chr((ord(char) - 97 + offset) % 26 + 97))
        elif char != " " and char.isupper():
            encrypted += "".join(chr((ord(char) - 65 + offset) % 26 + 65))
        if char == " ":
            encrypted += "".join(" ")
    return encrypted


def decrypt_msg(string, offset):
    decrypted = ""
    for char in string:
        if char != " " and char.islower():
            decrypted += "".join(chr((ord(char) - 97 - offset) % 26 + 97))
        elif char != " " and char.isupper():
            decrypted += "".join(chr((ord(char) - 65 - offset) % 26 + 65))
        if char == " ":
            decrypted += "".join(" ")
    return decrypted


def create_txt_file(filename, msg):
    with open(filename, "w") as writer:
        writer.write(msg)


def read_txt_file(filename):
    with open(filename, "r") as reader:
        return reader.read()


def get_offset() -> int:
    offset = "x"
    while re.search(r"[A-Za-z]", offset):
        offset = input("Enter offset: ")
        if re.fullmatch(r"\d+", offset):
            return int(offset)
        elif re.fullmatch(r"-\d+", offset):
            return int(offset)
        else:
            print("Please, enter only one digit")
    return None


if __name__ == "__main__":
    print(f'\n{" START ":-^60}\n')
    filename = input("Enter filename: ") + "_encrypted.txt"
    offset = get_offset()

    # msg = input("Enter message: ")
    msg = read_txt_file("freq.txt")
    encrypted = encrypt_msg(msg, offset)

    create_txt_file(filename, encrypted)
    decrypted = decrypt_msg(read_txt_file(filename), offset)

    print(f'{" RESULT ":-^60}')
    print(f"Encrypted message located in: {filename!r}")
    print(f"Encryption offset           : {offset!r}")
    # print(f"\nEncrypted message           : {encrypted!r}")
    # print(f"Decrypted message           : {decrypted!r}")
    print(f'\n{" END ":-^60}\n')

