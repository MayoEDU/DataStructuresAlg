#include "Graph.hpp"

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

    for (int i = 0; i < everyoneButPhoebe.size(); ++i)
    {
        for (int j = i + 1; j < everyoneButPhoebe.size(); ++j)
        {
            friends.insertEdge(everyoneButPhoebe[i], everyoneButPhoebe[j]);
        }
    }

    friends.print();

    return 0;
}