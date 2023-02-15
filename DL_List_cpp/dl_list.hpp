#ifndef DL_LIST_HPP
#define DL_LIST_HPP

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

template <class T>
class Node{
public:
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node(T data);
};

template<class T> Node<T>::Node(T data){
    this->data = data;
    this->prev = NULL;
    this->next = NULL;
}

template <class T>
class dll{
    Node<T> *head;
    Node<T> *tail;

public:
    int len;

    dll();
    dll(T data);
    dll(const dll<T> &List);
    
    Node<T> *gethead() const;
    Node<T> *gettail() const;

    void sethead(const Node<T> *ptr);
    void settail(const Node<T> *ptr);

    void append(T data);
    void push(T data);
    void insert(int index, T data);
    void remove(int index);
    void sort();
    void clear();
    void replace(int index, T data);
    void randint(int length, int min, int max);
    void randn(int length, int min, int max);
    void fill(int length, T data);
    void print();
    void reverse();
    void concatenate(dll<T> &list);
    bool isempty();
    int find(T data);
    T max();
    T min();

    //operators_overloading
    void operator=(const dll<T>& List);
    dll<T> operator+(dll &List);
    dll<T> operator+(T data);
    dll<T> operator*(dll &List);
    dll<T> operator*(T data);
    dll<T> operator-(dll &List);
    dll<T> operator-(T data);
    dll<T> operator/(dll &List);
    dll<T> operator/(T data);
    bool operator==(const dll &List);
    T operator[](int index);
};

template<class T> dll<T>::dll(){
    this->head = NULL;
    this->tail = NULL;
    this->len = 0;
}

template<class T> dll<T>::dll(T data){
    this->head =new Node(data);
    this->tail = this->head;
    this->len = 1;
}

template<class T> dll<T>::dll(const dll<T> &List){
    Node<T> *ptr = List.tail;
    while(ptr != NULL){
        this->push(ptr->data);
        ptr = ptr->prev;
    }
}

template<class T> Node<T> *dll<T>::gethead() const{
    return this->head;
}

template<class T> Node<T> *dll<T>::gettail() const{
    return this->tail;
}

template<class T> void dll<T>::sethead(const Node<T> *ptr){
    this->head = ptr;
}

template<class T> void dll<T>::settail(const Node<T> *ptr){
    this->tail = ptr;
}

template<class T> void dll<T>::append(T data){
    Node<T> *new_node = new Node(data);
    if(this->head == NULL){
        this->head = new_node;
        this->tail = new_node;
    }
    else{
        this->tail->next = new_node;
        new_node->prev = this->tail;
        this->tail = new_node;
    }
    this->len++;
}

template<class T> void dll<T>::push(T data){
    Node<T> *new_node = new Node(data);
    if(this->head == NULL)this->tail = new_node;
    new_node->next = this->head;
    if(this->head != NULL)this->head->prev = new_node;
    this->head = new_node;
    this->len++;
}

template<class T> void dll<T>::print(){
    if(this->head == NULL)cout << "[]\n";
    else{
        Node<T> *ptr = this->head;
        cout << "[";
        while(ptr->next != NULL){
            cout << ptr->data << ", ";
            ptr = ptr->next;
        }
        cout << ptr->data << "]\n";
    }
}

template<class T> void dll<T>::insert(int index, T data){
    if(this->head == NULL || index >= this->len || index < 0){
        cerr << "insert: this list is empty\n";
        return;
    }
    Node<T> *new_node = new Node(data);
    if(index > this->len/2){
        Node<T> *ptr = this->tail;
        int i = this->len - 1;
        while(i != index){
            ptr = ptr->prev;
            i--;
        }
        if(index == this->len-1)this->tail = new_node;
        new_node->next = ptr;
        new_node->prev = ptr->prev;
        ptr->prev->next = new_node;
        ptr->prev = new_node;
        this->len++;
    }
    else{
        int i = 0;
        Node<T> *ptr = this->head;
        while(i != index){
            ptr = ptr->next;
            i++;
        }
        if(index == 0)this->head = new_node;
        new_node->next = ptr;
        new_node->prev = ptr->prev;
        if(ptr->prev != NULL)ptr->prev->next = new_node;
        ptr->prev = new_node;
        this->len++;
        return;
    }
}

template<class T> void dll<T>::remove(int index){
    if(this->head == NULL || index >= this->len || index < 0)cerr << "remove: " << index << " out of size\n";
    else{
        if(index > (this->len-1)/2){
            int i = this->len - 1;
            Node<T> *ptr = this->tail;
            while(i != index){
                ptr = ptr->prev;
                i--;
            }
            this->tail = ptr->prev;
            ptr->prev->next = ptr->next;
            if(ptr->next != NULL)ptr->next->prev = ptr->prev;
            delete ptr;
            this->len--;
        }
        else{
            int i = 0;
            Node<T> *ptr = this->head;
            while(i != index){
                ptr = ptr->next;
                i++;
            }
            if(index == 0)this->head = ptr->next;
            if(ptr->prev != NULL)ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
            delete ptr;
            this->len--;
        }
    }
}

template<class T> void dll<T>::sort(){
    bool sorted = false;
    while(!sorted){
        Node<T> *ptr = this->head;
        sorted = true;
        while(ptr->next != NULL){
            if(ptr->data > ptr->next->data){
                sorted = false;
                swap(ptr->data, ptr->next->data);
            }
            ptr = ptr->next;
        }
    }
}

template<class T> void dll<T>::clear(){
    this->head = NULL;
    this->tail = NULL;
}

template <class T> void sswap(T &a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}

int randit(int min, int max){
    return min + rand() % (max-min+1);
}

template<> void dll<int>::randint(int length, int min, int max){
    int i = 0;
    while(i < length){
        this->append(randit(min, max));
        i++;
    }
}

float randfloat(int min, int max){
    return min + rand()/RAND_MAX*(max - 1);
}

template<class T> void dll<T>::randn(int length, int min, int max){
    int i = 0;
    while(i < length){
        this->append(randfloat(min, max));
        i++;
    }
}

template<class T> void dll<T>::fill(int length, T data){
    int i = 0;
    while(i < length){
        this->append(data);
        i++;
    }
}

template<class T> void dll<T>::replace(int index, T data){
    if(this->head == NULL || index >= this->len || index < 0)cerr << "replace: " << index << " out of size!\n";
    else{
        Node<T> *ptr = this->head;
        int i = 0;
        while(i != index){
            ptr = ptr->next;
            i++;
        }
        ptr->data = data;
    }
}

template<class T> void dll<T>::reverse(){
    if(this->head != this->tail){
        Node<T> *ptr1 = this->head;
        Node<T> *ptr2 = this->tail;
        int i = 0;
        while(i < (this->len/2)){
            sswap(ptr1->data, ptr2->data);
            ptr1 = ptr1->next;
            ptr2 = ptr2->prev;
            i++;
        }
    }
}

template<class T> void dll<T>::concatenate(dll<T> &list){
    this->tail->next = list.head;
    this->tail = list.tail;
    this->len += list.len;
    list.head = NULL;
    list.tail = NULL;
    delete list.head;
    delete list.tail;
}

template<class T> bool dll<T>::isempty(){
    return this->head == NULL;
}

template<class T> int dll<T>::find(T data){
    Node<T> *ptr = this->head;
    int i = 0;
    while(ptr != NULL){
        if(ptr->data == data)return i;
        ptr = ptr->next;
        i++;
    }
    cerr << "find:" << data << " not found\n";
    return -1;
}

template<class T> void dll<T>::operator=(const dll<T> &List){
    Node<T> *ptr = List.tail;
    while(ptr != NULL){
        this->push(ptr->data);
        ptr = ptr->prev;
    }
}

template<class T> dll<T> dll<T>::operator+(dll<T> &List){
    dll<T> new_list;
    if(this->len == List.len){
        Node<T> *ptr1 = this->head;
        Node<T> *ptr2 = List.head;
        while(ptr1 != NULL && ptr2 != NULL){
            new_list.append(ptr1->data + ptr2->data);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    return new_list;
}

template<class T> dll<T> dll<T>::operator-(dll<T> &List){
    dll<T> new_list;
    if(this->len == List.len){
        Node<T> *ptr1 = this->head;
        Node<T> *ptr2 = List.head;
        while(ptr1 != NULL && ptr2 != NULL){
            new_list.append(ptr1->data - ptr2->data);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    return new_list;
}

template<class T> dll<T> dll<T>::operator*(dll<T> &List){
    dll<T> new_list;
    if(this->len == List.len){
        Node<T> *ptr1 = this->head;
        Node<T> *ptr2 = List.head;
        while(ptr1 != NULL && ptr2 != NULL){
            new_list.append(ptr1->data * ptr2->data);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    return new_list;
}

template<class T> dll<T> dll<T>::operator/(dll<T> &List){
    dll<T> new_list;
    if(this->len == List.len){
        Node<T> *ptr1 = this->head;
        Node<T> *ptr2 = List.head;
        while(ptr1 != NULL && ptr2 != NULL){
            new_list.append(ptr1->data / ptr2->data);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    return new_list;
}

template<class T> bool dll<T>::operator==(const dll<T> &List){
    bool equa = false;
    if(this->len != List.len)return equa;
    else{
        Node<T> *ptr1 = this->head;
        Node<T> *ptr2 = List.head;
        while(ptr1 != NULL && ptr2 != NULL){
            if(ptr1->data != ptr2->data)break;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        if(ptr1 == NULL)equa = true;
        return equa;
    }
}

template<class T> T dll<T>::operator[](int index){
    if(this->head == NULL || index >= this->len || index < 0){
        cerr << "out of size\n";
        return (T)0;
    }
    else{
        int i = 0;
        Node<T> *ptr = this->head;
        while(i != index){
            ptr = ptr->next;
            i++;
        }
        return ptr->data;
    }
}

template<class T> dll<T> dll<T>::operator+(T data){
        dll<T> new_list;
        Node<T> *ptr = this->tail;
        while(ptr != NULL){
            new_list.push(ptr->data + data);
            ptr = ptr->prev;
        }
        return new_list;
}

template<class T> dll<T> dll<T>::operator*(T data){
    dll<T> new_list;
        Node<T> *ptr = this->tail;
        while(ptr != NULL){
            new_list.push(ptr->data * data);
            ptr = ptr->prev;
        }
        return new_list;
}

template<class T> dll<T> dll<T>::operator-(T data){
    dll<T> new_list;
        Node<T> *ptr = this->tail;
        while(ptr != NULL){
            new_list.push(ptr->data - data);
            ptr = ptr->prev;
        }
        return new_list;
}

template<class T> dll<T> dll<T>::operator/(T data){
    dll<T> new_list;
        Node<T> *ptr = this->tail;
        while(ptr != NULL){
            new_list.push(ptr->data / data);
            ptr = ptr->prev;
        }
        return new_list;
}

template<class T> T dll<T>::max(){
    T max = 0;
    Node<T> *ptr = this->head;
    while(ptr != NULL){
        if(ptr->data > max)max = ptr->data;
        ptr = ptr->next;
    }
    return max;
}

template<class T> T dll<T>::min(){
    T min = RAND_MAX;
    Node<T> *ptr = this->head;
    while(ptr != NULL){
        if(ptr->data < min)min = ptr->data;
        ptr = ptr->next;
    }
    return min;
}

#endif //DL_LIST_HPP