#ifndef LISTA_H
#define LISTA_H

typedef struct No {
	int vertice;
	struct No *prox;
} No;

typedef No * p_no;

p_no criar_lista();

int eh_vazia(p_no lista);

p_no insere_na_lista(p_no lista, int vertice);

void destruir_lista(p_no lista);

p_no obter_iterador(p_no* adjacencia, int vertice);

p_no avancar_posicao(p_no iterador);

int obter_vertice(p_no iterador);


#endif // LISTA_H
