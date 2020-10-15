#!/bin/bash

find . -name "$1" -mtime "-$2" -exec tar -rvf "$3" {} \;
