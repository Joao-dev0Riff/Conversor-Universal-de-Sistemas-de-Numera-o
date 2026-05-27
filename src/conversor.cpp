#include "conversor.h"
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

// Mapa de dígito (0-15) para caractere
static char digitoParaChar(int d) {
    if (d < 10) return '0' + d;
    return 'A' + (d - 10); // 10->A, 11->B, ..., 15->F
}

// Mapa de caractere para dígito (0-15)
static int charParaDigito(char c) {
    c = toupper(c);
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10; // A->10, B->11, ..., F->15
}

// F2 — Qualquer base → Decimal (somatório posicional)
// Ex: "1A3" hex → 1*256 + 10*16 + 3 = 419
double paraDecimal(const string& numero, Base base, string& passos) {
    ostringstream log;

    // Separa parte inteira e fracionária
    int pontoPosicao = -1;
    for (int i = 0; i < (int)numero.size(); i++)
        if (numero[i] == '.') { pontoPosicao = i; break; }

    string parteInteira  = (pontoPosicao == -1) ? numero : numero.substr(0, pontoPosicao);
    string parteFracao   = (pontoPosicao == -1) ? ""     : numero.substr(pontoPosicao + 1);

    log << "Somatorio posicional (base " << (int)base << " -> 10):\n";

    // Parte inteira: percorre da esquerda pra direita
    double resultado = 0;
    int expoente = (int)parteInteira.size() - 1;
    for (char c : parteInteira) {
        int d = charParaDigito(c);
        double parcela = d * pow((double)base, expoente);
        log << "  " << c << " x " << (int)base << "^" << expoente << " = " << parcela << "\n";
        resultado += parcela;
        expoente--;
    }

    // Parte fracionária: expoente negativo
    int expFrac = -1;
    for (char c : parteFracao) {
        int d = charParaDigito(c);
        double parcela = d * pow((double)base, expFrac);
        log << "  " << c << " x " << (int)base << "^" << expFrac << " = " << parcela << "\n";
        resultado += parcela;
        expFrac--;
    }

    log << "  Total = " << resultado << "\n";
    passos += log.str();
    return resultado;
}

// F1 — Decimal → qualquer base (divisões sucessivas)
// Ex: 13 -> binário: 13/2=6r1, 6/2=3r0, 3/2=1r1, 1/2=0r1 → lê restos de baixo pra cima: 1101
string decimalPara(double numero, Base base, bool temFracao, string& passos) {
    ostringstream log;
    string resultado = "";

    long long parteInteira = (long long)numero;
    double parteFracao     = numero - parteInteira;

    //Parte inteira: divisões sucessivas
    log << "Divisoes sucessivas (10 -> base " << (int)base << "):\n";

    if (parteInteira == 0) {
        resultado = "0";
    } else {
        string digitos = "";
        long long n = parteInteira;
        while (n > 0) {
            int resto = n % base;
            log << "  " << n << " / " << (int)base
                << " = " << n / base << "  resto " << resto
                << " (" << digitoParaChar(resto) << ")\n";
            digitos += digitoParaChar(resto);
            n /= base;
        }
        // Inverte os restos (lê de baixo pra cima)
        for (int i = (int)digitos.size() - 1; i >= 0; i--)
            resultado += digitos[i];
        log << "  Lendo restos de baixo pra cima: " << resultado << "\n";
    }

    // Parte fracionária: multiplicações sucessivas 
    if (temFracao && parteFracao > 0) {
        resultado += ".";
        log << "Multiplicacoes sucessivas (fracao):\n";
        int casas = 0;
        bool truncou = false;
        while (parteFracao > 0 && casas < 16) {
            parteFracao *= base;
            int digito = (int)parteFracao;
            parteFracao -= digito;
            resultado += digitoParaChar(digito);
            log << "  " << parteFracao + digito << " x " << (int)base
                << " = " << digitoParaChar(digito) << " (parte int.) + " << parteFracao << "\n";
            casas++;
        }
        if (parteFracao > 0) {
            truncou = true;
            log << "  [TRUNCADO em 16 casas]\n";
        }
    }

    passos += log.str();
    return resultado;
}

// F3 — Binário → Octal (grupos de 3 bits)
string binarioParaOctal(const string& bin, string& passos) {
    ostringstream log;
    log << "Agrupamento de 3 bits (bin -> oct):\n";

    // Separa inteiro e fracionário
    int ponto = -1;
    for (int i = 0; i < (int)bin.size(); i++)
        if (bin[i] == '.') { ponto = i; break; }

    string inteiro = (ponto == -1) ? bin : bin.substr(0, ponto);
    string fracao  = (ponto == -1) ? ""  : bin.substr(ponto + 1);

    // Completa à esquerda da parte inteira até múltiplo de 3
    while (inteiro.size() % 3 != 0) inteiro = "0" + inteiro;

    string resultado = "";
    for (int i = 0; i < (int)inteiro.size(); i += 3) {
        string grupo = inteiro.substr(i, 3);
        int val = (grupo[0]-'0')*4 + (grupo[1]-'0')*2 + (grupo[2]-'0');
        log << "  " << grupo << " -> " << val << "\n";
        resultado += digitoParaChar(val);
    }

    // Parte fracionária
    if (!fracao.empty()) {
        resultado += ".";
        while (fracao.size() % 3 != 0) fracao += "0"; // completa à direita
        for (int i = 0; i < (int)fracao.size(); i += 3) {
            string grupo = fracao.substr(i, 3);
            int val = (grupo[0]-'0')*4 + (grupo[1]-'0')*2 + (grupo[2]-'0');
            log << "  " << grupo << " -> " << val << "\n";
            resultado += digitoParaChar(val);
        }
    }

    passos += log.str();
    return resultado;
}

// F3 — Octal → Binário
string octalParaBinario(const string& oct, string& passos) {
    ostringstream log;
    log << "Cada digito octal -> 3 bits:\n";

    int ponto = -1;
    for (int i = 0; i < (int)oct.size(); i++)
        if (oct[i] == '.') { ponto = i; break; }

    auto digitoOctParaBin = [&](char c) -> string {
        int v = c - '0';
        string b = "";
        b += (char)('0' + ((v >> 2) & 1));
        b += (char)('0' + ((v >> 1) & 1));
        b += (char)('0' + (v & 1));
        log << "  " << c << " -> " << b << "\n";
        return b;
    };

    string resultado = "";
    string inteiro = (ponto == -1) ? oct : oct.substr(0, ponto);
    string fracao  = (ponto == -1) ? ""  : oct.substr(ponto + 1);

    for (char c : inteiro) resultado += digitoOctParaBin(c);
    if (!fracao.empty()) {
        resultado += ".";
        for (char c : fracao) resultado += digitoOctParaBin(c);
    }

    passos += log.str();
    return resultado;
}

// F3 — Binário → Hex (grupos de 4 bits)
string binarioParaHex(const string& bin, string& passos) {
    ostringstream log;
    log << "Agrupamento de 4 bits (bin -> hex):\n";

    int ponto = -1;
    for (int i = 0; i < (int)bin.size(); i++)
        if (bin[i] == '.') { ponto = i; break; }

    string inteiro = (ponto == -1) ? bin : bin.substr(0, ponto);
    string fracao  = (ponto == -1) ? ""  : bin.substr(ponto + 1);

    while (inteiro.size() % 4 != 0) inteiro = "0" + inteiro;

    string resultado = "";
    for (int i = 0; i < (int)inteiro.size(); i += 4) {
        string grupo = inteiro.substr(i, 4);
        int val = (grupo[0]-'0')*8 + (grupo[1]-'0')*4 + (grupo[2]-'0')*2 + (grupo[3]-'0');
        log << "  " << grupo << " -> " << digitoParaChar(val) << "\n";
        resultado += digitoParaChar(val);
    }

    if (!fracao.empty()) {
        resultado += ".";
        while (fracao.size() % 4 != 0) fracao += "0";
        for (int i = 0; i < (int)fracao.size(); i += 4) {
            string grupo = fracao.substr(i, 4);
            int val = (grupo[0]-'0')*8 + (grupo[1]-'0')*4 + (grupo[2]-'0')*2 + (grupo[3]-'0');
            log << "  " << grupo << " -> " << digitoParaChar(val) << "\n";
            resultado += digitoParaChar(val);
        }
    }

    passos += log.str();
    return resultado;
}

// F3 — Hex → Binário
string hexParaBinario(const string& hex, string& passos) {
    ostringstream log;
    log << "Cada digito hex -> 4 bits:\n";

    int ponto = -1;
    for (int i = 0; i < (int)hex.size(); i++)
        if (hex[i] == '.') { ponto = i; break; }

    auto digitoHexParaBin = [&](char c) -> string {
        int v = charParaDigito(c);
        string b = "";
        b += (char)('0' + ((v >> 3) & 1));
        b += (char)('0' + ((v >> 2) & 1));
        b += (char)('0' + ((v >> 1) & 1));
        b += (char)('0' + (v & 1));
        log << "  " << (char)toupper(c) << " -> " << b << "\n";
        return b;
    };

    string resultado = "";
    string inteiro = (ponto == -1) ? hex : hex.substr(0, ponto);
    string fracao  = (ponto == -1) ? ""  : hex.substr(ponto + 1);

    for (char c : inteiro) resultado += digitoHexParaBin(c);
    if (!fracao.empty()) {
        resultado += ".";
        for (char c : fracao) resultado += digitoHexParaBin(c);
    }

    passos += log.str();
    return resultado;
}

// Função principal de conversão — decide o caminho certo
Resultado converter(const string& numero, Base baseOrigem, Base baseDestino) {
    Resultado res;
    res.truncado = false;
    string passos = "";

    // Mesma base: sem conversão necessária
    if (baseOrigem == baseDestino) {
        res.valor = numero;
        res.passos = "Bases iguais, nenhuma conversao necessaria.\n";
        return res;
    }

    bool temFracao = (numero.find('.') != string::npos);

    // Caminhos diretos (sem passar pelo decimal) — F3 e F4
    if (baseOrigem == BINARIO && baseDestino == OCTAL)
        res.valor = binarioParaOctal(numero, passos);
    else if (baseOrigem == OCTAL && baseDestino == BINARIO)
        res.valor = octalParaBinario(numero, passos);
    else if (baseOrigem == BINARIO && baseDestino == HEXADECIMAL)
        res.valor = binarioParaHex(numero, passos);
    else if (baseOrigem == HEXADECIMAL && baseDestino == BINARIO)
        res.valor = hexParaBinario(numero, passos);
    // Octal <-> Hex usa binário como ponte — F4
    else if (baseOrigem == OCTAL && baseDestino == HEXADECIMAL) {
        string bin = octalParaBinario(numero, passos);
        res.valor = binarioParaHex(bin, passos);
    }
    else if (baseOrigem == HEXADECIMAL && baseDestino == OCTAL) {
        string bin = hexParaBinario(numero, passos);
        res.valor = binarioParaOctal(bin, passos);
    }
    // Qualquer outra conversão: passa pelo decimal
    else {
        double dec = paraDecimal(numero, baseOrigem, passos);
        res.valor = decimalPara(dec, baseDestino, temFracao, passos);
    }

    res.passos = passos;

    // Remove zeros à esquerda da parte inteira (ex: "0FF" -> "FF")
    int ponto = res.valor.find('.');
    string intPart = (ponto == string::npos) ? res.valor : res.valor.substr(0, ponto);
    string fracPart = (ponto == string::npos) ? "" : res.valor.substr(ponto);
    int i = 0;
    while (i < (int)intPart.size() - 1 && intPart[i] == '0') i++;
    res.valor = intPart.substr(i) + fracPart;

    return res;
}