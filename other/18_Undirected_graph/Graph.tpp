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
void Graph<T>::print() const
{
    for (int i = 0; i < verticies.size(); i++)
    {
        std::cout << verticies[i] << ": ";

        for (int neighbor : adjacency_lists[i])
        {
            std::cout << verticies[neighbor] << " ";
        }

        std::cout << "\n";
    }
}

template <typename T>
void Graph<T>::insertVertex(const T& value)
{
    // Check for dupes
    if (searchVertexIndex(value) != -1)
    {
        std::cout << "insertVertex: vertex already exists\n";
        return;
    }
    // Add new Vertex
    verticies.push_back(value);
    adjacency_lists.push_back(std::vector<int>()); // creates empty list of neighbors
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
    
    // Avoid duplicate edges
    for (int neighbor : adjacency_lists[i_v1])
    {
        if (neighbor == i_v2)
        {
            return;
        }
    }

    // Insert in the adjacency list
    adjacency_lists[i_v1].push_back(i_v2);
    adjacency_lists[i_v2].push_back(i_v1);
}

// Find vertex, -1 if not found
// Return adjacency_list size
template <typename T>
int Graph<T>::getDegree(const T& vertex) const
{
    int index = searchVertexIndex(vertex);
    if (index == -1)
    {
        return -1;
    }
    else
    {
        return adjacency_lists[index].size();
    }
}

//Find indices of both vert, return -1 if not found
// Search adjacency_list for first (second) index
template <typename T>
bool Graph<T>::hasEdge(const T& v1,const T& v2) const
{
    int index1 = searchVertexIndex(v1);
    int index2 = searchVertexIndex(v2);

    if (index1 == -1 || index2 == -1)
    {
        return false;
    }

    for (int neighbor : adjacency_lists[index1])
    {
        if (neighbor == index2)
        {
            return true;
        }
    }

    return false;
}