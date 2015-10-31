#include "var.h"
#include "headers.h"
#include "visual.h"
#include "functions.h"

void build_img(char file[], Pixel img[MAX][MAX]){
    int i, j;

    strcat(strcat(strcat(file, "-"), op), ".ppm");

    FILE *img_f;
    img_f = fopen(file, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w, h);
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            fprintf(img_f, "%i %i %i\n",
            (img[i][j].r > comp) ? comp : (img[i][j].r < 0) ? 0 : img[i][j].r,
            (img[i][j].g > comp) ? comp : (img[i][j].g < 0) ? 0 : img[i][j].g,
            (img[i][j].b > comp) ? comp : (img[i][j].b < 0) ? 0 : img[i][j].b);

    fclose(img_f);
}

void choice(Pixel img[w][h]) {
    op[0] = tolower(op[0]),
    op[1] = tolower(op[1]),
    op[2] = tolower(op[2]);

    if (strcmp(op, "fim") == 0)
        return;
    else {
        if (strcmp(op, "inf") == 0) {
            printf("Exibindo informacoes da imagem...\n");
            img_info(img);
        }else if (strcmp(op, "inv") == 0) {
            printf("Executando inversao...\n");
            img_invert(img);
            build_img(file_name, img);
        }else if (strcmp(op, "rlv") == 0) {
            printf("Executando alto-relevo...\n");
            img_high_relief(img);
            build_img(file_name, img);
        }else if (strcmp(op, "pop") == 0) {
            printf("Convertendo para o Pop Art...\n");
            img_popart(img);
            build_img(file_name, img);
        }else if (strcmp(op, "thr") == 0) {
            printf("Executando thresholding...\n");
            img_thresholding(img);
            build_img(file_name, img);
        }else if (strcmp(op, "peb") == 0) {
            printf("Deixando em Preto e Branco...\n");
            img_grayscale(img);
            build_img(file_name, img);
        }else if (strcmp(op, "blu") == 0) {
            printf("Executando blurring...\n");
            img_blurring(img);
            build_img(file_name, img);
        }else if (strcmp(op, "sha") == 0) {
            printf("Executando sharpening...\n");
            img_sharpening(img);
            build_img(file_name, img);
        }else if (strcmp(op, "rot") == 0) {
            char ang[3];
            printf("Digite o tipo de rotacao [dir, esq, 180]: ");
            scanf("%s", ang);
            if(strcmp(ang, "dir") == 0) {
                img_rot_right(img);
            }else if(strcmp(ang, "180") == 0) {
                img_rot_180(img);
            }else if(strcmp(ang, "esq") == 0) {
                img_rot_left(img);
            }else {
                printf("Voce nao escolheu uma opcao valida. Tente novamente:\n");
                choice(img);
                return;
            }
            printf("Rotacionando Imagem...\n");
            strcat(strcat(op, "-"), ang);
            build_img(file_name, img);
        }else if (strcmp(op, "amp") == 0) {
            int zoom;
            printf("Digite o zoom: ");
            scanf("%i", &zoom);
            printf("Ampliando Imagem...\n");
            img_amp(file_name, zoom, img);
        }else if (strcmp(op, "red") == 0) {
            int zoom;
            printf("Digite o zoom: ");
            scanf("%i", &zoom);
            if(h%zoom == 0 && w%zoom == 0) {
                printf("Reduzindo Imagem...\n");
                img_red(file_name, zoom, img);
            }else {
                printf("O zoom de reducao deve ser um multiplo dos lados (%i, %i).\n", w, h);
                choice(img);
                return;
            }
        }else {
            printf("A opcao selecionada nao esta disponivel.\nTente novamente: ");
            scanf("%s", op);
            choice(img);
        }
    }
}

int manip_ppm(char file[]) {
    strcpy(file_name, file);
    int i, j; //Iteradores

    FILE *img;

    img = fopen(strcat(file,".ppm"), "r");
    if (img == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fscanf(img, "P3 %i %i %i", &w, &h, &comp);

    MAX = (w > h) ? w : h;

    Pixel image[MAX][MAX];

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            fscanf(img, "%i %i %i", &image[i][j].r, &image[i][j].g, &image[i][j].b);

    fclose(img);

    menu();
    printf("O que voce deseja fazer? ");
    scanf("%s", op);
    choice(image);

    return 1;
}
