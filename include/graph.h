#include <stdbool.h>
#ifndef GRAPH_H
#define GRAPH_H

typedef enum Type{
	BASIC = 1,
	DIRECTED,
	UNDIRECTED
}Type;

typedef struct Vertex{
	char *data;
	int index;
	// bool deleteVertex;
}Vertex;

typedef struct Edge{
	Vertex *edge[2];
	int index;
}Edge;

typedef struct Graph{
	Vertex *vertices;
	Edge *edges;
	Type type;
	char *label;
	char *vertices_label;
	char *edges_label;
	int numberOfVertices;
	int numberOfEdges;
}Graph;

void addIndicesToVertices(Graph *);

Vertex *createVertex(char *);

void createVertices(Graph *);

Vertex *get1stVertexPtrFromVertexIndex(Graph*, int);

Vertex *get1stVertexPtrFromIndexInEdge(Graph*, int, int);

Edge *createEdge(Vertex *, Vertex *);

void createEdges(Graph *);

void addIndicesToEdges(Graph *);

Graph *createGraph();

void printGraph(Graph *);

void drawGraph(Graph *);

bool hasEdge(Graph *, Vertex *, Vertex *);

Vertex *getVertexFromIndex(Graph *, int);

void addVertex(Graph *, char *);

char *deleteVertex(Graph*);

char *deleteEdgeFromVertexIndex(Graph*, int);

Edge *removeEdge(Graph *, int); 

int getEdgeIndexFromVertexIndex(Edge *, int );

void adjustIndicesAfterDeletion(Graph*, int);

void updateEdgesAfterVertexShift(Graph *, Vertex *, Vertex *, int);

int getIndexFromStdInput(Graph *);

void insertVertex(Graph *);

void deleteEdge(Graph *);

void insertEdge(Graph *);

char *getGraphName(Graph *);

char *getGraphVertexName(Graph *);

char *getGraphEdgeName(Graph *);

char *getGraphType(Graph *);

void toUndirected(Graph *);

bool areEdgesEqual(Edge *, Edge *);

void deleteDuplicateEdges(Graph *);

void deleteDuplicateVertices(Graph *);

void deleteEdgesWithoutVertices(Graph *);

bool edgeInVertices(Vertex *, Edge *);

Graph *copyGraph(Graph *, char *);

Graph *basicToUndirected(Graph *, char *);

#endif
