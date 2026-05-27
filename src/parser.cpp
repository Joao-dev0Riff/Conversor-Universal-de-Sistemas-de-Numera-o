#include "parser.h"
#include <iostream>
#include <string>
#include <algorithm>

// Converte string digitada pelo usuário para o enum Base
Base stringParaBase(const std::string& s, bool& ok) {
    ok = true;
    if (s == "2"  || s == "binario"      || s == "bin") return BINARIO;
    if (s == "8"  || s == "octal"        || s == "oct") return OCTAL;
    if (s == "10" || s == "decimal"      || s == "dec") return DECIMAL;
    if (s == "16" || s == "hexadecimal"  || s == "hex") return HEXADECIMAL;
    ok = false;
    return DECIMAL; // valor padrão (não será usado pois ok=false)
}

// Verifica se cada dígito do número é válido na base informada
bool validarNumero(const std::string& numero, Base base) {
    // Permite número negativo
    int inicio = (numero[0] == '-') ? 1 : 0;

    // Separa parte inteira e fracionária
    bool temPonto = false;
    for (int i = inicio; i < (int)numero.size(); i++) {
        char c = toupper(numero[i]);

        // Aceita . ou , como separador decimal
        if (c == '.' || c == ',') {
            if (temPonto) return false; // dois separadores = inválido
            temPonto = true;
            continue;
        }

        // Verifica se o dígito é válido pra base
        int valor = -1;
        if (c >= '0' && c <= '9') valor = c - '0';
        else if (c >= 'A' && c <= 'F') valor = c - 'A' + 10;

        if (valor == -1 || valor >= base) return false;
    }
    return true;
}

// Lê e valida a entrada do usuário
EntradaUsuario lerEntrada() {
    EntradaUsuario entrada;
    entrada.valido = false;

    std::string sBaseOrigem, sBaseDestino;

    std::cout << "\n=== CONVERSOR DE BASES ===\n";
    std::cout << "Base de origem  (2, 8, 10, 16 / bin, oct, dec, hex): ";
    std::cin >> sBaseOrigem;

    bool ok1, ok2;
    entrada.baseOrigem = stringParaBase(sBaseOrigem, ok1);
    if (!ok1) {
        entrada.erro = "Base de origem invalida: " + sBaseOrigem;
        return entrada;
    }

    std::cout << "Numero a converter: ";
    std::cin >> entrada.numero;

    // Normaliza separador: troca , por .
    for (char& c : entrada.numero)
        if (c == ',') c = '.';

    if (!validarNumero(entrada.numero, entrada.baseOrigem)) {
        entrada.erro = "O numero \"" + entrada.numero +
                       "\" contem digitos invalidos para a base " +
                       std::to_string((int)entrada.baseOrigem) + ".";
        return entrada;
    }

    std::cout << "Base de destino (2, 8, 10, 16 / bin, oct, dec, hex): ";
    std::cin >> sBaseDestino;

    entrada.baseDestino = stringParaBase(sBaseDestino, ok2);
    if (!ok2) {
        entrada.erro = "Base de destino invalida: " + sBaseDestino;
        return entrada;
    }

    entrada.valido = true;
    return entrada;
}
