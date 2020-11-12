#!/bin/sh

trap 'echo "Zadzialanie funkcji trap!"' $( seq 1 15 );

for i in $( seq 0 119 )
do
	echo komunikat $i;
	sleep 1;
done
