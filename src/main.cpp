#include <iostream>
#include <string>
#include <cstdlib>

#include "parser.h"
#include "conversor.h"
#include "formatador.h"

void abrirInterfaceWeb() {
#ifdef _WIN32
    system("powershell -NoProfile -Command \"Start-Process '.\\src\\index.html'\"");
#elif __APPLE__
    system("open \"src/index.html\"");
#else
    system("xdg-open \"src/index.html\"");
#endif
}

int main() {
    abrirInterfaceWeb();

    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        EntradaUsuario entrada = lerEntrada();

        if (!entrada.valido) {
            std::cout << "\n[ERRO] " << entrada.erro << "\n";
        } else {
            char passoAPasso;

            std::cout << "Mostrar passo a passo? (s/n): ";
            std::cin >> passoAPasso;

            Resultado resultado = converter(
                entrada.numero,
                entrada.baseOrigem,
                entrada.baseDestino
            );

            if (passoAPasso == 's' || passoAPasso == 'S') {
                imprimirPassoAPasso(
                    entrada.numero,
                    entrada.baseOrigem,
                    resultado,
                    entrada.baseDestino
                );
            } else {
                imprimirResultado(
                    entrada.numero,
                    entrada.baseOrigem,
                    resultado,
                    entrada.baseDestino
                );
            }
        }

        std::cout << "\nConverter outro numero? (s/n): ";
        std::cin >> continuar;
    }

    std::cout << "\nAte mais!\n";

    return 0;
}