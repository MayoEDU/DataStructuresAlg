/// TODO HEADER

template <typename T, int size = 100>
class QueueArray {

    public:
        QueueArray();

    private:
        T data[size];
        int front, back;
}

// Prototypes for each method, deque, etc etc.