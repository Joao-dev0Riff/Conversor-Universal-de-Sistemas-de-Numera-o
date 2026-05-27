# Conversor Universal de Sistemas de Numeração

**GCC241 – Introdução à Computação – UFLA 2026/1**

---

## Dupla

- João Gabriel Maia de Moura
- Pedro França Lopes do Prado Gomes

---

## Linguagem

C++ padrão C++11

---

## Como compilar

No terminal, dentro da pasta principal do projeto, execute:

```bash
g++ src/main.cpp src/parser.cpp src/conversor.cpp src/formatador.cpp -o conversor
```

---

## Como executar

### Linux / Mac

```bash
./conversor
```

### Windows

```bash
conversor.exe
```

ou, no PowerShell:

```powershell
.\conversor.exe
```

Ao executar o programa, a interface gráfica em HTML também pode ser aberta automaticamente no navegador.

Caso a interface não abra automaticamente, ela pode ser aberta manualmente pelo arquivo:

```text
src/index.html
```

---

## Como rodar os testes

O projeto possui **41 casos de teste automatizados**.

### Linux / Mac

```bash
g++ tests/test_conversor.cpp src/conversor.cpp -o test && ./test
```

### Windows / PowerShell

```powershell
g++ tests/test_conversor.cpp src/conversor.cpp -o test
.\test.exe
```

---

## Funcionalidades

| Requisito | Descrição | Status |
|-----------|-----------|--------|
| F1 | Decimal → Binário / Octal / Hexadecimal usando divisões sucessivas | ✅ |
| F2 | Binário / Octal / Hexadecimal → Decimal usando somatório posicional | ✅ |
| F3 | Binário ↔ Octal por agrupamento de 3 bits e Binário ↔ Hexadecimal por agrupamento de 4 bits | ✅ |
| F4 | Octal ↔ Hexadecimal usando binário como intermediário | ✅ |
| F5 | Validação de entrada, rejeitando dígitos inválidos para a base informada | ✅ |
| F6 | Conversão de números fracionários em todas as bases, com truncamento em até 16 casas | ✅ |
| F7 | Modo passo a passo, exibindo o trace completo do algoritmo | ✅ |
| F8 | Modo batch, lendo `entrada.csv` e gravando `saida.csv` | ✅ |
| F9 | Modo quiz com 5 níveis de dificuldade e pontuação | ✅ |
| F10 | Calculadora de máximos: dado `k` bits, mostra `2^k - 1` nas quatro bases | ✅ |
| Extra | Interface gráfica simples em HTML, CSS e JavaScript | ✅ |

---

## Exemplos de uso

### Conversão simples com passo a passo

```text
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

---

### Número fracionário

```text
Base de origem: 10
Numero: 10.625
Base de destino: 2

Resultado: 1010.101
```

---

### Validação de entrada inválida

```text
Base de origem: 2
Numero: 10201
Base de destino: 10
```

Nesse caso, o programa identifica que o dígito `2` não pertence à base binária e exibe uma mensagem de erro.

---

### Modo batch CSV

```text
Opcao: 2
Arquivo de entrada: entrada_exemplo.csv
Arquivo de saida: saida.csv

Pronto! 7 conversoes gravadas em "saida.csv"
```

Exemplo de formato do arquivo de entrada:

```csv
valor;base_origem;base_destino
13;10;2
1010;2;10
FF;16;10
377;8;10
10.625;10;2
```

---

### Calculadora de máximos

```text
Opcao: 4
Quantos bits? 8

Maior valor com 8 bits (2^8 - 1):

Decimal     : 255
Binario     : 11111111
Octal       : 377
Hexadecimal : FF
```

---

## Interface gráfica

Além da versão em terminal, o projeto possui uma interface gráfica simples feita em **HTML, CSS e JavaScript**.

O arquivo da interface está localizado em:

```text
src/index.html
```

A interface permite:

- Digitar o número a ser convertido;
- Escolher a base de origem;
- Escolher a base de destino;
- Realizar a conversão;
- Limpar os campos;
- Copiar o resultado;
- Visualizar informações da conversão.

A interface pode ser aberta automaticamente ao executar o programa ou manualmente pelo navegador.

---

## Estrutura do projeto

```text
src/
  main.cpp          — menu principal e modos do programa
  parser.cpp/h      — leitura e validação da entrada
  conversor.cpp/h   — algoritmos de conversão
  formatador.cpp/h  — formatação da saída
  index.html        — interface gráfica simples em HTML

tests/
  test_conversor.cpp — 41 testes automatizados

entrada_exemplo.csv  — arquivo de exemplo para o modo batch
README.md
```

---

## Observação sobre funções proibidas

As conversões entre bases foram implementadas manualmente, sem utilizar funções prontas da linguagem para conversão entre bases.

Não foram utilizadas funções como:

```text
std::stoi(s, nullptr, base)
strtol(s, NULL, base)
printf("%x")
printf("%o")
std::bitset
```

O projeto utiliza operações aritméticas, manipulação de strings e estruturas de controle para realizar as conversões.

---

## Limitações conhecidas

- A parte fracionária é truncada em no máximo 16 casas.
- Números negativos: a validação aceita o sinal `-`, mas a conversão opera sobre o valor absoluto.
- O modo batch não suporta fracionários com vírgula no CSV. Use ponto, por exemplo: `10.625`.
- A interface HTML funciona separadamente da lógica C++ compilada, usando JavaScript no navegador.

---

## Link do vídeo

[A definir]

---

## Autores

- João Gabriel Maia de Moura
- Pedro França Lopes do Prado Gomes