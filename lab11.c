#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"
#include "fila.h"

#define DISTANCIA_NULA 0
#define TERREO 0

void insere_arestas_de_partida(p_grafo grafo, int n) {
	insere_aresta(grafo, (2 * n) + 2, (2 * n) + 1);
	insere_aresta(grafo, (2 * n) + 2, n);
}

void insere_arestas_no_elevador_A(p_grafo grafo, int i, int n, int X, int Y) {
	insere_aresta(grafo, i, i + n + 1);
	insere_aresta(grafo, i, i + Y);
	insere_aresta(grafo, i, i - X);
}

void insere_arestas_no_elevador_B(p_grafo grafo, int i, int n, int W, int Z) {
	insere_aresta(grafo, i + n + 1, i + n + 1 + Z);
	insere_aresta(grafo, i + n + 1, i + n + 1 - W);
	insere_aresta(grafo, i + n + 1, i);
}

void aumentar_tamanho_para_caber_todos_os_numeros(int* pai, int* tamanho_vetor, int* vertice) {
	while(pai[*vertice] != *vertice) {
		(*tamanho_vetor)++;
		*vertice = pai[*vertice];
	}
	(*tamanho_vetor)++; // um espaço alocado para adicionar o último 
	            			// vértice mais uma vez, para poder continuar
	            			// utilizando a condição pai[vertice] != vertice
}

int* inicializar_vetor_pais_ordenados(int tamanho, int vertice) {
	int *pais_ordenados = malloc(tamanho * sizeof(int));
	pais_ordenados[0] = 0;
	pais_ordenados[tamanho - 1] = vertice; // adicionando o topo do grafo (2n + 2) na 
						// última posição do vetor
	
	return pais_ordenados;
}

int decidir_valor_do_terreo(int* pai, int n) {
	return pai[0] != -1 ? 0 : n + 1;
}

void imprime_elevadores(int* pai, int qtd_vertices) {
	int tamanho_vetor = 1; //um espaço alocado para o vértice "0"
	
	int n = (qtd_vertices - 3) / 2;
	int terreo = decidir_valor_do_terreo(pai, n);
	
	int vertice = terreo;
	aumentar_tamanho_para_caber_todos_os_numeros(pai, &tamanho_vetor, &vertice);
	int* pais_ordenados = inicializar_vetor_pais_ordenados(tamanho_vetor, vertice);
	printf("%d", pais_ordenados[0]);
	
}

void inserir_demais_arestas(p_grafo grafo, int n) {
	for (int i = n; i > 0; i--) {
		int X, Y, W, Z;
		scanf("%d %d %d %d", &X, &Y, &W, &Z);
		insere_arestas_no_elevador_A(grafo, i, n, X, Y);
		insere_arestas_no_elevador_B(grafo, i, n, W, Z);
	}
}

void declarar_como_visitado(int* visitado, p_no no_atual) {
	visitado[no_atual->vertice] = 1;
}

void atualizar_pai(int* pai, p_no no_atual, int vertice) {
	pai[no_atual->vertice] = vertice;
}

void declarar_problema_resolvido_se_chegou_no_terreo(int n, p_no no_atual, int* problema_resolvido) {
	if (no_atual->vertice == 0 || no_atual->vertice == n + 1) {
		*problema_resolvido = 1;
	}
}

void ir_visitando_vertices_ate_chegar_no_terreo(int n, int* visitado, p_no no_atual, int* pai, p_fila fila, int* problema_resolvido, int vertice) {
	if (!visitado[no_atual->vertice]) {
		declarar_como_visitado(visitado, no_atual);
		atualizar_pai(pai, no_atual, vertice);
		enfileira(fila, no_atual->vertice);
		declarar_problema_resolvido_se_chegou_no_terreo(n, no_atual, problema_resolvido);
	}
}

void visitar_vertices(int* pai, int* visitado, p_grafo grafo, int vertice, p_fila fila, int* problema_resolvido) {
	int n = (grafo->qtd_vertices - 3) / 2;
	for (p_no no_atual = grafo->adjacencia[vertice]; no_atual != NULL; no_atual = no_atual->prox) {
		ir_visitando_vertices_ate_chegar_no_terreo(n, visitado, no_atual, pai, fila, problema_resolvido, vertice);
	}
}

int * busca_em_largura(p_grafo grafo, int vertice_inicial) {
	int vertice;
	int *visitado = malloc(grafo->qtd_vertices * sizeof(int));
	int *pai = malloc(grafo->qtd_vertices * sizeof(int));
	
	p_fila fila = criar_fila();
	for (vertice = 0; vertice < grafo->qtd_vertices; vertice++) {
		pai[vertice] = -1;
		visitado[vertice] = 0;
	}
	
	enfileira(fila, vertice_inicial);
	pai[vertice_inicial] = vertice_inicial;
	visitado[vertice_inicial] = 1;
	
	int problema_resolvido = 0;
	while(!fila_vazia(fila) && !problema_resolvido) {
		vertice = desenfileira(fila);
		visitar_vertices(pai, visitado, grafo, vertice, fila, &problema_resolvido);
	}
	
	destruir_fila(fila);
	free(visitado);
	return pai;
}


int* resolve_problema(p_grafo grafo, int n) {	
	insere_arestas_de_partida(grafo, n);
	inserir_demais_arestas(grafo, n);

	int *pai = busca_em_largura(grafo, (2 * n) + 2);	
	return pai;
}

int main() {
	int cenarios;
	scanf("%d", &cenarios);
	
	for (int i = 0; i < cenarios; i++) {
		int n;
		scanf("%d", &n);

		p_grafo grafo = criar_grafo((2 * n) + 3);

		int* pai = resolve_problema(grafo, n);
		imprime_elevadores(pai, (2 * n) + 3);
		destruir_grafo(grafo);
	}

	return EXIT_SUCCESS;
}
