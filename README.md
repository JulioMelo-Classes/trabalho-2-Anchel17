# Atividade 02 de LP1 - Concordo V3

## Para compilar

- Você deve possuir cmake com versão superior a 3.0

- Para compilar, digite em seu console:
```
mkdir build
cd build
cmake ../
cmake --build .
```

## Para executar
Com o programa compilado, você pode executar o Concordo das seguintes maneiras: 

Você pode rodar o sistema digitando um comando de cada vez e teclando ENTER
```console
cd build
./concordo
```

Ou pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:
```console
cd build
./concordo < ../data/script_comandos.txt
```

Por padrão, o Concordo vem com 2 arquivos de testes, para rodar um deles digite no seu console:
```console
./concordo < ../data/script_testes.txt
```
ou
```console
./concordo < ../data/script_comandos.txt
```

O mais indicado é testar com o arquivo "script_testes.txt", pois possui testes bem definidos de acordo com a especificação do Concordo V3.
