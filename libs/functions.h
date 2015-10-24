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

void img_auto_relevo(Pixel img[w][h]) {
    int i, j;
    Pixel tmp[w][h];
    for (i = 1; i < h - 1; i++)
        for (j = 0; j < w; j++)
            tmp[i][j].r = abs(img[i+1][j].r - img[i-1][j].r),
            tmp[i][j].g = abs(img[i+1][j].g - img[i-1][j].g),
            tmp[i][j].b = abs(img[i+1][j].b - img[i-1][j].b);
    for (i = 1; i < h - 1; i++)
        for (j = 0; j < w; j++)
            img[i][j].r = tmp[i][j].r + comp/2,
            img[i][j].g = tmp[i][j].g + comp/2,
            img[i][j].b = tmp[i][j].b + comp/2;
}

void img_blurring(Pixel img[w][h]) {
    int i, j;
    Pixel tmp[w][h];
    for (i = 1; i < h - 1; i++)
        for (j = 1; j < w - 1; j++)
            tmp[i][j].r = (img[i-1][j-1].r + img[i-1][j].r + img[i-1][j+1].r +
                            img[i][j-1].r + img[i][j].r + img[i][j+1].r +
                            img[i+1][j-1].r + img[i+1][j].r + img[i+1][j+1].r)/9,
            tmp[i][j].g = (img[i-1][j-1].g + img[i-1][j].g + img[i-1][j+1].g +
                            img[i][j-1].g + img[i][j].g + img[i][j+1].g +
                            img[i+1][j-1].g + img[i+1][j].g + img[i+1][j+1].g)/9,
            tmp[i][j].b = (img[i-1][j-1].b + img[i-1][j].b + img[i-1][j+1].b +
                            img[i][j-1].b + img[i][j].b + img[i][j+1].b +
                            img[i+1][j-1].b + img[i+1][j].b + img[i+1][j+1].b)/9;
    for (i = 1; i < h - 1; i++)
        for (j = 1; j < w - 1; j++)
            img[i][j].r = tmp[i][j].r,
            img[i][j].g = tmp[i][j].g,
            img[i][j].b = tmp[i][j].b;
}

void img_sharpening(Pixel img[w][h]) {
    int i, j;
    Pixel tmp[w][h];
    for (i = 1; i < h - 1; i++)
        for (j = 1; j < w - 1; j++)
            tmp[i][j].r = abs(5*img[i][j].r - img[i-1][j].r - img[i][j-1].r - img[i][j+1].r - img[i+1][j].r),
            tmp[i][j].g = abs(5*img[i][j].g - img[i-1][j].g - img[i][j-1].g - img[i][j+1].g - img[i+1][j].g),
            tmp[i][j].b = abs(5*img[i][j].b - img[i-1][j].b - img[i][j-1].b - img[i][j+1].b - img[i+1][j].b);
    for (i = 1; i < h - 1; i++)
        for (j = 1; j < w - 1; j++)
            img[i][j].r = tmp[i][j].r,
            img[i][j].g = tmp[i][j].g,
            img[i][j].b = tmp[i][j].b;
}

void img_thresholding(Pixel img[w][h]) {
    int i, j, pb;
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            pb = (img[i][j].r + img[i][j].g + img[i][j].b)/3,
            img[i][j].r = pb,
            img[i][j].g = pb,
            img[i][j].b = pb;
}

void img_invert(Pixel img[w][h]) {
    int i, j;
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[i][j].r = comp-img[i][j].r,
            img[i][j].g = comp-img[i][j].g,
            img[i][j].b = comp-img[i][j].b;
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
