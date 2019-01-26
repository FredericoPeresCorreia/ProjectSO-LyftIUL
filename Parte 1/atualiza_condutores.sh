#!/bin/bash
if [ -e viagens.txt ] && [ -e condutores.txt ]; then
	echo "Atualizando ficheiros"
	for line in $(cat viagens.txt);
		do
			numCondutor=$(echo $line | cut -d ":" -f2)
			linhaAlterar=$(cat condutores.txt | grep $numCondutor | cut -d ":" -f9-11)
			viagens=$(($(echo $linhaAlterar | cut -d ":" -f1)+1))
			pontos=$(($(echo $linhaAlterar | cut -d ":" -f2) + $(echo $line | cut -d ":" -f4))) 
			S1=$(echo $linhaAlterar | cut -d ":" -f3)
			S2=$(echo $line | cut -d ":" -f5)
			saldo=$(echo $S1 $S2 | awk '{ print $1 + $2}')
			linhaManter=$(cat condutores.txt | grep $numCondutor | cut -d ":" -f1-8)
			linhaSubstituir=$viagens:$pontos:$saldo
			line="$linhaManter:$linhaSubstituir"
			sed -i "/$numCondutor/c\\$line" condutores.txt
	done
	rm viagens.txt
else
	echo "Não existe ficheiro viagens para atualizar os condutores"  
fi
 
