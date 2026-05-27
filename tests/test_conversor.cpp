#include <iostream>
#include <string>
#include "../src/conversor.h"

using namespace std;

int passed = 0;
int failed = 0;

void check(const string& descricao,
           const string& numero, Base origem, Base destino,
           const string& esperado) {
    Resultado r = converter(numero, origem, destino);
    if (r.valor == esperado) {
        cout << "[OK] " << descricao << "\n";
        passed++;
    } else {
        cout << "[FALHOU] " << descricao << "\n";
        cout << "        Esperado: " << esperado << "\n";
        cout << "        Obtido:   " << r.valor << "\n";
        failed++;
    }
}

int main() {
    cout << "=== TESTES DO CONVERSOR ===\n\n";

    // F1 — Decimal -> outras bases
    check("13 dec -> bin",       "13",  DECIMAL, BINARIO,     "1101");
    check("255 dec -> bin",      "255", DECIMAL, BINARIO,     "11111111");
    check("8 dec -> bin",        "8",   DECIMAL, BINARIO,     "1000");
    check("0 dec -> bin",        "0",   DECIMAL, BINARIO,     "0");
    check("255 dec -> hex",      "255", DECIMAL, HEXADECIMAL, "FF");
    check("8 dec -> oct",        "8",   DECIMAL, OCTAL,       "10");
    check("255 dec -> oct",      "255", DECIMAL, OCTAL,       "377");

    // F2 — Outras bases -> Decimal
    check("1101 bin -> dec",     "1101",  BINARIO,     DECIMAL, "13");
    check("FF hex -> dec",       "FF",    HEXADECIMAL, DECIMAL, "255");
    check("10 oct -> dec",       "10",    OCTAL,       DECIMAL, "8");
    check("377 oct -> dec",      "377",   OCTAL,       DECIMAL, "255");
    check("1A hex -> dec",       "1A",    HEXADECIMAL, DECIMAL, "26");

    // F3 — Binário <-> Octal (agrupamento)
    check("1101 bin -> oct",     "1101",  BINARIO, OCTAL,   "15");
    check("15 oct -> bin",       "15",    OCTAL,   BINARIO, "1101");
    check("11111111 bin -> oct", "11111111", BINARIO, OCTAL, "377");

    // F3 — Binário <-> Hex (agrupamento)
    check("11111111 bin -> hex", "11111111", BINARIO,     HEXADECIMAL, "FF");
    check("FF hex -> bin",       "FF",       HEXADECIMAL, BINARIO,     "11111111");
    check("1A hex -> bin",       "1A",       HEXADECIMAL, BINARIO,     "11010");

    // F4 — Octal <-> Hex (via binário)
    check("377 oct -> hex",      "377", OCTAL,       HEXADECIMAL, "FF");
    check("FF hex -> oct",       "FF",  HEXADECIMAL, OCTAL,       "377");

    // Mesma base
    check("42 dec -> dec",       "42",  DECIMAL, DECIMAL, "42");

    cout << "\n=== RESULTADO: " << passed << " ok, " << failed << " falhou ===\n";
    return failed > 0 ? 1 : 0;
}