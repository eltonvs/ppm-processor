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

    strcat(strcat(strcat(file, "_"), op), ".ppm");

    // Cria uma variável do tipo arquivo
    FILE *img_f;
    // Cria um arquivo com o nome do arquivo + '_' + operação escolhida
    img_f = fopen(file, "w");

    // Cria o cabeçalho da imagem ppm
    fprintf(img_f, "%s\n", header);
    // Define a largura e altura da imagem
    fprintf(img_f, "%i %i\n", w, h);
    // Define a cor máximo (qualidade) da imagem
    fprintf(img_f, "%i\n", comp);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            // Trata erros básicos, como de cor negativa e/ou maior que o máximo.
            fprintf(img_f, "%i %i %i\n",
            (img[i][j].r > comp) ? comp : (img[i][j].r < 0) ? 0 : img[i][j].r,
            (img[i][j].g > comp) ? comp : (img[i][j].g < 0) ? 0 : img[i][j].g,
            (img[i][j].b > comp) ? comp : (img[i][j].b < 0) ? 0 : img[i][j].b);

    // Fecha o arquivo aberto
    fclose(img_f);
}

/*
 * Funções de Manipulação de Imagem
 */

// Funções "Obrigatórias"

void img_thresholding(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função de thresholding
     *
     *  Binariza a imagem, deixando-a apenas com as
     *  cores preta e branca, sem tons de cinza.
     *
     *  \param img - Matriz da imagem a ser alterada
     *  \return Nada
     */

    /** Cria uma variável para armazenar o valor da cor binária */
    int bin_color;

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            // Percorre cada elemento da matriz imagem e atribui a
            // bin_color 1 se a média dos 3 componentes (r, g, b) do
            // pixel for maior ou igual à metade da cor máxima, e 0
            // se a média for menor, atribuindo o mesmo valor a cada um
            bin_color = (img[i][j].r + img[i][j].g + img[i][j].b)/3 > comp/2,
            img[i][j].r = bin_color,
            img[i][j].g = bin_color,
            img[i][j].b = bin_color;

    /** Define a cor máxima (componente) como 1, literalmente, binárizando a imagem */
    comp = 1;
}

void img_blurring(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função de blurring
     *
     *  Desfoca a imagem atribuindo o valor da média do pixel (i, j)
     *  e todos os 8 pixels ao redor.<br>
     *  Seguindo a matriz:<br>
     *  | 1 &nbsp; 1 &nbsp; 1 | <br>
     *  | 1 &nbsp; 1 &nbsp; 1 | * 1/9 <br>
     *  | 1 &nbsp; 1 &nbsp; 1 |
     *
     *  \param img - Matriz da imagem a ser alterada
     *  \return Nada
     */

    // Cria uma matriz para armazenar a imagem original temporariamente
    Pixel tmp[MAX][MAX];

    // Copia a imagem original para a temporária
    copy_img(img, tmp);

    for (i = 1; i < h - 1; i++)
        for (j = 1; j < w - 1; j++)
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
     *  \brief Função de sharpening
     *
     *  Aumenta a clareza de detalhes da imagem subtraindo de
     *  5x o pixel (i, j) cada um dos 4 pixels laterais.<br>
     *  Seguindo a matriz:<br>
     *  | 0 &nbsp;-1 &nbsp; 0 | <br>
     *  | -1&nbsp; 5 &nbsp;-1 | <br>
     *  | 0 &nbsp;-1 &nbsp; 0 |
     *
     *  \param img - Matriz da imagem a ser alterada
     *  \return Nada
     */

    // Cria uma matriz para armazenar a imagem original temporariamente
    Pixel tmp[MAX][MAX];

    // Copia a imagem original para a temporária
    copy_img(img, tmp);

    for (i = 1; i < h - 1; i++)
        for (j = 1; j < w - 1; j++)
            img[i][j].r = 5*tmp[i][j].r - tmp[i-1][j].r - tmp[i][j-1].r - tmp[i][j+1].r - tmp[i+1][j].r,
            img[i][j].g = 5*tmp[i][j].g - tmp[i-1][j].g - tmp[i][j-1].g - tmp[i][j+1].g - tmp[i+1][j].g,
            img[i][j].b = 5*tmp[i][j].b - tmp[i-1][j].b - tmp[i][j-1].b - tmp[i][j+1].b - tmp[i+1][j].b;
}

void img_rot_left(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função de rotação em 90º para a esquerda
     *
     *  Faz a transposta da matriz da imagem e espelha verticalmente
     *
     *  \param img - Matriz da imagem a ser alterada
     *  \return Nada
     */

    int aux;

    // Cria uma matriz para armazenar a imagem original temporariamente
    Pixel tmp[MAX][MAX];

    // Copia a imagem original para a temporária
    copy_img(img, tmp);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[w-j-1][i] = tmp[i][j];

    // Faz o swap entre h e w, pois ao rotacionar, a altura troca com a largura
    aux = h, h = w, w = aux;
}

void img_rot_right(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função de rotação em 90º para a direita
     *
     *  Se considerarmos o ângulo de rotação para esquerda como x,
     *  o ângulo de rotação para esquerda se dá por x + 180º, portanto,
     *  para rotacionar a imagem para esquerda, podemos rotacioná-la para
     *  esquerda uma vez e depois rotacionar em 180º. E é isso que essa
     *  função faz.
     *
     *  \param img - Matriz da imagem a ser alterada
     *  \return Nada
     */

    // Rotaciona a imagem original 1 vez para a esquerda
    img_rot_left(img);
    // Rotaciona a imagem original em 180º
    img_rot_180(img);
}

void img_rot_180(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função de rotação em 180º
     *
     *  Para rotacionar uma imagem em 180º, poderíamos aplicar duas vezes
     *  o algoritmo de rotação para a esquerda (ou para a direita), no
     *  entanto, não há essa necessidade, pois uma imagem rotacionada em
     *  180º nada mais é do que uma imagem invertida horizontalmente e
     *  verticalmente ao mesmo tempo (flip_h + flip_v). E é isso que essa
     *  função faz.
     *
     *  \param img - Matriz da imagem a ser alterada
     *  \return Nada
     */

    // Inverte a imagem verticalmente (flip vertical)
    img_invert_v(img);
    // Inverte a imagem horizontalmente (flip horizontal)
    img_invert_h(img);
}

void img_amp(char file[], int zoom, Pixel img[MAX][MAX]) {
    /**
     *  \brief Função de ampliação da imagem
     *
     *  Para ampliar uma imagem n vezes, devemos repetir
     *  cada pixel n vezes horizontalmente e também cada
     *  linha n vezes.
     *
     *  \param file - Nome do arquivo de saída
     *  \param zoom - Zoom de ampliação da imagem
     *  \param img - Matriz da imagem a ser ampliada
     *  \return Nada
     */

    // Iteradores
    int k, l;

    strcat(file, "_amp.ppm");

    // Cria uma variável do tipo arquivo
    FILE *img_f;
    // Cria um arquivo com o nome do arquivo + '_amp.ppm'
    img_f = fopen(file, "w");

    // Cria o cabeçalho da imagem ppm
    fprintf(img_f, "%s\n", header);
    // Define as novas largura e altura da imagem (multiplicadas pelo zoom)
    fprintf(img_f, "%i %i\n", w*zoom, h*zoom);
    // Define a cor máximo (qualidade) da imagem
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i < h; i++)
        for (k = 0; k < zoom; k++)
            for (j = 0; j < w; j++)
                for (l = 0; l < zoom; l++)
                    // Trata erros básicos, como de cor negativa e/ou maior que o máximo.
                    fprintf(img_f, "%i %i %i\n",
                    (img[i][j].r > comp) ? comp : img[i][j].r,
                    (img[i][j].g > comp) ? comp : img[i][j].g,
                    (img[i][j].b > comp) ? comp : img[i][j].b);

    // Fecha o arquivo aberto
    fclose(img_f);
}

void img_red(char file[], int zoom, Pixel img[MAX][MAX]) {
    /**
     *  \brief Função de redução da imagem
     *
     *  Para reduzir uma imagem n vezes (sendo n|h e n|w),
     *  devemos atribuir à cada novo pixel da nova imagem
     *  a média dos pixels de subimagens de tamanho n x n
     *  da imagem original.
     *
     *  \param file - Nome do arquivo de saída
     *  \param zoom - Zoom de redução da imagem
     *  \param img - Matriz da imagem a ser reduzida
     *  \return Nada
     */

    // Iteradores
    int k, l;
    // Variável para armazenar o valor da área das subimagens
    int area = zoom*zoom;
    // Pixel para salvar o valor da soma dos pixels da subimagem
    Pixel sum = {0, 0, 0};

    strcat(file, "_red.ppm");

    // Cria uma variável do tipo arquivo
    FILE *img_f;
    // Cria um arquivo com o nome do arquivo + '_red.ppm'
    img_f = fopen(file, "w");

    // Cria o cabeçalho da imagem ppm
    fprintf(img_f, "%s\n", header);
    // Define as novas largura e altura da imagem (divididas pelo zoom)
    fprintf(img_f, "%i %i\n", w/zoom, h/zoom);
    // Define a cor máximo (qualidade) da imagem
    fprintf(img_f, "%i\n", comp);

    for (i = 0; i <= h-zoom; i += zoom)
        for (j = 0; j <= w-zoom; j += zoom, sum.r = 0, sum.g = 0, sum.b = 0) {
            for (k = 0; k < zoom; k++)
                for (l = 0; l < zoom; l++)
                    // Soma à sum o valor das cores de cada pixel da subimagem
                    sum.r += img[i+k][j+l].r,
                    sum.g += img[i+k][j+l].g,
                    sum.b += img[i+k][j+l].b;
            // Salva no arquivo o valor de cada pixel de soma dividido pela área
            fprintf(img_f, "%i %i %i\n",
            (sum.r/area > comp) ? comp : sum.r/area,
            (sum.g/area > comp) ? comp : sum.g/area,
            (sum.b/area > comp) ? comp : sum.b/area);
        }

    // Fecha o arquivo aberto
    fclose(img_f);
}

// Funções Extras

void img_info(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função para mostrar informações básicas da imagem
     *
     *  Função que mostra informações sobre a imagem lida
     *  Tipo do cabeçalho, largura, altura e cor máxima
     *
     *  Obs: As cores de cada pixel foram comentadas para
     *       evitar um laço muito extenso em imagens grandes
     *
     *  \param img - Matriz da imagem a ser lida
     *  \return Nada
     */

    printf("Dados da Imagem lida:\n");
    // Mostra o cabeçalho da imagem
    printf("Tipo: %s\n", header);
    // Mostra o tamanho da imagem (largura x altura)
    printf("Tamanho: %ix%i\n", w, h);
    // Mostra a cor máxima da imagem (qualidade)
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
     *  \brief Função para deixar a imagem com o efeito de Alto Relevo
     *
     *  Esse filtro pega o valor de uma posição (i + 1, j) e subtrai do
     *  valor da posição oposta (i - 1, j), substiruindo no valor central
     *  (i, j) e somando com a metade do componente para clareamento. <br>
     *  Seguindo a matriz: <br>
     *  | 0 &nbsp;-1 &nbsp; 0 | <br>
     *  | 0 &nbsp; 0 &nbsp; 0 | + component/2 <br>
     *  | 0 &nbsp; 1 &nbsp; 0 |
     */

    // Cria uma matriz para armazenar a imagem original temporariamente
    Pixel tmp[MAX][MAX];

    // Copia a imagem original para a temporária
    copy_img(img, tmp);

    for (i = 1; i < h - 1; i++)
        for (j = 0; j < w; j++)
            // Percorre cada elemento do array img e atribui à matriz
            // temporária o valor do algoritmo de alto relevo.
            tmp[i][j].r = img[i+1][j].r - img[i-1][j].r + comp/2,
            tmp[i][j].g = img[i+1][j].g - img[i-1][j].g + comp/2,
            tmp[i][j].b = img[i+1][j].b - img[i-1][j].b + comp/2;

    // Copia a matriz temporária para a matriz da imagem original
    copy_img(tmp, img);
}

void img_posterize(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função para posterizar a imagem
     *
     *  Função que lê cada componente (rgb) da cor da
     *  imagem e o altera para o seu extremo (se for
     *  menor que comp/2, vira 0, caso contrário, recebe
     *  o valor de comp).
     *
     *  \param img - Matriz da imagem a ser alterada
     *  \return Nada
     */

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            // Lê cada elemento da imagem e aplica o algoritmo
            img[i][j].r = (img[i][j].r > comp/2) ? comp: 0,
            img[i][j].g = (img[i][j].g > comp/2) ? comp: 0,
            img[i][j].b = (img[i][j].b > comp/2) ? comp: 0;
}

void img_grayscale(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função para deixar a imagem em preto e branco
     *
     *  Essa função lê cada pixel da imagem, faz a média
     *  entre os componentes (rgb) e atribui o valor da
     *  média a cada um dos componentes, deixando a imagem
     *  em preto e branco.
     *
     *  \param img - Matriz da imagem a ser alterada
     *  \return Nada
     */

    // Variável para armazenar a média dos componentes
    int pb;

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            // Faz o cálculo da média
            pb = (img[i][j].r + img[i][j].g + img[i][j].b)/3,
            // Atribui o valor da média a cada um dos componentes
            img[i][j].r = pb,
            img[i][j].g = pb,
            img[i][j].b = pb;
}

void img_negative(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função para inverter as cores da imagem (negativo)
     *
     *  Essa função lê cada pixel da imagem, e inverte a
     *  sua cor (se era branco, fica preto...) aplicando
     *  ao pixel o valor de comp menos o valor original.
     *
     *  \param img - Matriz da imagem a ser alterada
     *  \return Nada
     */

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            // Lê cada pixel da imagem e executa o algoritmo
            img[i][j].r = comp-img[i][j].r,
            img[i][j].g = comp-img[i][j].g,
            img[i][j].b = comp-img[i][j].b;
}

void img_invert_h(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função para inverter a imagem horizontalmente (flip)
     *
     *  Para inverter a imagem horizontalmente, foi
     *  utilizado uma matriz auxiliar (para armazenar a
     *  imagem original) e depois atribui a cada pixel n
     *  de cada linha da imagem original o valor do pixel
     *  largura - n - 1 (-1 pois a matriz vai de 0 até n-1).
     *
     *  \param img - Matriz da imagem a ser invertida horizontalmente
     *  \return Nada
     */

    // Cria a matriz para a imagem auxiliar
    Pixel tmp[MAX][MAX];

    // Copia a imagem original para a matriz auxiliar
    copy_img(img, tmp);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            // Atribui à imagem original (i, largura-j-1)
            // o valor da imagem auxiliar (i, j)
            img[i][w-j-1] = tmp[i][j];
}

void img_invert_v(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função para inverter a imagem verticalmente (flip)
     *
     *  Para inverter a imagem veticalmente, foi
     *  utilizado uma matriz auxiliar (para armazenar a
     *  imagem original) e depois atribui a cada pixel n
     *  de cada coluna da imagem original o valor do pixel
     *  altura - n - 1 (-1 pois a matriz vai de 0 até n-1).
     *
     *  \param img - Matriz da imagem a ser invertida veticalmente
     *  \return Nada
     */

    // Cria a matriz para a imagem auxiliar
    Pixel tmp[MAX][MAX];

    // Copia a imagem original para a matriz auxiliar
    copy_img(img, tmp);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            // Atribui à imagem original (altura - i - 1, j)
            // o valor da imagem auxiliar (i, j)
            img[h-i-1][j] = tmp[i][j];
}

void img_reflect_h(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função para refletir a imagem horizontalmente
     *
     *  Essa função faz com que a imagem fique espelhada horizontalmente,
     *  isto é, a imagem é "normal" até a sua metade (horizontal),
     *  quando começa a repetir a imagem, só que invertida, criando
     *  o efeito de ter colocado um espelho no meio da imagem.
     *
     *  \param img - Matriz da imagem a ser refletida horizontalmente
     *  \return Nada
     */

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            // Atribui a cada elemento (i, largura - j - 1)
            // o seu "correspondente" (i, j) da imagem
            img[i][w-j-1] = img[i][j];
}

void img_reflect_v(Pixel img[MAX][MAX]) {
    /**
     *  \brief Função para refletir a imagem verticalmente
     *
     *  Essa função faz com que a imagem fique espelhada verticalmente,
     *  isto é, a imagem é "normal" até a sua metade (vertical),
     *  quando começa a ser repetida, só que invertida, criando
     *  o efeito de ter colocado um espelho no meio da imagem.
     *
     *  \param img - Matriz da imagem a ser refletida verticalmente
     *  \return Nada
     */

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            // Atribui a cada elemento (altura - i - 1, j)
            // o seu "correspondente" (i, j) da imagem
            img[h-i-1][j] = img[i][j];
}

/*
 * Compressão de Imagem
 */

void img_compress(char file[], Pixel img[MAX][MAX]) {
    /**
     *  \brief Função para comprimir a imagem
     *
     *  Essa função comprime a imagem utilizando o algoritmo
     *  RLE (Run-Length Encoding), que verifica o número de
     *  pixels (rgb) repetidos sequencialmente e cria uma
     *  nova imagem com a estrutura n (r g b), no qual n
     *  representa o número de vezes que esse pixel está repetido
     *  sequencialmente.
     *
     *  \param file - Nome do arquivo de saída
     *  \param img - Matriz da imagem a ser comprimida
     *  \return Nada
     */

    // Cria a variável para contar as repetições (iniciada com 0)
    int cont = 0;
    // Cria duas variáveis do tipo pixel para comparação, sendo
    // a primeira inicializada com o primeiro pixel da imagem
    Pixel t1 = img[0][0], t2;

    strcat(file, "_compressed.ppm");

    // Cria uma variável do tipo arquivo
    FILE *img_f;
    // Cria um arquivo com o nome do arquivo + '_compressed.ppm'
    img_f = fopen(file, "w");

    // Cria o cabeçalho da imagem ppm
    fprintf(img_f, "%s\n", header);
    // Define a largura e altura da imagem
    fprintf(img_f, "%i %i\n", w, h);
    // Define a cor máximo (qualidade) da imagem e põe um c,
    // para indicar que o arquivo está comprimido
    fprintf(img_f, "%ic\n", comp);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++){
            // Atribui a t2 o conteúdo do "pixel atual" da leitura
            t2 = img[i][j];
            if (t1.r == t2.r && t1.g == t2.g && t1.b == t2.b && !(i == h-1 && j == w-1)) {
                // Se todos os componentes (rgb) de t2 forem iguais aos de t1 (pixel anterior)
                // e o pixel (i, j) não for o último pixel da imagem,
                // Incrementa o contador e pula para o próximo pixel (continue)
                cont++;
                continue;
            }
            if (t1.r == t2.r && t1.g == t2.g && t1.b == t2.b && i == h-1 && j == w-1)
                // Se todos os componentes (rgb) de t2 forem iguais aos de t1 (pixel anterior)
                // e o pixel (i, j) for o último pixel da imagem, incrementa o contador
                cont++;
            // Escreve no arquivo o valor do contador, seguido dos valores
            // dos componentes do pixel (que foi repetido contador vezes)
            fprintf(img_f, "%i(%i %i %i)\n", cont, t1.r, t1.g, t1.b);
            // O pixel anterior (de comparação) recebe o pixel atual (que
            // é diferente do anterior, pois a imagem foi escrita) e a
            // variável de contador recebe 1 (justamente o pixel t2)
            t1 = t2, cont = 1;
        }

    // Fecha o arquivo aberto
    fclose(img_f);
}

void img_uncompress(char file[]) {
    /**
     *  \brief Função para descomprimir a imagem
     *
     *  Essa função descomprime a imagem utilizando o algoritmo
     *  RLE (Run-Length Encoding) de forma reversa, lendo o número
     *  n de repetições do pixel (rgb) e repetindo n vezes o pixel
     *  na escrita de uma nova imagem (descomprimida).
     *
     *  \param file - Nome do arquivo de saída
     *  \return Nada
     */

    // Armazena o número de repetições do pixel
    int rpt;
    // Armazena os valores (rgb) do pixel lido
    Pixel p;

    strcat(file, "_uncompressed.ppm");

    // Cria uma variável do tipo arquivo
    FILE *uncomp_img;

    // Cria um arquivo com o nome do arquivo + '_compressed.ppm'
    uncomp_img = fopen(file, "w");

    // Cria o cabeçalho da imagem ppm
    fprintf(uncomp_img, "%s\n", header);
    // Define a largura e altura da imagem
    fprintf(uncomp_img, "%i %i\n", w, h);
    // Define a cor máximo (qualidade) da imagem,
    fprintf(uncomp_img, "%i\n", comp);

    while (fscanf(file_img, "%i(%i %i %i) ", &rpt, &p.r, &p.g, &p.b) != EOF)
        // Lê os valores de rpt e do pixel da imagem até
        // que o arquivo comprimido chegue ao final
        for (i = 0; i < rpt; i++)
            // Repete rpt vezes o valor do pixel
            // repetido no arquivo da nova imagem
            fprintf(uncomp_img, "%i %i %i\n", p.r, p.g, p.b);

    // Fecha o arquivo aberto
    fclose(uncomp_img);

    // Mostra para o usuário o nome da imagem final gerada
    printf("\nA imagem foi salva como %s\n", file);
}