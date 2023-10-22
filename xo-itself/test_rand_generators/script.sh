#!/bin/bash

while [ 1 -eq 1 ]; do
   [ $# -ne 0 ] && g++ $1 -g; ./a.out
done
