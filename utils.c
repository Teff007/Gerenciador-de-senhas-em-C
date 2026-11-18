/*
 * utils.c
 * Funcoes auxiliares de entrada de dados COM validacao.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void lerLinha(char *destino, int tamanho)
{
    if (fgets(destino, tamanho, stdin) == NULL) {
        /* Fim da entrada (Ctrl+D / arquivo acabou): encerra com seguranca */
        printf("\nEntrada encerrada.\n");
        exit(0);
    }

    size_t n = strlen(destino);
    if (n > 0 && destino[n - 1] == '\n') {
        destino[n - 1] = '\0';          /* remove o Enter */
    } else {
        int c;                          /* linha maior que o buffer: descarta o resto */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

int lerInteiro(const char *mensagem, int min, int max)
{
    char buffer[32];
    char *fim;

    while (true) {
        printf("%s", mensagem);
        lerLinha(buffer, sizeof(buffer));

        long valor = strtol(buffer, &fim, 10);

        /* valido se digitou algo, so tinha numero e esta na faixa */
        if (buffer[0] != '\0' && *fim == '\0' && valor >= min && valor <= max) {
            return (int)valor;
        }
        printf("Valor invalido! Digite um numero entre %d e %d.\n", min, max);
    }
}

bool lerSimNao(const char *mensagem)
{
    char buffer[8];

    while (true) {
        printf("%s (S/N): ", mensagem);
        lerLinha(buffer, sizeof(buffer));

        if (strlen(buffer) == 1) {
            char c = (char)toupper((unsigned char)buffer[0]);
            if (c == 'S') {
                return true;
            } else if (c == 'N') {
                return false;
            }
        }
        printf("Resposta invalida! Digite S ou N.\n");
    }
}

char lerGenero(void)
{
    char buffer[8];

    while (true) {
        printf("Genero do paciente (F/M): ");
        lerLinha(buffer, sizeof(buffer));

        if (strlen(buffer) == 1) {
            char c = (char)toupper((unsigned char)buffer[0]);
            if (c == 'F' || c == 'M') {
                return c;
            }
        }
        printf("Genero invalido! Digite F ou M.\n");
    }
}
