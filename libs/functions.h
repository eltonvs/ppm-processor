#include "var.h"
#include "visual.h"

void img_info(Pixel img[w][h]) {
    int i, j;
    printf("Dados da Imagem lida:\n");
    printf("Tipo: %s\n", header);
    printf("Tamanho: %ix%i\n", w, h);
    printf("Cor maxima: %i\n", component);
    printf("Cores de cada pixel:\n");
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            printf("%i %i %i\n", img[i][j].r, img[i][j].g, img[i][j].b);
}

void img_thresholding(Pixel img[w][h]) {
    int i, j, pb;
    char file_name_thr[50];

    strcpy(file_name_thr,  file_name);
    strcat(file_name_thr,"-thr.ppm");

    FILE *img_f;
    img_f = fopen(file_name_thr, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w, h);
    fprintf(img_f, "%i\n", component);
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            pb = (img[i][j].r + img[i][j].g + img[i][j].b)/3;
            fprintf(img_f, "%i %i %i%c", pb, pb, pb, j == w - 1 ? '\n' : ' ');
        }
    }

    fclose(img_f);
}

void img_invert(Pixel img[w][h]) {
    int i, j;
    char file_name_inv[50];

    strcpy(file_name_inv,  file_name);
    strcat(file_name_inv,"-inv.ppm");

    FILE *img_f;
    img_f = fopen(file_name_inv, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w, h);
    fprintf(img_f, "%i\n", component);
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            fprintf(img_f, "%i %i %i%c",
                    component - img[i][j].r,
                    component-img[i][j].g,
                    component-img[i][j].b,
                    j == w - 1 ? '\n' : ' ');
        }
    }

    fclose(img_f);
}

void choice(char op[3], Pixel img[w][h]) {
    op[0] = tolower(op[0]),
    op[1] = tolower(op[1]),
    op[2] = tolower(op[2]);

    if (strcmp(op, "fim") == 0)
        return;
    else {
        system("clear");
        if (strcmp(op, "inf") == 0) {
            printf("Exibindo informacoes da imagem...\n");
            img_info(img);
        }else if (strcmp(op, "inv") == 0) {
            printf("Executando inversao...\n");
            img_invert(img);
        }else if (strcmp(op, "thr") == 0) {
            printf("Executando thresholding...\n");
            img_thresholding(img);
        }else if (strcmp(op, "blu") == 0)
            printf("Executando blurring...\n");
        else if (strcmp(op, "sha") == 0)
            printf("Executando sharpening...\n");
        else if (strcmp(op, "rot") == 0) {
            int ang;
            printf("Digite o angulo de rotacao: ");
            scanf("%i", &ang);
            printf("Rotacionando Imagem...\n");
        }else if (strcmp(op, "amp") == 0) {
            int zoom;
            printf("Digite o zoom: ");
            scanf("%i", &zoom);
            printf("Ampliando Imagem...\n");
        }else if (strcmp(op, "red") == 0) {
            int zoom;
            printf("Digite o zoom: ");
            scanf("%i", &zoom);
            printf("Reduzindo Imagem...\n");
        }else {
            printf("A opcao selecionada nao esta disponivel.\nTente novamente: ");
            scanf("%s", op);
            choice(op, img);
        }
    }
}

int read_ppm(char file[]) {
    strcpy(file_name, file);
    int i, j; //Iteradores
    char op[3];

    FILE *img;

    img = fopen(strcat(file,".ppm"), "r");
    if (img == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fscanf(img, "%s", header);
    fscanf(img, "%i %i", &w, &h);
    fscanf(img, "%i", &component);

    Pixel image[w][h];

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            fscanf(img, "%i %i %i", &image[i][j].r, &image[i][j].g, &image[i][j].b);

    fclose(img);

    menu();
    printf("O que voce deseja fazer? ");
    scanf("%s", op);
    choice(op, image);

    return 1;
}
