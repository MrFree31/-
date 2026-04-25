#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
//==============Второе задание=============
typedef struct AdjNode{//Узел списка смежности(соседей)
	int vertex; //номер соседней вершины
	struct AdjNode* next; //след. сосед
}AdjNode;

typedef struct Graph{//Граф
	int numVertices; //кол-во вершин
	AdjNode** AdjLists; //Массив смежостей
	bool* visited; //Массив посещённых строк
}Graph;

AdjNode* createAdjNode(int v){//Создание узла списка смежностей
	AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;	
}

Graph* createGraph(int vertices){//Создание графа
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->numVertices = vertices;
	//Выделение памяти
	graph->AdjLists = (AdjNode**)malloc(vertices*sizeof(AdjNode*));
	graph->visited = (bool*)malloc(vertices*sizeof(bool));
	//Инициализация списков
	for(int i = 0; i<vertices; i++){
		graph->AdjLists[i] = NULL;
		graph->visited[i] = false;
	}
	return graph;
}

void freeGraph(Graph* graph){//Освободить память от графа
	for(int i = 0; i<graph->numVertices; i++){
		AdjNode* current = graph->AdjLists[i];
		while(current != NULL){
			AdjNode* temp = current;
			current = current->next;
			free(temp);			
		}
	}
	free(graph->AdjLists);
	free(graph->visited);
	free(graph);
}

void addEdge(Graph* graph, int src, int dest){
	//Прямо dest в src
	AdjNode* newNode = createAdjNode(dest);
	newNode->next = graph->AdjLists[src];//В начало ветки добавляем
	graph->AdjLists[src] = newNode;
	//Обратно src в dest
	newNode = createAdjNode(src);
	newNode->next = graph->AdjLists[dest];//В конец ветки
	graph->AdjLists[dest] = newNode;
}

void DFS(Graph* graph, int vertex){
	graph->visited[vertex] = true;//посетили вершину
	printf("%d ",vertex); //Вывод вершины
	
	AdjNode* adj = graph->AdjLists[vertex];
	while(adj!=NULL){// Идём далее по смежным, NULL - конец ветки
		int neighbor = adj->vertex;
		if(!graph->visited[neighbor]){
			DFS(graph,neighbor);
		}	
		adj = adj->next;
	}
	//ВОИД - НИКАКИХ РЕТЁРНОВ
}

//==============Третье задание==============
typedef struct TreeNode{//Cтруктура дерева
	int val;
	struct TreeNode* left;	
	struct TreeNode* right;
}TreeNode;

TreeNode* createTreeNode(int val){
	
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->val = val;
	root->left = NULL;
	root->right = NULL;
	return root;
}

TreeNode* fill(TreeNode* root, int add){
	if(root == NULL){
		root->val = add;
	}
	if(root->left == NULL){
		root->left = fill(root->left,add) ;
	}
	if(root->right == NULL){
		root->right = fill(root->right,add) ;
	}
	return root;
}

TreeNode* search(TreeNode* root, int target){
	if(root == NULL){
		return NULL;
	}
	if(root->val == target){
		return root;
	}
	TreeNode* leftR = search(root->left,target);
	if(leftR!=NULL){
		return leftR;
	}
	return search(root->right,target);
}

int main(){
	SetConsoleOutputCP(CP_UTF8);
	printf("ВТОРОЕ ЗАДАНИЕ\n");
	int startVertex = 0;
	Graph* graph = createGraph(7);
	addEdge(graph,0,1);
	addEdge(graph,0,2);	
	addEdge(graph,2,3);
	addEdge(graph,3,4);
	addEdge(graph,0,5);
	DFS(graph,4);
	freeGraph(graph);
	printf("\n");

	printf("ТРЕТЬЕ ЗАДАНИЕ\n");
	 TreeNode* root = createTreeNode(10);
    root->left = createTreeNode(5);
    root->right = createTreeNode(15);
    root->left->left = createTreeNode(3);
    root->left->right = createTreeNode(7);
    root->right->left = createTreeNode(67);
    root->right->right = createTreeNode(20);

    TreeNode* found = search(root, 67);
    if (found)
        printf("Найдено: %d\n", found->val);
    else
        printf("Не найдено\n");

    return 0;
}