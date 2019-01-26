#!/bin/bash
IFS=$'\n'
if [ -e condutores.txt ]; then
for line in $(cat condutores.txt)
        do
                nome=$(echo $line | cut -d ":" -f2)
                pontos=$(echo $line | cut -d ":" -f10)
                viagens=$(echo $line | cut -d ":" -f9)
                if [[ $viagens -eq 0 ]]; then
                        viagens=1
                fi
                rating=$((pontos/viagens))
                if [ $rating -lt 5 ]; then
                        echo Nome: $nome, tem $pontos pontos em $viagens viagens, logo, o seu rating é de $rating estrelas
                        saldo=$(echo $line | cut -d ":" -f11)
                        echo $nome:$pontos:$viagens:$rating:$saldo >> lnegra.txt
                fi
        done
if [ -e lnegra.txt ]; then
        echo Quer reportar os condutores? \(S/N\)
        read resposta
        case $resposta in
                  N) echo "OK";;
                  S) for line in $(cat lnegra.txt)
                        do
                                 nome=$(echo $line | cut -d ":" -f1)
                                 saldo=$(echo $line | cut -d ":" -f5)
                                 echo $nome, com um saldo no valor de $saldo€, recebeu um email a avisar sobre as queixas apresentadas à sua pessoa e a prepará-lo para a sua iminente expulsão
                        done;;
                  *) echo Tem que usar S ou N;;
        esac
fi
rm lnegra.txt

else echo "Não existe ficheiro condutores ou passageiros"

fi
