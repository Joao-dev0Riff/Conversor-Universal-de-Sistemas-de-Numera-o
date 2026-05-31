#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "parser.h"
#include "conversor.h"
#include "formatador.h"

// ---------------------------------------------------------------
// Modo conversão simples (F1-F7 juntos)
// ---------------------------------------------------------------
void modoConversao() {
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        EntradaUsuario entrada = lerEntrada();
        if (!entrada.valido) {
            std::cout << "\n[ERRO] " << entrada.erro << "\n";
        } else {
            char pap;
            std::cout << "Mostrar passo a passo? (s/n): ";
            std::cin >> pap;

            Resultado res = converter(entrada.numero, entrada.baseOrigem, entrada.baseDestino);

            if (pap == 's' || pap == 'S')
                imprimirPassoAPasso(entrada.numero, entrada.baseOrigem, res, entrada.baseDestino);
            else
                imprimirResultado(entrada.numero, entrada.baseOrigem, res, entrada.baseDestino);
        }
        std::cout << "\nConverter outro numero? (s/n): ";
        std::cin >> continuar;
    }
}

// ---------------------------------------------------------------
// F8 — Modo batch: lê entrada.csv e grava saida.csv
// Formato entrada: valor;base_origem;base_destino
// Formato saida:   valor;base_origem;resultado;base_destino
// ---------------------------------------------------------------
void modoBatch() {
    std::string arquivoEntrada, arquivoSaida;
    std::cout << "Nome do arquivo de entrada (ex: entrada.csv): ";
    std::cin >> arquivoEntrada;
    std::cout << "Nome do arquivo de saida   (ex: saida.csv): ";
    std::cin >> arquivoSaida;

    std::ifstream fin(arquivoEntrada);
    if (!fin.is_open()) {
        std::cout << "[ERRO] Nao foi possivel abrir: " << arquivoEntrada << "\n";
        return;
    }

    std::ofstream fout(arquivoSaida);
    fout << "valor;base_origem;resultado;base_destino\n";

    std::string linha;
    int total = 0, erros = 0;
    while (std::getline(fin, linha)) {
        if (linha.empty() || linha[0] == '#') continue; // pula comentários/cabeçalho

        // separa por ';'
        std::istringstream ss(linha);
        std::string sValor, sOrig, sDest;
        if (!std::getline(ss, sValor, ';') ||
            !std::getline(ss, sOrig,  ';') ||
            !std::getline(ss, sDest,  ';')) {
            fout << linha << ";ERRO: linha malformada\n";
            erros++; continue;
        }

        // normaliza vírgula
        for (char& c : sValor) if (c == ',') c = '.';

        bool ok1, ok2;
        Base orig = stringParaBase(sOrig, ok1);
        Base dest = stringParaBase(sDest, ok2);

        if (!ok1 || !ok2) {
            fout << sValor << ";" << sOrig << ";ERRO: base invalida;" << sDest << "\n";
            erros++; continue;
        }
        if (!validarNumero(sValor, orig)) {
            fout << sValor << ";" << sOrig << ";ERRO: digito invalido para a base;" << sDest << "\n";
            erros++; continue;
        }

        Resultado res = converter(sValor, orig, dest);
        fout << sValor << ";" << (int)orig << ";" << res.valor << ";" << (int)dest << "\n";
        total++;
    }

    fin.close(); fout.close();
    std::cout << "\nPronto! " << total << " conversoes gravadas em \"" << arquivoSaida << "\"";
    if (erros) std::cout << "  (" << erros << " erros)";
    std::cout << "\n";
}

// ---------------------------------------------------------------
// F9 — Modo quiz
// ---------------------------------------------------------------
struct Pergunta {
    std::string valor;
    Base origem;
    Base destino;
};

static Base baseAleatoria() {
    int r = rand() % 4;
    if (r == 0) return DECIMAL;
    if (r == 1) return BINARIO;
    if (r == 2) return OCTAL;
    return HEXADECIMAL;
}

static std::string nomeBaseCurto(Base b) {
    if (b == DECIMAL)     return "decimal";
    if (b == BINARIO)     return "binario";
    if (b == OCTAL)       return "octal";
    return "hexadecimal";
}

// Retorna um número decimal aleatório dentro de uma faixa por nível
static long long numeroParaNivel(int nivel) {
    // nivel 1: 0-15  | 2: 0-255 | 3: 0-4095 | 4: 0-65535 | 5: 0-1048575
    long long maxVal = 1;
    for (int i = 0; i < nivel * 4; i++) maxVal *= 2;
    return rand() % maxVal;
}

void modoQuiz() {
    srand((unsigned)time(nullptr));
    int pontos = 0;
    int rodada = 1;
    char continuar = 's';

    std::cout << "\n=== MODO QUIZ ===\n";
    std::cout << "Niveis de dificuldade:\n";
    std::cout << "  1 - Facil      (0 a 15)\n";
    std::cout << "  2 - Medio      (0 a 255)\n";
    std::cout << "  3 - Dificil    (0 a 4095)\n";
    std::cout << "  4 - Expert     (0 a 65535)\n";
    std::cout << "  5 - Mestre     (0 a 1048575)\n";

    int nivel;
    std::cout << "Escolha o nivel (1-5): ";
    std::cin >> nivel;
    if (nivel < 1 || nivel > 5) nivel = 1;

    while (continuar == 's' || continuar == 'S') {
        // Gera pergunta aleatória
        Base orig, dest;
        do {
            orig = baseAleatoria();
            dest = baseAleatoria();
        } while (orig == dest);

        long long numDec = numeroParaNivel(nivel);

        // Converte o número para a base de origem (para mostrar na pergunta)
        std::string passos = "";
        bool trunc = false;
        std::string numOrig;
        if (orig == DECIMAL) {
            std::ostringstream ss; ss << numDec; numOrig = ss.str();
        } else {
            numOrig = decimalPara((double)numDec, orig, false, passos, trunc);
        }

        // Calcula resposta correta
        Resultado correto = converter(numOrig, orig, dest);

        std::cout << "\n[Rodada " << rodada << " | Pontos: " << pontos << " | Nivel " << nivel << "]\n";
        std::cout << "Converta  " << numOrig
                  << "  (" << nomeBaseCurto(orig) << ")"
                  << "  para  " << nomeBaseCurto(dest) << ": ";

        std::string resposta;
        std::cin >> resposta;

        // Normaliza resposta (maiúsculo)
        for (char& c : resposta) c = toupper(c);
        std::string respostaCerta = correto.valor;
        for (char& c : respostaCerta) c = toupper(c);

        if (resposta == respostaCerta) {
            pontos += nivel * 10;
            std::cout << "  Correto! (+" << nivel * 10 << " pontos)\n";
        } else {
            std::cout << "  Errado. A resposta correta era: " << correto.valor << "\n";
            std::cout << "  Quer ver o passo a passo? (s/n): ";
            char verPasso;
            std::cin >> verPasso;
            if (verPasso == 's' || verPasso == 'S')
                imprimirPassoAPasso(numOrig, orig, correto, dest);
        }

        rodada++;
        std::cout << "Continuar? (s/n): ";
        std::cin >> continuar;
    }

    std::cout << "\n=== FIM DO QUIZ ===\n";
    std::cout << "Pontuacao final: " << pontos << " pontos em " << rodada - 1 << " rodadas.\n";
}

// ---------------------------------------------------------------
// F10 — Calculadora de máximos
// ---------------------------------------------------------------
void modoMaximos() {
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        int k;
        std::cout << "\nQuantos bits? (ex: 8, 16, 32): ";
        std::cin >> k;
        if (k <= 0 || k > 64) {
            std::cout << "[ERRO] Use um valor entre 1 e 64.\n";
        } else {
            MaxBits m = calcularMaximo(k);
            imprimirMaximo(k, m);
        }
        std::cout << "Calcular outro? (s/n): ";
        std::cin >> continuar;
    }
}

// ---------------------------------------------------------------
// Menu principal
// ---------------------------------------------------------------
int main() {
    int opcao = 0;
    while (opcao != 5) {
        std::cout << "\n======================================\n";
        std::cout <<   "   CONVERSOR UNIVERSAL DE NUMERACAO   \n";
        std::cout <<   "======================================\n";
        std::cout <<   "  1. Converter numero                 \n";
        std::cout <<   "  2. Modo batch (arquivo CSV)         \n";
        std::cout <<   "  3. Modo quiz                        \n";
        std::cout <<   "  4. Calculadora de maximos (k bits)  \n";
        std::cout <<   "  5. Sair                             \n";
        std::cout <<   "=======================================\n";
        std::cout <<   "Opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: modoConversao(); break;
            case 2: modoBatch();     break;
            case 3: modoQuiz();      break;
            case 4: modoMaximos();   break;
            case 5: std::cout << "\nAte mais!\n"; break;
            default: std::cout << "Opcao invalida.\n";
        }
    }
    return 0;
}
