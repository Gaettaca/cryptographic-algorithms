import numpy as np
from random import random
from math import floor


def enhanced_gcd(a, b):
    if a == 0:
        return b, 0, 1
    d, x1, y1 = enhanced_gcd(abs(b % a), a)
    x = y1 - (b // a) * x1
    y = x1
    return d, x, y


def find_any_solution(a, b):
    g = enhanced_gcd(abs(a), abs(b))
    return -g[1] if a < 0 else g[1]


def inverse_modulo(det, m):
    mod = find_any_solution(round(det), m)
    return (mod % m + m) % m


class HillsCipher:
    def __init__(self, n):
        self.n = n
        self.modulo = 29
        self.key = self.generate_key(n)
        self.alphabet = self.generate_alphabet()
        self.inv_alphabet = self.generate_inv_alphabet()

    def generate_key(self, n):
        key = np.random.random_integers(0, self.modulo - 1, (n, n))
        det = np.linalg.det(key)
        while round(det) == 0 or round(det) % self.modulo == 0:
            key = np.random.random_integers(0, self.modulo - 1, (n, n))
            det = np.linalg.det(key)

        return key

    def generate_alphabet(self):
        alpha = {chr(i): i - 65 for i in range(65, 91)}
        alpha[' '] = 26
        alpha['.'] = 27
        alpha['?'] = 28
        return alpha

    def generate_inv_alphabet(self):
        inv_alpha = {i: chr(i + 65) for i in range(26)}
        inv_alpha[26] = ' '
        inv_alpha[27] = '.'
        inv_alpha[28] = '?'
        return inv_alpha

    def resize_message(self, message):
        a = self.n - len(message) % self.n
        add = ''
        for (x, y), value in np.ndenumerate(np.random.random_integers(0, self.modulo - 1, (1, a))):
            add = add + self.inv_alphabet[value]
        return message + add

    def encrypt(self, text):
        text = self.resize_message(text)
        message_vector = np.array(self.alphabet[i] for i in text)
        encrypted_message = np.array([], dtype=int)
        for i in list(range(len(message_vector) - self.n + 1))[::self.n]:
            encrypted_message = np.concatenate(
                encrypted_message, self.key.dot(message_vector[i: i + self.n]) % self.modulo)
        return encrypted_message

    def decrypt(self, text):
        det = np.linalg.det(self.key)
        inverse_key = np.linalg.inv(self.key) * det

        inverse_key = np.round(inverse_key)
        inverse_key = inverse_key.astype(int)

        inverse_key %= self.modulo

        inv_det = inverse_modulo(det, self.modulo)

        inverse_key *= inv_det
        inverse_key %= self.modulo

        decrypted_message = np.array([], dtype=int)
        sliced_text = np.reshape(text, (text.size // self.n, self.n))

        for i in range(sliced_text.shape[0]):
            decrypted_message = np.concatenate(decrypted_message, inverse_key.dot(sliced_text[i]) % self.modulo)
        return decrypted_message

    def translate_into_alphabet(self, message):
        return ''.join([self.inv_alphabet[i] for i in message])

    def check(self):
        self.key = np.array([[6, 24, 1],
                             [13, 16, 10],
                             [20, 17, 15]])


def task3():
    hc = HillsCipher(5)

    message = "HELLOIMTHEDOCTORIMRIDICOLOUS"
    encrypted = hc.encrypt(message)
    decrypted = hc.decrypt(encrypted)
    print("encrypted: ", message, "-->", encrypted, "-->", hc.translate_into_alphabet(encrypted))
    print("decrypted: ", decrypted, "-->", hc.translate_into_alphabet(decrypted))

    # message = "TRUST"
    # encrypted = hc.encrypt(message)
    # decrypted = hc.decrypt(encrypted)
    # print("open text: ", message)
    # print("encrypted: ", encrypted, "-->", hc.translate_into_alphabet(encrypted))
    # print("decrypted: ", decrypted, "-->", hc.translate_into_alphabet(decrypted))

    # message2 = "THEM"
    # encrypted = hc.encrypt(message2)
    # decrypted = hc.decrypt(encrypted)
    # print("open text: ", message2)
    # print("encrypted: ", encrypted, "-->", hc.translate_into_alphabet(encrypted))
    # print("decrypted: ", decrypted, "-->", hc.translate_into_alphabet(decrypted))
