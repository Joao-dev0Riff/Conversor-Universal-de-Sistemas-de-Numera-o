#ifndef PARSER_H
#define PARSER_H

#include <string>

// bases suportadas
enum Base { DECIMAL = 10, BINARIO = 2, OCTAL = 8, HEXADECIMAL = 16 };

// estrutura com os dados já validados
struct EntradaUsuario {
    std::string numero;   // o número original como string
    Base baseOrigem;      // a base original
    Base baseDestino;     // qual base vai virar
    bool valido;          // false se o usuário digitou algo errado
    std::string erro;     // mensagem de erro, se houver
};

// le e valida o que o usuário digitou
EntradaUsuario lerEntrada();

// verifica se um número é válido na base digitada ("9" é inválido em octal)
bool validarNumero(const std::string& numero, Base base);

// converter string da base para o enum Base
Base stringParaBase(const std::string& s, bool& ok);

#endif