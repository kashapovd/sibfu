#!/bin/bash

if [ -z $1 ] || [ -z $2 ]; then
    echo "Error: \$1 and \$2 must be defined. F.e. $0 100 file"
	exit;
fi

while true;
do
	PIDS=$(ps -e -o pid h | head -n -2)
	echo "Found $(echo $PIDS | wc -w) processes"
	for P in $PIDS
	do
		UTIME=$(cat /proc/$P/stat 2>&1 | awk '{print $14}')
		if [[ ! -z $UTIME ]] && [[ $(echo "$UTIME / $(getconf CLK_TCK)" | bc) -gt $1 ]]; then
			#kill $P
			echo "$(date '+%Y/%m/%d %H:%M:%S') $P was killed\\n" >> $2
		fi
	done 
done



