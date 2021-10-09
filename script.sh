#!/bin/bash

i="0"
read end

for ((i;i<=end;i++)); do
echo ./nachos -A 1 -rs $i
./nachos -A 1 -rs $i
done
