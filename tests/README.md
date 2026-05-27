# Conversor Universal de Sistemas de Numeração

## Dupla
- João Gabriel Maia de Moura
- Pedro França Lopes do Prado Gomes

## Linguagem
- C++ 

## Como compilar

g++ src/main.cpp src/parser.cpp src/conversor.cpp src/formatador.cpp -o conversor

## Como executar

conversor.exe

## Como rodar os testes (41 casos)

g++ tests/test_conversor.cpp src/conversor.cpp -o test && ./test

## Funcionalidades

| Requisito | Descrição | Status |
|-----------|-----------|--------|
| F1 | Decimal → Binário / Octal / Hex (divisões sucessivas) 
| F2 | Binário / Octal / Hex → Decimal (somatório posicional) 
| F3 | Binário ↔ Octal (3 bits) e Binário ↔ Hex (4 bits) direto 
| F4 | Octal ↔ Hex via binário como intermediário 
| F5 | Validação de entrada (dígitos inválidos para a base) 
| F6 | Números fracionários em todas as bases (trunca em 16 casas) 
| F7 | Modo passo a passo (trace completo do algoritmo)
| F8 | Modo batch: lê entrada.csv e grava saida.csv 
| F9 | Modo quiz com 5 níveis de dificuldade e pontuação 
| F10 | Calculadora de máximos: dado k bits, mostra 2^k-1 nas 4 bases 

## Exemplos de uso

### Conversão simples com passo a passo

Opcao: 1
Base de origem: 10
Numero: 13
Base de destino: 2
Mostrar passo a passo? s

======== PASSO A PASSO ========
Divisoes sucessivas (dec -> base 2):
  13 / 2 = 6  resto 1 (1)
  6 / 2 = 3   resto 0 (0)
  3 / 2 = 1   resto 1 (1)
  1 / 2 = 0   resto 1 (1)
  Lendo restos de baixo pra cima: 1101
================================
  13   [Decimal      (base 10)]
       v
  1101 [Binario      (base  2)]
```

### Número fracionário
```
Base de origem: 10
Numero: 10.625
Base de destino: 2
→ 1010.101
```

### Modo batch (CSV)
```
Opcao: 2
Arquivo de entrada: entrada_exemplo.csv
Arquivo de saida:   saida.csv
Pronto! 7 conversoes gravadas em "saida.csv"
```

### Calculadora de máximos
```
Opcao: 4
Quantos bits? 8
  Maior valor com 8 bits (2^8 - 1):
  Decimal     : 255
  Binario     : 11111111
  Octal       : 377
  Hexadecimal : FF
```

---

## Estrutura do projeto

```
src/
  main.cpp         — menu principal e modos (batch, quiz, máximos)
  parser.cpp/h     — leitura e validação da entrada
  conversor.cpp/h  — algoritmos de conversão
  formatador.cpp/h — formatação da saída
tests/
  test_conversor.cpp — 41 testes automatizados
entrada_exemplo.csv  — arquivo de exemplo para o modo batch
README.md
```

## Limitações conhecidas
- Parte fracionária truncada em no máximo 16 casas
- Números negativos: validação aceita o sinal `-`, mas conversão opera sobre o valor absoluto
- Modo batch não suporta fracionários com vírgula no CSV (use ponto)

## Interface gráfica

O projeto também possui uma interface simples em HTML localizada em:

src/index.html

## Link do vídeo
[a definir]
