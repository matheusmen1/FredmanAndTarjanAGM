#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

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
	ListaAdjacencia *nova, *aux, *ant, *Lista;

	//se lista vazia
	if(*lista == NULL){
		inserirLista(&(*lista),origem, peso);
		if(vertice != '\0')
			inserirListaPeso(lista, origem, vertice, peso);
	}
	else
	{
		//procurar o vertice origem
		aux = *lista;
		while(aux != NULL && origem != aux->vertice)
			aux = aux->head;
		
		//se nao existe eu crio o vertice origem
		if(aux == NULL)
		{ //entao nao existe esse vertice origem
			nova = novaCaixaLista(origem, peso);
		
			if ((*lista)->vertice > origem)
			{
				nova->head = *lista;
				*lista = nova;
			}
			else
			{
				aux = *lista;
				ant = aux;
				while (aux != NULL && aux->vertice < origem)
				{
					ant = aux;
					aux = aux->head;
				}
				if (aux != NULL) // meio
				{
					nova->head = ant->head;
					ant->head = nova;
				}
				else
				{
					ant->head = nova;
				}
			}
			if(vertice != '\0')
				inserirListaPeso(lista, origem, vertice, peso);
		}
		else
		{		
			//fazer a busca na horizontal, buscar o vertice de destino
			Lista = aux;
			aux = aux->tail;
			while(aux != NULL && vertice != aux->vertice)
				aux = aux->tail;
			
			//nao existe o vertice para o destino
			if(aux == NULL)
			{
				nova = novaCaixaLista(vertice, peso);
				if (Lista->tail == NULL)
				{
					Lista->tail = nova;
				}
				else
				if (Lista->tail->vertice > vertice)
				{
					nova->tail = Lista->tail;
					Lista->tail = nova;
				}
				else
				{
					aux = Lista->tail;
					ant = aux;
					while (aux != NULL && aux->vertice < vertice)
					{
						ant = aux;
						aux = aux->tail;
					}
					if (aux != NULL) // meio
					{
						nova->tail = ant->tail;
						ant->tail = nova;
					}
					else // fim
					{
						ant->tail = nova;
					}
				}
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
