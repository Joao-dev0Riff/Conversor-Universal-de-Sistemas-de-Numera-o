#include "formatador.h"
#include <iostream>
#include <string>

using namespace std;

string nomeBase(Base b) {
    switch (b) {
        case BINARIO:      return "Binario      (base 2)";
        case OCTAL:        return "Octal        (base 8)";
        case DECIMAL:      return "Decimal      (base 10)";
        case HEXADECIMAL:  return "Hexadecimal  (base 16)";
        default:           return "Desconhecida";
    }
}

void imprimirResultado(const string& numeroOriginal,
                       Base baseOrigem,
                       const Resultado& resultado,
                       Base baseDestino) {
    cout << "\n----------------------------------------\n";
    cout << "  " << numeroOriginal << "  [" << nomeBase(baseOrigem) << "]\n";
    cout << "           v\n";
    cout << "  " << resultado.valor << "  [" << nomeBase(baseDestino) << "]\n";
    if (resultado.truncado)
        cout << "  (!) Parte fracionaria truncada em 16 casas.\n";
    cout << "----------------------------------------\n";
}

void imprimirPassoAPasso(const string& numeroOriginal,
                         Base baseOrigem,
                         const Resultado& resultado,
                         Base baseDestino) {
    cout << "\n======== PASSO A PASSO ========\n";
    cout << resultado.passos;
    cout << "===============================\n";
    imprimirResultado(numeroOriginal, baseOrigem, resultado, baseDestino);
}