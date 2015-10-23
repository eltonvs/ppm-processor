void img_info(Pixel img[w][h]) {
    int i, j;
    printf("Dados da Imagem lida:\n");
    printf("Tipo: %s\n", header);
    printf("Tamanho: %ix%i\n", w, h);
    printf("Cor maxima: %i\n", comp);
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
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            pb = (img[i][j].r + img[i][j].g + img[i][j].b)/3;
            fprintf(img_f, "%i %i %i%c", pb, pb, pb, (j == w-1)?'\n':' ');
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
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            fprintf(img_f, "%i %i %i%c", comp-img[i][j].r, comp-img[i][j].g, comp-img[i][j].b, (j == w-1)?'\n':' ');
        }
    }

    fclose(img_f);
}

void img_rot_90(Pixel img[w][h]) {
    int i, j;
    char file_name_rot_90[50];

    strcpy(file_name_rot_90,  file_name);
    strcat(file_name_rot_90,"-rot-90.ppm");

    FILE *img_f;
    img_f = fopen(file_name_rot_90, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", h, w);
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i < w; i++) {
        for (j = h-1; j >= 0; j--) {
            fprintf(img_f, "%i %i %i%c", img[j][i].r, img[j][i].g, img[j][i].b, (j == 0)?'\n':' ');
        }
    }

    fclose(img_f);
}

void img_rot_180(Pixel img[w][h]) {
    int i, j;
    char file_name_rot_180[50];

    strcpy(file_name_rot_180,  file_name);
    strcat(file_name_rot_180,"-rot-180.ppm");

    FILE *img_f;
    img_f = fopen(file_name_rot_180, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w, h);
    fprintf(img_f, "%i\n", comp);
    for (i = h-1; i >= 0; i--) {
        for (j = w-1; j >= 0; j--) {
            fprintf(img_f, "%i %i %i%c", img[i][j].r, img[i][j].g, img[i][j].b, (j == 0)?'\n':' ');
        }
    }

    fclose(img_f);
}

void img_rot_270(Pixel img[w][h]) {
    int i, j;
    char file_name_rot_270[50];

    strcpy(file_name_rot_270,  file_name);
    strcat(file_name_rot_270,"-rot-270.ppm");

    FILE *img_f;
    img_f = fopen(file_name_rot_270, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", h, w);
    fprintf(img_f, "%i\n", comp);
    for (i = w-1; i >= 0; i--) {
        for (j = 0; j < h; j++) {
            fprintf(img_f, "%i %i %i%c", img[j][i].r, img[j][i].g, img[j][i].b, (j == w-1)?'\n':' ');
        }
    }

    fclose(img_f);
}
