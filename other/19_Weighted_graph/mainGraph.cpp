#include "Graph.hpp"

#include <iostream>
#include <string>
#include <vector>

int main()
{
    Graph<std::string> cities;

    cities.insertVertex("Lakeland");
    cities.insertVertex("Orlando");
    cities.insertVertex("Miami");
    cities.insertVertex("Naples");
    cities.insertVertex("Tampa");

    cities.insertEdge("Lakeland", "Orlando", 50);
    cities.insertEdge("Orlando", "Miami", 200);
    cities.insertEdge("Miami", "Naples", 150);
    cities.insertEdge("Naples", "Tampa", 185);
    cities.insertEdge("Tampa", "Lakeland", 40);
    cities.insertEdge("Lakeland", "Miami", 350);
    cities.insertEdge("Miami", "Tampa", 500);

    // graph print
    cities.print();

    cities.BFS("Lakeland");

    std::cout << "isConnected: " << cities.isConnected() << std::endl;

    // how many connections Lakeland has
    std::cout << cities.getDegree("Lakeland") << std::endl;

    // are Miami and Tampa connected
    std::cout << cities.hasEdge("Miami", "Tampa") << std::endl;

    cities.BFS("Lakeland");
    cities.DFS("Lakeland");

    std::cout << "Lakeland to Miami: "
        << cities.shortestPath("Lakeland", "Miami") << " miles" << std::endl;
    std::cout << "Lakeland to Miami: "
        << cities.shortestPathByEdges("Lakeland", "Miami") << " edges" << std::endl;

    return 0;
}
