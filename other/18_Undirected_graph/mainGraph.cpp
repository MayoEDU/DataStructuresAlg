#include "Graph.hpp"

#include <iostream>
#include <string>
#include <vector>

int main()
{
    Graph<std::string> friends;

    friends.insertVertex("Ross");
    friends.insertVertex("Monica");
    friends.insertVertex("Rachel");
    friends.insertVertex("Chandler");
    friends.insertVertex("Joey");
    friends.insertVertex("Phoebe");
    
    // Create friendships between everyone except Phoebe.
    const std::vector<std::string> everyoneButPhoebe{
        "Ross", "Monica", "Rachel", "Chandler", "Joey"
    };

    for (std::size_t i = 0; i < everyoneButPhoebe.size(); ++i)
    {
        for (std::size_t j = i + 1; j < everyoneButPhoebe.size(); ++j)
        {
            friends.insertEdge(everyoneButPhoebe[i], everyoneButPhoebe[j]);
        }
    }

    // graph print
    friends.print();
    
    friends.BFS("Ross");
    
    std::cout << "isConnected: " << friends.isConnected() << std::endl;
    friends.insertEdge("Ross", "Phoebe");
    std::cout << "isConnected: " << friends.isConnected() << std::endl;

    // how many friends chandler has
    std::cout<< friends.getDegree("Chandler") << std::endl;
    
    // are phobe and joey friend
    std::cout << friends.hasEdge("Phoebe", "Joey") << std::endl;
    
    friends.BFS("Ross");
    friends.DFS("Ross");
    
    std::cout << "Ross to Phoebe: "
              << friends.shortestPath("Ross", "Phoebe") << std::endl;
    
    return 0;
}