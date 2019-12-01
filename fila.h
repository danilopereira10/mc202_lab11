#ifndef FILA_H
#define FILA_H

#include "lista.h"

typedef struct {
	p_no inicio, fim;
} Fila;

typedef Fila * p_fila;

p_fila criar_fila();

void destruir_fila(p_fila fila);

int fila_vazia(p_fila fila);

void enfileira(p_fila fila, int x);

int desenfileira(p_fila fila);

#endif // FILA_H
