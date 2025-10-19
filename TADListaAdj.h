#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct listaAdjacencia
{
    char vertice;
    int peso;
    struct listaAdjacencia *head, *tail;
};
typedef struct listaAdjacencia ListaAdjacencia;

//TAD da LISTA ---------------------------------------------------------------------------------------
ListaAdjacencia *novaCaixaVazia(void)
{
    ListaAdjacencia *nova = (ListaAdjacencia *)malloc(sizeof(ListaAdjacencia));
    nova->vertice = '0';
    nova->peso = 0;
    nova->head = nova->tail = NULL;
    return nova;
}

ListaAdjacencia *novaCaixaLista(char vertice, int peso)
{
    ListaAdjacencia *nova = (ListaAdjacencia *)malloc(sizeof(ListaAdjacencia));
    nova->vertice = vertice;
    nova->peso = peso;
    nova->head = nova->tail = NULL;
    return nova;
}

//FUNCOES PARA LISTA DE ADJACENCIA ----------------------------------------------------------------------------------
void inserirLista(ListaAdjacencia**lista, char vertice, int peso){
	*lista = novaCaixaLista(vertice, peso);
}

void inserirListaPeso(ListaAdjacencia**lista, char origem, char vertice, int peso)
{
	ListaAdjacencia * nova, *aux, *ant;

	//se lista vazia
	if(*lista == NULL){
		inserirLista(&(*lista),origem, peso);
	}
	else{
		//procurar o vertice origem
		aux = ant = *lista;
		while(aux != NULL && origem != aux->vertice){
			ant = aux;
			aux = aux->head;
		}
		//se nao existe eu crio o vertice origem
		if(aux == NULL){ //entao nao existe esse vertice origem
			ant->head = novaCaixaLista(origem, peso);
		}
		else{
			//fazer a busca na horizontal, buscar o vertice de destino
			ant = aux;
			aux = aux->tail;
			while(aux != NULL && vertice != aux->vertice){
				ant = aux;
				aux = aux->tail;
			}
			//nao existe o vertice para o destino
			if(aux == NULL){
				nova = novaCaixaLista(vertice, peso);
				nova->peso = peso;
				ant->tail = nova;
			}
		}
	}
}
void exibirListaAdjacencia(ListaAdjacencia * lista)
{
	ListaAdjacencia *auxVert, *auxHori;
	auxVert = lista;
	//descer verticalmente
	printf("\n");
	while(auxVert != NULL)
	{
		printf("Vertice: %c -> ",auxVert->vertice);
		auxHori = auxVert->tail;
		while(auxHori != NULL)
		{
			if(auxHori->tail == NULL)
			{
				printf("%c,%d",auxHori->vertice,auxHori->peso);	
			}
			else
			{
				printf("%c,%d || ",auxHori->vertice,auxHori->peso);
			}
			auxHori = auxHori->tail;
		}
		printf("\n");
		auxVert = auxVert->head;
	}
}





