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
 *        - error_message()
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
            strcat(op, "_h");
        }else if(dir == 'v') {
            img_invert_v(img);
            strcat(op, "_v");
        }else {
            error_message(0);
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
            error_message(0);
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
            error_message(2);
            choice(img);
            return;
        }
    }else if (!strcmp(op, "rle")) {
        printf("Comprimindo Imagem...\n");
        img_compress(file_name, img);
    }else {
        error_message(1);
        choice(img);
    }
}

void skip_comments() {
    char buffer;
    buffer = fgetc(img_file);
    if (buffer == '#' || buffer == ' ')
        while(buffer != '\n')
            buffer = fgetc(img_file);
    else
        ungetc(buffer, img_file);
}

void manip_ppm(char file[]) {
    int i, j; //Iteradores

    strcpy(file_name, file);

    img_file = fopen(strcat(file,".ppm"), "r");
    if (img_file == NULL) {
        error_message(3);
        return;
    }

    skip_comments();
    fscanf(img_file, "P3 ");
    skip_comments();
    fscanf(img_file, "%i ", &w);
    skip_comments();
    fscanf(img_file, "%i ", &h);
    skip_comments();
    fscanf(img_file, "%i ", &comp);
    skip_comments();

    if (!w || !h || !comp) {
        error_message(3);
        return;
    }

    MAX = (w > h) ? w : h;

    Pixel image[MAX][MAX];

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++) {
            fscanf(img_file, "%i ", &image[i][j].r);
            skip_comments();
            fscanf(img_file, "%i ", &image[i][j].g);
            skip_comments();
            fscanf(img_file, "%i ", &image[i][j].b);
            skip_comments();
        }

    fclose(img_file);

    menu();
    printf("O que você deseja fazer? ");
    scanf("%s", op);
    clr_screen();
    choice(image);
}
