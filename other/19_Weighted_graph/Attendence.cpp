#include "Graph.hpp"
#include <iostream>
#include <string>
int main() {
    Graph<std::string> cities;
    cities.insertVertex("Lakeland");
    cities.insertVertex("Orlando");
    cities.insertVertex("Tampa");
    cities.insertVertex("Miami");
    cities.insertVertex("Naples");
    cities.insertVertex("KeyWest");
    cities.insertEdge("Lakeland", "Orlando", 50);
    cities.insertEdge("Lakeland", "Miami", 350);
    cities.insertEdge("Lakeland", "Tampa", 40);
    cities.insertEdge("Orlando", "Miami", 200);
    cities.insertEdge("Naples", "Miami", 150);
    cities.insertEdge("Tampa", "Miami", 500);
    cities.insertEdge("Tampa", "Naples", 185);
    // Check connectivity and unreachable paths
    bool disconnected = !cities.isConnected() &&
    cities.shortestPathByEdges("Lakeland", "KeyWest") == -1;
    cities.insertEdge("Naples", "KeyWest", 170);
    bool connected = cities.isConnected();
    if (!disconnected || !connected) {
        std::cout << "Check your graph implementation.\n";
        return 0;
    }
    // Generate the attendance code
    std::string code;
    code += static_cast<char>('0' + cities.getDegree("Miami"));
    code += static_cast<char>(
    '0' + cities.shortestPathByEdges("Lakeland", "KeyWest")
    + cities.shortestPathByEdges("Lakeland", "Naples")
    );
    code += static_cast<char>(
    'A' + cities.getDegree("Tampa")
    + cities.shortestPathByEdges("Orlando", "Naples")
    );
    code += static_cast<char>(
    'A' + cities.getDegree("Miami")
    + cities.shortestPathByEdges("Lakeland", "Naples")
    );
    code += static_cast<char>(
    '0' + cities.shortestPathByEdges("Lakeland", "KeyWest")
    + connected
    );
    std::cout << "Attendance code: " << code << '\n';
    return 0;
}