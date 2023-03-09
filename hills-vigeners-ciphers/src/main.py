import string
import vigener_cipher as vc
import hills_cipher as hc
from math import floor
from random import random


def generate_key():
    alphabet = list(string.ascii_uppercase)
    j = len(alphabet)
    while j > 1:
        i = int(floor(random() * j))
        j -= 1
        alphabet[i], alphabet[j] = alphabet[j], alphabet[i]
    return ''.join(alphabet)


class SubstitutionCipher:
    def __init__(self):
        self.key = generate_key()
        self.alphabet = ''.join(string.ascii_uppercase)

    def translate(self, text, encrypt=True):
        a = self.alphabet
        b = self.key
        if not encrypt:
            a, b = b, a
        return text.translate(text.maketrans(a, b))

    def get_key(self):
        return self.key


def task1():
    cipher = SubstitutionCipher()
    cipher_text = cipher.translate("HELLODARKNET")
    decipher_text = cipher.translate(cipher_text, False)
    print("alphabet: ", string.ascii_uppercase)
    print("key:      ", cipher.get_key())
    print("encrypted:", cipher_text)
    print("decrypted:", decipher_text)
    print("-----------------")


def main():
    # vc.task2()
    hc.task3()


if __name__ == '__main__':
    main()
