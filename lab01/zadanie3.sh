#!/bin/bash

$wynik=`find . -name "$1" -mtime "-$2"`

#tworzenie archiwum tar
