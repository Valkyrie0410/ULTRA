#include "../Algorithms/Dijkstra/Dijkstra.h"
#include "Commands/NetworkIO.h"
#include "../DataStructures/Graph/Graph.h"
#include "../DataStructures/Queries/Queries.h"
#include<iostream>

int main() {
	TransferGraph graph_1;
	Graph::fromDimacs("graph_data", graph_1);
	Dijkstra<TransferGraph> dijkstra(graph_1);
	std::vector<VertexQuery> queries = generateRandomVertexQueries(1070377, 200);
	auto start = std::chrono::steady_clock::now();
	for (const auto& query : queries) {

	    Vertex source(query.source);
	    dijkstra.run(source);
	    Vertex target(query.target);
	    int shortestLength = dijkstra.getDistance(target);
	    std::vector<Vertex> shortestPath = dijkstra.getPath(target);
	}
	auto end = std::chrono::steady_clock::now();
	auto runtime_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    std::cout << "Total runtime in seconds for 200 random Dijkstra: " << runtime_seconds << std::endl;
	
    return 0;
}