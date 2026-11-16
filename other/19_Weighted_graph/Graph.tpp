#include <iostream>
#include <limits>
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

        for (const Edge& edge : adjacency_lists[i])
        {
            std::cout << verticies[edge.neighbor] << "(" << edge.weight << ") ";
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
    adjacency_lists.push_back(std::vector<Edge>()); // creates empty list of neighbors
}

template <typename T>
void Graph<T>::insertEdge(const T& v1, const T& v2, int weight)
{
    const int i_v1 = searchVertexIndex(v1);
    const int i_v2 = searchVertexIndex(v2);

    if (i_v1 == -1 || i_v2 == -1)
    {
        std::cout << "insertEdge: incorrect vertices\n";
        return;
    }
    if (weight < 0)
    {
        std::cout << "insertEdge: weight cannot be negative\n";
        return;
    }

    // Avoid duplicate edges
    for (const Edge& edge : adjacency_lists[i_v1])
    {
        if (edge.neighbor == i_v2)
        {
            return;
        }
    }

    // Insert in the adjacency list
    adjacency_lists[i_v1].push_back({i_v2, weight});
    adjacency_lists[i_v2].push_back({i_v1, weight});
}

// Find vertex, -1 if not found
// Return adjacency_list size
template <typename T>
int Graph<T>::getDegree(const T& vertex) const
{
    const int index = searchVertexIndex(vertex);
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
bool Graph<T>::hasEdge(const T& v1, const T& v2) const
{
    const int i_v1 = searchVertexIndex(v1);
    const int i_v2 = searchVertexIndex(v2);

    if (i_v1 == -1 || i_v2 == -1)
    {
        return false;
    }

    for (const Edge& edge : adjacency_lists[i_v1])
    {
        if (edge.neighbor == i_v2)
        {
            return true;
        }
    }

    return false;
}

template <typename T>
int Graph<T>::getEdgeWeight(const T& v1, const T& v2) const
{
    const int i_v1 = searchVertexIndex(v1);
    const int i_v2 = searchVertexIndex(v2);

    if (i_v1 == -1 || i_v2 == -1)
    {
        return -1;
    }

    for (const Edge& edge : adjacency_lists[i_v1])
    {
        if (edge.neighbor == i_v2)
        {
            return edge.weight;
        }
    }
    return -1;
}

// BFS
template <typename T>
void Graph<T>::BFS(const T& start) const
{
    const int start_index = searchVertexIndex(start);

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
        for (const Edge& edge : adjacency_lists[curent_index])
        {
            if (!discovered[edge.neighbor])
            {
                discovered[edge.neighbor] = true;
                q.push(edge.neighbor);
            }
        }
        std::cout << "\n";
    }
}

// DFS
template <typename T>
void Graph<T>::DFS(const T& start) const
{
    const int start_index = searchVertexIndex(start);
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
    for (const Edge& edge : adjacency_lists[index])
    {
        if (!visited[edge.neighbor])
        {
            DFSExplore(edge.neighbor, visited, print);
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
    for (bool v : visited)
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
    const int start_index = searchVertexIndex(start);
    const int end_index = searchVertexIndex(end);

    if (start_index == -1 || end_index == -1)
    {
        std::cout << "shortestPath: incorrect vertex index\n";
        return -1;
    }

    if (start == end)
    {
        return 0;
    }

    // Create a distance vector and repeatedly select the closest unvisited vertex.
    const int infinity = std::numeric_limits<int>::max();
    std::vector<int> distances(verticies.size(), infinity);
    std::vector<bool> visited(verticies.size(), false);
    distances[start_index] = 0;

    for (std::size_t step = 0; step < verticies.size(); ++step)
    {
        int current_index = -1;
        for (std::size_t i = 0; i < distances.size(); ++i)
        {
            if (!visited[i] && distances[i] != infinity &&
                (current_index == -1 || distances[i] < distances[current_index]))
            {
                current_index = static_cast<int>(i);
            }
        }

        if (current_index == -1)
        {
            break;
        }
        if (current_index == end_index)
        {
            return distances[current_index];
        }

        visited[current_index] = true;
        for (const Edge& edge : adjacency_lists[current_index])
        {
            if (!visited[edge.neighbor] &&
                distances[current_index] <= infinity - edge.weight &&
                distances[current_index] + edge.weight < distances[edge.neighbor])
            {
                distances[edge.neighbor] = distances[current_index] + edge.weight;
            }
        }
    }

    return -1;
}

template <typename T>
int Graph<T>::shortestPathByEdges(const T& start, const T& end) const
{
    const int start_index = searchVertexIndex(start);
    const int end_index = searchVertexIndex(end);

    if (start_index == -1 || end_index == -1)
    {
        std::cout << "shortestPathByEdges: incorrect vertex index\n";
        return -1;
    }
    if (start_index == end_index)
    {
        return 0;
    }

    std::queue<int> q;
    std::vector<int> distances(verticies.size(), -1);
    q.push(start_index);
    distances[start_index] = 0;

    while (!q.empty())
    {
        const int current_index = q.front();
        q.pop();

        for (const Edge& edge : adjacency_lists[current_index])
        {
            if (distances[edge.neighbor] == -1)
            {
                distances[edge.neighbor] = distances[current_index] + 1;
                if (edge.neighbor == end_index)
                {
                    return distances[edge.neighbor];
                }
                q.push(edge.neighbor);
            }
        }
    }

    return -1;
}
