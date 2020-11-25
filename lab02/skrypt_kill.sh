#!/bin/bash

scriptPID=$(ps l | grep "[s]h skrypt_trap.sh" | cut -d ' ' -f 7);

kill -n $1 $scriptPID;
