#!/bin/bash
rm passageiros.txt
IFS=$'\n'	
	for line in $(cat /etc/passwd)
		do
			number=$(echo $line | cut -d ':' -f1 | cut -d 'a' -f2)
			if [[ $number =~ ^[0-9]+$ ]]; then	
				name=$(echo $line | cut -d ':' -f5 | cut -d ',' -f1)
				echo $number:$name:::a$number@iscte-iul.pt: >> passageiros.txt
			fi
		done
 
