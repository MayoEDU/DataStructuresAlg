#ifndef QUEUE_ARRAY_TPP
#define QUEUE_ARRAY_TPP

template <typename T, int CAPACITY>
QueueArray<T, CAPACITY>::QueueArray()
    : front_idx(0), back_idx(-1), queue_size(0) {}

template <typename T, int CAPACITY>
QueueArray<T, CAPACITY>::~QueueArray() {
    clear();
}

template <typename T, int CAPACITY>
int QueueArray<T, CAPACITY>::next_index(int index) const {
    return (index + 1) % CAPACITY;
}

template <typename T, int CAPACITY>
void QueueArray<T, CAPACITY>::enqueue(const T& value) {
    if (full()) {
        throw std::overflow_error("Queue is full");
    }
    back_idx = (back_idx + 1) % CAPACITY;
    data[back_idx] = value;
    ++queue_size;
}

template <typename T, int CAPACITY>
T QueueArray<T, CAPACITY>::dequeue() {
    if (empty()) {
        throw std::out_of_range("dequeue: Empty queue");
    }
    T value = data[front_idx];
    front_idx = (front_idx + 1) % CAPACITY;
    --queue_size;
    
    return value;
}

template <typename T, int CAPACITY>
const T& QueueArray<T, CAPACITY>::front_element() const {
    if (empty()) {
        throw std::underflow_error("Queue is empty");
    }
    return data[front_idx];
}

template <typename T, int CAPACITY>
int QueueArray<T, CAPACITY>::size() const {
    return queue_size;
}

template <typename T, int CAPACITY>
bool QueueArray<T, CAPACITY>::empty() const {
    return queue_size == 0;
}

template <typename T, int CAPACITY>
bool QueueArray<T, CAPACITY>::full() const {
    return queue_size == CAPACITY;
}

template <typename T, int CAPACITY>
void QueueArray<T, CAPACITY>::print() const {
    std::cout << "[ ";
    if (!empty()) {
        int i = front_idx;
        while (true) {
            std::cout << data[i];
            if (i == back_idx) break;
            std::cout << " <- ";
            i = (i + 1) % CAPACITY;
        }
    }
    std::cout << " ]" << std::endl;
}

template <typename T, int CAPACITY>
void QueueArray<T, CAPACITY>::clear() {
    front_idx = 0;
    back_idx = -1;
    queue_size = 0;
}

#endif
