/*
 * tipos.h
 * Tipos de dados e constantes compartilhados por todos os modulos.
 */
#ifndef TIPOS_H
#define TIPOS_H

#include <stdbool.h>

#define TAM_CODIGO 8   /* Ex.: "N001" + '\0' */
#define MAX_FILA   100 /* Quantidade maxima de senhas na fila */

/* Categorias de atendimento (a ordem define a prioridade: maior = mais urgente) */
typedef enum {
    NORMAL = 0,
    PREFERENCIAL = 1,
    URGENTE = 2
} Categoria;

/* Situacao de uma senha dentro da fila */
typedef enum {
    AGUARDANDO,
    EM_ATENDIMENTO,
    FINALIZADA
} StatusSenha;

/* Dados informados pelo atendente sobre o paciente */
typedef struct {
    char genero;               /* 'F' ou 'M' */
    int  idade;
    bool gestante;
    bool lactante;
    bool necessidadeEspecial;
    bool obeso;
} Paciente;

/* Senha emitida para o paciente */
typedef struct {
    char        codigo[TAM_CODIGO]; /* N001, P001, U001... */
    Categoria   categoria;
    StatusSenha status;
} Senha;

#endif
