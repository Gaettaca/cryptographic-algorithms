from ngram_score import NgramScore
import random


def decipher(ctext: str, key: str) -> str:
    return ctext.translate(ctext.maketrans(''.join(key), 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'))


def files() -> list:
    return [f'./src/encrypted/ct{i}.txt' for i in range(1, 20)]


def make_quadragrams() -> NgramScore:
    quadgrams = open('english_quadgrams.txt', 'r')
    ngram: NgramScore = NgramScore(quadgrams)
    return ngram


ngram: NgramScore


def hill_climbing_algorithm(filename: str):
    with open(filename, 'r') as file:
        ctext = ''.join(line for line in file)

    maxkey = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
    maxscore = -99e9
    parent_score, parent_key = maxscore, maxkey[:]

    print(filename)
    output_file = './src/decrypted' + filename[15:]
    output = open(output_file, 'w')
    for i in range(10):
        random.shuffle(parent_key)
        deciphered = decipher(ctext
                              , parent_key)
        parent_score = ngram.score(ctext)
        count = 0
        while count < 1000:
            a = random.randint(0, 25)
            b = random.randint(0, 25)
            child = parent_key[:]

            child[a], child[b] = child[b], child[a]
            deciphered = decipher(ctext, child)
            score = ngram.score(deciphered)

            if score > parent_score:
                parent_score = score
                parent_key = child[:]
                count = 0
            count += 1
        if parent_score > maxscore:
            maxscore, maxkey = parent_score, parent_key[:]
            output.write("-----------------------------------------\n")
            output.write("count: " + str(i) + "\n")
            output.write("best score: " + str(maxscore) + "\n")
            output.write("best key: " + ''.join(maxkey) + "\n")
            output.write("plaintext: " + decipher(ctext, maxkey) + "\n")
    output.close()


def main():
    files_names = files()

    global ngram
    with open('./src/english_quadgrams.txt', 'r') as quadgrams:
        ngram = NgramScore(quadgrams)

    print(len(ngram.ngrams))
    for i in files_names:
        hill_climbing_algorithm(i)


if __name__ == '__main__':
    main()
