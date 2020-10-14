#!/bin/bash

LC_TIME=C

day=`date +%u`

if [ $day != 6 ] && [ $day != 7 ]
then
	echo "Jest dzien roboczy."
else
	echo "Jest weekend"
fi

