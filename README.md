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

- Você pode rodar o sistema digitando um comando de cada vez e teclando ENTER
```console
cd build
./concordo
```

- pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:
```console
cd build
./concordo < ../data/script_comandos.txt
```

- Por padrão, o Concordo vem com 2 arquivos de testes, para rodar um deles digite no seu console:
```console
./concordo < ../data/script_testes.txt
```
ou
```console
./concordo < ../data/script_comandos.txt
```

O mais indicado é testar com o arquivo "script_testes.txt", pois possui testes bem definidos de acordo com a especificação do Concordo V3.

# Avaliação
## Funcionalidades
- A1.2 ok
- A1.3 ok
- A1.4 ok
- A2.1 ok
- A2.2 ok
- A2.3 ok
- A2.4 ok
- A2.5 ok
- A2.6 ok
- A2.7 ok
- A2.8 ok
- A2.9 ok
- B1.1 ok
- B1.2 ok
- B1.3 ok
- B1.4 ok
- B1.5 ok
- B2.1 ok
- B2.2 ok

## Classes
- Servidor ok
- Canal ok
- Mensagem ok

## Boas Práticas
- Documentação ok
- Testes 50%
    A ideia aqui era que você escrevesse arquivos de entrada e documentasse os testes no readme
- Organização 75%
    Removi 25% pela forma como os includes foi usada.

## Observações
    Acho que o trabalho ficou bem completo, a parte das coisas que já conversamos na entrevista, tem o problema dos includes usando caminhos relativos. Como te falei
você não precisa fazer isso e é até problemático em certos casos.

    Vi também uns "ponteiros por referencia", lembre que ponteiros sempre são referencias logo você, usualmente, não precisa fazer `void func(tipo &*paramentro)`.