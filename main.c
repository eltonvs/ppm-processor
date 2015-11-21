/**
 *  \mainpage Processador de Imagens
 *  \author Elton Viana
 *  \date 2015
 *  \version 1.0
 *
 *  \file main.c
 *  \brief Arquivo principal
 *
 *  Arquivo que é compilado e executado
 *
 */

#include <stdio.h> /** Biblioteca de funções de entrada/saída */
#include <stdlib.h> /** Biblioteca de funções padrão */
#include <string.h> /** Biblioteca de funções com strings */
#include <ctype.h> /** Biblioteca de funções úteis */
#include "libs/img_manip.h" /** Biblioteca para o processamento da imagem */

int main() {
    /**
     *  \brief Função para receber o arquivo
     *  \param Nenhum
     *  \return 0
     */

    /** Armazena o nome do arquivo a ser lido */
    char file[50];
    /** Armazena a escolha do usuário de continuar ou não */
    int alive;

    /** Loop para poder executar o programa várias vezes */
    do {
        /** Limpa a tela */
        clr_screen();

        printf("Digite o nome do arquivo a ser lido (sem extensão): ");
        /** Recebe o nome do arquivo */
        scanf("%s", file);

        /** Processa a imagem */
        manip_ppm(file);

        /** Loop para receber a resposta do usuário */
        do {
            printf("\nFazer outra manipulação? [1 - Sim | 0 - Não] ");
            /** Recebe a resposta do usuário */
            scanf("%i", &alive);
        } while (alive != 0 && alive != 1);

    } while (alive);

    /** Mensagem de programa finalizado */
    printf("\nPrograma finalizado.\n");

    return 0;
}
