#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libs/img_manip.h"

/*
 * Bibliotecas utilizadas:
 *  - stdio.h:
 *     - Funções de input/output
 *     - Funções de leitura/escrita de arquivos
 *  - stdlib.h:
 *     - Funções do systema, para a função clr_screen()
 *  - string.h:
 *     - strcmp() para comparação de strings (escolhas do menu)
 *     - strcat() para concatenar strings (nome do arquivo de saída)
 *     - strcpy() para copiar strings ("backup" do nome do arquivo original)
 *  - ctype.h:
 *     - tolower() para prevenir letras maiúsculas na interação com o usuário
 *  - img_manip.h:
 *     - Biblioteca com todas as funcionalidades do processamento de imagem
 */

int main() {
    /*
     * Variáveis utilizadas
     *  - file:
     *     - Tipo: Vetor de char - String
     *     - Função: Armazenar o nome do arquivo a ser lido
     */

    char file[50];

    // Limpa a tela
    clr_screen();

    // Recebe o nome do arquivo
    printf("Digite o nome do arquivo a ser lido (sem extensao): ");
    scanf("%s", file);

    // Processa a imagem
    manip_ppm(file);

    printf("Programa finalizado.\n");

    return 0;
}
