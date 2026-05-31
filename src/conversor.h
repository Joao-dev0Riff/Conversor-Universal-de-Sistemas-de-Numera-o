#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <string>
#include "parser.h"

// Estrutura com o resultado e o passo a passo
struct Resultado {
    std::string valor;   // resultado final (ex: "1101")
    std::string passos;  // trace do algoritmo (modo passo a passo)
    bool truncado;       // true se parte fracionária foi truncada em 16 casas
};

// Função principal: converte numero da baseOrigem para baseDestino
Resultado converter(const std::string& numero, Base baseOrigem, Base baseDestino);

// ---------- funções internas (usadas pelo converter) ----------
double      paraDecimal    (const std::string& numero, Base base, std::string& passos);
std::string decimalPara    (double numero, Base base, bool temFracao, std::string& passos, bool& truncado);
std::string binarioParaOctal(const std::string& bin, std::string& passos);
std::string octalParaBinario(const std::string& oct, std::string& passos);
std::string binarioParaHex  (const std::string& bin, std::string& passos);
std::string hexParaBinario  (const std::string& hex, std::string& passos);

// F10 — dado k bits, retorna o maior valor representável (2^k - 1) nas 4 bases
struct MaxBits { std::string dec, bin, oct, hex; };
MaxBits calcularMaximo(int k);

#endif
