#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

template <typename T>
class Graph
{
    public:
        void insertVertex(const T& value);
        void insertEdge(const T& v1, const T& v2);
    
        void print() const; // Print vertices and adjacency list
        int getDegree(const T& vertex) const;
        bool hasEdge(const T& v1, const T& v2) const;
        bool isConnected() const;
    
        // Graph Traversals (BSF and DFS
        void BFS(const T& v) const;
        void DFS(const T& v) const;
    
        int shortestPath(const T& start, const T& end) const;
    
    private:
        std::vector<T> verticies;
        std::vector<std::vector<int>> adjacency_lists;
    
        int searchVertexIndex(const T& value) const;
        void DFSExplore(int index, std::vector<bool>& visited, bool print = true) const;
};

#include "Graph.tpp"

#endif