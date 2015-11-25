/**
 *  \file functions.h
 *  \brief Arquivo com funções de manipulação da imagem.
 *
 *  Arquivo com todas as funções de filtro e manipulação da imagem.
 *
 */

void copy_img(Pixel origin[MAX][MAX], Pixel destiny[MAX][MAX]) {
    /**
     *  \brief Função para copiar a matriz da imagem
     *
     *  Função que copia uma imagem de uma matriz para outra
     *  através da passagem de parâmetros por referência
     *
     *  \param origin - Imagem a ser copiada
     *  \param destiny - Imagem para onde será copiada
     *  \return Nada
     */

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            destiny[i][j] = origin[i][j];
}

void build_img(char file[], Pixel img[MAX][MAX]){
    /**
     *  \brief Função para criar a imagem
     *
     *  Função que gera uma imagem ppm a partir de uma matriz de Pixels
     *
     *  \param file - Nome do arquivo de saída
     *  \param img - Matriz da imagem a ser gerada
     *  \return Nada
     */
    /**
     */

    strcat(strcat(strcat(file, "_"), op), ".ppm");

    /// Cria uma variável do tipo arquivo
    FILE *img_f;
    /// Cria um arquivo com o nome do arquivo + '_' + operação escolhida
    img_f = fopen(file, "w");

    /// Cria o cabeçalho da imagem ppm
    fprintf(img_f, "%s\n", header);
    /// Define a largura e altura da imagem
    fprintf(img_f, "%i %i\n", w, h);
    /// Define a cor máximo (qualidade) da imagem
    fprintf(img_f, "%i\n", comp);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            /** Percorre cada elemento da matriz img e adiciona as cores de cada pixel \
               Tratando erros básicos, como de cor negativa e/ou maior que o máximo. */
            fprintf(img_f, "%i %i %i\n",
            (img[i][j].r > comp) ? comp : (img[i][j].r < 0) ? 0 : img[i][j].r,
            (img[i][j].g > comp) ? comp : (img[i][j].g < 0) ? 0 : img[i][j].g,
            (img[i][j].b > comp) ? comp : (img[i][j].b < 0) ? 0 : img[i][j].b);

    /** Fecha o arquivo aberto */
    fclose(img_f);

    /** Mostra para o usuário o nome da imagem final gerada */
    printf("\nA imagem foi salva como %s\n", file);
}

/*
 * Funções de Manipulação de Imagem
 */

/** Funções "Obrigatórias" */

void img_thresholding(Pixel img[MAX][MAX]) {
    /**
     * Função de thresholding
     *
     * Binariza a imagem, deixando-a apenas com as
     * cores preta e branca, sem tons de cinza.
     */

    /** Cria uma variável para armazenar o valor da cor binária */
    int bin_color;

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            /** Percorre cada elemento da matriz imagem e atribui a \
               bin_color 1 se a média dos 3 componentes (r, g, b) do \
               pixel for maior ou igual à metade da cor máxima, e 0 \
               se a média for menor, atribuindo o mesmo valor a cada um */
            bin_color = (img[i][j].r + img[i][j].g + img[i][j].b)/3 > comp/2,
            img[i][j].r = bin_color,
            img[i][j].g = bin_color,
            img[i][j].b = bin_color;

    /** Define a cor máxima (componente) como 1, literalmente, binárizando a imagem */
    comp = 1;
}

void img_blurring(Pixel img[MAX][MAX]) {
    /**
     * Função de blurring
     *
     * Desfoca a imagem atribuindo o valor da média do pixel (i, j)
     * e todos os 8 pixels ao redor, de acordo com a matriz:
     *      | 1  1  1 |
     *  1/9 | 1  1  1 |
     *      | 1  1  1 |
     */

    /** Cria uma matriz para armazenar a imagem original temporariamente */
    Pixel tmp[MAX][MAX];

    /** Copia a imagem original para a temporária */
    copy_img(img, tmp);

    for (i = 1; i < h - 1; i++)
        for (j = 1; j < w - 1; j++)
            /** Percorre cada elemento do array img e atribui à matriz \
               original o valor do algoritmo de blurring. */
            img[i][j].r = (tmp[i-1][j-1].r + tmp[i-1][j].r + tmp[i-1][j+1].r +
                           tmp[i][j-1].r + tmp[i][j].r + tmp[i][j+1].r +
                           tmp[i+1][j-1].r + tmp[i+1][j].r + tmp[i+1][j+1].r)/9,
            img[i][j].g = (tmp[i-1][j-1].g + tmp[i-1][j].g + tmp[i-1][j+1].g +
                           tmp[i][j-1].g + tmp[i][j].g + tmp[i][j+1].g +
                           tmp[i+1][j-1].g + tmp[i+1][j].g + tmp[i+1][j+1].g)/9,
            img[i][j].b = (tmp[i-1][j-1].b + tmp[i-1][j].b + tmp[i-1][j+1].b +
                           tmp[i][j-1].b + tmp[i][j].b + tmp[i][j+1].b +
                           tmp[i+1][j-1].b + tmp[i+1][j].b + tmp[i+1][j+1].b)/9;
}

void img_sharpening(Pixel img[MAX][MAX]) {
    /**
     * Função de sharpening
     *
     * Aumenta a clareza de detalhes da imagem subtraindo de 5x o pixel
     * (i, j) cada um dos 4 pixels laterais, segundo a matriz:
     *  | 0  1  0 |
     *  | 1  5  1 |
     *  | 0  1  0 |
     */

    /** Cria uma matriz para armazenar a imagem original temporariamente */
    Pixel tmp[MAX][MAX];

    /** Copia a imagem original para a temporária */
    copy_img(img, tmp);

    for (i = 1; i < h - 1; i++)
        for (j = 1; j < w - 1; j++)
            /** Percorre cada elemento do array img e atribui à matriz \
               original o valor do algoritmo de sharpening */
            img[i][j].r = 5*tmp[i][j].r - tmp[i-1][j].r - tmp[i][j-1].r - tmp[i][j+1].r - tmp[i+1][j].r,
            img[i][j].g = 5*tmp[i][j].g - tmp[i-1][j].g - tmp[i][j-1].g - tmp[i][j+1].g - tmp[i+1][j].g,
            img[i][j].b = 5*tmp[i][j].b - tmp[i-1][j].b - tmp[i][j-1].b - tmp[i][j+1].b - tmp[i+1][j].b;
}

void img_rot_left(Pixel img[MAX][MAX]) {
    /**
     * Função de rotação em 90º para a esquerda
     */

    /** Cria uma variável auxiliar para poder fazer o swap */
    int aux;

    /** Cria uma matriz para armazenar a imagem original temporariamente */
    Pixel tmp[MAX][MAX];

    /** Copia a imagem original para a temporária */
    copy_img(img, tmp);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            /** Copia para a matriz temporária a transposta da matriz original */
            img[w-j-1][i] = tmp[i][j];

    /** Faz o swap entre h e w, pois ao rotacionar, a altura troca com a largura */
    aux = h, h = w, w = aux;
}

void img_rot_right(Pixel img[MAX][MAX]) {
    /**
     * Função de rotação em 90º para a direita
     *
     * Se considerarmos o ângulo de rotação para esquerda como x,
     * o ângulo de rotação para esquerda se dá por x + 180º, portanto,
     * para rotacionar a imagem para esquerda, podemos rotacioná-la para
     * esquerda uma vez e depois rotacionar em 180º. E é isso que essa
     * função faz.
     */

    /** Rotaciona a imagem original 1 vez para a esquerda */
    img_rot_left(img);
    /** Rotaciona a imagem original em 180º */
    img_rot_180(img);
}

void img_rot_180(Pixel img[MAX][MAX]) {
    /**
     * Função de rotação em 180º
     *
     * Para rotacionar uma imagem em 180º, poderíamos aplicar duas vezes
     * o algoritmo de rotação para a esquerda (ou para a direita), no
     * entanto, não há essa necessidade, pois uma imagem rotacionada em
     * 180º nada mais é do que uma imagem invertida horizontalmente e
     * verticalmente ao mesmo tempo (flip_h + flip_v). E é isso que essa
     * função faz.
     */

    /** Inverte a imagem verticalmente (flip vertical) */
    img_invert_v(img);
    /** Inverte a imagem horizontalmente (flip horizontal) */
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

/** Funções Extras */

void img_info(Pixel img[MAX][MAX]) {
    /**
     * Função que mostra informações sobre a imagem lida
     * Tipo do cabeçalho, largura, altura e cor máxima
     *
     * Obs: As cores de cada pixel foram comentadas para
     *      evitar um laço muito extenso em imagens grandes
     */

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

void img_emboss(Pixel img[MAX][MAX]) {
    /**
     * Função para deixar a imagem com o efeito de Alto Relevo
     *
     * Esse filtro pega o valor de uma posição (i+1, j) e subtrai do
     * valor da posição oposta (i-1, j), substiruindo no valor central
     * (i, j) e somando com a metade do componente para clareamento.
     * Seguindo a matriz:
     * | 0  -1   0 |
     * | 0   0   0 | + component/2
     * | 0   1   0 |
     */

    /** Cria uma matriz para armazenar a imagem original temporariamente */
    Pixel tmp[MAX][MAX];

    /** Copia a imagem original para a temporária */
    copy_img(img, tmp);

    for (i = 1; i < h - 1; i++)
        for (j = 0; j < w; j++)
            /** Percorre cada elemento do array img e atribui à matriz \
               temporária o valor do algoritmo de alto relevo. */
            tmp[i][j].r = img[i+1][j].r - img[i-1][j].r + comp/2,
            tmp[i][j].g = img[i+1][j].g - img[i-1][j].g + comp/2,
            tmp[i][j].b = img[i+1][j].b - img[i-1][j].b + comp/2;

    /** Copia a matriz temporária para a matriz da imagem original */
    copy_img(tmp, img);
}

void img_posterize(Pixel img[MAX][MAX]) {
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[i][j].r = (img[i][j].r > comp/2) ? comp: 0,
            img[i][j].g = (img[i][j].g > comp/2) ? comp: 0,
            img[i][j].b = (img[i][j].b > comp/2) ? comp: 0;
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

void img_reflect_h(Pixel img[MAX][MAX]) {
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[i][w-j-1] = img[i][j];
}

void img_reflect_v(Pixel img[MAX][MAX]) {
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[h-i-1][j] = img[i][j];
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