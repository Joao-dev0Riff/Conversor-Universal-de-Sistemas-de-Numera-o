# Conversor Universal de Sistemas de Numeração

Projeto desenvolvido em C++ para conversão entre diferentes sistemas de numeração, com suporte a modo interativo, passo a passo, modo batch, quiz, calculadora de máximos e interface gráfica simples em HTML.

---

## Dupla

- João Gabriel Maia de Moura
- Pedro França Lopes do Prado Gomes

---

## Linguagem

- C++

---

## Sistemas de numeração suportados

O conversor trabalha com as seguintes bases:

| Base | Sistema | Dígitos válidos |
|------|---------|-----------------|
| 2 | Binário | 0 e 1 |
| 8 | Octal | 0 a 7 |
| 10 | Decimal | 0 a 9 |
| 16 | Hexadecimal | 0 a 9 e A a F |

---

## Funcionalidades

| Requisito | Descrição | Status |
|-----------|-----------|--------|
| F1 | Decimal → Binário / Octal / Hexadecimal por divisões sucessivas | ✅ |
| F2 | Binário / Octal / Hexadecimal → Decimal por somatório posicional | ✅ |
| F3 | Binário ↔ Octal usando agrupamento de 3 bits e Binário ↔ Hexadecimal usando agrupamento de 4 bits | ✅ |
| F4 | Octal ↔ Hexadecimal usando binário como intermediário | ✅ |
| F5 | Validação de entrada, detectando dígitos inválidos para cada base | ✅ |
| F6 | Suporte a números fracionários em todas as bases, com truncamento em até 16 casas | ✅ |
| F7 | Modo passo a passo, mostrando o processo completo da conversão | ✅ |
| F8 | Modo batch, lendo `entrada.csv` e gravando `saida.csv` | ✅ |
| F9 | Modo quiz com 5 níveis de dificuldade e sistema de pontuação | ✅ |
| F10 | Calculadora de máximos: dado `k` bits, mostra `2^k - 1` nas quatro bases | ✅ |
| F11 | Interface gráfica simples em HTML | ✅ |

---

## Estrutura do projeto

```text
Conversor-Universal-de-Sistemas-de-Numero/
├── src/
│   ├── main.cpp
│   ├── parser.cpp
│   ├── parser.h
│   ├── conversor.cpp
│   ├── conversor.h
│   ├── formatador.cpp
│   ├── formatador.h
│   └── index.html
├── tests/
│   ├── test_conversor.cpp
│   └── entrada_exemplo.csv
├── README.md
└── conversor.exe