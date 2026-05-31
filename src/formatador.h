#ifndef FORMATADOR_H
#define FORMATADOR_H

#include "conversor.h"
#include "parser.h"

void imprimirResultado (const std::string& original, Base origem, const Resultado& res, Base destino);
void imprimirPassoAPasso (const std::string& original, Base origem, const Resultado& res, Base destino);
void imprimirMaximo (int k, const MaxBits& m);
std::string nomeBase (Base b);

#endif