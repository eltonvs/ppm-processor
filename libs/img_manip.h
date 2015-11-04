#include "global.h"
#include "headers.h"
#include "visual.h"
#include "functions.h"

/*
 * Bibliotecas utilizadas:
 *  - global.h:
 *     - Constantes, variáveis e typedefs globais
 *  - headers.h:
 *     - Inicialização das funções para evitar erros de declaração implícita
 *  - visual.h:
 *     - Funções com o intuito "visual"
 *        - clr_screen()
 *        - error_message()
 *        - menu()
 *  - functions.h:
 *     - Funções de processamento e manipulação da imagem
 */

void choice(Pixel img[w][h]) {
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
    char buffer = fgetc(file_img);
    do {
        if (buffer == '#')
            while (buffer != '\n')
                buffer = fgetc(file_img);
        else
            ungetc(buffer, file_img);
        buffer = fgetc(file_img);
    } while (buffer == '#');
    ungetc(buffer, file_img);
}

void read_ppm(Pixel img[MAX][MAX]) {
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++) {
            fscanf(file_img, "%i ", &img[i][j].r);
            skip_comments();
            fscanf(file_img, "%i ", &img[i][j].g);
            skip_comments();
            fscanf(file_img, "%i ", &img[i][j].b);
            skip_comments();
        }
}

void manip_ppm(char file[]) {
    char compressed;

    strcpy(file_name, file);

    file_img = fopen(strcat(file,".ppm"), "r");
    if (file_img == NULL) {
        error_message(3);
        return;
    }

    skip_comments();
    fscanf(file_img, "P3 ");
    skip_comments();
    fscanf(file_img, "%i ", &w);
    skip_comments();
    fscanf(file_img, "%i ", &h);
    skip_comments();
    fscanf(file_img, "%i%c", &comp, &compressed);
    skip_comments();

    if (!w || !h || !comp) {
        error_message(3);
        return;
    }

    MAX = (w > h) ? w : h;

    Pixel image[MAX][MAX];

    if (compressed == 'c') {
        int c;
        printf("A imagem selecionada está comprimida.\n");
        printf("Deseja descomprimir? [1 - Sim / 2 - Não] ");
        scanf("%i", &c);
        if (c) img_uncompress(file_name, image);
        printf("\nA imagem foi salva como %s\n", file_name);
        return;
    }else {
        read_ppm(image);
    }

    fclose(file_img);

    menu();
    printf("O que você deseja fazer? ");
    scanf("%s", op);
    clr_screen();
    choice(image);
}
