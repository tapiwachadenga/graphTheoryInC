#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "graph.h"

int main()
{
	Graph *graph = createGraph();
	// Graph *oldestSibling = createGraph();
	
	/*	
	for(int i = 0; i < graph->numberOfVertices; i++)
		fprintf(stdout, "Vertex Index: %-10ddata: %-10svisited: %10s\n", (graph->vertices + i)->index, (graph->vertices + i)->data, (graph->vertices + i)->visited ? "true":"false"); 

	fprintf(stdout, "\n");
	for(int i = 0; i < graph->numberOfEdges; i++)
		fprintf(stdout, "Edge: %-10dvert_1_data: %s<-------->vert_2_data: %-10s\n", i, (graph->edges + i)->edge[0]->data, (graph->edges + i)->edge[1]->data);
	fprintf(stdout, "\n");
	*/

	// printGraph(graph);
	printGraph(graph);
	drawGraph(graph);
	// deleteVertex(graph);
	// deleteEdge(graph);
	// insertVertex(graph);
	// insertEdge(graph);
	// fprintf(stdout, "\ngraph type: %s\n", getGraphType(graph));
        	
	// deleteDuplicateEdges(graph);
	// deleteDuplicateVertices(graph);
	// Graph *copy = copyGraph(graph, "copy");
	Graph *uGraph = basicToUndirected(graph, "undirected");
	printGraph(uGraph);
	drawGraph(uGraph);

	fprintf(stdout, "\n");

	return EXIT_SUCCESS;
}
