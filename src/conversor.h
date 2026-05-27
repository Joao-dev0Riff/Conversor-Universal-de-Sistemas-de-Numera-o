#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <string>
#include "parser.h"

// Estrutura com o resultado e o passo a passo
struct Resultado {
    std::string valor;       // resultado final (ex: "1101")
    std::string passos;      // trace do algoritmo (para modo passo a passo)
    bool truncado;           // true se parte fracionária foi truncada
};

// Função principal: converte numero da baseOrigem para baseDestino
Resultado converter(const std::string& numero, Base baseOrigem, Base baseDestino);

// funções internas (usadas pelo converter) 

// Converte qualquer base -> decimal (como double para suportar fracionários)
double paraDecimal(const std::string& numero, Base base, std::string& passos);

// Converte decimal -> qualquer base
std::string decimalPara(double numero, Base base, bool temFracao, std::string& passos);

// Converte binário <-> octal  (agrupamento de 3 bits)  [F3]
std::string binarioParaOctal(const std::string& bin, std::string& passos);
std::string octalParaBinario(const std::string& oct, std::string& passos);

// Converte binário <-> hex    (agrupamento de 4 bits)  [F3]
std::string binarioParaHex(const std::string& bin, std::string& passos);
std::string hexParaBinario(const std::string& hex, std::string& passos);

#endif
