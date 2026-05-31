#include "formatador.h"
#include <iostream>

std::string nomeBase(Base b) {
    switch (b) {
        case BINARIO:     return "Binario      (base  2)";
        case OCTAL:       return "Octal        (base  8)";
        case DECIMAL:     return "Decimal      (base 10)";
        case HEXADECIMAL: return "Hexadecimal  (base 16)";
        default:          return "Desconhecida";
    }
}

void imprimirResultado(const std::string& original, Base origem,
                       const Resultado& res, Base destino) {
    std::cout << "\n----------------------------------------\n";
    std::cout << "  " << original  << "  [" << nomeBase(origem)  << "]\n";
    std::cout << "           v\n";
    std::cout << "  " << res.valor << "  [" << nomeBase(destino) << "]\n";
    if (res.truncado)
        std::cout << "  (!!) Parte fracionaria truncada em 16 casas.\n";
    std::cout << "----------------------------------------\n";
}

void imprimirPassoAPasso(const std::string& original, Base origem,
                         const Resultado& res, Base destino) {
    std::cout << "\n======== PASSO A PASSO ========\n";
    std::cout << res.passos;
    std::cout << "================================\n";
    imprimirResultado(original, origem, res, destino);
}

void imprimirMaximo(int k, const MaxBits& m) {
    std::cout << "\n========================================\n";
    std::cout << "  Maior valor com " << k << " bits (2^" << k << " - 1):\n";
    std::cout << "  Decimal     : " << m.dec << "\n";
    std::cout << "  Binario     : " << m.bin << "\n";
    std::cout << "  Octal       : " << m.oct << "\n";
    std::cout << "  Hexadecimal : " << m.hex << "\n";
    std::cout << "========================================\n";
}