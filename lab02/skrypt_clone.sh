#!/bin/bash

if [ -v cnt ]
then
	cnt=$(($cnt+1));

	if [ $cnt -lt 500 ]
	then
		./skrypt_clone.sh;
	else
		echo "Stworzono 500 procesów!";
	fi
else
	export cnt=1;
	./skrypt_clone.sh;
fi
