#!/bin/bash
IFS=$'\n'
if [ -e condutores.txt ] && [ -e passageiros.txt ]; then
nCondutores=$(cat condutores.txt | wc -l)
nPassageiros=$(cat passageiros.txt | wc -l)
echo "O sistema tem $nCondutores condutores e $nPassageiros passageiros"
saldoTotal=0
list=$(cat condutores.txt | cut -d ":" -f11)
for line in $list
     do
        saldoTotal=$(($saldoTotal + $line))
    done
echo "$saldoTotal é o valor total do saldo dos condutores"
topFive=$(cat condutores.txt | sed 's/:/ /g'| sort -k11 -n -r | head -5)
echo "Os melhores condutores são:"
for line in $topFive
    do    
	echo " $(echo $line | cut -d " " -f2,3) com  $(echo $line | cut -d " " -f11)  pontos"
    done
for line in $(cat condutores.txt)
    do
        nome=$(echo $line | cut -d ":" -f2)
        pontos=$(echo $line | cut -d ":" -f10)
        viagens=$(echo $line | cut -d ":" -f9)
        if [viagens -eq 0 ]; then 
		rating=0	
		else
		rating=$((pontos/viagens))
        fi
		echo "$rating $nome" >> rating.txt
    done

topThree=$(cat rating.txt |sort -n -r |head -3)

echo "Os condutores com maior rating são:"
for line in $topThree
    do
	    nome=$(echo $line | cut -d " " -f2,3)
		pontos=$(echo $line | cut -d " " -f1)   
		echo " $nome com um rating de $pontos"
    done
rm rating.txt
lei=0
eti=0
ige=0
for line in $(cat condutores.txt)
    do
        curso=$(echo $line | cut -d ":" -f3)
        case $curso in
            EI*) lei=$((lei + 1));;
            ET*) eti=$((eti + 1));;
            I*) ige=$((ige + 1));;
        esac
    done
echo " IGE: $ige, ETI: $eti, LEI: $lei"

else echo "Não existe o ficheiro passageiros ou condutores"
fi
