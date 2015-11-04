/*
 * Arquivo com todas as variáveis, constantes e
 * estruturas a serem usados em todo o projeto.
 *
 * Constantes
 *  - header:
 *     - Tipo: Vetor de char - String
 *     - Função: Definir o cabeçalho do arquivo ppm suportado
 *
 * Variáveis
 *  - file_img:
 *     - Tipo: FILE - Arquivo
 *     - Função: Armazenar a imagem lida
 *  - file_name:
 *     - Tipo: Vetor de char - String
 *     - Função: Armazenar o nome final da imagem
 *  - op:
 *     - Tipo: Vetor de char - String
 *     - Função: Armazenar a escolha do usuário no menu
 *  - w, h:
 *     - Tipo: Inteiro
 *     - Função: Armazenar a largura e altura (respectivamente) da imagem
 *  - MAX:
 *     - Tipo: Inteiro
 *     - Função: Armazenar o valor máximo que a imagem pode
                 assumir (maior entre a largura e a altura)
 *  - comp:
 *     - Tipo: Inteiro
 *     - Função: Armazenar o máximo de cor da imagem (qualidade)
 *
 * Estruturas
 *  - Pixel:
 *     - Tipo: Tipo (struct)
 *     - Função: Armazenar as cores (em RGB) de um pixel
 *     - Conteúdo:
 *        - r:
 *           - Tipo: Inteiro
 *           - Função: Armazenar a quantidade de vermelho da cor
 *        - g:
 *           - Tipo: Inteiro
 *           - Função: Armazenar a quantidade de verde da cor
 *        - b:
 *           - Tipo: Inteiro
 *           - Função: Armazenar a quantidade de azul da cor
 */

#define header "P3"

FILE *file_img;

char file_name[50], op[3];
int w, h, MAX, comp;

typedef struct {
    int r, g, b;
} Pixel;
