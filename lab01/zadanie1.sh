#!/bin/bash

LC_TIME=C

day=`date | cut -d ' ' -f 1`

if [ $day == 'Wed' ]
then
	echo "wed"
else
	echo "not wed"
fi

