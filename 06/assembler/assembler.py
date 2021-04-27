#!/usr/bin/python
import os, sys

def firstPass():
    root = sys.argv[1]
    infile = open(root + ".asm")
    outfile = open(root + ".tmp", "w")

    for words in infile:
        print(words)

    infile.close()
    outfile.close()

firstPass()
