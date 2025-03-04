#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int tabuleiro [10] [10];                                //MATRIZ DO TABULEIRO
int navio1 [3] = {3,3,3};                               //VETOR QUE GRAVA POSIÇÃO DO NAVIO 1
int navio2 [3] = {3,3,3};                               //VETOR QUE GRAVA POSIÇÃO DO NAVIO 2
int selectLinha;                                        //VARIÁVEL USADA NA LÓGICA PARA GRAVAÇÃO DE NAVIO
int selectColuna;                                       //VARIÁVEL USADA NA LÓGICA PARA GRAVAÇÃO DE NAVIO
int chave = 1;                                          //VARIÁVEL USADA NA LÓGICA PARA SABER SE O PROGRAMA DEVE RODAR OU GRAVAR;
int cone [3] [5];
int cruz [3] [5];
int octaedro [3] [3];

void configCone ()
{
    // ATRIBUINDO VALORES À MATRIZ CONE;
    for (int i = 0; i < 3; i++)            // LINHA
    {
        for (int j = 0; j < 5; j++)        // COLUNA
        {
            if (i == 0 && j == 2)
            {
                cone [i] [j] = 1;          // QUANDO CHEGAR NO ENDEREÇO CONE [0] [2] IRÁ ATRIBUIR O VALOR '1' A ESTE.       00100
            }
            if ((i == 1) && (j>=1 && j<=3))
            {
                cone [i] [j] = 1;          // QUANDO ESTIVER NA LINHA 1 E COLUNAS 1,2 E 3, IRÁ ATRIBUIR O VALOR 1 A ELES.   01110
            }
            if (i == 2)
            {
                cone [i] [j] = 1;          // QUANDO CHEGAR NA LINHAS 2, IRÁ ATRIBUIR O VALOR '1' A TODAS AS COLUNAS        11111
            }
        }
    }
}

void configCruz ()
{
    // ATRIBUINDO VALORES À MATRIZ CRUZ;
    for (int i = 0; i < 3; i++)            // LINHA
    {
        for (int j = 0; j < 5; j++)        // COLUNA
        {
            if ((i == 0 || i == 2) && (j == 2))
            {
                cruz [i] [j] = 1;          // QUANDO CHEGAR NA LINHA 0 OU 2 E ESTANDO NA COLUNA 2, IRÁ ATRIBUIR O VALOR '1'        00100
            }
            if (i == 1)
            {
                cruz [i] [j] = 1;          // QUANDO ESTIVER NA LINHA 1 IRÁ ATRIBUIR O VALOR 1 A TODAS AS COLUNAS.                 11111
            }
        }
    }

}

void configOctaedro ()
{
    // ATRIBUINDO VALORES À MATRIZ OCTAEDRO;
    for (int i = 0; i < 3; i++)            // LINHA
    {
        for (int j = 0; j < 3; j++)        // COLUNA
        {
            if ((i == 0 || i == 2) && j == 1)
            {
                octaedro [i] [j] = 1;          // QUANDO CHEGAR NA COLUNA 1 E ESTIVER NA LINHA 0 OU 2 IRÁ ATRIBUIR O VALOR '1' A ELES     010
            }
            if (i == 1)
            {
                octaedro [i] [j] = 1;          // QUANDO ESTIVER NA LINHA 1 IRÁ ATRIBUIR O VALOR '1' A TODAS AS COLUNAS                   111
            }
        }
    }
}


// FUNÇÃO QUE GRAVA O VALOR 0 EM TODAS OS ENDEREÇOS DA MATRIZ 'TABULEIRO'
void zerarTabuleiro ()
{
    for (int i = 0; i < 10; i++)            // LINHA
    {
        for (int j = 0; j < 10; j++)        // COLUNA
        {
            tabuleiro [i] [j] = 0;          //  LOOP VAI FAZER A MATRIZ 'TABULEIRO' PASSAR POR TODOS OS ENDEREÇOS ATRAVÉS
        }                                   //  DAS VARIÁVEIS I E J, ATRIBUINDO O VALOR 0 A TODOS ELES.
    }
}


// FUNÇÃO QUE IMPRIME TODOS OS ENDEREÇOS GRAVADOS NA MATRIZ TABULEIRO;
void imprimirTabuleiro()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d  ", tabuleiro [i] [j]);      //  LOOP VAI FAZER A MATRIZ 'TABULEIRO' PASSAR POR TODOS OS ENDEREÇOS ATRAVÉS
        }                                           //  DAS VARIÁVEIS I E J, ATRIBUINDO O VALOR 0 A TODOS ELES.
        printf("\n");
    }
}


// FUNÇÃO QUE TESTA SE PODE GRAVAR, SE NÃO TEM GRAVAÇÃO NO LOCAL E POR FIM GRAVARÁ O NAVIO NA POSIÇÃO ESCOLHIDA NA LINHA;
void horizontal()
{
    int coluna;
    coluna = selectColuna;  // VARIÁVEL 'COLUNA' RECEBE O VALOR DA VARIÁVEL 'SELECTCOLUNA' PARA QUE O VALOR DESTE NÃO ALTERE.

/*
     COMO A GRAVAÇÃO DESTA FUNÇÃO É EM HORIZONTAL, TEMOS QUE TOMAR CUIDADO COM O LOCAL QUE SE INICIA A GRAVAÇÃO
     PARA QUE SUPORTE CORRETAMENTE O TAMANHO DO NAVIO NA MATRIZ. PARA QUE ISSO FUNCIONE PERFEITAMENTE, APENAS SERÁ FEITA A GRAVAÇÃO
     SE ESTA SE INICIAR NA COLUNA 0 ATÉ A COLUNA 7 (CONSIDERANDO O TAMANHO DO NAVIO DE 3 ESPAÇOS) E NA LINHA 0 ATÉ A 9.
     CASO A GRAVAÇÃO SE INICIE NA COLUNA 8 OU 9, O NAVIO FICARÁ IMCOMPLETO.
     LEMBRE-SE DE QUE A GRAVAÇÃO COMEÇARA EM DIREÇÃO VERTICAL DA ESQUERDA PARA A DIREITA.
*/
    if ((selectColuna < 8) && (selectLinha <10)) // PERMITE GRAVAÇÃO (HORIZONTAL) ATÉ A COLUNA 7 E EM QUALQUER LINHA DA MATRIZ 10X10.
    {
        //ESTE LOOP VERIFICA SE NA POSIÇÃO SELECIONADA NO CÓDIGO 'SELECTLINHA' E 'SELECTCOLUNA' JÁ TEM ALGUMA GRAVAÇÃO.
        for (int j = 0; j < 3; j++)
        {
            // NESTA LÓGICA O LOOP EXECUTARÁ 3X. IRÁ VERIFICAR SE NA LINHA E COLUNA SELECIONADA JÁ TEM O VALOR 3 GRAVADO.
            // APÓS TESTAR A CONDIÇÃO, A VARIÁVEL COLUNA SERA ACRESCENTADA +1,E ENTÃO TESTARA A MESMA LINHA, PORÉM COM A COLUNA SUBSEQUENTE.
            // SENDO ASSIM O LOOP TESTARÁ AS TRÊS POSIÇÕES AONDE SERÁ GRAVADO O NAVIO.
            // CASO JÁ HOUVER GRAVAÇÃO NO LOCAL DESEJADO, SERA ATRIBUIDO O VALOR 3 À VARIAVEL CHAVE;
            if (tabuleiro [selectLinha] [coluna] == 3)
            {
                chave=3;
            }
            ++coluna;
        }
        // EXECUTARÁ CASO NO LOCAL DESEJADO DA GRAVAÇÃO JÁ HOUVESSE UM NAVIO NO LOCAL E ENTÃO EXIBIRÁ A MENSAGEM ABAIXO.
        if (chave == 3)
        {
            printf("Posição indisponível\n\n");
        }
        /*
        SE NÃO HOUVER UM NAVIO NO LOCAL DESEJADO DA GRAVAÇÃO, A VARIAVEL 'CHAVE' CONTINUARÁ COM O VALOR 1 E IRA REALIZAR A GRAVAÇÃO
        DO NAVIO NO LOCAL DESEJADO.
        */
        if (chave == 1)
        {
            //NESTE LOOP SERÁ REALIZADO A GRAVAÇÃO DO NAVIO NO LOCAL DESEJADO. SERÁ EXECUTADO 3X FIXANDO A LINHA E ALTERANDO APENAS
            //AS COLUNAS, GRAVANDO EM CADA ENDEREÇO O VALOR 3;
            for (int j = 0; j < 3; j++)
            {
                tabuleiro [selectLinha] [selectColuna] = 3;
                ++selectColuna;
            }
        }
    }
    else  // CASO O TAMANHO DA MATRIZ NÃO SUPORTE O LOCAL QUE INICIARÁ A GRAVAÇÃO, SERA GRAVADO A MENSAGEM ABAIXO.
    {
        printf("Posição indisponível\n\n");
        chave = 3; //PARA INFORMAR QUE A POSIÇÃO ESTA INDISPONÍVEL.
    }
}


// FUNÇÃO QUE TESTA SE PODE GRAVAR, SE NÃO TEM GRAVAÇÃO NO LOCAL E POR FIM GRAVARÁ O NAVIO NA POSIÇÃO ESCOLHIDA NA COLUNA;
void vertical()
{
    int linha;
    linha = selectLinha;   // VARIÁVEL 'COLUNA' RECEBE O VALOR DA VARIÁVEL 'SELECTCOLUNA' PARA QUE O VALOR DESTE NÃO ALTERE.

/*
     COMO A GRAVAÇÃO DESTA FUNÇÃO É EM VERTICAL, TEMOS QUE TOMAR CUIDADO COM O LOCAL QUE SE INICIA A GRAVAÇÃO
     PARA QUE SUPORTE CORRETAMENTE O TAMANHO DO NAVIO NA MATRIZ. PARA QUE ISSO FUNCIONE PERFEITAMENTE, APENAS SERÁ FEITA A GRAVAÇÃO
     SE ESTA SE INICIAR NA LINHA 0 ATÉ A LINHA 7 (CONSIDERANDO O TAMANHO DO NAVIO DE 3 ESPAÇOS) E NA COLUNA 0 ATÉ A 9.
     CASO A GRAVAÇÃO SE INICIE NA LINHA 8 OU 9, O NAVIO FICARÁ IMCOMPLETO.
     LEMBRE-SE DE QUE A GRAVAÇÃO COMEÇARA EM DIREÇÃO VERTICAL DE CIMA PARA BAIXO.
*/

    if ((selectColuna < 10) && (selectLinha <8)) // PERMITE GRAVAÇÃO (VERTICAL) ATÉ A LINHA 7 E EM QUALQUER COLUNA DA MATRIZ 10X10.
    {
        //ESTE LOOP VERIFICA SE NA POSIÇÃO SELECIONADA NO CÓDIGO 'SELECTLINHA' E 'SELECTCOLUNA' JÁ TEM ALGUMA GRAVAÇÃO.
        for (int j = 0; j < 3; j++)
        {
            // NESTA LÓGICA O LOOP EXECUTARÁ 3X. IRÁ VERIFICAR SE NA LINHA E COLUNA SELECIONADA JÁ TEM O VALOR 3 GRAVADO.
            // APÓS TESTAR A CONDIÇÃO, A VARIÁVEL LINHA SERA ACRESCENTADA +1, E ENTÃO TESTARA A MESMA COLUNA, PORÉM COM A LINHA SUBSEQUENTE.
            // SENDO ASSIM O LOOP TESTARÁ AS TRÊS POSIÇÕES AONDE SERÁ GRAVADO O NAVIO.
            // CASO JÁ HOUVER GRAVAÇÃO NO LOCAL DESEJADO, SERA ATRIBUIDO O VALOR 3 À VARIAVEL CHAVE;
            if (tabuleiro [linha] [selectColuna] == 3)
            {
                chave=3;
            }

        ++linha;

        // EXECUTARÁ CASO NO LOCAL DESEJADO DA GRAVAÇÃO JÁ HOUVESSE UM NAVIO NO LOCAL E ENTÃO EXIBIRÁ A MENSAGEM ABAIXO.
        }
        if (chave == 3)
        {
            system("cls");
            printf("Posição indisponível\n\n");
        }
        /*
        SE NÃO HOUVER UM NAVIO NO LOCAL DESEJADO DA GRAVAÇÃO, A VARIAVEL 'CHAVE' CONTINUARÁ COM O VALOR 1 E IRA REALIZAR A GRAVAÇÃO
        DO NAVIO NO LOCAL DESEJADO.
        */
        if (chave == 1)
        {
            //NESTE LOOP SERÁ REALIZADO A GRAVAÇÃO DO NAVIO NO LOCAL DESEJADO. SERÁ EXECUTADO 3X FIXANDO A COLUNA E ALTERANDO APENAS
            //AS LINHAS, GRAVANDO EM CADA ENDEREÇO O VALOR 3;
            for (int j = 0; j < 3; j++)
            {
                tabuleiro [selectLinha] [selectColuna] = 3;
                ++selectLinha;
            }
        }
    }
    else // CASO O TAMANHO DA MATRIZ NÃO SUPORTE O LOCAL QUE INICIARÁ A GRAVAÇÃO, SERA GRAVADO A MENSAGEM ABAIXO.
    {
        printf("Posição indisponível\n\n");
        chave = 3; //PARA INFORMAR QUE A POSIÇÃO ESTA INDISPONÍVEL.
    }
}

// FUNÇÃO QUE TESTA SE PODE GRAVAR, SE NÃO TEM GRAVAÇÃO NO LOCAL E POR FIM GRAVARÁ O NAVIO NA POSIÇÃO ESCOLHIDA NA LINHA E COLUNA;
void diagonal()
{
    int coluna;
    int linha;
    coluna = selectColuna;  // VARIÁVEL 'COLUNA' RECEBE O VALOR DA VARIÁVEL 'SELECTCOLUNA' PARA QUE O VALOR DESTE NÃO ALTERE.
    linha = selectLinha;     // VARIÁVEL 'LINHA' RECEBE O VALOR DA VARIÁVEL 'SELECTLINHA' PARA QUE O VALOR DESTE NÃO ALTERE.

/*
     COMO A GRAVAÇÃO DESTA FUNÇÃO É EM DIAGONAL, TEMOS QUE TOMAR CUIDADO COM O LOCAL QUE SE INICIA A GRAVAÇÃO
     PARA QUE SUPORTE CORRETAMENTE O TAMANHO DO NAVIO NO TABULEIRO. PARA QUE ISSO FUNCIONE PERFEITAMENTE, APENAS SERÁ FEITA A GRAVAÇÃO
     SE ESTA SE INICIAR NA COLUNA 0 ATÉ A COLUNA 7 (CONSIDERANDO O TAMANHO DO NAVIO DE 3 ESPAÇOS) E NA LINHA 0 ATÉ A 7.
     CASO A GRAVAÇÃO SE INICIE NA COLUNA OU LINHA 8 OU 9, O NAVIO FICARÁ IMCOMPLETO.
     LEMBRE-SE DE QUE A GRAVAÇÃO IRÁ EM DIREÇÃO DIAGONAL (PARA BAIXO E PARA DIREITA SIMULTÂNEAMENTE.
*/
    if ((selectColuna < 8) && (selectLinha <8)) // PERMITE GRAVAÇÃO (DIAGONAL) ATÉ A COLUNA 7 E ATÉ A LINHA 7.
    {
        //ESTE LOOP VERIFICA SE NA POSIÇÃO SELECIONADA NO CÓDIGO 'SELECTLINHA' E 'SELECTCOLUNA' JÁ TEM ALGUMA GRAVAÇÃO.
        for (int j = 0; j < 3; j++)
        {
            // NESTA LÓGICA O LOOP EXECUTARÁ 3X. IRÁ VERIFICAR SE NA LINHA E COLUNA SELECIONADA JÁ TEM O VALOR 3 GRAVADO.
            // APÓS TESTAR A CONDIÇÃO, A VARIÁVEL COLUNA E LINHA SERA ACRESCENTADA +1,E ENTÃO TESTARA A LINHA E A COLUNA SUBSEQUENTE.
            // SENDO ASSIM O LOOP TESTARÁ AS TRÊS POSIÇÕES AONDE SERÁ GRAVADO O NAVIO.
            // CASO JÁ HOUVER GRAVAÇÃO NO LOCAL DESEJADO, SERA ATRIBUIDO O VALOR 3 À VARIAVEL CHAVE;
            if (tabuleiro [linha] [coluna] == 3)
            {
                chave=3;
            }
            ++coluna;
            ++linha;
        }
        // EXECUTARÁ CASO NO LOCAL DESEJADO DA GRAVAÇÃO JÁ HOUVESSE UM NAVIO NO LOCAL E ENTÃO EXIBIRÁ A MENSAGEM ABAIXO.
        if (chave == 3)
        {
            printf("Posição indisponível\n\n");
        }
        /*
        SE NÃO HOUVER UM NAVIO NO LOCAL DESEJADO DA GRAVAÇÃO, A VARIAVEL 'CHAVE' CONTINUARÁ COM O VALOR 1 E IRA REALIZAR A GRAVAÇÃO
        DO NAVIO NO LOCAL DESEJADO.
        */
        if (chave == 1)
        {
        //NESTE LOOP SERÁ REALIZADO A GRAVAÇÃO DO NAVIO NO LOCAL DESEJADO. SERÁ EXECUTADO 3X SUBSEQUENTE AO ENDEREÇO INICIAL
        //ESCOLHIDO ANTERIORMENTE ATRAVÉS DAS VARIÁVEIS SELECTLINHA E SELECTCOLUNA. CADA EXECUÇÃO DO LOOP PULARÁ PARA PRÓXIMA LINHA E COLUNA;
            for (int j = 0; j < 3; j++)
            {
                tabuleiro [selectLinha] [selectColuna] = 3;
                ++selectColuna;
                ++selectLinha;
            }
        }
    }
    else  // CASO O TAMANHO DA MATRIZ NÃO SUPORTE O LOCAL QUE INICIARÁ A GRAVAÇÃO, SERA GRAVADO A MENSAGEM ABAIXO.
    {
        printf("Posição indisponível\n\n");
        chave = 3; //PARA INFORMAR QUE A POSIÇÃO ESTA INDISPONÍVEL.
    }
}

void habCONE()
{
    int soma;     // VARIÁVEL QUE VAI AJUDAR NA LÓGICA
    int coluna;
    int linha;

    linha = selectLinha;         //VARIAVEL LINHA RECEBE O VALOR DE SELECTLINHA
    coluna = selectColuna - 2;   //VARIÁVEL QUE RECEBE O VALOR DE SELECTCOLUNA -2 PARA FICAR MAIS FACIL DE INTERPRETAR A LÓGICA
                                // SENDO ASSIM O ENDEREÇO DE ORIGEM SMP SERÁ LINHA 0 E COLUNA 0;

    if ((coluna >= 0 && coluna <=5) && (linha >= 0 && linha <= 7)) //CONDIÇÃO PARA QUE A HABILIDADE NÃO EXCEDA OS LIMITES DA MATRIZ TABULEIRO
    {
        /*
            NESTA LÓGICA SERA USADO LOOPS ANINHADOS PARA PASSAR POR 3 LINHAS E POR 5 COLUNAS, SOMANDO AS MATRIZES TABULEIRO E CONE.
        */
        for (int i = 0; i < 3; i++)  // PASSARÁ 3X (PASSARÁ POR TRÊS LINHAS)
        {
            for (int j = 0; j < 5; j++) // PASSARÁ 5X (PASSARÁ POR 5 COLUNAS)
            {
                /*
                    A VARIÁVEL 'SOMA' IRA PEGAR O VALOR DA VARIÁVEL CONE  SOMADO COM A VARIÁVEL TABULEIRO PARA SABER SE NO ENDEREÇO DESEJADO
                    HÁ UM NAVIO, UMA HABILIDADE OU UMA HABILIDADE ATINGINDO UM NAVIO.
                */
                soma = tabuleiro [linha] [coluna] + cone [i] [j];
                if (soma == 4) // SIGNIFICA QUE TEM UMA HABILIDADE E UM NAVIO NO MESMO ENDEREÇO. MUDA O VALOR DESTE ENDEREÇO PARA 5
                {
                    soma = 5;
                }
                if (soma == 2) // SIGNIFICA QUE TEM DUAS HABILIDADES NO MESMO ENDEREÇO, VOLTA O VALOR PARA '1'
                {
                    soma = 1;
                }
                tabuleiro [linha] [coluna] = soma; // A MATRIZ TABULEIRO, NO ENDEREÇO DEFINIDO ANTERIORMENTE PELO CÓDIGO, RECEBE O VALOR DE 'SOMA'
                coluna++; // ACRESCENTA MAIS 1 NA VARIÁVEL COLUNA PARA SE PASSAR NAS 5 COLUNAS
            }
            coluna = selectColuna - 2; // RETORNA O VALOR DE 'COLUNA' PARA O ENDEREÇO INICIAL. PARA REPETIR NA PRÓXIMA LINHA.
            linha++; // PULA PARA PRÓXIMA LINHA
        }
    }
}

void habCRUZ()
{
    int soma;     // VARIÁVEL QUE VAI AJUDAR NA LÓGICA
    int coluna;
    int linha;

    linha = selectLinha - 1;      //VARIAVEL LINHA RECEBE O VALOR DE SELECTLINHA -1 PARA FICAR MAIS FACIL DE INTERPRETAR A LÓGICA
    coluna = selectColuna - 2;   //VARIÁVEL QUE RECEBE O VALOR DE SELECTCOLUNA -2 PARA FICAR MAIS FACIL DE INTERPRETAR A LÓGICA
                                // SENDO ASSIM O ENDEREÇO DE ORIGEM SMP SERÁ LINHA 0 E COLUNA 0;

    if ((coluna >= 0 && coluna <=5) && (linha >= 0 && linha <= 7)) //CONDIÇÃO PARA QUE A HABILIDADE NÃO EXCEDA OS LIMITES DA MATRIZ TABULEIRO
    {
        /*
            NESTA LÓGICA SERA USADO LOOPS ANINHADOS PARA PASSAR POR 3 LINHAS E POR 5 COLUNAS, SOMANDO AS MATRIZES TABULEIRO E CRUZ.
        */
        for (int i = 0; i < 3; i++)  // PASSARÁ 3X (PASSARÁ POR TRÊS LINHAS)
        {
            for (int j = 0; j < 5; j++) // PASSARÁ 5X (PASSARÁ POR 5 COLUNAS)
            {
                /*
                    A VARIÁVEL 'SOMA' IRA PEGAR O VALOR DA VARIÁVEL CRUZ  SOMANDO COM A VARIÁVEL TABULEIRO PARA SABER SE NO ENDEREÇO DESEJADO
                    HÁ UM NAVIO, UMA HABILIDADE OU UMA HABILIDADE ATINGINDO UM NAVIO.
                */
                soma = tabuleiro [linha] [coluna] + cruz [i] [j];
                if (soma == 4) // SIGNIFICA QUE TEM UMA HABILIDADE E UM NAVIO NO MESMO ENDEREÇO. MUDA O VALOR DESTE ENDEREÇO PARA 5
                {
                    soma = 5;
                }
                if (soma == 2) // SIGNIFICA QUE TEM DUAS HABILIDADES NO MESMO ENDEREÇO, VOLTA O VALOR PARA '1'
                {
                    soma = 1;
                }
                tabuleiro [linha] [coluna] = soma; // A MATRIZ TABULEIRO, NO ENDEREÇO DEFINIDO ANTERIORMENTE PELO CÓDIGO, RECEBE O VALOR DE 'SOMA'
                coluna++; // ACRESCENTA MAIS 1 NA VARIÁVEL COLUNA PARA SE PASSAR NAS 5 COLUNAS
            }
            coluna = selectColuna - 2; // RETORNA O VALOR DE 'COLUNA' PARA O ENDEREÇO INICIAL. PARA REPETIR NA PRÓXIMA LINHA.
            linha++; // PULA PARA PRÓXIMA LINHA
        }
    }
}

void habOCTAEDRO()
{
    int soma;     // VARIÁVEL QUE VAI AJUDAR NA LÓGICA
    int coluna;
    int linha;

    linha = selectLinha - 1;      //VARIAVEL LINHA RECEBE O VALOR DE SELECTLINHA -1 PARA FICAR MAIS FACIL DE INTERPRETAR A LÓGICA
    coluna = selectColuna - 1;   //VARIÁVEL QUE RECEBE O VALOR DE SELECTCOLUNA -1 PARA FICAR MAIS FACIL DE INTERPRETAR A LÓGICA
                                // SENDO ASSIM O ENDEREÇO DE ORIGEM SMP SERÁ LINHA 0 E COLUNA 0;

    if ((coluna >= 0 && coluna <=7) && (linha >= 0 && linha <= 7)) //CONDIÇÃO PARA QUE A HABILIDADE NÃO EXCEDA OS LIMITES DA MATRIZ TABULEIRO
    {
        /*
            NESTA LÓGICA SERA USADO LOOPS ANINHADOS PARA PASSAR POR 3 LINHAS E POR 3 COLUNAS, SOMANDO AS MATRIZES TABULEIRO E OCTAEDRO.
        */
        for (int i = 0; i < 3; i++)  // PASSARÁ 3X (PASSARÁ POR TRÊS LINHAS)
        {
            for (int j = 0; j < 3; j++) // PASSARÁ 5X (PASSARÁ POR 3 COLUNAS)
            {
                /*
                    A VARIÁVEL 'SOMA' IRA PEGAR O VALOR DA VARIÁVEL OCTAEDRO  SOMANDO COM A VARIÁVEL TABULEIRO PARA SABER SE NO ENDEREÇO DESEJADO
                    HÁ UM NAVIO, UMA HABILIDADE OU UMA HABILIDADE ATINGINDO UM NAVIO.
                */
                soma = tabuleiro [linha] [coluna] + octaedro [i] [j];
                if (soma == 4) // SIGNIFICA QUE TEM UMA HABILIDADE E UM NAVIO NO MESMO ENDEREÇO. MUDA O VALOR DESTE ENDEREÇO PARA 5
                {
                    soma = 5;
                }
                if (soma == 2) // SIGNIFICA QUE TEM DUAS HABILIDADES NO MESMO ENDEREÇO, VOLTA O VALOR PARA '1'
                {
                    soma = 1;
                }
                tabuleiro [linha] [coluna] = soma; // A MATRIZ TABULEIRO, NO ENDEREÇO DEFINIDO ANTERIORMENTE PELO CÓDIGO, RECEBE O VALOR DE 'SOMA'
                coluna++; // ACRESCENTA MAIS 1 NA VARIÁVEL COLUNA PARA SE PASSAR NAS 3 COLUNAS
            }
            coluna = selectColuna - 1; // RETORNA O VALOR DE 'COLUNA' PARA O ENDEREÇO INICIAL. PARA REPETIR NA PRÓXIMA LINHA.
            linha++; // PULA PARA PRÓXIMA LINHA
        }
    }
}



int main()
{
    setlocale(LC_ALL, "portuguese");

    zerarTabuleiro(); // FUNÇÃO PARA ATRIBUIR O VALOR '0' EM TODOS OS ENDEREÇOS DA MATRIZ 'TABULEIRO'.
    configCone();     // CONFIGURA A MATRIZ CONE
    configCruz();     // CONFIGURA A MATRIZ CRUZ
    configOctaedro(); // CONFIGURA A MATRIZ OCTAEDRO


    //**********************NAVIO 01************************

    selectColuna = 0; //SELECIONA NO CÓDIGO A COLUNA QUE DEVE SE INICIAR A GRAVAÇÃO;
    selectLinha = 0; //SELECIONA NO CÓDIGO A LINHA QUE DEVE SE INICIAR A GRAVAÇÃO;

    // TESTA E SE CASO POSSÍVEL IRÁ GRAVAR EM HORIZONTAL O NAVIO NA MATRIZ 'TABULEIRO' DE ACORDO COM O VALOR DEFINIDO NAS VARIAVEIS ACIMA;
    horizontal();

    //**********************NAVIO 02************************

    selectColuna = 9; //SELECIONA NO CÓDIGO A COLUNA QUE DEVE SE INICIAR A GRAVAÇÃO;
    selectLinha = 7; //SELECIONA NO CÓDIGO A LINHA QUE DEVE SE INICIAR A GRAVAÇÃO;

    // TESTA E SE CASO POSSÍVEL IRÁ GRAVAR EM HORIZONTAL O NAVIO NA MATRIZ 'TABULEIRO' DE ACORDO COM O VALOR DEFINIDO NAS VARIAVEIS ACIMA;
    vertical();

    //**********************NAVIO 03************************

    selectColuna = 5; //SELECIONA NO CÓDIGO A COLUNA QUE DEVE SE INICIAR A GRAVAÇÃO;
    selectLinha = 7; //SELECIONA NO CÓDIGO A LINHA QUE DEVE SE INICIAR A GRAVAÇÃO;

    // TESTA E SE CASO POSSÍVEL IRÁ GRAVAR EM DIAGONAL O NAVIO NA MATRIZ 'TABULEIRO' DE ACORDO COM O VALOR DEFINIDO NAS VARIAVEIS ACIMA;
    diagonal();

    //**********************NAVIO 04************************

    selectColuna = 4; //SELECIONA NO CÓDIGO A COLUNA QUE DEVE SE INICIAR A GRAVAÇÃO;
    selectLinha = 4; //SELECIONA NO CÓDIGO A LINHA QUE DEVE SE INICIAR A GRAVAÇÃO;

    // TESTA E SE CASO POSSÍVEL IRÁ GRAVAR EM DIAGONAL O NAVIO NA MATRIZ 'TABULEIRO' DE ACORDO COM O VALOR DEFINIDO NAS VARIAVEIS ACIMA;
    diagonal();



    //******************* HABILIDADE CONE********************

    selectColuna = 2; //SELECIONA NO CÓDIGO A COLUNA QUE DEVE SE INICIAR A GRAVAÇÃO;
    selectLinha = 0; //SELECIONA NO CÓDIGO A LINHA QUE DEVE SE INICIAR A GRAVAÇÃO;

    habCONE();

    //******************* HABILIDADE CRUZ********************

    selectColuna = 2; //SELECIONA NO CÓDIGO A COLUNA QUE DEVE SE INICIAR A GRAVAÇÃO;
    selectLinha = 7; //SELECIONA NO CÓDIGO A LINHA QUE DEVE SE INICIAR A GRAVAÇÃO;

    habCRUZ();

    //******************* HABILIDADE OCTAEDRO********************

    selectColuna = 7; //SELECIONA NO CÓDIGO A COLUNA QUE DEVE SE INICIAR A GRAVAÇÃO;
    selectLinha = 3; //SELECIONA NO CÓDIGO A LINHA QUE DEVE SE INICIAR A GRAVAÇÃO;

    habOCTAEDRO();
    
    //******************** EXIBIÇÃO DA TELA********************

    if(chave == 1) // SE A CHAVE NÃO FOR ALTERADAS NAS FUNÇÕES ACIMA, SERÁ IMPRESSO O TABULEIRO.
    {
        imprimirTabuleiro();
    }
}