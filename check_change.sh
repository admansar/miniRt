#!/bin/bash

while [ true ]
do
	ls -l > .old_file
	sleep 1
	ls -l > .new_file
	if [ $(diff .new_file .old_file | wc -l) -ne 0 ];
	then
		make re
	fi
done

