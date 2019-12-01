#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

p_no criar_lista() {
	return NULL;
}

int eh_vazia(p_no lista) {
	return lista == NULL;
}

p_no insere_na_lista(p_no lista, int vertice) {
	p_no novoNo = malloc(sizeof(No));
	
	if (novoNo == NULL) {
		printf("Erro de alocação de memória");
		exit(1);	
	}	

	novoNo->vertice = vertice;
	novoNo->prox = lista;
	return novoNo;
}

void destruir_lista(p_no lista) {
	if (!eh_vazia(lista)) {
		destruir_lista(lista->prox);
		free(lista);
	}
}

p_no obter_iterador(p_no* adjacencia, int vertice) {
	return adjacencia[vertice];
}

p_no avancar_posicao(p_no iterador) {
	return iterador->prox;
}

int obter_vertice(p_no iterador) {
	return iterador->vertice;
}
