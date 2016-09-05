#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

enum ERR {BAD};

template<typename T>
class node
{
    public:
        node(const T &d = T());
        ~node();
        node(const node<T> &other);
        node<T>& operator=(const node<T> &other);

        void setNext(node<T> *p);
        node<T>* getNext() const;
        void setData(const T &d);
        T& getData();

        template<typename U>
        friend
        ostream& operator<<(ostream &out, const node<U> &n);

        template<typename U>
        friend
        istream& operator>>(istream &in, node<U> &n);


    private:
        T data;
        node<T> *next;
};

template <typename T>
node<T>::node(const T &d)
{
    data = d;
    next = NULL;
}


template <typename T>
node<T>::~node()
{
    data = T();
    next = NULL;
}

template <typename T>
node<T>::node(const node<T> &other)
{
    data = other.data;
    next = NULL;
}

template <typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        next = NULL;
        data = other.data;
    }
}

template <typename T>
void node<T>::setNext(node<T> *p)
{
    next = p;
}

template <typename T>
node<T>* node<T>::getNext() const
{
    return next;
}

template <typename T>
void node<T>::setData(const T &d)
{
    data = d;
}

template <typename T>
T& node<T>::getData()
{
    return data;
}

template<typename U>
ostream& operator<<(ostream &out, const node<U> &n)
{
    out<<n.data<<" ";
    return out;
}

template<typename U>
istream& operator>>(istream &in, node<U> &n)
{
    n.next = NULL;
    in>>n.data;
    if(!in.good())
        throw BAD;
    return in;
}


#endif // NODE_H
