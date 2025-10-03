// WRITE IMPLEMENTATIONS OF METHODS BELOW
#include <stdexcept>

#include "queue.h"

template <typename T>
Queue<T>::Queue() {

}

template <typename T>
Queue<T>::~Queue() {

}

template <typename T>
void Queue<T>::enqueue(T value) {
    first_stack.push(value);
    return; //dummy
}

template <typename T>
T Queue<T>::dequeue() {
    if(isEmpty()) throw std::invalid_argument("Empty Queue Dequeue Error");
    else if(second_stack.isEmpty()){
        while(!first_stack.isEmpty()){
            second_stack.push(first_stack.pop());
        }
    } 
    return T(second_stack.pop()); //dummy
}

template <typename T>
T Queue<T>::peek() {
    if(isEmpty()) throw std::invalid_argument("Empty Queue Peek Error")   ;
    else if(second_stack.isEmpty()){
        while(!first_stack.isEmpty()){
            second_stack.push(first_stack.pop());
        }
    } 
    return T(second_stack.peek()); //dummy
}

template <typename T>
bool Queue<T>::isEmpty() {
    return first_stack.isEmpty() && second_stack.isEmpty(); // dummy
}

template <typename T>
size_t Queue<T>::getSize() {
    return first_stack.getSize() + second_stack.getSize(); // dummy
}
