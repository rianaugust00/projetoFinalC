#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#endif // HEADERS_H_INCLUDED

void iniciarQuiz();

void clearConsole();

void geografia();

void historia();

void ciencia();

void cultura();

void matematica();

void mix();

void admTema();

void verificacao();

void salvarPontuacao();

void fimDeJogo();

void records();

void admin();

typedef struct
{
#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH 256

    char nome[MAX_NAME_LENGTH];
    int pontuacao;
} Jogador;


