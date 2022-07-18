#!/bin/bash
#usage: ./test.sh path-to-rsa.py

function textgen {
    randomtext=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $(shuf -i 1-100 -n 1) | head -1)
    echo $randomtext
}

for i in {1..79}
do
    (( power=(i+10-1)/10+3 ))
    ./$1 -g -b $(echo "2^$power" | bc -l) > /dev/null 2>&1
    
    text=$(textgen)
    echo $text > plaintext.txt
    ./$1 -p plaintext.txt
    rm plaintext.txt
    ./$1 -c chiphertext.txt
    plaintext=$(cat plaintext.txt)
    
    if [[ $plaintext == $text ]]; then
        echo "[OK] RSA$(echo "2^$power" | bc -l) $i: '$text' -> '$plaintext'"
    else
        echo "[WRONG] RSA$(echo "2^$power" | bc -l) $i: '$text' -> '$plaintext'"
    fi
    unset text
    unset plaintext
done
