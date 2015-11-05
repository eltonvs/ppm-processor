/*
 * Helpers
 */

void copy_img(Pixel origin[MAX][MAX], Pixel destiny[MAX][MAX]) {
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            destiny[i][j] = origin[i][j];
}

void build_img(char file[], Pixel img[MAX][MAX]){
    strcat(strcat(strcat(file, "_"), op), ".ppm");

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

    printf("\nA imagem foi salva como %s\n", file);
}

/*
 * Funções de Manipulação de Imagem
 */

void img_info(Pixel img[MAX][MAX]) {
    printf("Dados da Imagem lida:\n");
    printf("Tipo: %s\n", header);
    printf("Tamanho: %ix%i\n", w, h);
    printf("Cor máxima: %i\n", comp);
    /*
    printf("Cores de cada pixel:\n");
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            printf("%i %i %i\n", img[i][j].r, img[i][j].g, img[i][j].b);
    */
}

void img_high_relief(Pixel img[MAX][MAX]) {
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 1; i < h - 1; i++)
        for (j = 0; j < w; j++)
            tmp[i][j].r = abs(img[i+1][j].r - img[i-1][j].r) + comp/2,
            tmp[i][j].g = abs(img[i+1][j].g - img[i-1][j].g) + comp/2,
            tmp[i][j].b = abs(img[i+1][j].b - img[i-1][j].b) + comp/2;
    copy_img(tmp, img);
}

void img_blurring(Pixel img[MAX][MAX]) {
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
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
    copy_img(tmp, img);
}

void img_sharpening(Pixel img[MAX][MAX]) {
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 1; i < h - 1; i++)
        for (j = 1; j < w - 1; j++)
            tmp[i][j].r = abs(5*img[i][j].r - img[i-1][j].r - img[i][j-1].r - img[i][j+1].r - img[i+1][j].r),
            tmp[i][j].g = abs(5*img[i][j].g - img[i-1][j].g - img[i][j-1].g - img[i][j+1].g - img[i+1][j].g),
            tmp[i][j].b = abs(5*img[i][j].b - img[i-1][j].b - img[i][j-1].b - img[i][j+1].b - img[i+1][j].b);
    copy_img(tmp, img);
}

void img_posterize(Pixel img[MAX][MAX]) {
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[i][j].r = (img[i][j].r > comp/2) ? comp: 0,
            img[i][j].g = (img[i][j].g > comp/2) ? comp: 0,
            img[i][j].b = (img[i][j].b > comp/2) ? comp: 0;
}

void img_thresholding(Pixel img[MAX][MAX]) {
    int bin_color;
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            bin_color = (img[i][j].r + img[i][j].g + img[i][j].b)/3 > comp/2,
            img[i][j].r = bin_color,
            img[i][j].g = bin_color,
            img[i][j].b = bin_color;
    comp = 1;
}

void img_grayscale(Pixel img[MAX][MAX]) {
    int pb;
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            pb = (img[i][j].r + img[i][j].g + img[i][j].b)/3,
            img[i][j].r = pb,
            img[i][j].g = pb,
            img[i][j].b = pb;
}

void img_negative(Pixel img[MAX][MAX]) {
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[i][j].r = comp-img[i][j].r,
            img[i][j].g = comp-img[i][j].g,
            img[i][j].b = comp-img[i][j].b;
}

void img_invert_h(Pixel img[MAX][MAX]) {
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[i][w-j-1] = tmp[i][j];
}

void img_invert_v(Pixel img[MAX][MAX]) {
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[h-i-1][j] = tmp[i][j];
}

void img_rot_left(Pixel img[MAX][MAX]) {
    int aux;
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[w-j-1][i] = tmp[i][j];
    aux = h, h = w, w = aux;
}

void img_rot_right(Pixel img[MAX][MAX]) {
    img_rot_left(img);
    img_rot_180(img);
}

void img_rot_180(Pixel img[MAX][MAX]) {
    img_invert_v(img);
    img_invert_h(img);
}

void img_amp(char file[], int zoom, Pixel img[MAX][MAX]) {
    int k, l;

    strcat(file, "_amp.ppm");

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

    printf("\nA imagem foi salva como %s\n", file);
}

void img_red(char file[], int zoom, Pixel img[MAX][MAX]) {
    int k, l, area = zoom*zoom;
    Pixel sum = {0, 0, 0};

    strcat(file, "_red.ppm");

    FILE *img_f;
    img_f = fopen(file, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w/zoom, h/zoom);
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i <= h-zoom; i += zoom)
        for (j = 0; j <= w-zoom; j += zoom, sum.r = 0, sum.g = 0, sum.b = 0) {
            for (k = 0; k < zoom; k++)
                for (l = 0; l < zoom; l++)
                    sum.r += img[i+k][j+l].r,
                    sum.g += img[i+k][j+l].g,
                    sum.b += img[i+k][j+l].b;
            fprintf(img_f, "%i %i %i\n",
            (sum.r/area > comp) ? comp : sum.r/area,
            (sum.g/area > comp) ? comp : sum.g/area,
            (sum.b/area > comp) ? comp : sum.b/area);
        }

    fclose(img_f);

    printf("\nA imagem foi salva como %s\n", file);
}

/*
 * Compressão de Imagem
 */

void img_compress(char file[], Pixel img[MAX][MAX]) {
    int cont = 0;
    Pixel t1 = img[0][0], t2;

    strcat(file, "_compressed.ppm");

    FILE *img_f;
    img_f = fopen(file, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w, h);
    fprintf(img_f, "%ic\n", comp);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++){
            t2 = img[i][j];
            if (t1.r == t2.r && t1.g == t2.g && t1.b == t2.b && !(i == h-1 && j == w-1)) {
                cont++;
                continue;
            }
            if (t1.r == t2.r && t1.g == t2.g && t1.b == t2.b && i == h-1 && j == w-1)
                cont++;
            fprintf(img_f, "%i(%i %i %i)\n", cont, t1.r, t1.g, t1.b);
            t1 = t2, cont = 1;
        }

    fclose(img_f);

    printf("\nA imagem foi salva como %s\n", file);
}

void img_uncompress(char file[], Pixel img[MAX][MAX]) {
    int rpt;
    Pixel p;
    strcat(file, "_uncompressed.ppm");

    FILE *uncomp_img;

    uncomp_img = fopen(file, "w");

    fprintf(uncomp_img, "%s\n%i %i\n%i\n", header, w, h, comp);

    while (fscanf(file_img, "%i(%i %i %i) ", &rpt, &p.r, &p.g, &p.b) != EOF)
        for (i = 0; i < rpt; i++)
            fprintf(uncomp_img, "%i %i %i\n", p.r, p.g, p.b);

    fclose(uncomp_img);

    printf("\nA imagem foi salva como %s\n", file);
}