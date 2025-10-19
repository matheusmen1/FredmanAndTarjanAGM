#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TF 50
struct fibno
{
	int key; // custo da aresta
	struct fibno *esq, *dir; // fila circular
	struct fibno *pai;
	struct fibno *filho;
	int degree; // numero de filhos
	int mark; // se ja teve filho removido, 0 - nao 1 - sim
	
};
typedef struct fibno FibNo;

struct fibheap
{
	int n; // numero de nos
	struct fibno *min; // aponta para o nó com menor aresta
};
typedef struct fibheap FibHeap;

void inicializar(FibHeap **heap)
{
	*heap = (FibHeap*)malloc(sizeof(FibHeap));
	(*heap)->n = 0;
	(*heap)->min = NULL;
}
FibNo *NovoFibNo(int peso)
{
	FibNo *NC;
	NC = (FibNo*)malloc(sizeof(FibNo));
	NC->key = peso;
	NC->esq = NC;
	NC->dir = NC;
	NC->pai = NULL;
	NC->filho = NULL;
	NC->degree = 0;
	NC->mark = 0;
	
	return NC;
}

void inserir(FibHeap **heap, int peso)
{
	FibNo *NC;
	NC = NovoFibNo(peso);
	if((*heap)->min == NULL)
	{
		(*heap)->min = NC;
	}
	else
	{
		// min->esq <-> NC <-> min
		
		(*heap)->min->esq->dir = NC;
		NC->dir = (*heap)->min;
		NC->esq = (*heap)->min->esq;
		(*heap)->min->esq = NC;
		if ((*heap)->min->key > peso)
			(*heap)->min = NC;
	}
	(*heap)->n = (*heap)->n + 1;
	
}
FibNo *getMin(FibHeap **heap)
{
	return (*heap)->min;
}

FibHeap *meld(FibHeap *h1, FibHeap *h2)
{
	FibNo *temp1 = h1->min->dir;
	FibNo *temp2 = h2->min->esq;
	
	h1->min->dir = h2->min;
	h2->min->esq = h1->min;
	temp2->dir = temp1;
	temp1->esq = temp2;
	
	if (h1->min->key > h2->min->key)
		h1->min = h2->min;
		
	h1->n = h1->n + h2->n;
	
	return h1;

}
void fibHeapLink(FibHeap *heap, FibNo *y, FibNo *x) // insere y da raiz, na lista de filhos de x
{
	y->dir->esq = y->esq;
	y->esq->dir = y->dir;
	
	y->pai = x;
	if (x->filho == NULL)
	{
		x->filho = y;
		y->dir = y;
		y->esq = y;
	}
	else
	{
		y->esq = x->filho;
		y->dir = x->filho->dir;
		x->filho->dir->esq = y;
		x->filho->dir = y;
	}
	x->degree++;
	y->mark = 0;
}
int calcDegree(int n)
{
	int count = 0;
	while (n > 0)
	{
		n = n / 2;
		count++;
	}
	return count;
}
void consolidate(FibHeap *heap)
{
	// garantir que exista apenas um no com aquela quantidade de degree
	int degree, tamanho, TL;
	tamanho = calcDegree(heap->n);
	FibNo *vet[tamanho],*inicio, *atual, *y, *x, *proximo; 
	FibNo *lista[heap->n];
	
	int i;
	for (i = 0; i < tamanho; i++)
	{
		vet[i] = NULL;
	}
	
	// lista de nós raizes
	inicio = heap->min;
	atual = inicio;
	TL = 0;
	do
	{
		lista[TL] = atual;
		TL++;
		atual = atual->dir;
		
	}while(atual != inicio);
	
	i = 0;
	while(i < TL)
	{
		x = lista[i];
		degree = x->degree;
		while(vet[degree] != NULL)
		{
			int aux;
			aux = degree;
			y = vet[degree];
			if (y->key < x->key)
			{
				FibNo *temp;
				temp = x;
				x = y;
				y = temp;
				
			}
			fibHeapLink(heap, y, x);
			degree = x->degree;
			vet[aux] = NULL;
			
		}
		vet[degree] = x;
		i++;
	}
		
	// recriar a lista de nós raizes, a partir do meu vetor de no
	heap->min = NULL;
	i = 0;
	while(i < tamanho)
	{
		if (vet[i] != NULL)
		{
			vet[i]->dir = vet[i];
			vet[i]->esq = vet[i];
			if (heap->min == NULL)
				heap->min = vet[i];
			else
			{
				vet[i]->esq = heap->min;
				vet[i]->dir = heap->min->dir;
				heap->min->dir->esq = vet[i];
				heap->min->dir = vet[i];
				if (heap->min->key > vet[i]->key)
					heap->min = vet[i];
			}
		}
		i++;
	}

}
FibNo *extractMin(FibHeap *heap)
{
	FibNo *min, *filho, *atual;
	min = heap->min;
	if (min != NULL)
	{
		if (min->filho != NULL)
		{
			filho = min->filho;
			atual = filho;
			do
			{
				atual->pai = NULL; // agora todos os filhos do min, são nos raizes
				atual = atual->dir;
				
			}while(atual != filho);
			
			// unifica a lista circular dos filhos, com a da raiz (meld)
			FibNo *temp1, *temp2;
			
			temp1 = min->dir;
			temp2 = filho->esq;
			
			min->dir = filho;
			filho->esq = min;
			temp2->dir = temp1;
			temp1->esq = temp2;
		}
		// remover min
		min->esq->dir = min->dir;
		min->dir->esq = min->esq;
		
		if (min == min->dir) // unico da lista de raiz e sem filhos
		{
			heap->min = NULL;
		}
		else
		{
			heap->min = min->dir;
			consolidate(heap);
			
		}
		heap->n = heap->n - 1;
	}
	
	return min;
}
void cut (FibHeap *heap, FibNo *no, FibNo *pai)
{
	no->esq->dir = no->dir;
	no->dir->esq = no->esq;
	if (pai->filho == no)
	{
		if (no->dir == no) // filho unico
		{
			pai->filho = NULL;
		}
		else
		{
			pai->filho = no->dir;
		}
	}
	pai->degree--;
	
	// inserir no na lista de raizes
	no->dir = heap->min->dir;
	no->esq = heap->min;
	heap->min->dir->esq = no;
	heap->min->dir = no;
	
	no->pai = NULL;
	no->mark = 0;
	
}
void cascadingCut(FibHeap *heap, FibNo *pai) // garante que a arvore fique equilibrada
{
	FibNo *avo;
	// pegar o avo
	avo = pai->pai;
	if (avo != NULL) // nao for no da lista de raizes
	{
		if (pai->mark == 0) // ainda n teve filho removido
		{
			pai->mark = 1;
		}
		else
		{
			cut(heap, pai, avo);
			cascadingCut(heap, avo);
		}
		
	}
	
}
void decreaseKey(FibHeap *heap, FibNo *no, int novoPeso)
{
	if (novoPeso < no->key)
	{
		FibNo *pai;
		no->key = novoPeso;
		pai = no->pai;
		if (pai != NULL) // no é raiz
		{
			if (no->key < pai->key)
			{
				cut(heap, no, pai);
				cascadingCut(heap, pai);
			}
		}
	
		if (heap->min->key > no->key)
		{
			heap->min = no;
		}
		
	}

}

void exibirNo(FibNo *no, char *indent);

// exibicao by gpt
void exibirHeap(FibNo *min)
{
    if (min == NULL)
    {
        printf("Heap esta vazio.\n");
        return;
    }
    
    FibNo *inicio = min;
    FibNo *atual = min;
    
    printf("\n--- Estrutura do Heap (Min: %d) ---\n", min->key);
    do
    {
        exibirNo(atual, "");
        atual = atual->dir;
    } while (atual != inicio);
    printf("-------------------------------------\n");
}

void exibirNo(FibNo *no, char *indent)
{
    if (no != NULL) 
	{
	    printf("%s|- No (%d) [Degree: %d, Marca: %d]\n", 
	           indent, no->key, no->degree, no->mark);
	    char novaIndent[256]; 
	    snprintf(novaIndent, 256, "%s|   ", indent);
	    if (no->filho != NULL)
	    {
	        FibNo *filho_inicio = no->filho;
	        FibNo *filho_atual = no->filho;
	        do
	        {
	            exibirNo(filho_atual, novaIndent);
	            filho_atual = filho_atual->dir;
	        } while (filho_atual != filho_inicio);
	    }
	}

}

