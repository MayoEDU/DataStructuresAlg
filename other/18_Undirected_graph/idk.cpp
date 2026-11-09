
#include <iostream>
#include <string>
#include "Graph.hpp"
int main() {
    Graph<char> secret;
    // Vertices and edges are intentionally not in code order.
    for (char symbol : std::string("YAG@KU#ZCRBDT")) {
        secret.insertVertex(symbol);
    }
    secret.insertEdge('R', '@');
    secret.insertEdge('#', 'Y');
    secret.insertEdge('U', 'A');
    secret.insertEdge('Z', 'C');
    secret.insertEdge('G', '@');
    secret.insertEdge('Y', 'D');
    secret.insertEdge('#', 'R');
    secret.insertEdge('Z', 'A');
    secret.insertEdge('G', 'B');
    secret.insertEdge('U', '#');
    secret.insertEdge('Y', 'A');
    secret.insertEdge('Z', '#');
    secret.insertEdge('G', '#');
    secret.insertEdge('Y', 'B');
    secret.insertEdge('@', 'U');
    secret.insertEdge('Z', 'B');
    secret.insertEdge('Y', 'C');
    secret.insertEdge('G', 'A');
    secret.insertEdge('Y', '@');
    secret.insertEdge('@', 'Z');
    secret.insertEdge('#', 'K');
    secret.insertEdge('@', 'T');
    // Arrange the printed letters by INCREASING degree.
    std::cout << "\nCandidate letters and their degrees:\n";
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (secret.hasEdge('@', c) && secret.hasEdge('#', c)) {
            std::cout << c << ": " << secret.getDegree(c) << '\n';
        }
    }
    return 0;
}