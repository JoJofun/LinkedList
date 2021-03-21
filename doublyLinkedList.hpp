#pragma once

//copyright nicholas heerdt 2021
//im not good at writing these messages but ask for permission before using
//though theres libraries out there that probably do all of this but better
//using visual studio 2019

#include <cassert>
template<class T>
struct node
{
    T data;
    node<T>* next;
    node<T>* back;
};

template <class T>
class doublyLinkedList
{
private:
    node<T>* front;
    node<T>* end;
    int size;

public:
    doublyLinkedList();
    //default constuctor which initializes to an empty state

    doublyLinkedList(doublyLinkedList<T>& toCopy);
    //copy constructor

    ~doublyLinkedList();
    //destructor

    bool insert(const T& to_ins);
    //default insert that inserts at the front, returns true if successful, which should be always

    bool insert_back(const T& to_ins);
    //inserts at back, returns true if successful, which should be always

    bool insert(const T& to_ins, int index);
    //inserts at index, returns true if successful, returns false if out of range
    //for clarification it inserts at where it will be after a size increase from 0 to n-1
    //ex LL size 4 insert(item, 4) will put it at the very end

    bool RemoveByIndex(int index);
    //goes to the index'th element and deletes it, returns true if successful, returns false if out of range

    bool RemoveByData(const T& to_rem);
    //removesbydata, if found deletes and returns true, if not found returns false
    //also if any duplicates removes the first instance of that data

    T FindByIndex(int index);
    //returns the index'th element of the linked list
    //if it fails because the index is out of bounds, it gives an error

    T FindByData(const T& to_find);
    //searches through the linked list to find the first element that matches the data
    //returns said data if found, if not found it gives an error

    int SearchByData(const T& to_sea);
    //searches the linked list to find the data, if found returns the index, if not found then returns -1

    void Clear();
    //removes all elements sets count to 0, and sets the front and back ptrs to null

    int Count() {//returns the count of items in the linked list
        return size;
    }
};
template <class T>
doublyLinkedList<T>::doublyLinkedList() {
    front = nullptr;
    end = nullptr;
    size = 0;
}

template <class T>
doublyLinkedList<T>::doublyLinkedList(doublyLinkedList<T>& toCopy) {
    front = nullptr;
    end = nullptr;
    size = 0;
    for (int i = 0; i < toCopy.Count(); i++) {
        insert_back(toCopy.FindByIndex(i));
    }
}

template <class T>
doublyLinkedList<T>::~doublyLinkedList() {
    Clear();
}

template <class T>
bool doublyLinkedList<T>::insert(const T& to_ins) {//insert at front
    node<T>* newNode;
    newNode = new node<T>;
    newNode->data = to_ins;
    newNode->back = nullptr;
    newNode->next = nullptr;

    if (front == nullptr) {
        front = newNode;
        end = newNode;
        size++;
    }
    else {
        newNode->next = front;
        front->back = newNode;
        front = newNode;
        size++;
    }
    return true;
}

template <class T>
bool doublyLinkedList<T>::insert_back(const T& to_ins) {//insert at back
    node<T>* newNode;
    newNode = new node<T>;
    newNode->data = to_ins;
    newNode->back = nullptr;
    newNode->next = nullptr;
    if (front == nullptr) {//if front is null then back is null so I just copypasted this from front ins
        front = newNode;
        end = newNode;
        size++;
    }
    else {
        newNode->back = end;
        end->next = newNode;
        end = newNode;
        size++;
    }
    return true;
}

template <class T>
bool doublyLinkedList<T>::insert(const T& to_ins, int index) {

    if (index == 0) {
        return insert(to_ins);//if 0 ins at front
    }
    else if(index == size) {
        return insert_back(to_ins);//if size insert at back
    }
    else if (index > size) {//if out of range return false
        return false;
    }

    else {
        node<T>* newNode;
        newNode = new node<T>;
        newNode->data = to_ins;
        newNode->back = nullptr;
        newNode->next = nullptr;

        node<T>* trail = front;

        for (int i = 0; i < index; i++) {
            trail = trail->next;
        }
        newNode->next = trail;
        newNode->back = trail->back;
        newNode->back->next = newNode;
        trail->back = newNode;
        size++;
        return true;

    }
}

template <class T>
bool doublyLinkedList<T>::RemoveByIndex(int index) {
    if (size == 0 || size <= index) {
        return false;
    }

    node<T>* trail = front;


    if (index == 0 and front == end) {
        front == nullptr;
        end == nullptr;
    }
    //case if first
    else if (index == 0) {
        front = front->next;
        front->back = nullptr;
    }
    //case if end
    else if (index == size - 1) {
        trail = end;
        end = end->back;
        end->next = nullptr;
    }
    else {
        for (int i = 0; i < index; i++) {
            trail = trail->next;
        }
        trail->back->next = trail->next;
        trail->next->back = trail->back;
    }
    size--;
    delete trail;
    return true;

}

template <class T>
bool doublyLinkedList<T>::RemoveByData(const T& to_rem) {
    int temp = SearchByData(to_rem);
    if (temp != -1) {
        RemoveByIndex(temp);
        return true;
    }
    else {
        return false;
    }
}

template <class T>
void doublyLinkedList<T>::Clear() {
    while (size != 0) {
        RemoveByIndex(0);
    }
}
template <class T>
int doublyLinkedList<T>::SearchByData(const T& to_sea) {

    node<T>* trail = front;
    for (int i = 0; i < size; i++) {
        if (trail->data == to_sea) {
            return i;
        }
        trail = trail->next;
    }
    return -1;
}

template <class T>
T doublyLinkedList<T>::FindByIndex(int index) {
    assert(!(index < 0) && "Find by index out of bounds");
    assert(!(index >= size) && "Find by index out of bounds");

    node<T>* trail = front;
    for (int i = 0; i < index; i++) {
        trail = trail->next;
    }
    return trail->data;
}

template <class T>
T doublyLinkedList<T>::FindByData(const T& to_find) {
    int temp = SearchByData(to_find);
    assert( (temp != -1) && "Cannot return to_find of T-type, not found in linked list");
    return FindByIndex(temp);
}
