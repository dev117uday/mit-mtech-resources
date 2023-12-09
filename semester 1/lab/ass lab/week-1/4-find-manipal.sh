#!/bin/bash
name=$(grep "manipal" -rH . | cut -d: -f 1)

cat $name 
printf "\n"