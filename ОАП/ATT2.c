#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Узел списка смежности. Одна вершина
typedef struct adjnode{
    int vertex;//соседняя вершина
    struct adjnode* next;//След. сосед
}AdjNode;

//структура графа
typedef struct Graph{
    int numVertices;//кол-во вершин
    AdjNode** adjLists;//массив списков смежности
    bool* visited;//массив посещённых вершин (Для DFS)
}Graph;

AdjNode* createAdjNode(int v)
{
 AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}