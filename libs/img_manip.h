/**
 *  \file img_manip.h
 *  \brief Arquivo com as funções principais do programa.
 *
 *  Arquivo com todas as constantes, variáveis e estruturas globais.
 *
 */

#include "global.h" /** Constantes, variáveis e typedefs globais */
#include "headers.h" /** Inicialização das funções para evitar erros de declaração implícita */
#include "visual.h" /** Funções com o intuito "visual" */
#include "functions.h" /** Funções de processamento e manipulação da imagem */


void choice(Pixel img[w][h]) {
    /**
     * Função para verificar a opção escolhida
     * no menu e chamar sua respectiva função
     */

    /** Percorre cada elemento de op[] e converte para minúsculo */
    for(i = 0; i < strlen(op); i++)
        op[i] = tolower(op[i]);

    if (!strcmp(op, "fim"))
        /** Se a opção escolhida foi fim, finaliza o programa */
        return;
    if (!strcmp(op, "inf")) {
        /** Se a opção escolhida foi inf, chama a função img_info() */
        printf("Exibindo informações da imagem...\n");
        img_info(img);
    }else if (!strcmp(op, "neg")) {
        /** Se a opção escolhida foi neg, chama a função img_negative() */
        printf("Criando o negativo da imagem...\n");
        img_negative(img);
        /** Cria um novo arquivo ppm com as alterações feitas */
        build_img(file_name, img);
    }else if (!strcmp(op, "rlv")) {
        /** Se a opção escolhida foi rlv, chama a função img_emboss() */
        printf("Executando alto-relevo...\n");
        img_emboss(img);
        /** Cria um novo arquivo ppm com as alterações feitas */
        build_img(file_name, img);
    }else if (!strcmp(op, "pos")) {
        /** Se a opção escolhida foi pos, chama a função img_posterize() */
        printf("Executando Posterização...\n");
        img_posterize(img);
        /** Cria um novo arquivo ppm com as alterações feitas */
        build_img(file_name, img);
    }else if (!strcmp(op, "thr")) {
        /** Se a opção escolhida foi thr, chama a função img_thresholding() */
        printf("Executando thresholding...\n");
        img_thresholding(img);
        /** Cria um novo arquivo ppm com as alterações feitas */
        build_img(file_name, img);
    }else if (!strcmp(op, "peb")) {
        /** Se a opção escolhida foi peb, chama a função img_grayscale() */
        printf("Deixando em Preto e Branco...\n");
        img_grayscale(img);
        /** Cria um novo arquivo ppm com as alterações feitas */
        build_img(file_name, img);
    }else if (!strcmp(op, "blu")) {
        /** Se a opção escolhida foi blu, chama a função img_blurring() */
        printf("Executando blurring...\n");
        img_blurring(img);
        /** Cria um novo arquivo ppm com as alterações feitas */
        build_img(file_name, img);
    }else if (!strcmp(op, "sha")) {
        /** Se a opção escolhida foi sha, chama a função img_sharpening() */
        printf("Executando sharpening...\n");
        img_sharpening(img);
        /** Cria um novo arquivo ppm com as alterações feitas */
        build_img(file_name, img);
    }else if (!strcmp(op, "inv")) {
        /** Cria uma variável para armazenar a direção da inversão */
        char dir;
        /** Lê a direção da inversão */
        printf("Digite o tipo de inversão [h: horizontal ou v: vertical]: ");
        scanf(" %c", &dir);
        if(dir == 'h') {
            /** Se a direção escolhida foi h, chama a função img_invert_h() */
            img_invert_h(img);
            /** Concatena a operação realizada com "_h" \
               para alterar o nome do arquivo de saída */
            strcat(op, "_h");
        }else if(dir == 'v') {
            /** Se a direção escolhida foi v, chama a função img_invert_v() */
            img_invert_v(img);
            /** Concatena a operação realizada com "_v" \
               para alterar o nome do arquivo de saída */
            strcat(op, "_v");
        }else {
            /** Se a opção escolhida não for válida, mostra uma mensagem de erro */
            error_message(0);
            /** Recursão para ler novamente até que a opção escolhida seja válida */
            choice(img);
            return;
        }
        printf("Invertendo imagem...\n");
        /** Cria um novo arquivo ppm com as alterações feitas */
        build_img(file_name, img);
    }else if (!strcmp(op, "esp")) {
        /** Cria uma variável para armazenar a direção do espelhamento */
        char dir;
        /** Lê a direção do espelhamento */
        printf("Digite o tipo de espelhamento [h: horizontal ou v: vertical]: ");
        scanf(" %c", &dir);
        if(dir == 'h') {
            /** Se a direção escolhida foi h, chama a função img_reflect_h() */
            img_reflect_h(img);
            /** Concatena a operação realizada com "_h" \
               para alterar o nome do arquivo de saída */
            strcat(op, "_h");
        }else if(dir == 'v') {
            /** Se a direção escolhida foi v, chama a função img_reflect_v() */
            img_reflect_v(img);
            /** Concatena a operação realizada com "_v" \
               para alterar o nome do arquivo de saída */
            strcat(op, "_v");
        }else {
            /** Se a opção escolhida não for válida, mostra uma mensagem de erro */
            error_message(0);
            /** Recursão para ler novamente até que a opção escolhida seja válida */
            choice(img);
            return;
        }
        printf("Espelhando imagem...\n");
        /** Cria um novo arquivo ppm com as alterações feitas */
        build_img(file_name, img);
    }else if (!strcmp(op, "rot")) {
        /** Cria uma variável para armazenar o ângulo/direção de rotação */
        char ang[3];
        /** Lê o ângulo/direção de rotação */
        printf("Digite o tipo de rotação [dir, esq, 180]: ");
        scanf("%s", ang);
        if(!strcmp(ang, "dir")) {
            /** Se o ângulo/direção escolhido for dir, chama a função img_rot_right() */
            img_rot_right(img);
        }else if(!strcmp(ang, "180")) {
            /** Se o ângulo/direção escolhido for 180, chama a função img_rot_180() */
            img_rot_180(img);
        }else if(!strcmp(ang, "esq")) {
            /** Se o ângulo/direção escolhido for esq, chama a função img_rot_left() */
            img_rot_left(img);
        }else {
            /** Se o ângulo/direção escolhido for inválido, mostra uma mensagem de erro */
            error_message(0);
            /** Recursão para ler novamente até que a opção escolhida seja válida */
            choice(img);
            return;
        }
        printf("Rotacionando Imagem...\n");
        /** Concatena a operação realizada com '_' e com o ângulo/direção \
           escolhida para alterar o nome do arquivo de saída */
        strcat(strcat(op, "_"), ang);
        /** Cria um novo arquivo ppm com as alterações feitas */
        build_img(file_name, img);
    }else if (!strcmp(op, "amp")) {
        /** Cria uma variável para armazenar o valor do zoom (ampliação) */
        int zoom;
        /** Lê o valor do zoom */
        printf("Digite o zoom: ");
        scanf("%i", &zoom);
        printf("Ampliando Imagem...\n");
        /** Chama a função img_amp(), que já cria diretamente uma nova imagem */
        img_amp(file_name, zoom, img);
    }else if (!strcmp(op, "red")) {
        /** Cria uma variável para armazenar o valor do zoom (redução) */
        int zoom;
        /** Lê o valor do zoom */
        printf("Digite o zoom: ");
        scanf("%i", &zoom);
        /** Verifica se o valor informado é congruente às dimensões do arquivo */
        if(h%zoom == 0 && w%zoom == 0) {
            /** Se for, chama a função img_red(), que já cria diretamente uma nova imagem */
            printf("Reduzindo Imagem...\n");
            img_red(file_name, zoom, img);
        }else {
            /** Caso contrário, mostra uma mensagem de erro */
            error_message(2);
            /** Recursão para ler novamente até que a opção escolhida seja válida */
            choice(img);
            return;
        }
    }else if (!strcmp(op, "rle")) {
        /** Se a opção escolhida foi rle (compactação da imagem), chama a função \
           img_compress(), que já cria diretamente o arquivo de saída (compactado) */
        printf("Comprimindo Imagem...\n");
        img_compress(file_name, img);
    }else {
        /** Caso o usuário tenha escolhido uma opção inválida, mostra uma mensagem de erro */
        error_message(1);
        /** Recursão para ler novamente até que a opção escolhida seja válida */
        choice(img);
    }
}

void skip_comments() {
    /*
     * Função para ignorar os comentários da imagem durante a sua leitura
     */

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
    /*
     * Função para ler as cores de cada pixel do arquivo ppm
     */

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
    /*
     * Função "principal" que processa a imagem ppm
     * e direciona o usuário para outras funções
     */

    /** Variável para verificar se a imagem lida está comprimida */
    char compressed;

    /** Faz uma cópia do nome do arquivo sem extensão */
    strcpy(file_name, file);

    /** Lê o arquivo ppm (nome lido concatenado com a extensão ".ppm") */
    file_img = fopen(strcat(file,".ppm"), "r");

    /** Verifica se o arquivo existe */
    if (file_img == NULL) {
        /** Se não existir, mostra uma mensagem de erro e finaliza o programa */
        error_message(3);
        return;
    }

    /** Lê o cabeçalho da imagem ignorando comentários */
    skip_comments();
    fscanf(file_img, "P3 ");
    /** Lê a largura da imagem ignorando comentários */
    skip_comments();
    fscanf(file_img, "%i ", &w);
    /** Lê a altura da imagem ignorando comentários */
    skip_comments();
    fscanf(file_img, "%i ", &h);
    /** Lê a cor máxima (qualidade) da imagem e o caractere de compressão ignorando comentários */
    skip_comments();
    fscanf(file_img, "%i%c", &comp, &compressed);
    skip_comments();

    /** Verifica se as variáveis lidas não são nulas */
    if (!w || !h || !comp) {
        /** Se alguma for, mostra uma mensagem de erro, fecha \
           a leitura do arquivo e finaliza o programa */
        error_message(3);
        fclose(file_img);
        return;
    }

    /** Define, com uma comparação ternária, o valor máximo de altura/largura \
       a fim de evitar erros de segmentação (Segmentation fault) na matriz */
    MAX = (w > h) ? w : h;

    /** Cria a imagem como uma matriz de pixels (tamanho MAX x MAX) */
    Pixel image[MAX][MAX];

    /** Verifica se a imagem está comprimida */
    if (compressed == 'c') {
        /** Cria uma variável para armazenar a escolha do usuário */
        int c;
        /** Lê a escolha do usuário */
        printf("A imagem selecionada está comprimida.\n");
        do {
            printf("Deseja descomprimir? [1 - Sim / 0 - Não] ");
            scanf("%i", &c);
        } while (c != 1 && c != 0);
        /** Verifica se o usuário quer descomprimir a imagem */
        if (c)
            /** Chama a função para descompressão */
            img_uncompress(file_name, image);
        /** Fecha a leitura do arquivo e finaliza programa */
        fclose(file_img);
        return;
    /** Verifica se a imagem não estã comprimida e é válida */
    }else if (compressed == ' ' || compressed == '\n') {
        /** Lê a imagem */
        read_ppm(image);
    /** Caso a imagem não seja válida */
    }else {
        /** Mostra uma mensagem de erro, fecha a leitura do arquivo e finaliza o programa */
        error_message(3);
        fclose(file_img);
        return;
    }

    /** Fecha a leitura do arquivo */
    fclose(file_img);

    /** Mostra o menu de opções */
    menu();
    /** Lê a opção escolhida */
    printf("O que você deseja fazer? ");
    scanf("%s", op);
    /** Limpa a tela */
    clr_screen();
    /** Chama a função choice() para enviar o usuário para a opção escolhida */
    choice(image);
}
