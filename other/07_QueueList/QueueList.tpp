#ifndef QUEUE_LIST_TPP
#define QUEUE_LIST_TPP

template <typename T>
QueueList<T>::QueueList()
    : front(nullptr), back(nullptr), queue_size(0) {}

template <typename T>
QueueList<T>::~QueueList() {
    clear();
}

template <typename T>
void QueueList<T>::enqueue(const T& value) {
    DDLNode<T>* node = new DDLNode<T>(value);
    
    if (empty()) {
        front = node;
        back = node;
    } else {
        back->next = node;
        back = node;
    }
    
    ++queue_size;
}

template <typename T>
T QueueList<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("dequeue: Empty queue");
    }
    
    T value = front->data;
    DDLNode<T>* old_front = front;
    front = front->next;
    delete old_front;
    --queue_size;
    
    if (empty()) {
        back = nullptr;
    }
    
    return value;
}

template <typename T>
const T& QueueList<T>::front_element() const {
    if (empty()) {
        throw std::out_of_range("front_element: Empty queue");
    }
    return front->data;
}

template <typename T>
int QueueList<T>::size() const {
    return queue_size;
}

template <typename T>
bool QueueList<T>::empty() const {
    return queue_size == 0;
}

template <typename T>
void QueueList<T>::print() const {
    std::cout << "[ ";
    DDLNode<T>* current = front;
    while (current) {
        std::cout << current->data;
        if (current->next) {
            std::cout << " <- ";
        }
        current = current->next;
    }
    std::cout << " ]" << std::endl;
}

template <typename T>
void QueueList<T>::clear() {
    while (!empty()) {
        dequeue();
    }
}

#endif
