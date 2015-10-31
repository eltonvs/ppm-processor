#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "libs/img_manip.h"

int main() {
    char file[50];

    clr_screen();

    //Recebe o nome do arquivo
    printf("Digite o nome do arquivo a ser lido (sem extensao): ");
    scanf("%s", file);

    //Lê a imagem
    manip_ppm(file);

    printf("Programa finalizado.\n");

    return 0;
}
