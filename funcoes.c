#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAX_LINE_LENGTH 150

//Funcao para iniciar
void iniciarQuiz()
{
    clearConsole();
    int escolha;

    printf("|---------------------|\n");
    printf("|*****QUIZ GAME*******|\n");
    printf("|                     |\n");
    printf("|   ESCOLHA UM TEMA   |\n");
    printf("| 1 GEOGRAFIA         |\n");
    printf("| 2 HISTORIA          |\n");
    printf("| 3 CIENCIAS          |\n");
    printf("| 4 CULTURA           |\n");
    printf("| 5 MATEMATICA        |\n");
    printf("| 6 MIX(TODOS)        |\n");
    printf("| 7 ADMIN TEMA        |\n");
    printf("| 0 PARA VOLTAR       |\n");
    printf("|                     |\n");
    printf("|---------------------|\n");
    scanf("%d", &escolha);

    switch (escolha)
    {

    case 0:
        return;
        break;
    case 1:
        clearConsole();
        geografia();
        break;
    case 2:
        clearConsole();
        historia();
        break;
    case 3:
        clearConsole();
        ciencia();
        break;
    case 4:
        clearConsole();
        cultura();
        break;
    case 5:
        clearConsole();
        matematica();
        break;
    case 6:
        clearConsole();
        mix();
        break;
    case 7:
        clearConsole();
        admTema();
    }


}
//Funcao para limpar a tela do console
void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
//Quiz Geografia
void geografia()
{
    FILE* file = fopen("perguntasGeo.txt", "r");

    if (file == NULL)
    {
        printf("Arquivo nao encontrado\n");
        getchar(); // Deixa a mensagem na tela
        exit(0); // Fecha o programa
    }
    verificacao(file);
}
//Quiz Historia
void historia()
{
    FILE* file = fopen("perguntasHistoria.txt", "r");

    if (file == NULL)
    {
        printf("Arquivo nao encontrado\n");
        getchar();
        exit(0);
    }
    verificacao(file);

}
//Quiz Ciencia
void ciencia()
{
    FILE* file = fopen("perguntasCiencia.txt", "r");

    if (file == NULL)
    {
        printf("Arquivo nao encontrado\n");
        getchar(); // Deixa a mensagem na tela
        exit(0); // Fecha o programa
    }
    verificacao(file);

}
//Quiz Cultura
void cultura()
{
    FILE* file = fopen("perguntasCultura.txt", "r");

    if (file == NULL)
    {
        printf("Arquivo nao encontrado\n");
        getchar();
        exit(0);
    }
    verificacao(file);

}
//Quiz Matematica
void matematica()
{
    FILE* file = fopen("perguntasMat.txt", "r");

    if (file == NULL)
    {
        printf("Arquivo nao encontrado\n");
        getchar();
        exit(0);
    }
    verificacao(file);
}
//Quiz Mix
void mix()
{
    FILE* file = fopen("perguntasMix.txt", "r");

    if (file == NULL)
    {
        printf("Arquivo nao encontrado\n");
        getchar();
        exit(0);
    }
    verificacao(file);
}
//Quiz Admin
void admTema()
{
    FILE* file = fopen("perguntasAdmin.txt", "r");

    if (file == NULL)
    {
        printf("Arquivo nao encontrado\n");
        getchar();
        exit(0);
    }
    verificacao(file);
}
//struct de jogador
typedef struct
{
#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH 256

    char nome[MAX_NAME_LENGTH];
    int pontuacao;
} Jogador;
//funcao verifiar perguntas e respostas
void verificacao(FILE* file)
{

    char perguntas[MAX_LINE_LENGTH];
    char alternativas[4][MAX_LINE_LENGTH];
    int userChoice;
    int pergunta_num = 1;
    int respostaCorreta;
    int pontuacao = 0;
    char nomeUser[50];

    while (fgets(perguntas, MAX_LINE_LENGTH, file) != NULL)
    {
        printf("Pergunta %d: %s\n", pergunta_num, perguntas);

        // L� as 4 alternativas
        for (int i = 0; i < 4; i++)
        {
            if (fgets(alternativas[i], MAX_LINE_LENGTH, file) != NULL)
            {
                printf("%d. %s", i + 1, alternativas[i]);
            }
        }

        // L� a resposta correta do arquivo exemplo: Resposta Correta: 2
        fscanf(file, "Resposta Correta: %d\n", &respostaCorreta);

        // Pausa para leitura da pergunta
        printf("Voce tem 10 segundos para ler a pergunta.\n");
        Sleep(1000);

        // Recebe a resposta do usu�rio
        printf("Digite sua resposta (1-4): ");
        scanf("%d", &userChoice);

        // Verifica se a resposta est� correta
        if (userChoice == respostaCorreta)
        {
            printf("Resposta correta!\n");
            printf("+1 ponto!\n");
            pontuacao = pontuacao + 1;
        }
        else
        {
            printf("Resposta errada. A resposta correta era: %d. %s\n", respostaCorreta, alternativas[respostaCorreta - 1]);
        }

        pergunta_num++;
        printf("-------------------------------------------------\n");
    }
    fimDeJogo(pontuacao);

    fclose(file);  // Fecha o arquivo ap�s todas as perguntas terem sido processadas
}
//funcao para salvar dados do jogador
void salvarPontuacao(Jogador *jogador)
{
    FILE *file = fopen("jogadores.txt", "r+");
    if (file == NULL)
    {
        file = fopen("jogadores.txt", "w");  // Cria o arquivo se ele não existir
    }

    char nomeArquivo[MAX_NAME_LENGTH];
    int pontuacaoArquivo;
    int encontrado = 0;
    long posicao;

    // Procura se o jogador já existe no arquivo
    while (fscanf(file, "%s %d", nomeArquivo, &pontuacaoArquivo) != EOF)
    {
        if (strcmp(jogador->nome, nomeArquivo) == 0)
        {
            // Atualiza a pontuação do jogador
            posicao = ftell(file) - (pontuacaoArquivo);
            fseek(file, posicao, SEEK_SET);
            fprintf(file, "%d\n", jogador->pontuacao);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado)
    {
        // move o ponteiro para o fim do arquivo para adicionar novo jogador
        fseek(file, 0, SEEK_END);
        fprintf(file, "%s %d\n", jogador->nome, jogador->pontuacao);
    }

    fclose(file);
}
//função principal que termina o jogo e salva a pontuação
void fimDeJogo(int pontuacao)
{

    char nomeUser[MAX_NAME_LENGTH];
    Jogador jogador;
    printf("FIM DE JOGO!\n");
    printf("Pontuacao total: %d\n", pontuacao);
    printf("Digite seu nome: ");
    scanf("%s", nomeUser);

    //prepara os dados do jogador
    strcpy(jogador.nome, nomeUser);
    jogador.pontuacao = pontuacao;

    //salva a pontuação do jogador no arquivo
    salvarPontuacao(&jogador);

    //retorna para a home
    iniciarQuiz();
}
//Records
void records()
{

    FILE* file = fopen("jogadores.txt", "r");
    if (file == NULL)
    {
        printf("Nenhum recorde encontrado.\n");
        return;
    }

    printf("|----------------------|\n");
    printf("|       QUIZ GAME      |\n");
    printf("|                      |\n");
    printf("|        RECORDS       |\n");
    printf("|                      |\n");
    printf("| NOME       PONTOS    |\n");
    printf("|----------------------|\n");

    Jogador jogador;
    while (fscanf(file, "%s %d", jogador.nome, &jogador.pontuacao) != EOF)
    {
        printf("| %-10s  %-8d |\n", jogador.nome, jogador.pontuacao);
    }

    printf("|----------------------|\n");
    fclose(file);

    printf("Pressione qualquer tecla para voltar ao menu.\n");
    getchar(); // aguarda o usuário pressionar uma tecla
    getchar();
}
//Admin
void admin()
{
    FILE *file;
    int perguntas, i;

    //abre o arquivo em modo de escrita
    file = fopen("perguntasAdmin.txt", "a");
    if (file == NULL)
    {
        file = fopen("perguntasAdmin.txt", "w");
    }

    printf("Para começarmos, digite quantas perguntas deseja fazer: \n");
    scanf("%d", &perguntas);

    //perguntas
    for (i = 0; i < perguntas; i++)
    {
        char *pergunta = (char *)malloc(256 * sizeof(char));
        char *alternativa1 = (char *)malloc(256 * sizeof(char));
        char *alternativa2 = (char *)malloc(256 * sizeof(char));
        char *alternativa3 = (char *)malloc(256 * sizeof(char));
        char *alternativa4 = (char *)malloc(256 * sizeof(char));
        int respostaCorreta;

        if (pergunta == NULL || alternativa1 == NULL || alternativa2 == NULL || alternativa3 == NULL || alternativa4 == NULL)
        {
            printf("Erro ao alocar memória\n");
            exit(1);
        }

        // Coletando a pergunta e alternativas
        printf("Digite a pergunta %d: \n", i + 1);
        getchar();
        fgets(pergunta, 256, stdin);

        printf("Digite a alternativa 1: \n");
        fgets(alternativa1, 256, stdin);

        printf("Digite a alternativa 2: \n");
        fgets(alternativa2, 256, stdin);

        printf("Digite a alternativa 3: \n");
        fgets(alternativa3, 256, stdin);

        printf("Digite a alternativa 4: \n");
        fgets(alternativa4, 256, stdin);

        printf("Digite o número da resposta correta (1-4): \n");
        scanf("%d", &respostaCorreta);

        if (respostaCorreta > 4 || respostaCorreta < 1)
        {
            printf("O número da resposta correta deve estar entre 1 e 4. Tente novamente!\n");
            i--;
        }
        else
        {
            //salva o arquivo
            fprintf(file, "%s", pergunta);
            fprintf(file, "%s", alternativa1);
            fprintf(file, "%s", alternativa2);
            fprintf(file, "%s", alternativa3);
            fprintf(file, "%s", alternativa4);
            fprintf(file, "Resposta Correta: %d\n", respostaCorreta);
        }

        //liberar memória
        free(pergunta);
        free(alternativa1);
        free(alternativa2);
        free(alternativa3);
        free(alternativa4);
    }

    fclose(file);
    printf("Perguntas salvas com sucesso!\n");
    printf("Voltando ao menu principal!\n");
    sleep(3);
    return;
}
