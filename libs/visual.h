void menu() {
    printf("-------------------- MENU --------------------\n");
    printf("'rle' \t Comprimir imagem usando RLE.\n");
    printf("'neg' \t Criar o negativo da imagem.\n");
    printf("'inv' \t Inverter imagem (flip).\n");
    printf("'rlv' \t Deixar imagem em auto-relevo.\n");
    printf("'pos' \t Posterizar imagem.\n");
    printf("'peb' \t Deixar imagem em Preto e Branco.\n");
    printf("'thr' \t Binarizar imagem usando thresholding.\n");
    printf("'blu' \t Executar blurring.\n");
    printf("'sha' \t Executar sharpening.\n");
    printf("'rot' \t Rotacionar imagem.\n");
    printf("'amp' \t Ampliar imagem.\n");
    printf("'red' \t Reduzir imagem.\n\n");
    printf("'inf' \t Mostrar informações da imagem.\n");
    printf("'fim' \t Finalizar programa.\n");
    printf("----------------------------------------------\n\n");
}

void clr_screen() {
    #if defined WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void error_message(int type) {
    clr_screen();
    switch (type) {
        case 1: // Opção inválida do menu
            menu();
            printf("Você não escolheu uma opção válida. Tente novamente:\n");
            printf("O que você deseja fazer? ");
            scanf("%s", op);
            clr_screen();
            break;
        case 2: // Zoom de redução inválida
            printf("O zoom de redução deve ser múltiplo de ambos os lados (%i, %i).\n", w, h);
            break;
        case 3: // Erro de abertura de arquivo
            printf("Erro ao abrir o arquivo.\n");
            break;
        default: // Erro padrão de opção inválida
            printf("Você nao escolheu uma opção válida. Tente novamente:\n");
    }
}
