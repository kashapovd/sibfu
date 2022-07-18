#!/bin/bash

BRAND=('CISCO' 'MIKROTIK' 'SISTEMATICS' 'TP-LINK' 'DLINK')
CATEGORY=('Switch' 'Modem' 'Router' 'AP')
UNIT="item"

randomNum() {
    echo $(shuf -i $1-$2 -n 1)
}

if [[ -f $1 ]]; then
    rm $1
fi
echo -e "ID\tAMOUNT\tCOST\tUNIT\tBRAND\tCATEGORY" > $1
for i in $(seq 1 $2); 
do
    echo -e "$i\t$(randomNum 10 1000)\t$(randomNum 100 100000)\t$UNIT\t${BRAND[$(randomNum 0 4)]}\t${CATEGORY[$(randomNum 0 3)]}" >> $1
done

