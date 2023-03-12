### Simple implementations of the Vigenere cipher (polyalphabetic substitution cipher) and the Hill cipher (polygraphic substitution cipher).

### Hill cipher.
The [Hill cipher](https://en.wikipedia.org/wiki/Hill_cipher) relies on linear algebra and modular arithmetic. Namely, multiplying a matrix by a vector, finding the inverse of a matrix modulo. And to find the inverse number modulo, the "extended Euclidean algorithm" is used.
Hill's implementation of the cipher uses **_numpy_** and its modules **_linalg_** and **_random_**.
1. The _linalg_ module provides many standard linear algebra algorithms (determinant, inverse matrix)
2. With _random_ you can generate random key matrices

### Vigenere cipher.
An implementation of the [Wiesener cipher](https://en.wikipedia.org/wiki/Vigenère_cipher) uses uncomplicated modular arithmetic for encryption and decryption.

Both cipher implementations can be found at **./src**
