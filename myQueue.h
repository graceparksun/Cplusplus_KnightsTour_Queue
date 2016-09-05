//Runtime: 0.0003764 seconds
//Runtime: 0.0003868 seconds
//Runtime: 0.0003946 seconds

#ifndef M7YQUEUE_H
#define M7YQUEUE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include  "node.h"

using namespace std;

enum ERRORS {EMPTY, FULL};

template <typename T>
class myQueue
{
    public:
        myQueue(int s = 5);
        ~myQueue();
        myQueue(const myQueue<T> &other);
        myQueue& operator=(const myQueue<T> &other);

        bool empty() const;
        bool full();
        void clear();

        T& Eoq();
        void eraseEoq();
        bool find(const T &d) const;
        int index(const T &d) const;

        void resize(int s);
        int size();
        int capacity();

        myQueue<T>& operator<<(const T &d);
        myQueue<T>& operator>>(T &d);

        void enqueue(const T &d);
        void dequeue(T &d);

        template<typename U>
        friend
        ostream &operator<<(ostream &out, const myQueue<U> &q);

        template<typename U>
        friend
        istream &operator>>(istream &out, myQueue<U> &q);


    private:
        void *boq, *eoq;
        int mySize, myCapacity;

        void nukem();
        void removeOne();
        void copy(const myQueue <T> &q);
};


template<typename T>
myQueue<T>::myQueue(int s) //checked
{
    boq = eoq = NULL;
    mySize = 0;
    myCapacity = s;
}


template<typename T>
myQueue<T>::~myQueue() //checked
{
    nukem();
}


template<typename T>
myQueue<T>::myQueue(const myQueue<T> &other) //checked
{
    copy(other);
}


template<typename T>
myQueue<T>& myQueue<T>::operator=(const myQueue<T> &other) //checked
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}


template<typename T>
bool myQueue<T>::empty() const //checked
{
    return !boq;
}


template<typename T>
bool myQueue<T>::full() //checked
{
    return mySize == myCapacity;
}


template<typename T>
void myQueue<T>::clear()//checked
{
    cout << "in clear" << endl;
    nukem();
}


template<typename T>
T& myQueue<T>::Eoq ()
{
    return ((node<T>*) eoq)->getData();
}


template<typename T>
void myQueue<T>:: eraseEoq()
{
    int i=1;
    for(node<T> *ptr = ((node<T> *) boq); ptr; ptr=ptr->getNext())
    {
        if(i==size()-1)
        {
            eoq = ptr;
            ptr->setNext(NULL);
        }
        else
            ++i;
    }
}

template<typename T>
bool myQueue<T>::find(const T &d) const
{
    if(empty())
        throw EMPTY;
    for (node<T> *ptr = ((node<T> *) boq); ptr; ptr=ptr->getNext())
        if(ptr->getData() == d)
            return true;
    return false;
}


template<typename T>
int myQueue<T>::index(const T &d) const
{
    int index = 1;
    if(empty())
        throw EMPTY;
    for (node<T> *ptr = ((node<T> *) boq); ptr; ptr=ptr->getNext())
    {
        if(ptr->getData() == d)
            return index;
        ++index;
    }
}


template<typename T>
void myQueue<T>::resize(int s) // checked
{
    if(s < myCapacity)
    {
        while(mySize > s)
            removeOne();
    }
    myCapacity = s;
}


template<typename T>
void myQueue<T>::nukem()//checked
{
    while(mySize)
        removeOne();
    boq=eoq=NULL;
}


template<typename T>
int myQueue<T>::size() //checked
{
    return mySize;
}


template<typename T>
int myQueue<T>::capacity()//checked
{
    return myCapacity;
}


template<typename T>
myQueue<T>& myQueue<T>::operator<<(const T &d) //checked
{
    enqueue(d);
    return *this;
}


template<typename T>
myQueue<T>& myQueue<T>::operator>>(T &d) //checked
{
    dequeue(d);
    return *this;
}


template<typename T>
void myQueue<T>::enqueue(const T &d)
{
    if(full())
        throw FULL;
    node<T> *newNode = new node<T>(d);
    if(!boq)
    {
        boq = eoq = newNode;
        mySize = 1;
        return;
    }
    ((node<T>*)eoq)->setNext(newNode);
    eoq = newNode;
    mySize++;
}


template<typename T>
void myQueue<T>::dequeue(T &d)
{
    if(empty())
        throw EMPTY;
    node<T> *temp = (node<T> *)boq;
    d = temp->getData();
    boq = temp->getNext();
    delete temp;
    --mySize;
}


template<typename T>
void myQueue<T>::removeOne() //checked
{
    if(empty())
        throw (EMPTY);
    node<T> *temp = (node<T> *)boq;
    boq = temp->getNext();
    delete temp;
    --mySize;
}


template<typename T>
void myQueue<T>::copy(const myQueue<T> &other)
{
    for(node<T> *ptr = (node<T> *)other.boq; ptr; ptr = ptr->getNext())
        enqueue(ptr->getData());
}


template<typename U>
ostream &operator<<(ostream &out, const myQueue<U> &q)
{
    int i=0;
    if (q.empty())
        out << "Empty queue" << endl;
    else
    {
        if (out == cout)
        {
            for(node<U> *ptr = ((node<U> *)q.boq); ptr; ptr = ptr->getNext())
            {
                out<< "Tour[" << i<<"]: " << ptr->getData() << endl;
                ++i;
            }
        }
        else
            for(node<U> *ptr = ((node<U> *)q.boq); ptr; ptr = ptr->getNext())
                out << ptr->getData() << endl;
    }
    return out;
}


template<typename U>
istream &operator>>(istream &in, myQueue<U> &q)
{
    U data;
    if(!in.good())
        throw BAD;
    q<<data;
    return in;
}


#endif // M7YQUEUE_H

