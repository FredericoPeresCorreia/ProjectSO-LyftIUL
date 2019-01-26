#!/bin/bash
IFS=$'\n'
echo "Escolha uma opcao:"
echo "1. Cria condutor"
echo "2. Cria passageiros"
echo "3. Lista negra"
echo "4. Atualiza condutores"
echo "5. Stats"
echo "6. Sair"
option=0
while [ "$option" != "6" ]; do
    read -p "Qual programa quer correr? :" option
    case $option in
        1)read -p "Introduza o Número do condutor: " numero
          read -p "Introduza o nome do condutor: " nome
          read -p "Introduza a turma do condutor: " turma
          read -p "Introduza o contacto do condutor: " contacto
          read -p "Introduza o email do condutor: " email
          read -p "Introduza o tipo de Veículo do condutor: " tipoDeVeiculo
          read -p "Introduza a marca do veículo do condutor: " marca
          read -p "Introduza a matrícula do condutor: " matricula
          ./cria_condutor.sh "$numero" "$nome" "$turma" "$contacto" "$email" "$tipoDeVeiculo" "$marca" "$matricula";;
        2) ./cria_passageiros.sh;;
        3) ./lista_negra.sh;;
        4) ./atualiza_condutores.sh;;
        5) ./stats.sh;;
        6) echo "Ok, sessão acabada.";;
        *) echo "Opção impossível use entre 1-6";;
    esac
done
