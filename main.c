#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    int opc;
    setlocale(LC_ALL, "pt_BR.UTF-8");


        printf("|--------------------|\n");
        printf("|*****QUIZ GAME******|\n");
        printf("|                    |\n");
        printf("|   VAMOS COMECAR?   |\n");
        printf("|   DIGITE:          |\n");
        printf("|   1 PARA COMECAR   |\n");
        printf("|   2 PARA RECORDS   |\n");
        printf("|   3 PARA ADMIN     |\n");
        printf("|   0 PARA SAIR      |\n");
        printf("|--------------------|\n");
        scanf("%d", &opc);

        switch(opc){

    case 0:
        printf("At� logo!\n");
        exit(0);
        break;
    case 1:
        clearConsole();
        iniciarQuiz();
        break;
    case 2:
        //records();
        break;
    case 3:
        //admin();
        break;
        }

    clearConsole();

    return 0;
}
