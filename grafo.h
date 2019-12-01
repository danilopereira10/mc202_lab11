#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"


typedef struct {
	p_no *adjacencia;
	int qtd_vertices;
} Grafo;

typedef Grafo * p_grafo;

p_grafo criar_grafo(int qtd_vertices);

void destruir_grafo(p_grafo grafo);

void insere_aresta(p_grafo grafo, int origem, int destino);

p_no obter_adjacencia(p_grafo grafo, int vertice);




#endif // GRAFO_H
