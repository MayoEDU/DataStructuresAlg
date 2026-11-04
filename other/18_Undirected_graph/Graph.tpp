#include <iostream>

#include "Graph.hpp"

template <typename T>
int Graph<T>::searchVertexIndex(const T& value) const
{
    for (int i = 0; i < static_cast<int>(verticies.size()); i++)
    {
        if (verticies[i] == value)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
void Graph<T>::insertVertex(const T& v)
{
    // Check for dupes
    if (searchVertexIndex(v) != -1)
    {
        std::cout << "insertVertex: vertex already exists\n";
        return;
    }
    // Add new Vertex
    verticies.push_back(v);
    std::vector<int> tmp;
    adjacency_lists.push_back(tmp); // creates empty list of neighbors
}

template <typename T>
void Graph<T>::insertEdge(const T& v1, const T& v2)
{
    const int i_v1 = searchVertexIndex(v1);
    const int i_v2 = searchVertexIndex(v2);

    if (i_v1 == -1 || i_v2 == -1)
    {
        std::cout << "insertEdge: incorrect vertices\n";
        return;
    }

    // Insert in the adjacency list
    adjacency_lists[i_v1].push_back(i_v2);
    adjacency_lists[i_v2].push_back(i_v1);
}