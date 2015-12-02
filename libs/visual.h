/**
 *  \file visual.h
 *  \brief Arquivo com funções apenas de impressão na tela.
 *
 *  Arquivo com as funções de mostrar o menu, limpar tela, e mensagens de erro.
 *
 */

void menu() {
    /**
     *  \brief Função para mostrar o menu de opções para o usuário
     *
     *  Essa função serve apenas para mostrar o menu com as
     *  opções de manipulação de imagem que o usuário tem.
     *
     *  \return Nada
     */

    printf("-------------------- MENU --------------------\n");
    printf("'rle' \t Comprimir imagem usando RLE.\n");
    printf("'neg' \t Criar o negativo da imagem.\n");
    printf("'inv' \t Inverter imagem (flip).\n");
    printf("'esp' \t Espelhar imagem.\n");
    printf("'rlv' \t Deixar imagem em Alto Relevo.\n");
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
    /**
     *  \brief Função para limpar a tela
     *
     *  Essa função consegue limpar a tela do console em qualquer SO
     *
     *  \return Nada
     */

    #if defined WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void error_message(int type) {
    /**
     *  \brief Função para mostrar as mensagens de erro para cada situação
     *
     *  Essa função mostra uma determinada mensagem de erro
     *  para cada cada código de erro predefinido.
     *
     *  \param type Recebe o tipo (número) do erro
     *  \return Nada
     */

    clr_screen();
    switch (type) {
        // Erro padrão de opção inválida
        case 0:
            printf("Você nao escolheu uma opção válida. Tente novamente:\n");
            break;
        // Opção inválida do menu
        case 1:
            menu();
            printf("Você não escolheu uma opção válida. Tente novamente:\n");
            printf("O que você deseja fazer? ");
            scanf("%s", op);
            clr_screen();
            break;
        // Zoom de redução inválida
        case 2:
            printf("O zoom de redução deve ser múltiplo de ambos os lados (%i, %i).\n", w, h);
            break;
        // Erro de abertura de arquivo
        case 3:
            printf("Erro ao abrir o arquivo.\n");
            break;
        // Erro desconhecido
        default:
            printf("Ocorreu um erro desconhecido.\n");
    }
}
