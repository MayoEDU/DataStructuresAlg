#include <iostream>
#include <queue>

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
    for (std::size_t i = 0; i < verticies.size(); i++)
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

// BFS
template <typename T>
void Graph<T>::BFS(const T& start) const
{
    int start_index = searchVertexIndex(start);
    
    if (start_index == -1)
    {
        std::cout << "BFS: Incorrect vertex index\n";
        return;
    }
    std::cout << "BFS: ";
    // Create queue for vector of discovered vert.
    std::queue<int> q;
    std::vector<bool> discovered(verticies.size(), false);
    
    // Add start vertex for queue
    q.push(start_index);
    discovered[start_index] = true;
    
    while (!q.empty())
    {
        // Get front
        int curent_index = q.front();
        q.pop();
        
        std::cout << verticies[curent_index] << " ";
        
        // Discover Neighbor (s) and add non-discovered to queue
        for (int neighbor : adjacency_lists[curent_index])
        {
         if (!discovered[neighbor])
         {
             discovered[neighbor] = true;
             q.push(neighbor);
         }   
        }
        std::cout << "\n";
    }
}

// DFS
template <typename T>
void Graph<T>::DFS(const T& start) const
{
    int start_index = searchVertexIndex(start);
    if (start_index == -1)
    {
        std::cout << "DFS: Incorrect vertex index\n";
        return;
    }
    std::cout << "DFS: ";
    
    std::vector<bool> visited(verticies.size(), false);
    DFSExplore(start_index, visited);
    std::cout << "\n";
}

template <typename T>
void Graph<T>::DFSExplore(int index, std::vector<bool>& visited, bool print) const
{
    // Mark the current index as visited
    if (index < 0 || index >= static_cast<int>(verticies.size()))
    {
        std::cout << "DFSExplore: Incorrect vertex index\n";
        return;
    }

    visited[index] = true;
    if (print)
    {
        std::cout << verticies[index] << " ";
    }
    
    // Go through neighbors, if not visited, call DFSExplore for that vertex.
    for (int neighbor : adjacency_lists[index])
    {
        if (!visited[neighbor])
        {
            DFSExplore(neighbor, visited, print);
        }
    }
}

template <typename T>
bool Graph<T>::isConnected() const
{
    // Empty Graph
    if (verticies.empty())
    {
        return true;
    }
    
    //visited
    std::vector<bool> visited(verticies.size(), false);
    
    // Perform DFS
    DFSExplore(0, visited, false);
    for (bool v: visited)
    {
        if (!v)
        {
            return false;
        }
    }
    return true;
}

template <typename T>
int Graph<T>::shortestPath(const T& start, const T& end) const
{
    int start_index = searchVertexIndex(start);
    int end_index = searchVertexIndex(end);
    
    if (start_index == -1 || end_index == -1)
    {
        std::cout << "shortestPath: incorrect vertex index\n";
        return -1;
    }
    if (start == end)
    {
        return 0;
    }
    
    // Create queue, vector of discoverted vert
    std::queue<int> q;
    std::vector<int> distances(verticies.size(), -1);
    
    //Add start vertex to queue
    q.push(start_index);
    
    //Mark start index discovered
    distances[start_index] = 0;
    
    while (!q.empty())
    {
        int current_index = q.front();
        q.pop();
        
        for (int neighbor : adjacency_lists[current_index])
        {
            if (distances[neighbor] == -1)
            {
                distances[neighbor] = distances[current_index] + 1;
                if (neighbor == end_index)
                {
                    return distances[neighbor];
                }
                q.push(neighbor);
            }
        }
    }
    return -1;
}
