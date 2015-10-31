void menu() {
    printf("-------------------- MENU --------------------\n");
    printf("'inf' \t mostrar informacoes da imagem.\n");
    printf("'inv' \t inverter cores da imagem.\n");
    printf("'rlv' \t deixar imagem em auto-relevo.\n");
    printf("'peb' \t deixar imagem em Preto e Branco.\n");
    printf("'pop' \t deixar a imagem no estilo pop art.\n");
    printf("'thr' \t binarizar imagem usando thresholding.\n");
    printf("'blu' \t executar blurring.\n");
    printf("'sha' \t executar sharpening.\n");
    printf("'rot' \t rotacionar imagem.\n");
    printf("'amp' \t ampliar imagem.\n");
    printf("'red' \t reduzir imagem.\n\n");
    printf("'fim' \t finalizar programa.\n");
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
