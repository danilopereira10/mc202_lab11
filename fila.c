#include "fila.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

#define SEM_PROXIMO_NO NULL

p_fila criar_fila() {
	p_fila fila;
	fila = malloc(sizeof(Fila));
	
	if (fila == NULL) {
		printf("Erro de alocação de memória");
		exit(1);
	}
	
	fila->inicio = NULL;
	fila->fim = NULL;
	return fila;
}

void destruir_fila(p_fila fila) {
	if (!fila_vazia(fila)) {
		destruir_lista(fila->inicio);
	}
	free(fila);
}

int fila_vazia(p_fila fila) {
	return eh_vazia(fila->inicio);
}

void enfileira(p_fila fila, int x) {
	if (fila_vazia(fila)) {
		insere_na_lista(fila->inicio, x);
		fila->fim = fila->inicio;
	} else {
		p_no novo_no = insere_na_lista(criar_lista(), x);
		fila->fim->prox = novo_no;
		fila->fim = novo_no;
	}	
}

int desenfileira(p_fila fila) {
	if (fila_vazia(fila)) {
		return -1;
	}
	
	p_no primeiro_no = fila->inicio;
	int primeiro_vertice = primeiro_no->vertice;
	
	fila->inicio = fila->inicio->prox;
	
	if (fila->inicio == NULL) {
		fila->fim = NULL;
	}
	
	free(primeiro_no);
	return primeiro_vertice;
}




