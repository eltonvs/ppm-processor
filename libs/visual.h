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
    printf("'inf' \t Mostrar informacoes da imagem.\n");
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
    if (type == 1) {
        menu();
        printf("Voce nao escolheu uma opcao valida. Tente novamente:\n");
        printf("O que voce deseja fazer? ");
        scanf("%s", op);
        clr_screen();
    }else if (type == 2) {
        printf("Voce nao escolheu uma opcao valida. Tente novamente:\n");
    }else if (type == 3) {
        printf("O zoom de reducao deve ser um multiplo dos lados (%i, %i).\n", w, h);
    }
}
