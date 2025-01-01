#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "graph.h"

Graph *createGraph()
{
	// system("clear");
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	
	char *_label_ = (char *)malloc(sizeof(char) * 8);
	fprintf(stdout, "\nEnter graph name: ");
	fscanf(stdin, "%s", _label_);

	graph->label = _label_;		

	createVertices(graph);

	createEdges(graph);

	graph->type = BASIC;

	system("clear");

	return graph;
}

Vertex *createVertex(char *data)
{
	Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
	char *_data_ = (char *)malloc(sizeof(char) * 8);
	strcpy(_data_, data);
	vertex->data = _data_;
	// fprintf(stdout, "\ndata in createVertex: %s\n", _data_);
	// vertex->deleteVertex = 1;
	return vertex;
}

void createVertices(Graph *graph)
{
	char *label = (char *)malloc(sizeof(char) * 8);
	fprintf(stdout, "\nEnter vertex name: ");
	fscanf(stdin, "%s", label);
	graph->vertices_label = label;

	int numberOfVertices;
	fprintf(stdout, "Enter number of %s(s): ", graph->vertices_label);
	fscanf(stdin, "%d", &numberOfVertices);
	graph->numberOfVertices = numberOfVertices;

	Vertex *vertices = (Vertex *)malloc(sizeof(Vertex) * graph->numberOfVertices);
	graph->vertices = vertices;

	fprintf(stdout, "\nEnter the %d %s value(s) below:\n_________________\n", graph->numberOfVertices, graph->vertices_label);
	for (int i = 0; i < graph->numberOfVertices; i++)
	{
		char *str = (char *)malloc(sizeof(char) * 8);
		fprintf(stdout, "%d. ", i);
		fscanf(stdin, "%s", str);
		*(graph->vertices + i) = *createVertex(str);
		(graph->vertices + i)->index = i;
		// (graph->vertices + i)->deleteVertex = 1;
	}

	fprintf(stdout, "\nAll %d %s(s) entered:\n_________________\n", graph->numberOfVertices, graph->vertices_label);
}

void addIndicesToVertices(Graph *graph)
{
	int i = 0;
	for (Vertex *vertex = graph->vertices; vertex < graph->vertices + graph->numberOfVertices; vertex++)
	{
		vertex->index = i;
		i++;
	}
}

Edge *createEdge(Vertex *v_0, Vertex *v_1)
{
	Edge *edge = (Edge *)malloc(sizeof(Edge));
	
	edge->edge[0] = v_0;
	edge->edge[1] = v_1;
	
	return edge;
}

void createEdges(Graph *graph)
{
	char *_label_ = (char *)malloc(sizeof(char) * 8);
	fprintf(stdout, "\nEnter inter-vertex property (relationship): ");
	fscanf(stdin, "%s", _label_);
	graph->edges_label = _label_;

	int numberOfEdges;
	fprintf(stdout, "Enter number of %s relationships: ", graph->edges_label);
	fscanf(stdin, "%d", &numberOfEdges);

	if(graph->numberOfVertices <= 0) 
		numberOfEdges = 0;
	else if(graph->numberOfVertices == 1 ) 
	{	if(numberOfEdges == 0 || numberOfEdges == 1) numberOfEdges = numberOfEdges;
		else
			numberOfEdges = 1;
	}
	else 
		numberOfEdges = numberOfEdges % ( ( graph->numberOfVertices * (graph->numberOfVertices - 1) ) + 1 );
		
	graph->numberOfEdges = numberOfEdges;

	Edge *edges = (Edge *)malloc(sizeof(Edge) * graph->numberOfEdges);
	graph->edges = edges;
	
	if(graph->numberOfVertices == 0) return;
	fprintf(stdout, "\nEnter the %d pairs of %s relationships below:\n_________________\n", graph->numberOfEdges, graph->edges_label);
	for (int i = 0; i < graph->numberOfEdges; i++)
	{
		int index_0, index_1;
		Vertex *vertex_0, *vertex_1;
		fprintf(stdout, "Edge %d\n", i);
		fprintf(stdout, "%s in index: ", graph->vertices_label);
		fscanf(stdin, "%d", &index_0);	
		fprintf(stdout, "%s %s in index ", graph->edges_label, graph->vertices_label);	
		fscanf(stdin, "%d", &index_1);
		
		vertex_0 = get1stVertexPtrFromVertexIndex(graph, index_0);
		vertex_1 = get1stVertexPtrFromVertexIndex(graph, index_1);
		*(graph->edges + i) = *createEdge(vertex_0, vertex_1);	
		(graph->edges + i)->index = i;
	}

	addIndicesToEdges(graph);

	fprintf(stdout, "\n%d pairs of vertices created:\n_________________\n\n", graph->numberOfEdges);
}

void addIndicesToEdges(Graph *graph)
{
	int i = 0;
	for(Edge *edge = graph->edges; edge < graph->edges + graph->numberOfEdges; edge++)
	{
		edge->index = i;
		i++;
	}
}

Vertex *get1stVertexPtrFromIndexInEdge(Graph *graph, int edgeIndex, int index)
{
	// fprintf(stdout, "\nedgeIndex in g1vpfiie: %d\n", edgeIndex);
	for(int i = 0; i < graph->numberOfVertices; i++)
		if( strcmp( (graph->vertices + i)->data, (graph->edges + edgeIndex)->edge[index]->data ) == 0 ) return (graph->vertices + i);
	fprintf(stdout, "\nedgeIndex in g1vpfiie: %d\n", edgeIndex);
	return NULL;	
}	

Vertex *get1stVertexPtrFromVertexIndex(Graph *graph, int index)
{
	if( index < 0) index *= -1;
	index %= graph->numberOfVertices;
	
	for(int i = 0; i < graph->numberOfVertices; i++)
	{
		if( (graph->vertices + i)->index == index ) return (graph->vertices + i);
	}
	return NULL;
}

void printGraph(Graph *graph)
{
	char *punc_vertex = (char *)malloc(sizeof(char) * 2);
	char *punc_edge = (char *)malloc(sizeof(char) * 2);
	strcpy(punc_vertex, "; ");
	strcpy(punc_edge, "; ");
	fprintf(stdout, "\nGraph_%s { ", graph->label );

	fprintf(stdout, "\n\tVertices_%s { ", graph->vertices_label );
	for (int i = 0; i < graph->numberOfVertices; i++)
	{
		if(i == graph->numberOfVertices - 1) strcpy(punc_vertex, " ");
		fprintf(stdout, "%d: %s%s", (graph->vertices + i)->index, (graph->vertices + i)->data, punc_vertex);
	}
	fprintf(stdout, "}" );

	fprintf(stdout, "\n\tEdges_%s { ", graph->edges_label );
	for (int i = 0; i < graph->numberOfEdges; i++)
	{
		if(i == graph->numberOfEdges - 1) strcpy(punc_edge, " ");
		fprintf(stdout, "%d: (%d, %d)%s",(graph->edges + i)->index, (graph->edges + i)->edge[0]->index, (graph->edges + i)->edge[1]->index, punc_edge);
	}
	fprintf(stdout, "}" );

	fprintf(stdout, "\n}\n" );
}

void drawGraph(Graph *graph)
{
	int size = graph->numberOfVertices;

	fprintf(stdout, "\n\n");
	for (int i = 0; i <= size; i++) 
		if(i > 0) 
			fprintf(stdout, "%-20s", (graph->vertices + (i - 1))->data);
		else fprintf(stdout, "%20s", " ");
	fprintf(stdout, "\n");
	for (int i = 0; i < size; i++) fprintf(stdout, "______________________");
	fprintf(stdout, "\n");

	for (int i = 0; i < size; i++)
	{
		Vertex *v_1 = get1stVertexPtrFromVertexIndex(graph, i);
		for (int j = 0; j <= size; j++)
		{
			if( j == 0) fprintf(stdout, "%-18s %-2s", (graph->vertices + i)->data, "|");
			else{
				Vertex *v_2 = NULL;
	
				if( size == 1) 
				{
					v_2 = v_1;
					// fprintf(stdout, "v_1: %p\tedge->edge[0]: %p\tv_2: %p\tedge->edge[1]: %p\n", v_1, graph->edges->edge[0], v_2, graph->edges->edge[1]);
				}
				else v_2 = get1stVertexPtrFromVertexIndex(graph, (j - 1));
				fprintf(stdout, "%-20d", hasEdge(graph, v_1, v_2));
			}
		}
		fprintf(stdout, "\n");
		fprintf(stdout, "%20s\n", "|");
	}
	for (int i = 0; i < size; i++) fprintf(stdout, "______________________");
	fprintf(stdout, "\n\n");
}

bool hasEdge(Graph *graph, Vertex *v_1, Vertex *v_2)
{
	for (Edge *edge = graph->edges; edge <  graph->edges + graph->numberOfEdges; edge++)
	{
		if((v_1 == edge->edge[0] && v_2 == edge->edge[1]) || (v_2 == edge->edge[0] && v_1 == edge->edge[1]) )
			return true; 
	}
	return false;
}

void addVertex(Graph *graph, char *data)
{                
	char *str = (char *)malloc(sizeof(char) * 8);
	strcpy(str, data);
	
	*(graph->vertices + graph->numberOfVertices) = *createVertex(str);

	(graph->vertices + graph->numberOfVertices)->index += graph->numberOfVertices; 	
	graph->numberOfVertices += 1;
}

char *deleteVertex(Graph* graph)
{
	int index = getIndexFromStdInput(graph);

	int k = index;

	char *data = (char *)malloc(sizeof(char) * 8);

	while (k < graph->numberOfVertices)
	{
		if( k == index ) 
		{
			data = (graph->vertices + index)->data;
			graph->numberOfVertices -= 1;
		}

		if (k < graph->numberOfVertices)
		{
			*(graph->vertices + k) = *(graph->vertices + k + 1);
			(graph->vertices + k)->index -= 1;
		}
		else
		{
			*(graph->vertices + k) = *(graph->vertices + k);
			(graph->vertices + k)->index = (graph->vertices + k)->index;
		}
	
		k++;	
	}

	deleteEdgeFromVertexIndex(graph, index);

	adjustIndicesAfterDeletion(graph, index);

	return data;
}

char *deleteEdgeFromVertexIndex(Graph* graph, int index)
{
	char *data = (char *)malloc(sizeof(char) * 8 );
	data = graph->vertices->data;

	for (Edge *edge = graph->edges; edge < graph->edges + graph->numberOfEdges; edge++)
	{

		int e_index = getEdgeIndexFromVertexIndex(edge, index);
		if(e_index >= 0)
		{

		       	removeEdge(graph, e_index);
			edge--; 
		}
	}

	return data;
}

int getEdgeIndexFromVertexIndex(Edge *edge, int v_index)
{
	if(edge->edge[0]->index == v_index || edge->edge[1]->index == v_index) return edge->index;	
	return -1;
}

 
Edge *removeEdge(Graph *graph, int index)
{
	Edge *_edge_ = (Edge *)malloc(sizeof(Edge));
	_edge_ = graph->edges + index;

	int k = index;

	while(k < graph->numberOfEdges)
	{
		if(k == index) graph->numberOfEdges--;
		graph->edges[k] = graph->edges[k + 1];
		(graph->edges + k)->index -= 1;
		k++;	
	}
		
	return _edge_;
}
 
void adjustIndicesAfterDeletion(Graph *graph, int index){
	fprintf(stdout, "\n");
	for(Edge* edge = graph->edges; edge < graph->edges + graph->numberOfEdges; edge++)
	{
		// fprintf(stdout, "before %d (%d, %d)\n", edge->index, edge->edge[0]->index, edge->edge[1]->index);
		if(edge->edge[0]->index > index) 
		{
			edge->edge[0]--;
			//edge->edge[0]->deleteVertex = 0;

		}
		if(edge->edge[1]->index > index) 
		{
			edge->edge[1]--;
			//edge->edge[1]->deleteVertex = 0;
		}
		// fprintf(stdout, "after %d (%d, %d)\n\n", edge->index, edge->edge[0]->index, edge->edge[1]->index);
		
	}
	
/*	
	for(Vertex *vertices = graph->vertices; vertices < graph->vertices + graph->numberOfVertices; vertices++)
	{
		vertices->deleteVertex = 1;
	}	
*/
}

int getIndexFromStdInput(Graph *graph)
{
	int index;
        fprintf(stdout, "\n\nEnter index: ");
        fscanf(stdin, "%d", &index);

        // if (graph->numberOfVertices <= 0) return 0;
        if (index < 0) index *= -1;

        if (index >= graph->numberOfVertices) index %= graph->numberOfVertices + 1;
	return index;
}

void insertVertex(Graph *graph)
{
	char *str = (char *)malloc(sizeof(char) * 8);
        fprintf(stdout, "\nEnter new %s: ", graph->vertices_label);
        fscanf(stdin, "%s", str);

	int index = getIndexFromStdInput(graph);

	if(index == graph->numberOfVertices)
		addVertex(graph, str);
	else{
	
		int k = graph->numberOfVertices;
		printGraph(graph);

		char *temp = (char *) malloc(sizeof(char) * 8); 
	
		*temp = *((graph->vertices)->data);
	
		while(k >= index)
		{
			*(graph->vertices + k + 1) = *(graph->vertices + k);
			
			(graph->vertices + k + 1)->index += 1;
			k--;
		}
		*(graph->vertices + index) = *createVertex(str);
		(graph->vertices + index)->index = index;
		graph->numberOfVertices++;
	}
}

void deleteEdge(Graph *graph)
{
	fprintf(stdout, "\nEnter index of edge to be deleted: ");
 
	int index = getIndexFromStdInput(graph);

	index %= graph->numberOfEdges;

	int k = index;

	while (k < graph->numberOfEdges)
	{
		*(graph->edges + k) = *(graph->edges + k + 1);
		(graph->edges + k)->index -= 1;
	
		k++;	
	}
	graph->numberOfEdges -= 1;
}

void insertEdge(Graph *graph)
{
	int stVertexIndex, ndVertexIndex;
	fprintf(stdout, "Enter indices of vertices for new edge: ");
	fprintf(stdout, "\nIndex for first vertex: ");
	fscanf(stdin, "%d", &stVertexIndex);
	fprintf(stdout, "Index for second vertex: ");
	fscanf(stdin, "%d", &ndVertexIndex);

	stVertexIndex %= graph->numberOfVertices;
	ndVertexIndex %= graph->numberOfVertices;

	Edge *edge = (Edge *)malloc(sizeof(Edge));

	for (Vertex *vertex = graph->vertices; vertex < graph->vertices + graph->numberOfVertices; vertex++)
	{
		if(vertex->index == stVertexIndex) edge->edge[0] = vertex;
		if(vertex->index == ndVertexIndex) edge->edge[1] = vertex;
	}

	*(graph->edges + graph->numberOfEdges) = *edge;
	(graph->edges + graph->numberOfEdges)->index = graph->numberOfEdges;
	graph->numberOfEdges++;
}

char *getGraphName(Graph *graph)
{
	return graph->label;
}

char *getGraphVertexName(Graph *graph)
{
	return graph->vertices_label;
}

char *getGraphEdgeName(Graph *graph)
{
	return graph->edges_label;
}

char *getGraphType(Graph *graph)
{
	char *type = (char *)malloc(sizeof(type));
	switch(graph->type)
	{
		case 1:
			strcpy(type, "Basic");
			break;
		case 2:
			strcpy(type, "Directed");
			break;
		case 3:
			strcpy(type, "Undirected");
			break;
	}
	return type;
}

bool areEdgesEqual(Edge *e_0, Edge *e_1)
{
	if( (e_0->edge[0] == e_1->edge[0] && e_0->edge[1] == e_1->edge[1] ) || ( e_0->edge[0] == e_1->edge[1] && e_0->edge[1] == e_1->edge[0] )) 		
		return true;
	return false;
}

void deleteDuplicateEdges(Graph *graph)
{
	for(Edge *edge_1 = graph->edges; edge_1 < graph->edges + graph->numberOfEdges - 1; edge_1++)
	{
		for(Edge *edge_2 = edge_1 + 1; edge_2 < graph->edges + graph->numberOfEdges; edge_2++)
		{
			if(areEdgesEqual(edge_1, edge_2) == 1) 
			{
				int k = edge_2->index;
				while(k < graph->numberOfEdges)
				{
					*(graph->edges + k) = *(graph->edges + k + 1);
					(graph->edges + k)->index -= 1;
					k++;
					edge_1--;
					edge_2--;
				}	
				graph->numberOfEdges -= 1;	
			}
		}
	}
}

void deleteDuplicateVertices(Graph *graph)
{
	for(Vertex *vertex_1 = graph->vertices; vertex_1 < graph->vertices + graph->numberOfVertices - 1; vertex_1++)
		for(Vertex *vertex_2 = vertex_1 + 1; vertex_2 < graph->vertices + graph->numberOfVertices; vertex_2++)
			if(strcmp(vertex_1->data, vertex_2->data) == 0)
			{
				// fprintf(stdout, "\nvertices_start: %p\tv_1: %p\tv_2: %p\tvertices_end: %p\n",graph->vertices, vertex_1, vertex_2, graph->vertices + graph->numberOfVertices);
				int k = vertex_2->index;
				while(k < graph->numberOfVertices)
				{
					*(graph->vertices + k) = *(graph->vertices + k + 1);
					(graph->vertices + k)->index -= 1;
					k++;
				}
				vertex_2--;
				graph->numberOfVertices -= 1;
			}
}

void deleteEdgesWithoutVertices(Graph *graph)
{
	/* return NULL;
	for(Vertex* vertex = graph->vertices; vertex < graph->vertices + graph->numberOfVertices; vertex++)
	{
		for(Edge *edge = graph->edges; edge < graph->edges + graph->numberOfEdges; edge++)
		{
			if(!edgeInVertices(vertex, edge))
			{
				// fprintf(stdout, "\nedgeInVertices(vertex, edge): %d\n", edgeInVertices(vertex, edge));
				int k = graph->edges->index;
				while(k < graph->numberOfEdges)
				{
					*(graph->edges + k) = *(graph->edges + k + 1);
					(graph->edges + k)->index -= 1;
					k++;
					// vertex--;
				}
				// vertex--;
				edge--;
				graph->numberOfEdges -= 1;
			}
			fprintf(stdout, "\nedgeInVertices(vertex, edge): %d\n", edgeInVertices(vertex, edge));
		}
	}*/

	/*
	for(Edge *edge = graph->edges; edge < graph->edges + graph->numberOfEdges; edge++)
	{
		int cnt = 0;
		for(int i = 0; i < 2; i++)
		{
			for(Vertex* vertex = graph->vertices; vertex < graph->vertices + graph->numberOfVertices; vertex++)
			{
				if(edge->edge[i]->index == vertex->index)
					cnt++;

			}
				
		}
		if(cnt < 2)
		{
			int k = edge->index;		
			while(k < graph->numberOfEdges)
			{
				*(graph->edges + k) = *(graph->edges + k + 1);
				(graph->edges + k)->index -= 1;
				k++;
				// vertex--;
			}
			// vertex--;
			edge--;
			graph->numberOfEdges -= 1;
		}
	}
	*/

	// for(Edge *edge = graph->edges; edge < graph->edges + graph->numberOfEdges; edge++)
	for(int i = 0; i < graph->numberOfEdges; i++)
	{
		// int index = edge->index;
		// fprintf(stdout, "\ni in dewv: %d\n", i);
		Vertex *vertex_0 = get1stVertexPtrFromIndexInEdge(graph, i, 0);
             	Vertex *vertex_1 = get1stVertexPtrFromIndexInEdge(graph, i, 1);
             	*(graph->edges + i) = *createEdge(vertex_0, vertex_1);
		(graph->edges + i)->index = i;
		fprintf(stdout, "\ni in dewv: %d\n", i);
		// edge->edge[0] = createVertice(); 
	}
}

/*
bool edgeInVertices(Vertex *vertex, Edge *edge)
{
	int cnt = 0;
	// for(Vertex* vertex = graph->vertices; vertex < graph->numberOfVertices; vertex++)
	for(int i = 0; i < 2; i++)
	{
		// for(int i = 0; i < 2; i++)
		for(Vertex* vertex = graph->vertices; vertex < graph->vertices + graph->numberOfVertices; vertex++)
			if(edge->edge[i]->index == vertex->index)
				cnt++;
	}
	fprintf(stdout, "\ncnt: %d\n", cnt);	
	if (cnt < 1)
		return false;
	return true;
}
*/

Graph *copyGraph(Graph *graph, char *label)
{
	Graph *graphCopy = (Graph *)malloc(sizeof(Graph));
	graphCopy->type = graph->type;
	graphCopy->numberOfVertices = graph->numberOfVertices;
	graphCopy->numberOfEdges = graph->numberOfEdges;
	
	char *_label = (char *)malloc(sizeof(char) * 8);
	strcat(_label, graph->label);
	strcat(_label, "_");
	strcat(_label, label);
	graphCopy->label = _label;

	char *__label = (char *)malloc(sizeof(char) * 8);
	strcpy(__label, graph->vertices_label);
	graphCopy->vertices_label = __label;
	
	char *___label = (char *)malloc(sizeof(char) * 8);
	strcpy(___label, graph->edges_label);
	graphCopy->edges_label = ___label;

	Vertex *vertices = (Vertex *)malloc(sizeof(Vertex) * graph->numberOfVertices);
	for(int i = 0; i < graph->numberOfVertices; i++)
	{
		char *data = (char *)malloc(sizeof(char) * 8);
		strcpy(data, (graph->vertices + i)->data);
		(vertices + i)->data = data;
		(vertices + i)->index = (graph->vertices + i)->index;
	}
	graphCopy->vertices = vertices;
/*
	for (Vertex* vertex = vertices; vertex < vertices + graph->numberOfVertices; vertex++)
		fprintf(stdout, "vertices: %p\n", vertex);

	fprintf(stdout, "\n");

	for (Vertex* vertex = graph->vertices; vertex < graph->vertices + graph->numberOfVertices; vertex++)
		fprintf(stdout, "graph->vertices: %p\n", vertex);
*/
	Edge *edges = (Edge *)malloc(sizeof(Edge) * graph->numberOfEdges);
	
	int i = 0;
	// for(int i = 0; i < graph->numberOfEdges; i++)
	for(Edge *edge = graph->edges; edge < graph->edges + graph->numberOfEdges; edge++)
	{
		Edge *_edge_ = (Edge *)malloc(sizeof(Edge));	
		// int i = 0;
		// fprintf(stdout, "\nedge[%d]->edge[0]: %s\tedge[%d]->edge[1]: %s\n", i, edge->edge[0]->data, i, edge->edge[1]->data);
		for(Vertex *vertex = graphCopy->vertices; vertex < graphCopy->vertices + graphCopy->numberOfVertices; vertex++)
		{
			if(edge->edge[0]->index == vertex->index)
				_edge_->edge[0] = vertex;	
			if(edge->edge[1]->index == vertex->index)
				_edge_->edge[1] = vertex;
		}
			
		// fprintf(stdout, "\n_edge_[%d]->edge[0]: %s\t_edge_[%d]->edge[1]: %s\n", i, _edge_->edge[0]->data, i, _edge_->edge[1]->data);
		*(edges + i) = *_edge_;
		(edges + i)->index = (graph->edges + i)->index;
		i++;

		/*
		edge->edge[0] = getVertexFromIndex(graph, (graph->edges + i)->edge[0]->index);
		edge->edge[1] = getVertexFromIndex(graph, (graph->edges + i)->edge[1]->index);
		// (edges + i)->edge = edge;
		(edges + i)->index = (graph->edges + i)->index;
		*(edges + i) = *edge;
		*/
		// fprintf(stdout, "edge[%d]->data = %s\tedges[%d]->data = %s\n", i, (edge->edge + i)[0]->data, i, (edges->edge + i)[0]->data);
	}
	graphCopy->edges = edges;
	//graphCopy->edges = graph->edges;
	/*
	for (Edge* edge = edges; edge < edges + graph->numberOfEdges; edge++)
		fprintf(stdout, "edge->edge[0]: %p\tedge->edge[1]: %p\n", edge->edge[0], edge->edge[1]);

	fprintf(stdout, "\n");

	for (Edge* edge = graph->edges; edge < graph->edges + graph->numberOfEdges; edge++)
		fprintf(stdout, "edge->edge[0]: %p\tedge->edge[1]: %p\n", edge->edge[0], edge->edge[1]);
	*/
	return graphCopy;
}

Graph *basicToUndirected(Graph *graph, char *label)
{
	Graph *nGraph = copyGraph(graph, label);

	deleteDuplicateVertices(nGraph);
	
	deleteEdgesWithoutVertices(nGraph);

	deleteDuplicateEdges(nGraph);

	// deleteEdgesWithoutVertices(nGraph);

	return nGraph;
}
