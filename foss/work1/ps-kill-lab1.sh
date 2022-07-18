#!/bin/bash

USER_TIME=$1
LOG_FILE=$2

usage() {
    echo "Usage: $0 <seconds> <file>"
    exit
}

pkill() {
	local CLK_TCK=$(getconf CLK_TCK)

	while true;
	do
		PIDS=$(ps -e -o pid h | head -n -2)
 		echo "Found $(echo $PIDS | wc -w) processes"
		for P in $PIDS
		do
			UTIME=$(cat /proc/$P/stat 2>&1 | awk '{print $14}')
			if [[ -n $UTIME ]] && [[ $(echo "$UTIME / $CLK_TCK" | bc) -gt $USER_TIME ]]; then
				#kill $P
				echo "$(date +%s) $P was killed" >> $LOG_FILE
			fi
		done
	done
}

if [ -z $1 ] || [ -z $2 ]; then
    usage
fi

pkill

