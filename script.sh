#!/bin/bash

i="0"
echo "Enter number of loops: "
read end

for ((i;i<=end;i++)); do
echo nachos -tt 5 -rs $i
nachos -tt 5 -rs $i
done
