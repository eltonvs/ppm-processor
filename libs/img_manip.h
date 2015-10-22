#include "var.h"
#include "visual.h"
#include "functions.h"

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
        }else if (strcmp(op, "blu") == 0) {
            printf("Executando blurring...\n");
        }else if (strcmp(op, "sha") == 0) {
            printf("Executando sharpening...\n");
        }else if (strcmp(op, "rot") == 0) {
            int ang;
            printf("Digite o angulo de rotacao [90, 180, 270]: ");
            scanf("%i", &ang);
            printf("Rotacionando Imagem...\n");
            if(ang%360 == 90)
                img_rot_90(img);
            if(ang%360 == 180)
                img_rot_180(img);
            if(ang%360 == 270)
                img_rot_270(img);
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
    fscanf(img, "%i", &comp);

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
