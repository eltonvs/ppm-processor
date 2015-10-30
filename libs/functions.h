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

void img_high_relief(Pixel img[w][h]) {
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

void img_popart(Pixel img[w][h]) {
    int i, j, pb;
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[i][j].r = (img[i][j].r > 127) ? 255: 0,
            img[i][j].g = (img[i][j].g > 127) ? 255: 0,
            img[i][j].b = (img[i][j].b > 127) ? 255: 0;
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

void img_rot_left(Pixel img[MAX][MAX]) {
    int i, j, aux;
    Pixel tmp[MAX][MAX];
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            tmp[i][j].r = img[i][j].r,
            tmp[i][j].g = img[i][j].g,
            tmp[i][j].b = img[i][j].b;
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[w-j-1][i].r = tmp[i][j].r,
            img[w-j-1][i].g = tmp[i][j].g,
            img[w-j-1][i].b = tmp[i][j].b;
    aux = h, h = w, w = aux;
}

void img_rot_right(Pixel img[MAX][MAX]) {
    int i;
    for (i = 0; i < 3; i++)
        img_rot_left(img);
}

void img_rot_180(Pixel img[MAX][MAX]) {
    int i;
    for (i = 0; i < 2; i++)
        img_rot_left(img);
}

void img_amp(char file[], int zoom, Pixel img[MAX][MAX]) {
    int i, j, k, l;

    strcat(file, "-amp.ppm");

    FILE *img_f;
    img_f = fopen(file, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w*zoom, h*zoom);
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i < h; i++)
        for (k = 0; k < zoom; k++)
            for (j = 0; j < w; j++)
                for (l = 0; l < zoom; l++)
                    fprintf(img_f, "%i %i %i\n",
                    (img[i][j].r > comp) ? comp : img[i][j].r,
                    (img[i][j].g > comp) ? comp : img[i][j].g,
                    (img[i][j].b > comp) ? comp : img[i][j].b);

    fclose(img_f);
}

void img_red(char file[], int zoom, Pixel img[MAX][MAX]) {
    int i, j, k, l, area = zoom*zoom;
    Pixel mean = {0, 0, 0};

    strcat(file, "-red.ppm");

    FILE *img_f;
    img_f = fopen(file, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w/zoom, h/zoom);
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i <= h-zoom; i += zoom)
        for (j = 0; j <= w-zoom; j += zoom, mean.r = 0, mean.g = 0, mean.b = 0) {
            for (k = 0; k < zoom; k++)
                for (l = 0; l < zoom; l++)
                    mean.r += img[i+k][j+l].r/area,
                    mean.g += img[i+k][j+l].g/area,
                    mean.b += img[i+k][j+l].b/area;
            fprintf(img_f, "%i %i %i\n",
            (mean.r > comp) ? comp : mean.r,
            (mean.g > comp) ? comp : mean.g,
            (mean.b > comp) ? comp : mean.b);
        }

    fclose(img_f);
}
