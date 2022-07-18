#!/bin/bash
#usage: ./test.sh path-to-hillpher.py

function textgen {
    randomtext=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $(shuf -i 1-20 -n 1) | head -1)
    echo $randomtext
}

for i in {1..100}
    do
    #генерируем ключ
    key=$(textgen)
    #генерируем плэйнтекст
    text=$(textgen)
    #шифруем плэйнтекст
    ciphertext=$(./$1 -k="$key" -t="$text")
    retVal=$?
    ciphertext=$(echo $ciphertext | sed 's/^.//;s/.$//')

    if [[ $retVal == 129 ]]; then
        #wooops, детерминант ключевой матрицы, помимо единицы, имеет другие делители с размером алфавита. Обратный элемент в кольце вычетов по модулю $len(alph) не существует!
        echo "[WARN] $i: bad key was generated ($key)"
        continue
    fi
    #дешифруем полученный шифротекст
    plaintext=$(./$1 -k="$key" -c="$ciphertext" | sed 's/^.//;s/.$//' | xargs)
    if [[ $plaintext == $text ]]; then
        echo "[OK] $i: '$text' -> '$ciphertext' -> '$plaintext' with '$key' key"
    else
        echo "[WRONG] $i: '$text' -> '$ciphertext' -> '$plaintext' with '$key' key"
    fi
done
