#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>
p_grafo criar_grafo(int qtd_vertices) {
	p_grafo novoGrafo = malloc(sizeof(Grafo));
	
	if (novoGrafo == NULL) {
		printf("Erro de alocação de memória");
		exit(1);
	}
	
	novoGrafo->qtd_vertices = qtd_vertices;
	novoGrafo->adjacencia = malloc(qtd_vertices * sizeof(p_no));
	
	if (novoGrafo->adjacencia == NULL) {
		printf("Erro de alocação de memória");
		exit(1);
	}
	
	for (int i = 0; i < qtd_vertices; i++) {
		novoGrafo->adjacencia[i] = criar_lista();
	}
	return novoGrafo;
}

void destruir_grafo(p_grafo grafo) {
	free(grafo->adjacencia);
	free(grafo);
}

void insere_aresta(p_grafo grafo, int origem, int destino) {
	grafo->adjacencia[origem] = insere_na_lista(grafo->adjacencia[origem], destino);
}

p_no obter_adjacencia(p_grafo grafo, int vertice) {
	return obter_iterador(grafo->adjacencia, vertice);
}

