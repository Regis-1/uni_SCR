#!/bin/bash

LC_TIME=C

day=`date +%u`

if [ $day -lt 5 ]
then
	echo "Jest dzien roboczy."
else
	echo "Jest weekend"
fi

