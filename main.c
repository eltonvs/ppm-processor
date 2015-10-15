#include <stdio.h>
#include <string.h>

typedef struct {
    int r;
    int g;
    int b;
} Pixel;

void menu() {
    printf("'thr' - binarizacao da imagem usando thresholding\n");
    printf("'blu' - executa blurring\n");
    printf("'sha' - executa sharpening\n");
    printf("'rot: - rotacao da imagem, dado o angulo\n");
    printf("'amp' - ampliar a imagem, dado o zoom.\n");
    printf("'red' - reduzir a imagem, dado o zoom.\n");
}

int main() {
    char header[3], op[4];
    int i, j; //Iteradores
    int w, h, max_color; //Dados da imagem

    printf("Lendo imagem...\n\n");

    FILE *img;
    
    img = fopen("teste.ppm", "r");

    fscanf(img, "%s", header);
    fscanf(img, "%i %i", &w, &h);
    fscanf(img, "%i", &max_color);

    Pixel imagem[w][h];

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            fscanf(img, "%i %i %i", &imagem[i][j].r, &imagem[i][j].g, &imagem[i][j].b);
    
    fclose(img);

    printf("Dados da Imagem lida:\n");
    printf("Tipo: %s\n", header);
    printf("Tamanho: %ix%i\n", w, h);
    printf("Cor maxima: %i\n", max_color);
    printf("Cores de cada pixel:\n");
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            printf("%i %i %i\n", imagem[i][j].r, imagem[i][j].g, imagem[i][j].b);

    return 0;
}
