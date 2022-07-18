import sys
import argparse
import random
import os.path
import time

appname = "rsaasr"
appver = "0.1"

pubkeyFileName = "rsa.pub"
privFileName = "rsa.priv"
chipherTextFileName = "chiphertext.txt"
plainTextFileName = "plaintext.txt"

e = 65537
defbits=1024
first_primes_list = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 
                     53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 
                     109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 
                     173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 
                     233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 
                     293, 307, 311, 313, 317, 331, 337, 347, 349]

def gcdExtended(a, b):  
    if b == 0:
        return a, 1, 0
    else:
        d, x, y = gcdExtended(b, a % b)
        return d, y, x - y * (a // b)

def multInvMod(num, mod):
    gcd,x,y = gcdExtended(num, mod)
    if x > 0:
        return x
    else:
        return mod+x

def nBitRandom(n):
    return (random.randrange(2**(n-1)+1, 2**n-1))

def isPrime(n):
    while True: 
        prime_candidate = nBitRandom(n)  
        for divisor in first_primes_list:  
            if prime_candidate % divisor == 0 and divisor**2 <= prime_candidate: 
                break
            return prime_candidate 

def isPrimeMillerRabin(mrc):
    max_divisions_by_two = 0
    ec = mrc-1
    while ec % 2 == 0: 
        ec >>= 1
        max_divisions_by_two += 1
    #assert(2**max_divisions_by_two * ec == mrc-1)
  
    def trialComposite(round_tester): 
        if pow(round_tester, ec, mrc) == 1: 
            return False
        for i in range(max_divisions_by_two): 
            if pow(round_tester, 2**i * ec, mrc) == mrc-1: 
                return False
        return True
  
    trials_amount = 20 
    for i in range(trials_amount): 
        round_tester = random.randrange(2, mrc) 
        if trialComposite(round_tester): 
            return False
    return True

def genPrime(bits):
    while True:
        p = isPrime(bits)
        if not isPrimeMillerRabin(p): 
            continue
        return p

def genKeypair(bits):
    p = genPrime(bits)
    q = genPrime(bits)
    n = p*q
    phi = (p-1) * (q-1)
    d = multInvMod(e, phi)
    return ((e, n), (d, n))

def checkKeyExistence():
    return os.path.exists(pubkeyFileName) and os.path.exists(privFileName)

def createKeypair(bits):
    print("<<RSA-{}>>".format(bits))
    overwrite = False
    if checkKeyExistence():
        overwrite = True
    stime = time.time()
    print("Generating...")
    ((e, n), (d, n)) = genKeypair(int(bits/2))
    print("Calculations took {:.1f} seconds".format((time.time() - stime)))
    
    write((e, n), pubkeyFileName)
    write((d, n), privFileName)
    if checkKeyExistence():
        if overwrite:
            print("keys has been overwritten")
        else:
            print("keys are created")

def decode(ciphertextfile):
    ciphertext = readints(ciphertextfile)
    d, n = readints(privFileName)
    plaintext = [chr(pow(char, d, n)) for char in ciphertext]
    write(plaintext, plainTextFileName)
    
def encode(plaintextfile):
    with open(plaintextfile) as f:
        plaintext = f.read()
    e, n = readints(pubkeyFileName)
    ciphertext = [pow(ord(char), e, n) for char in plaintext]
    write(ciphertext, chipherTextFileName)

def readints(filename):
    with open(filename) as f:
        return [int(x) for x in next(f).split()]
    
def write(data, filename):
    f = open(filename, "w")
    if(type(data[0]) == int):
        for i in data:
            f.write("{} ".format(i)) 
    else:
        f.write("".join(data))
    f.close()

if __name__ == "__main__":
    
    parser = argparse.ArgumentParser()
    inputexgr = parser.add_mutually_exclusive_group()
    
    inputexgr.add_argument(
        "-p", "--plaintext",
        help="defines plaintext file for encryption",
        dest="plaintext",
        type=str
    )
    inputexgr.add_argument(
        "-c", "--chiphertext",
        help="defines chiphertext file for decryption",
        dest="chiphertext",
        type=str
    )
    parser.add_argument(
        "-g", "--genkeys",
        help="calculate only private and public keys",
        dest='command',
        action='store_const',
        const='genkeys'
    )
    parser.add_argument(
        "-b", "--bits",
        help="bits",
        dest='bits',
        action='store',
        default=0,
        type=int
    )
    parser.add_argument(
        "-v", "--version",
        help="output version information and exit",
        action="version",
        version="{} {}".format(appname, appver)
    )
    
    args = parser.parse_args()
    if args.command == "genkeys":
        if args.bits == 0:
            print("default key size is selected ({})".format(defbits))
            createKeypair(defbits)
        else:
            createKeypair(args.bits)
    else:
        if args.plaintext == None:
            decode(args.chiphertext)
        else:
            encode(args.plaintext)
