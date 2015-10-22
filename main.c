#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libs/img_manip.h"

int main() {
    char file[50];

    //Recebe o nome do arquivo
    printf("Digite o nome do arquivo a ser lido (sem extensao): ");
    scanf("%s", file);

    //Lê a imagem
    manip_ppm(file);

    printf("\nPrograma finalizado.\n");

    return 0;
}
