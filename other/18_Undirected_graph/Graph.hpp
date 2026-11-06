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

    private:
        std::vector<T> verticies;
        std::vector<std::vector<int>> adjacency_lists;
    
        int searchVertexIndex(const T& value) const;
};

#include "Graph.tpp"

#endif