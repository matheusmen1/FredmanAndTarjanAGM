#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#define L 50
#define C 50

#include "TADFibHeap.h"
#include "TADListaAdj.h"

void Moldura(int CI, int LI, int CF, int LF, int CorTxt, int CorFundo);

void molduraFredTarjan()
{
	Moldura(1,1, 120,30, 7, 7);
	gotoxy(45,4), printf("     ====================================");
	gotoxy(65,5), textcolor(LIGHTBLUE),printf ("Fredman");
	gotoxy(67,6), textcolor(3),printf ("And");
	gotoxy(65,7), textcolor(3),printf ("Tarjan");
	gotoxy(45,8), textcolor(7),printf("     ====================================");
}

void lerTxTMatrizAdjacencia(int m[L][C], int *qtdeVertices, int *qtdeLinhas, int *qtdeColunas, char vertices[C])
{

	int j = 0, num, linhas = 0, colunas = 0;
	char linha[50], aux[50];
	FILE * Ptr = fopen("entradaMA.txt", "r");
	rewind(Ptr); // joga o ponteiro para o inicio
	fgets(linha, sizeof(linha), Ptr); // le a primeira linha, contendo todos meus vertices
	for (int i = 0; i < strlen(linha);i++)
	{
		if (linha[i] != ' ' && linha[i] != '\n')
		{
			vertices[j] = linha[i];
			*qtdeVertices = *qtdeVertices + 1;
			j++;
		}
	}
	
	while(fgets(linha, sizeof(linha), Ptr))
	{
		j = 0;
		colunas = 0;
		for(int i = 0; i < strlen(linha); i++)
		{
			if(linha[i] != ' ' && linha[i] != '\n')
			{
				aux[j] = linha[i];
				j++;
			}
			else
			{
				aux[j] = '\0';
				num = atoi(aux);
				m[linhas][colunas] = num;
				j = 0;
				colunas++;
			}
		
			
		}
		if (j > 0)
		{
			
			aux[j] = '\0';
			num = atoi(aux);
			m[linhas][colunas] = num;

		}
		if (colunas > *qtdeColunas)
			*qtdeColunas = colunas;
		linhas++;
	}
	*qtdeLinhas = linhas;
	
	fclose(Ptr);
}

void converterMatrizParaLista(int m[L][C], ListaAdjacencia **Lista, int qtdeVertices, char vertices[L])
{
	
	for (int i = 0; i < qtdeVertices; i++)
	{
		for (int j = 0; j < qtdeVertices;j++)
		{
			
			if (m[i][j] != 0) // tem aresta
			{
				inserirListaPeso(&(*Lista), vertices[i], vertices[j], m[i][j]);
				inserirListaPeso(&(*Lista), vertices[j], vertices[i], m[j][i]);
			}
			
		}
	}

}

void Moldura(int CI, int LI, int CF, int LF, int CorTxt, int CorFundo)
{
	int a;
	textcolor(CorTxt); // 0...15
	textbackground(CorFundo); // 0..7
	gotoxy(CI, LI); printf("%c", 201);
	gotoxy(CI, LF); printf("%c", 200);
	gotoxy(CF, LI); printf("%c", 187);
	gotoxy(CF, LF); printf("%c", 188);
	
	for(a=CI+1; a<CF; a++)
	{
		gotoxy(a, LI);	printf("%c", 205);
		gotoxy(a, LF);	printf("%c", 205);
	}
	
	for(a=LI+1; a<LF; a++)
	{
		gotoxy(CI, a);	printf("%c", 186);
		gotoxy(CF, a);	printf("%c", 186);
	}
	
	textcolor(7);
	textbackground(0);
}

void exibirMatrizAdjacenciaComVertices(int m[L][C], char vertices[C], int qtdeLinhas, int qtdeColunas)
{
	molduraFredTarjan();
	
	gotoxy(5,3), textcolor(3),printf("MA"); 
    for (int j = 0; j < qtdeColunas; j++)
	{
        gotoxy(9 + j*4,3), textcolor(3),printf("%c", vertices[j]);
    }
    for (int i = 0; i < qtdeLinhas; i++)
	{
        gotoxy(5,5+i), textcolor(3),printf("%c", vertices[i]);
        for (int j = 0; j < qtdeColunas; j++)
		{
            if (m[i][j] != 0)	
				gotoxy(8+j * 4,5+i), textcolor(2),printf("%2d", m[i][j]); // x y (coluna, linha)
			else
				gotoxy(8+j * 4,5+i), textcolor(7),printf("%2d", m[i][j]); // x y (coluna, linha)
        }
    }
}

//funcoes para a arvore geradora minima
int valorArvoreMinima(ListaAdjacencia * arvoreMinima)
{
	int soma = 0;
	ListaAdjacencia * aresta;
	
	while(arvoreMinima != NULL)
	{
		aresta = arvoreMinima->tail; //primeira aresta
		while(aresta != NULL)
		{
			soma += aresta->peso;
			aresta = aresta->tail;
		}
		
		arvoreMinima = arvoreMinima->head; //andando na vertical
	}
	return soma/2; //divisao por 2 pois forma um grafo nao direcionado
}

int charParaIndice(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    else if (c >= 'A' && c <= 'Z')
		return c - 'A';
    else
        return -1;
}

int contaNos(ListaAdjacencia * lista) //contar os vertices do meu grafo
{
	int i = 0;
	
	while(lista != NULL){
		lista = lista->head;
		i++;
	}
	
	return i;
}

void buscaPosicao (ListaAdjacencia **aux, ListaAdjacencia *listaOriginal, char vertice)
{
	while(listaOriginal != NULL && listaOriginal->vertice != vertice)
		listaOriginal = listaOriginal->head;
	*aux = listaOriginal;
}

void adicionarAdjacentes(ListaAdjacencia * vertice, int visitados[], FibHeap ** fibHeap)
{
	ListaAdjacencia * arestas; //andar pela horizontal
	arestas = vertice->tail;
	while(arestas != NULL)
	{
		if(visitados[charParaIndice(arestas->vertice)] == 0)//se esse vertice ainda nao foi visitado
		{
			inserirPesoChar(fibHeap, arestas->peso, vertice->vertice, arestas->vertice); //inserir no fibHeap
		}
		
		arestas = arestas->tail;
	}
}

void liberarMemListaAdj(ListaAdjacencia ** lista)
{
	ListaAdjacencia *antHead;
	while(*lista != NULL)
	{
		antHead = *lista;
		ListaAdjacencia * horizontal = (*lista)->tail, *ant;
		while(horizontal != NULL)
		{
			ant = horizontal;
			
			horizontal = horizontal->tail;
			free(ant);
		}
		*lista = (*lista)->head;
		free(antHead);
	}
}

void liberarMemFibHeap(FibNo * atual)
{
	FibNo * inicio = atual, *proximo;
	
	if(atual != NULL)
	{
		do
		{
			proximo = atual->dir;
			liberarMemFibHeap(atual->filho);
			free(atual);
			atual = proximo;
		} while(atual != inicio); //andar na horizontal pelos primos
	}
}
void inicializarVetorInt(int vet[], int tam)
{
	for (int i = 0; i < tam; i++)
	{
		vet[i] = 0;
	}
}
void inicializarVetorChar(char vet[], int tam)
{
	for (int i = 0; i < tam; i++)
	{
		vet[i] = 0;
	}
}
void arvoreGeradoraMinima(ListaAdjacencia * grafo, ListaAdjacencia ** arvoreMinima, char origem[], char destino[], int peso[], int debug)
{
	ListaAdjacencia * verticeAtual = grafo; //recebe um vertice arbitrario, no nosso caso recebe o primeiro do grafo
	int cont = 1, quantNos = contaNos(grafo);
	//int visitados[quantNos] = {}; //vetor de vertices visitados inicializado com 0 (nao visitado)
	int visitados[quantNos];
	inicializarVetorInt(visitados, quantNos);
	FibNo * menor;
	FibHeap * fibHeap;
	
	//inicializacoes
	*arvoreMinima = NULL; //inicializar a arvore minima
	inicializar(&fibHeap);
	if(debug == 1)
	{
		textcolor(LIGHTBLUE);
		printf("\nArvore Minima e FibHeap Inicializados!\n");
		textcolor(WHITE);
		getch();
	}
	
	do
	{
		if(visitados[charParaIndice(verticeAtual->vertice)] == 0) //verificacao para evitar de adicionar elementos duplicados
		{
			visitados[charParaIndice(verticeAtual->vertice)] = 1; //marco o vertice atual como já visitado
			adicionarAdjacentes(verticeAtual, visitados, &fibHeap); //adiciono ao meu fibHeap os vertices adjacentes ao meu atual -> FEITO!
			if(debug == 1){
				textcolor(LIGHTBLUE);
				printf("\nAdicionei Elementos no FibHeap:");
				textcolor(WHITE);
				exibirHeap(getMin(&fibHeap));
				getch();
			}
		}
		
		if(fibHeap != NULL)
		{
			menor = extractMin(fibHeap);
			if(debug == 1){
				textcolor(LIGHTBLUE);
				printf("\nMinimo Extraido!\n");
				printf("Origem: %c -> Destino: %c | Peso: %d\n", menor->origem, menor->destino, menor->key);
				textcolor(WHITE);
				getch();
			}
			
			int indice = charParaIndice(menor->destino);
			if(visitados[indice] == 0) //vertice nao visitado, posso ir
			{
				if(debug == 1){
					textcolor(LIGHTBLUE);
					printf("\nMinimo Valido!\n");
					printf("Origem: %c -> Destino: %c | Peso: %d\n", menor->origem, menor->destino, menor->key);
					printf("\nDepois de Retirado (valido -> Adicionar na Arvore):");
					textcolor(WHITE);
					exibirHeap(getMin(&fibHeap));
					getch();
				}
				
				visitados[charParaIndice(verticeAtual->vertice)] = 1; //marco o vertice atual como já visitado
				inserirListaPeso(arvoreMinima, menor->origem, menor->destino, menor->key); //insiro na arvore a aresta escolhida
				inserirListaPeso(arvoreMinima, menor->destino, menor->origem, menor->key);
				
				//para realizar a exibicao da arvore com niveis fora desse escopo
				origem[cont-1] = menor->origem;
				destino[cont-1] = menor->destino;
				peso[cont-1] = menor->key;
				
				if(debug == 1){
					textcolor(LIGHTBLUE);
					printf("\nMenor Inserido na Arvore Minima!\n");
					textcolor(WHITE);
					exibirListaAdjacencia(*arvoreMinima);
					getch();
				}
				
				cont++;
				buscaPosicao(&verticeAtual, grafo, menor->destino); //verticeAtual com o proximo vertice a ser visitado
				free(menor); //liberar o no da memoria
			}
		}
	} while(fibHeap != NULL && cont < quantNos); //enquanto tem elementos na minha fila e nem todos foram visitados
	liberarMemFibHeap(getMin(&fibHeap));
}

void exibirArvoreRec(char atual, char pai, char vet1[], char vet2[], int peso[], int n, int nivel)
{
    for (int i = 0; i < n; i++)
    {
        // Se há uma aresta atual ? outroVértice
        if (vet1[i] == atual && vet2[i] != pai)
        {
            for (int j = 0; j < nivel; j++) printf("    ");
            printf("+-- %c (%d)\n", vet2[i], peso[i]);
            exibirArvoreRec(vet2[i], atual, vet1, vet2, peso, n, nivel + 1);
        }
        else if (vet2[i] == atual && vet1[i] != pai)
        {
            for (int j = 0; j < nivel; j++) printf("    ");
            printf("+-- %c (%d)\n", vet1[i], peso[i]);
            exibirArvoreRec(vet1[i], atual, vet1, vet2, peso, n, nivel + 1);
        }
    }
}

// Função principal para exibir a árvore geradora mínima
void exibirArvoreGeradoraMinima(char raiz, char vet1[], char vet2[], int peso[], int n)
{
	printf("    ");
    printf("%c\n", raiz);
    exibirArvoreRec(raiz, '\0', vet1, vet2, peso, n, 1);
}

char menu (void)
{
	gotoxy(4,9), textcolor(7),printf("[A] - Matriz de Adjacencia -> Formar estruturas");
	gotoxy(4,10), textcolor(7),printf("[B] - Testar Insert E Meld -> Fib Heap");
	gotoxy(4,11), textcolor(7),printf("[C] - Testar ExtractMin -> Fib Heap");
	gotoxy(4,12), textcolor(7),printf("[D] - Arvore Geradora Minima (MST) -> Modo Debug");
	gotoxy(4,13), textcolor(7),printf("[E] - Arvore Geradora Minima (MST) -> Modo Corrido");
	gotoxy(4,14), textcolor(7),printf ("[ESC] - Sair");
	
	return toupper(getch());
}

void executar(void)
{
	char op;
	int qtdeVertices = 0;
	ListaAdjacencia *Lista = NULL, *arvoreMin;
	do
	{
		FibHeap *heap, *heap2;
		FibNo *min;
		inicializar(&heap);
		inicializar(&heap2);
		int m[L][C], qtdeLinhas = 0, qtdeColunas = 0, qtdeArestas = 0;
		char vertices[C], arestas[C];
		arestas[0] = '\0';
		
		//exibicao de moldura
		clrscr();
		Moldura(1,1, 120,30, 7, 7);
		gotoxy(45,4), printf("     ====================================");
		gotoxy(65,5), textcolor(3),printf ("Fredman");
		gotoxy(67,6), textcolor(3),printf ("And");
		gotoxy(65,7), textcolor(3),printf ("Tarjan");
		gotoxy(45,8), textcolor(7),printf("     ====================================");
		
		op = menu();
		switch(op)
		{
			case 'A': //formar estruturas
			{
				clrscr();
				lerTxTMatrizAdjacencia(m, &qtdeVertices, &qtdeLinhas, &qtdeColunas, vertices);
				exibirMatrizAdjacenciaComVertices(m, vertices,qtdeLinhas,qtdeColunas);
				getch();
				converterMatrizParaLista(m, &Lista, qtdeVertices, vertices);
				clrscr();
				exibirListaAdjacencia(Lista); //esse seria o meu grafo
				getch();
				break;
			}
			case 'B': //insert e meld -> fib heap
			{
				clrscr();
				inserir(&heap, 3);
				inserir(&heap, 10);
				inserir(&heap, 7);
				printf("\nminimo: %d\n", heap->min->key);
   				exibirHeap(heap->min);
   				printf("\nminimo: %d\n", heap->min->key);
   				inserir(&heap2, 2);
				inserir(&heap2, 8);
				inserir(&heap2, 5);
				meld(heap, heap2);
				exibirHeap(heap->min);
				printf("\nminimo: %d\n", heap->min->key);
				consolidate(heap);
				exibirHeap(heap->min);
   				getch();
				break;
			}
			case 'C': //extract min -> fib heap
			{
				clrscr();
				inserir(&heap, 5);
				inserir(&heap, 2);
				inserir(&heap, 8);
				min = extractMin(heap);
				printf ("\nMinimo: %d\n", min->key);
				inserir(&heap, 3);
				inserir(&heap, 1);
				min = extractMin(heap);
				printf ("\nMinimo: %d\n", min->key);
				exibirHeap(heap->min);
				printf ("Fila de Prioridade\n");
				inicializar(&heap);
				int i = 1;
				while (i <= 10)
				{
					inserir(&heap, i);
					
					i++;
				}
				min = extractMin(heap);
				printf ("Minimo: %d\n", min->key);
				exibirHeap(heap->min);
				getch();
				break;
			}
			case 'D': //arvore geradore minima (MST) -> debug
			{
				//gerar a arvore minima
				//ja tenho o meu grafo (lista de adjacencia gerada -> Lista)
				
				//funcao para gerar a arvore minima
				clrscr();
				//char origem[qtdeVertices] = {};
				//char destino[qtdeVertices] = {};
				//int peso[qtdeVertices] = {};
				char origem[qtdeVertices];
				char destino[qtdeVertices];
				int peso[qtdeVertices];
				inicializarVetorInt(peso, qtdeVertices);
				inicializarVetorChar(origem, qtdeVertices);
				inicializarVetorChar(destino, qtdeVertices);
				arvoreGeradoraMinima(Lista, &arvoreMin, origem, destino, peso, 1);
				
				//exibir a arvore gerada
				clrscr();
				textcolor(3),printf("\nLista de Adjacencia da Arvore Geradora Minima (MST):\n");
				textcolor(WHITE);
				exibirListaAdjacencia(arvoreMin);
				textcolor(3),printf("\nArvore Geradora Minima (MST) Com Niveis:\n");
				textcolor(WHITE);
				exibirArvoreGeradoraMinima(origem[0], origem, destino, peso, qtdeVertices);
				
				//exibir o valor da arvore gerada
				int valor = valorArvoreMinima(arvoreMin);
				textcolor(3),printf("\nValor da Arvore Gerada: %d\n", valor);
				textcolor(WHITE);
				getch();
				
				break;
			}
			case 'E': //arvore geradore minima (MST) -> corrido
			{
				//gerar a arvore minima
				//ja tenho o meu grafo (lista de adjacencia gerada -> Lista)
				
				//funcao para gerar a arvore minima
				clrscr();
				//char origem[qtdeVertices] = {};
				//char destino[qtdeVertices] = {};
				//int peso[qtdeVertices] = {};
				char origem[qtdeVertices];
				char destino[qtdeVertices];
				int peso[qtdeVertices];
				inicializarVetorInt(peso, qtdeVertices);
				inicializarVetorChar(origem, qtdeVertices);
				inicializarVetorChar(destino, qtdeVertices);
				arvoreGeradoraMinima(Lista, &arvoreMin, origem, destino, peso, 0);
				
				//exibir a arvore gerada
				clrscr();
				textcolor(3),printf("\nLista de Adjacencia da Arvore Geradora Minima (MST):\n");
				textcolor(WHITE);
				exibirListaAdjacencia(arvoreMin);
				textcolor(3),printf("\nArvore Geradora Minima (MST) Com Niveis:\n");
				textcolor(WHITE);
				exibirArvoreGeradoraMinima(origem[0], origem, destino, peso, qtdeVertices);
				
				//exibir o valor da arvore gerada
				int valor = valorArvoreMinima(arvoreMin);
				textcolor(3),printf("\nValor da Arvore Gerada: %d\n", valor);
				textcolor(WHITE);
				getch();
				
				break;
			}
		}
	}while(op != 27);
	liberarMemListaAdj(&Lista);
	liberarMemListaAdj(&arvoreMin);
}

int main(void)
{
	executar();
	return 0;
}
