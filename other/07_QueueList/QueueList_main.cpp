#include "QueueList.hpp"
#include <iostream>

int main() {
    QueueList<int> queue;

    // Test enqueue
    queue.enqueue(5);
    queue.enqueue(15);
    queue.enqueue(25);
    queue.enqueue(35);

    std::cout << "Queue after enqueuing 5, 15, 25, 35:" << std::endl;
    queue.print();
    std::cout << "Size: " << queue.size() << std::endl;
    std::cout << "Front: " << queue.front_element() << std::endl;

    // Test dequeue
    std::cout << "\nDequeuing..." << std::endl;
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    queue.print();

    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    queue.print();

    // Test empty after dequeuing all
    std::cout << "\nDequeuing remaining elements..." << std::endl;
    queue.dequeue();
    queue.dequeue();
    queue.print();
    std::cout << "Empty? " << (queue.empty() ? "true" : "false") << std::endl;

    return 0;
}
