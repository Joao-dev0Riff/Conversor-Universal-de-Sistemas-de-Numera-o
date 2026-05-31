#include "conversor.h"
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>

// ---------- helpers ----------

static char digitoParaChar(int d) {
    if (d < 10) return '0' + d;
    return 'A' + (d - 10);
}

static int charParaDigito(char c) {
    c = toupper(c);
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}

// Remove zeros à esquerda, mas mantém pelo menos 1 dígito antes do ponto
static std::string removerZerosEsquerda(const std::string& s) {
    int ponto = -1;
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] == '.') { ponto = i; break; }
    std::string intPart = (ponto == -1) ? s : s.substr(0, ponto);
    std::string fracPart = (ponto == -1) ? "" : s.substr(ponto);
    int i = 0;
    while (i < (int)intPart.size() - 1 && intPart[i] == '0') i++;
    return intPart.substr(i) + fracPart;
}

// Separa parte inteira e fracionária de uma string (usa '.' como separador)
static void separarPartes(const std::string& numero, std::string& inteiro, std::string& fracao) {
    int ponto = -1;
    for (int i = 0; i < (int)numero.size(); i++)
        if (numero[i] == '.') { ponto = i; break; }
    inteiro = (ponto == -1) ? numero : numero.substr(0, ponto);
    fracao  = (ponto == -1) ? ""     : numero.substr(ponto + 1);
}

// ---------------------------------------------------------------
// F2 — Qualquer base → Decimal  (somatório posicional)
// ---------------------------------------------------------------
double paraDecimal(const std::string& numero, Base base, std::string& passos) {
    std::ostringstream log;
    std::string inteiro, fracao;
    separarPartes(numero, inteiro, fracao);

    log << "Somatorio posicional (base " << (int)base << " -> 10):\n";

    double resultado = 0;
    int exp = (int)inteiro.size() - 1;
    for (char c : inteiro) {
        int d = charParaDigito(c);
        double parcela = d * pow((double)base, exp);
        log << "  " << (char)toupper(c) << " x " << (int)base << "^" << exp << " = " << parcela << "\n";
        resultado += parcela;
        exp--;
    }
    int expFrac = -1;
    for (char c : fracao) {
        int d = charParaDigito(c);
        double parcela = d * pow((double)base, expFrac);
        log << "  " << (char)toupper(c) << " x " << (int)base << "^" << expFrac << " = " << parcela << "\n";
        resultado += parcela;
        expFrac--;
    }
    log << "  Total = " << resultado << "\n";
    passos += log.str();
    return resultado;
}

// ---------------------------------------------------------------
// F1 — Decimal → qualquer base  (divisões / multiplicações sucessivas)
// ---------------------------------------------------------------
std::string decimalPara(double numero, Base base, bool temFracao, std::string& passos, bool& truncado) {
    std::ostringstream log;
    truncado = false;

    long long parteInteira = (long long)numero;
    double    parteFracao  = numero - (double)parteInteira;
    // corrige imprecisão de ponto flutuante
    if (parteFracao < 0) { parteInteira--; parteFracao += 1.0; }

    // --- Parte inteira: divisões sucessivas ---
    log << "Divisoes sucessivas (dec -> base " << (int)base << "):\n";
    std::string resultado = "";

    if (parteInteira == 0) {
        resultado = "0";
        log << "  0\n";
    } else {
        std::string digitos = "";
        long long n = parteInteira;
        while (n > 0) {
            int resto = (int)(n % base);
            log << "  " << n << " / " << (int)base
                << " = " << n / base << "  resto " << resto
                << " (" << digitoParaChar(resto) << ")\n";
            digitos += digitoParaChar(resto);
            n /= base;
        }
        for (int i = (int)digitos.size() - 1; i >= 0; i--)
            resultado += digitos[i];
        log << "  Lendo restos de baixo pra cima: " << resultado << "\n";
    }

    // --- Parte fracionária: multiplicações sucessivas ---
    if (temFracao && parteFracao > 1e-10) {
        resultado += ".";
        log << "Multiplicacoes sucessivas (fracao, base " << (int)base << "):\n";
        int casas = 0;
        double f = parteFracao;
        while (f > 1e-10 && casas < 16) {
            f *= base;
            int digito = (int)f;
            if (digito >= base) digito = base - 1;
            f -= digito;
            resultado += digitoParaChar(digito);
            log << "  x" << (int)base << " -> " << digitoParaChar(digito) << "  (resto " << f << ")\n";
            casas++;
        }
        if (f > 1e-10) {
            truncado = true;
            log << "  [TRUNCADO em 16 casas decimais]\n";
        }
    }

    passos += log.str();
    return resultado;
}

// ---------------------------------------------------------------
// F3 — Binário ↔ Octal  (grupos de 3 bits)
// ---------------------------------------------------------------
std::string binarioParaOctal(const std::string& bin, std::string& passos) {
    std::ostringstream log;
    log << "Agrupamento de 3 bits (bin -> oct):\n";

    std::string inteiro, fracao;
    separarPartes(bin, inteiro, fracao);

    while (inteiro.size() % 3 != 0) inteiro = "0" + inteiro;

    std::string resultado = "";
    for (int i = 0; i < (int)inteiro.size(); i += 3) {
        std::string g = inteiro.substr(i, 3);
        int val = (g[0]-'0')*4 + (g[1]-'0')*2 + (g[2]-'0');
        log << "  " << g << " -> " << val << "\n";
        resultado += digitoParaChar(val);
    }
    if (!fracao.empty()) {
        resultado += ".";
        while (fracao.size() % 3 != 0) fracao += "0";
        for (int i = 0; i < (int)fracao.size(); i += 3) {
            std::string g = fracao.substr(i, 3);
            int val = (g[0]-'0')*4 + (g[1]-'0')*2 + (g[2]-'0');
            log << "  " << g << " -> " << val << "\n";
            resultado += digitoParaChar(val);
        }
    }
    passos += log.str();
    return resultado;
}

std::string octalParaBinario(const std::string& oct, std::string& passos) {
    std::ostringstream log;
    log << "Cada digito octal -> 3 bits:\n";

    std::string inteiro, fracao;
    separarPartes(oct, inteiro, fracao);

    auto toBin3 = [&](char c) -> std::string {
        int v = c - '0';
        std::string b = "";
        b += (char)('0' + ((v >> 2) & 1));
        b += (char)('0' + ((v >> 1) & 1));
        b += (char)('0' + (v & 1));
        log << "  " << c << " -> " << b << "\n";
        return b;
    };

    std::string resultado = "";
    for (char c : inteiro) resultado += toBin3(c);
    if (!fracao.empty()) {
        resultado += ".";
        for (char c : fracao) resultado += toBin3(c);
    }
    passos += log.str();
    return resultado;
}

// ---------------------------------------------------------------
// F3 — Binário ↔ Hex  (grupos de 4 bits)
// ---------------------------------------------------------------
std::string binarioParaHex(const std::string& bin, std::string& passos) {
    std::ostringstream log;
    log << "Agrupamento de 4 bits (bin -> hex):\n";

    std::string inteiro, fracao;
    separarPartes(bin, inteiro, fracao);

    while (inteiro.size() % 4 != 0) inteiro = "0" + inteiro;

    std::string resultado = "";
    for (int i = 0; i < (int)inteiro.size(); i += 4) {
        std::string g = inteiro.substr(i, 4);
        int val = (g[0]-'0')*8 + (g[1]-'0')*4 + (g[2]-'0')*2 + (g[3]-'0');
        log << "  " << g << " -> " << digitoParaChar(val) << "\n";
        resultado += digitoParaChar(val);
    }
    if (!fracao.empty()) {
        resultado += ".";
        while (fracao.size() % 4 != 0) fracao += "0";
        for (int i = 0; i < (int)fracao.size(); i += 4) {
            std::string g = fracao.substr(i, 4);
            int val = (g[0]-'0')*8 + (g[1]-'0')*4 + (g[2]-'0')*2 + (g[3]-'0');
            log << "  " << g << " -> " << digitoParaChar(val) << "\n";
            resultado += digitoParaChar(val);
        }
    }
    passos += log.str();
    return resultado;
}

std::string hexParaBinario(const std::string& hex, std::string& passos) {
    std::ostringstream log;
    log << "Cada digito hex -> 4 bits:\n";

    std::string inteiro, fracao;
    separarPartes(hex, inteiro, fracao);

    auto toBin4 = [&](char c) -> std::string {
        int v = charParaDigito(c);
        std::string b = "";
        b += (char)('0' + ((v >> 3) & 1));
        b += (char)('0' + ((v >> 2) & 1));
        b += (char)('0' + ((v >> 1) & 1));
        b += (char)('0' + (v & 1));
        log << "  " << (char)toupper(c) << " -> " << b << "\n";
        return b;
    };

    std::string resultado = "";
    for (char c : inteiro) resultado += toBin4(c);
    if (!fracao.empty()) {
        resultado += ".";
        for (char c : fracao) resultado += toBin4(c);
    }
    passos += log.str();
    return resultado;
}

// ---------------------------------------------------------------
// F10 — Maior valor representável com k bits
// ---------------------------------------------------------------
MaxBits calcularMaximo(int k) {
    // 2^k - 1 usando só aritmética inteira (sem pow)
    // para k grande usamos string de 1s no binário
    std::string binStr = "";
    for (int i = 0; i < k; i++) binStr += "1";

    std::string passos = "";
    double dec = paraDecimal(binStr, BINARIO, passos);

    passos = "";
    bool trunc = false;
    std::string decStr = decimalPara(dec, DECIMAL, false, passos, trunc);
    passos = "";
    std::string octStr = decimalPara(dec, OCTAL,   false, passos, trunc);
    passos = "";
    std::string hexStr = decimalPara(dec, HEXADECIMAL, false, passos, trunc);

    MaxBits m;
    m.bin = binStr;
    m.dec = decStr;
    m.oct = octStr;
    m.hex = hexStr;
    return m;
}

// ---------------------------------------------------------------
// Função principal de conversão
// ---------------------------------------------------------------
Resultado converter(const std::string& numero, Base baseOrigem, Base baseDestino) {
    Resultado res;
    res.truncado = false;
    std::string passos = "";

    if (baseOrigem == baseDestino) {
        res.valor  = numero;
        res.passos = "Bases iguais, nenhuma conversao necessaria.\n";
        return res;
    }

    bool temFracao = (numero.find('.') != std::string::npos);
    bool trunc = false;

    // Caminhos diretos (F3 / F4) — sem passar pelo decimal
    if      (baseOrigem == BINARIO      && baseDestino == OCTAL)        res.valor = binarioParaOctal(numero, passos);
    else if (baseOrigem == OCTAL        && baseDestino == BINARIO)       res.valor = octalParaBinario(numero, passos);
    else if (baseOrigem == BINARIO      && baseDestino == HEXADECIMAL)   res.valor = binarioParaHex(numero, passos);
    else if (baseOrigem == HEXADECIMAL  && baseDestino == BINARIO)       res.valor = hexParaBinario(numero, passos);
    else if (baseOrigem == OCTAL        && baseDestino == HEXADECIMAL) {
        std::string bin = octalParaBinario(numero, passos);
        res.valor = binarioParaHex(bin, passos);
    }
    else if (baseOrigem == HEXADECIMAL  && baseDestino == OCTAL) {
        std::string bin = hexParaBinario(numero, passos);
        res.valor = binarioParaOctal(bin, passos);
    }
    else {
        double dec = paraDecimal(numero, baseOrigem, passos);
        res.valor  = decimalPara(dec, baseDestino, temFracao, passos, trunc);
        res.truncado = trunc;
    }

    res.passos = passos;
    res.valor  = removerZerosEsquerda(res.valor);
    return res;
}