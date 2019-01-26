#!/bin/bash
IFS=$'\n'
if [ -e ~/projeto/condutores.txt ] && [ -e ~/projeto/passageiros.txt ];then
#header do html da página
head=$(echo "<html>
        <head>
          <meta charset='UTF-8'>
          <title>Estatísticas LyftIUL</title>
        </head>
        <body>
         <h1>Condutores</h1>")


#Cria a lista dos condutores na página, cria um temp file para ser mais fácil de separar as linhas
echo -e "<ul>" > ~/projeto/condutores
for line in $(cat ~/projeto/condutores.txt); do
        numero=$(echo $line | cut -d  ":" -f1)
        nome=$(echo $line | cut -d  ":" -f2)
        viagens=$(echo $line | cut -d  ":" -f9)
        pontos=$(echo $line | cut -d  ":" -f10)
        if [ $viagens -eq "0" ]; then
                rating=0
        else
                rating=$(($pontos/$viagens))
        fi
        saldo=$(echo $line | cut -d  ":" -f11)
        echo -e "<li>$numero, $nome, viagens: $viagens, pontos: $pontos, rating: $rating, saldo: $saldo</li>" >> ~/projeto/condutores
done
echo -e "</ul>" >> ~/projeto/condutores


#Criar passageiros na página, demora um pouco devido ao número de operações(?)
echo -e "<h1>Passageiros</h1>\n<ul>" > ~/projeto/passageiros
for  line in $(cat ~/projeto/passageiros.txt); do
        numero=$(echo $line | cut -d ":" -f1)
        nome=$(echo $line | cut -d ":" -f2)
        echo "<li>$numero, $nome, Não divulgou a turma</li>" >> ~/projeto/passageiros
done
echo "</ul>" >> ~/projeto/passageiros


# Pega no ficheiro temp dos condutores e pega nos que têm rating abaixo de 5
echo -e "<h1>Maus Condutores</h1>\n<ul>" > ~/projeto/mausCondutores
for line in $(cat ~/projeto/condutores); do
        if [ "$line" != "<ul>" ] && [ "$line" != "</ul>" ];then
                rating=$(echo $line | cut -d ","  -f5 | cut -d ":" -f2 | cut -d " " -f2 )
                if [ $rating -lt 5 ];then
                        echo "$line" >> ~/projeto/mausCondutores
                fi
        fi
done
echo "</ul>" >> ~/projeto/mausCondutores

#faz o footer da página
footer=$(echo "</body>
        </html>")

#Cria o  ficheiro html, feio
echo $head > ~/public_html/stats.html
cat ~/projeto/condutores >> ~/public_html/stats.html
cat ~/projeto/passageiros >> ~/public_html/stats.html
cat ~/projeto/mausCondutores >> ~/public_html/stats.html
echo $footer >> ~/public_html/stats.html
rm ~/projeto/condutores ~/projeto/mausCondutores ~/projeto/passageiros

else
	echo "Não existe o ficheiro condutores.txt ou passageiros.txt"
fi
