void menu() {
    printf("-------------------- MENU --------------------\n");
    printf("'inv' \t Inverter cores da imagem.\n");
    printf("'rlv' \t Deixar imagem em auto-relevo.\n");
    printf("'pop' \t Deixar a imagem no estilo pop art.\n");
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

void invalid_option(int type) {
    clr_screen();
    switch (type) {
        case 1:
            menu();
            printf("Você não escolheu uma opção válida. Tente novamente:\n");
            printf("O que você deseja fazer? ");
            scanf("%s", op);
            clr_screen();
            break;
        case 2:
            printf("O zoom de redução deve ser múltiplo de ambos os lados (%i, %i).\n", w, h);
            break;
        default:
            printf("Você nao escolheu uma opção válida. Tente novamente:\n");
    }
}
