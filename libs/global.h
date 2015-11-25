/**
 *  \file global.h
 *  \brief Arquivo com as variáveis globais.
 *
 *  Arquivo com todas as constantes, variáveis e estruturas globais.
 *
 */

/** Define o cabeçalho do arquivo ppm suportado. */
#define header "P3"

/** Armazena a imagem lida. */
FILE *file_img;

/** Armazena o nome final da imagem. */
char file_name[50];

/** Armazena a escolha do usuário no menu. */
char op[3];

/** Armazena a largura da imagem. */
int w;

/** Armazena a altura da imagem. */
int h;

/** Armazena o valor máximo que a imagem pode assumir. */
int MAX;

/** Armazena a cor máxima da imagem (qualidade). */
int comp;

/** Iterador primário padrão. */
int i;

/** Iterador secundário padrão.. */
int j;


/**
 *  Struct para armazenar as cores (em RGB) de um pixel.
 */
typedef struct {
    int r; /**< Armazena a quantidade de vermelho (r) da cor. */
    int g; /**< Armazena a quantidade de verde (g) da cor. */
    int b; /**< Armazena a quantidade de azul (b) da cor. */
} Pixel;
