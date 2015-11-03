#include "global.h"
#include "headers.h"
#include "visual.h"
#include "functions.h"

/*
 * Bibliotecas utilizadas:
 *  - global.h:
 *     - Variáveis e typedefs globais
 *  - headers.h:
 *     - Inicialização das funções para evitar erros de declaração implícita
 *  - visual.h:
 *     - Funções com o intuito "visual"
 *        - clr_screen()
 *        - menu()
 *        - invalid_option()
 *  - functions.h:
 *     - Funções de processamento da imagem
 */

void choice(Pixel img[w][h]) {
    int i;

    for(i = 0; i < strlen(op); i++)
        op[i] = tolower(op[i]);

    if (!strcmp(op, "fim"))
        return;
    if (!strcmp(op, "inf")) {
        printf("Exibindo informações da imagem...\n");
        img_info(img);
    }else if (!strcmp(op, "neg")) {
        printf("Criando o negativo da imagem...\n");
        img_negative(img);
        build_img(file_name, img);
    }else if (!strcmp(op, "rlv")) {
        printf("Executando alto-relevo...\n");
        img_high_relief(img);
        build_img(file_name, img);
    }else if (!strcmp(op, "pos")) {
        printf("Executando Posterização...\n");
        img_posterize(img);
        build_img(file_name, img);
    }else if (!strcmp(op, "thr")) {
        printf("Executando thresholding...\n");
        img_thresholding(img);
        build_img(file_name, img);
    }else if (!strcmp(op, "peb")) {
        printf("Deixando em Preto e Branco...\n");
        img_grayscale(img);
        build_img(file_name, img);
    }else if (!strcmp(op, "blu")) {
        printf("Executando blurring...\n");
        img_blurring(img);
        build_img(file_name, img);
    }else if (!strcmp(op, "sha")) {
        printf("Executando sharpening...\n");
        img_sharpening(img);
        build_img(file_name, img);
    }else if (!strcmp(op, "inv")) {
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
            invalid_option(0);
            choice(img);
            return;
        }
        printf("Invertendo imagem...\n");
        build_img(file_name, img);
    }else if (!strcmp(op, "rot")) {
        char ang[3];
        printf("Digite o tipo de rotação [dir, esq, 180]: ");
        scanf("%s", ang);
        if(!strcmp(ang, "dir")) {
            img_rot_right(img);
        }else if(!strcmp(ang, "180")) {
            img_rot_180(img);
        }else if(!strcmp(ang, "esq")) {
            img_rot_left(img);
        }else {
            invalid_option(0);
            choice(img);
            return;
        }
        printf("Rotacionando Imagem...\n");
        strcat(strcat(op, "-"), ang);
        build_img(file_name, img);
    }else if (!strcmp(op, "amp")) {
        int zoom;
        printf("Digite o zoom: ");
        scanf("%i", &zoom);
        printf("Ampliando Imagem...\n");
        img_amp(file_name, zoom, img);
    }else if (!strcmp(op, "red")) {
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
    int i, j; //Iteradores

    strcpy(file_name, file);

    img_file = fopen(strcat(file,".ppm"), "r");
    if (img_file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fscanf(img_file, "P3\n");
    fscanf(img_file, "%i %i\n", &w, &h);
    fscanf(img_file, "%i\n", &comp);

    if (w == 0 || h == 0 || comp == 0) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    MAX = (w > h) ? w : h;

    Pixel image[MAX][MAX];

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            fscanf(img_file, "%i %i %i", &image[i][j].r, &image[i][j].g, &image[i][j].b);

    fclose(img_file);

    menu();
    printf("O que você deseja fazer? ");
    scanf("%s", op);
    clr_screen();
    choice(image);
}
