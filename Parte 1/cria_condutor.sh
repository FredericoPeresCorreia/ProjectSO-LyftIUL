#!/bin/bash
IFS=$'\n'
if test "$#" -ne 8; then
        echo "O número de argumentos inseridos não é o esperado (8)"
        exit
fi
i=0
if [ -e condutores.txt ];then
list=$(cat condutores.txt | cut -d ":" -f1)
        for line in $list;
        do
                        if [ "$1" = "$line" ]; then
                                echo "O condutor $2 já existe na nossa base de dados, respeitando as normas instruídas pela GDPR"
                                i=1
            fi
        done
fi
    if [ $i = 0 ]; then
            echo $1:$2:$3:$4:$5:$6:$7:$8:0:0:0 >>  condutores.txt
    fi
