#ifndef PARSER_H
#define PARSER_H

#include <string>

// Bases suportadas
enum Base { DECIMAL = 10, BINARIO = 2, OCTAL = 8, HEXADECIMAL = 16 };

// Estrutura com os dados já validados, prontos pro conversor usar
struct EntradaUsuario {
    std::string numero;   // o número como string (ex: "1A3")
    Base baseOrigem;      // de qual base vem
    Base baseDestino;     // pra qual base vai
    bool valido;          // false se o usuário digitou algo errado
    std::string erro;     // mensagem de erro, se houver
};

// Lê e valida o que o usuário digitou
EntradaUsuario lerEntrada();

// Verifica se um número é válido numa base (ex: "9" é inválido em octal)
bool validarNumero(const std::string& numero, Base base);

// Converte string da base para o enum Base
Base stringParaBase(const std::string& s, bool& ok);

#endif
