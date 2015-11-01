#include "global.h"
#include "headers.h"
#include "visual.h"
#include "functions.h"

void choice(Pixel img[w][h]) {
    int i;

    for(i = 0; op[i] != '\0'; i++)
        op[i] = tolower(op[i]);

    if (strcmp(op, "fim") == 0)
        return;
    if (strcmp(op, "inf") == 0) {
        printf("Exibindo informações da imagem...\n");
        img_info(img);
    }else if (strcmp(op, "neg") == 0) {
        printf("Criando o negativo da imagem...\n");
        img_negative(img);
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
    }else if (strcmp(op, "inv") == 0) {
        char dir;
        printf("Digite o tipo de inversão [h: horizontal ou v: vertical]: ");
        scanf(" %c", &dir);
        if(dir == 'h') {
            img_invert_h(img);
            strcat(op, "-h");
        }else if(dir == 'v') {
            img_invert_v(img);
            strcat(op, "-v");
        }else {
            invalid_option(3);
            choice(img);
            return;
        }
        printf("Invertendo imagem...\n");
        build_img(file_name, img);
    }else if (strcmp(op, "rot") == 0) {
        char ang[3];
        printf("Digite o tipo de rotação [dir, esq, 180]: ");
        scanf("%s", ang);
        if(strcmp(ang, "dir") == 0) {
            img_rot_right(img);
        }else if(strcmp(ang, "180") == 0) {
            img_rot_180(img);
        }else if(strcmp(ang, "esq") == 0) {
            img_rot_left(img);
        }else {
            invalid_option(3);
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
            invalid_option(2);
            choice(img);
            return;
        }
    }else {
        invalid_option(1);
        choice(img);
    }
}

void manip_ppm(char file[]) {
    strcpy(file_name, file);
    int i, j; //Iteradores

    FILE *img;

    img = fopen(strcat(file,".ppm"), "r");
    if (img == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fscanf(img, "P3 %i %i %i", &w, &h, &comp);

    MAX = (w > h) ? w : h;

    Pixel image[MAX][MAX];

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            fscanf(img, "%i %i %i", &image[i][j].r, &image[i][j].g, &image[i][j].b);

    fclose(img);

    menu();
    printf("O que você deseja fazer? ");
    scanf("%s", op);
    clr_screen();
    choice(image);
}
