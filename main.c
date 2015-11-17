/**
 *  \mainpage Arquivo principal
 *  \author Elton Viana
 *  \date 2015
 */

#include <stdio.h> /** Biblioteca de funções de entrada/saída */
#include <stdlib.h> /** Biblioteca de funções padrão */
#include <string.h> /** Biblioteca de funções com strings */
#include <ctype.h>  /** Biblioteca de funções úteis */
#include "libs/img_manip.h" /** Biblioteca para o processamento da imagem */

/** \brief Função principal */
int main() {
    /**
     *  \details Função para receber o arquivo
     *  \param Nenhum
     *  \return Um inteiro 0
     */

    /** Aramazena o nome do arquivo a ser lido */
    char file[50];

    /** Limpa a tela */
    clr_screen();

    printf("Digite o nome do arquivo a ser lido (sem extensão): ");
    /** Recebe o nome do arquivo */
    scanf("%s", file);

    /** Processa a imagem */
    manip_ppm(file);

    printf("Programa finalizado.\n");

    return 0;
}
