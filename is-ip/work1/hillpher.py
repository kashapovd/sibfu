#!/usr/bin/env python

import sys
import argparse
import string
import sympy
import math
from enum import Enum

appname = "hillpher"
appver = "1.0"

alph = (string.digits + string.ascii_letters + string.punctuation + " №®")
keyPower = 32 #max key length = 2^32 = about 4 billion

class operation(Enum):
    encode = 0
    decode = 1

def main(result):
    print("\'{}\'".format(result))
    return 0

def encode(plaintext, key):
    keyPower = int(len(key)**0.5)
    plaintext = textCompletion(plaintext, keyPower)

    ciphertext = ""
    for i in range(int(len(plaintext) / keyPower)):
        ciphertext += createStrFromMatrix(
            (createMatrixFromStr(plaintext[keyPower*i:keyPower*(i+1)], 1) 
             * createMatrixFromStr(key, keyPower))
            % len(alph)
            )

    return ciphertext

def decode(ciphertext, key):
    keyPower = int(len(key)**0.5)
    
    plaintext = ""
    for i in range(int(len(ciphertext) / keyPower)):
        plaintext += createStrFromMatrix(
            (createMatrixFromStr(ciphertext[keyPower*i:keyPower*(i+1)], 1) 
             * invMatrixMod(createMatrixFromStr(key, keyPower), len(alph)))
            % len(alph)
            )
    
    return(plaintext)

def keyCompletion(key):
    for i in range(1, keyPower):
        keyLength = len(key)
        if keyLength <= i**2:
            offset = alph.find('a')
            for j in range(offset, i**2 - keyLength + offset):
                key += alph[j]
            break
    return key

def textCompletion(text, keyPower):
    while(len(text) % keyPower):
        text += " "
    return text

def createMatrixFromStr(string, order):
    m = list(string)
    for i,l in enumerate(m):
        m[i] = int(alph.find(l))
    m = sympy.Matrix(m)
    if order != 1:
        m = m.reshape(order, order)
    else:
        m = m.T
    return m

def createStrFromMatrix(m):
    string = ""
    for x in m:
        string += alph[x]
    return string

def gcdExtended(a, b):  
    if b == 0:
        return a, 1, 0
    else:
        d, x, y = gcdExtended(b, a % b)
        return d, y, x - y * (a // b)

def multInvMod(num, mod):
    gcd,x,y = gcdExtended(num, mod)
    return (x if x > 0 else mod+x)

def invMatrixMod(m, mod):
    det = int(sympy.det(m))
    detInv = multInvMod(det, mod)
    return (m.adjugate() * detInv) % mod

def isAlphConsistOf(string):
    if string != None:
        for l in string:
            if alph.find(l) == -1:
                print("Error: symbol \'{}\' not contained in the alphabet".format(l))
                print("Allowable set of symbols: {}".format(tuple(alph)))
                sys.exit(1)

def checkInput(key, plaintext, ciphertext):
    isAlphConsistOf(plaintext)
    isAlphConsistOf(ciphertext)
    isAlphConsistOf(key)
    
    keyMatrix = createMatrixFromStr(args.key, int(len(args.key)**0.5))
    det = sympy.det(keyMatrix)
    if math.gcd(det, len(alph)) != 1:
        print("Error: bad key, choose another one [modular multiplicative inverse doesn't exist].\n"
            "The Greatest Common Divisor between determinant of key matrix({}) and alphabet length({}) must be 1".format(det, len(alph)))
        sys.exit(129)
    
if __name__ == "__main__":
   
    parser = argparse.ArgumentParser(description="Hill\'s encryptor and decryptor.")
   
    mutexgr = parser.add_mutually_exclusive_group(required=True)
    mutexgr.add_argument(
            "-t", "--text",
            help="defines the plaintext for encryption",
            dest="plaintext",
            type=str
            )
    mutexgr.add_argument(
            "-c", "--cipher",
            help="defines the ciphertext for decryption",
            dest="ciphertext",
            type=str
            )
    parser.add_argument(
            "-k", "--key",
            help="cryptor key",
            dest="key",
            type=str,
            required=True
            )
    parser.add_argument(
            "-v", "--version",
            help="output version information and exit",
            action="version",
            version="{} {}".format(appname, appver)
            )

    args = parser.parse_args()
    op = operation(args.plaintext == None)
    args.key = keyCompletion(args.key)
    checkInput(args.key, args.plaintext, args.ciphertext)
    
    if op == operation.decode:
        main(decode(args.ciphertext, args.key))
    else:
        main(encode(args.plaintext, args.key))
