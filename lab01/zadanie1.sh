#!/bin/bash

LC_TIME=C

day=`date | cut -d ' ' -f 1`

if [ $day != 'Sat' ] && [ $day != 'Sun' ]
then
	echo "weekday"
else
	echo "weekend"
fi

