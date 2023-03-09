from math import log10
from typing import TextIO


class NgramScore:
    def __init__(self, ngramfile: TextIO, sep: str = ' '):
        self.ngrams = {}
        for line in ngramfile:
            key, count = line.split(sep)
            self.ngrams[key] = int(count)
        self.length = 4
        self.amount = sum(self.ngrams.values())

        for key in self.ngrams.keys():
            self.ngrams[key] = log10(float(self.ngrams[key]) / self.amount)
        self.floor = log10(0.01 / self.amount)            # self.floor == -11.625737060717677 (ct01.txt)

    def score(self, text):
        score = 0
        ngrams = self.ngrams.__getitem__
        for i in range(len(text) - self.length + 1):
            if text[i:i + self.length] in self.ngrams:
                score += ngrams(text[i:i + self.length])
            else:
                score += self.floor                       # score == -4778.071993211164
        return score
