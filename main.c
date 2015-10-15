#include <stdio.h>
#include <string.h>

typedef struct {
    int r;
    int g;
    int b;
} Pixel;

void menu() {
    printf("-------------------- MENU --------------------\n");
    printf("'thr' \t binarizar imagem usando thresholding.\n");
    printf("'blu' \t executar blurring.\n");
    printf("'sha' \t executar sharpening.\n");
    printf("'rot' \t rotacionar imagem.\n");
    printf("'amp' \t ampliar imagem.\n");
    printf("'red' \t reduzir imagem.\n\n");
    printf("'fim' \t finalizar programa.\n");
    printf("----------------------------------------------\n\n");
}

void read_ppm(char file_name[]) {
    char header[3], op[4];
    int i, j; //Iteradores
    int w, h, max_color; //Dados da imagem

    FILE *img;
    
    img = fopen(file_name, "r");
    if (img == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
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
}

int main() {
    char file[50];

    //Recebe o nome do arquivo
    printf("Digite o nome do arquivo a ser lido: ");
    scanf("%s", file);

    //Lê a imagem
    read_ppm(file);

    return 0;
}
