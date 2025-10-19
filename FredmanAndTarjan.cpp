#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#define L 50
#define C 50

#include "TADFibHeap.h"
#include "TADListaAdj.h"
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
    Moldura(1,1, 120,30, 7, 7);
	gotoxy(45,4), printf("     ====================================");
	gotoxy(65,5), textcolor(3),printf ("Fredman");
	gotoxy(67,6), textcolor(3),printf ("And");
	gotoxy(65,7), textcolor(3),printf ("Tarjan");
	gotoxy(45,8), textcolor(7),printf("     ====================================");
	
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
char menu (void)
{
	gotoxy(4,9), textcolor(7),printf("[A] - Matriz de Adjacencia");
	gotoxy(4,10), textcolor(7),printf("[B] - Testar Insert E Meld");
	gotoxy(4,11), textcolor(7),printf("[C] - Testar ExtractMin");
	gotoxy(4,12), textcolor(7),printf ("[ESC] - Sair");
	
	return toupper(getch());
}




void executar(void)
{
	char op;
	do
	{
		FibHeap *heap, *heap2;
		FibNo *min;
		inicializar(&heap);
		inicializar(&heap2);
		int m[L][C], qtdeVertices = 0, qtdeLinhas = 0, qtdeColunas = 0, qtdeArestas = 0;
		char vertices[C], arestas[C];
		ListaAdjacencia *Lista = NULL;
		arestas[0] = '\0';
		clrscr();
		//Moldura(1,1, 120,30, 7, 7);
		gotoxy(45,4), printf("     ====================================");
		gotoxy(65,5), textcolor(3),printf ("Fredman");
		gotoxy(67,6), textcolor(3),printf ("And");
		gotoxy(65,7), textcolor(3),printf ("Tarjan");
		gotoxy(45,8), textcolor(7),printf("     ====================================");
		op = menu();
		switch(op)
		{
			case 'A':
				clrscr();
				lerTxTMatrizAdjacencia(m, &qtdeVertices, &qtdeLinhas, &qtdeColunas, vertices);
				exibirMatrizAdjacenciaComVertices(m, vertices,qtdeLinhas,qtdeColunas);
				getch();
				converterMatrizParaLista(m, &Lista, qtdeVertices, vertices);
				clrscr();
				exibirListaAdjacencia(Lista);
				getch();
				//prim_fibheap(m, qtdeVertices);
				break;
			case 'B':
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
			case 'C':
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
	}while(op != 27);
	
}
int main(void)
{
	executar();
	return 0;
}
