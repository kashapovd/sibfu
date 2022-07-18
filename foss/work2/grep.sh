#!/bin/bash

REGEXPR="kernel:.*(?:Freeing).*(:?memory):.[1-9]\d{2,}[1-9]"
LOGFILE=$1

if [[ -z $LOGFILE ]]; then
    journalctl | grep -P $(echo $REGEXPR)
else
    if [[ -f $LOGFILE ]]; then
	    grep -P $(echo $REGEXPR) $1
    else
	echo "file $1 doesn't exist"
    fi
fi
