#ifndef FORMATADOR_H
#define FORMATADOR_H

#include "conversor.h"
#include "parser.h"

// Imprime resultado simples
void imprimirResultado(const std::string& numeroOriginal,
                       Base baseOrigem,
                       const Resultado& resultado,
                       Base baseDestino);

// Imprime resultado com passo a passo
void imprimirPassoAPasso(const std::string& numeroOriginal,
                         Base baseOrigem,
                         const Resultado& resultado,
                         Base baseDestino);

// Nome legível da base (ex: BINARIO -> "Binario (base 2)")
std::string nomeBase(Base b);

#endif
