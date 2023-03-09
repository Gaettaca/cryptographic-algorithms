import string


class VigenereCipher:
    def __init__(self, key):
        self.alphabet = ''.join(string.ascii_uppercase)
        self.key = key

    def size_key(self, text_len):
        sized_key = self.key
        for i in range(len(self.key), text_len):
            sized_key += self.key[i % len(self.key)]
        print("sized key:", sized_key)
        return sized_key

    def encrypt(self, text):
        sized_key = self.size_key(len(text))
        encrypted = ''
        for i in range(len(text)):
            encrypted += chr((ord(sized_key[i]) + ord(text[i]) - 130) % 26 + 65)
        return encrypted

    def decrypt(self, text):
        sized_key = self.size_key(len(text))
        decrypted = ''
        for i in range(len(text)):
            decrypted += chr((ord(text[i]) - (ord(sized_key[i]))) % 26 + 65)
        return decrypted


def task2():
    cipher = VigenereCipher("LEMON")
    encrypted = cipher.encrypt("ATTACKATDAWN")
    decrypted = cipher.decrypt(encrypted)
    print("encrypted:", encrypted)
    print("decrypted:", decrypted)
    print("-----------------")