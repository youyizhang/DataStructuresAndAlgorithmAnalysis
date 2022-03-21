#pragma once
#include <iostream>
#include <algorithm>

namespace MySTL{

    template <typename Object>
    class Vector {

    public:
        static const int SPARE_CAPACITY = 16;

    private:
        int theSize;
        int theCapacity;
        Object *object;

    public:
        explicit Vector(int initSize = 0) :
                theSize{initSize},
                theCapacity{initSize+SPARE_CAPACITY}
        {
            object = new Object[theCapacity];
        }

        Vector(const Vector &rhs):
                theSize{rhs.theSize},
                theCapacity{rhs.theCapacity},
                object{nullptr}
        {
            object = new Object[theCapacity];
            for (int i = 0; i < theSize; ++i) {
                object[i] = rhs.object[i];
            }
        }

        Vector& operator=(const Vector &rhs){
            Vector copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        ~Vector(){
            delete[] object;
        }


        Vector(Vector &&rhs) :
                theSize{rhs.theSize},
                theCapacity{rhs.theCapacity},
                object{rhs.object}
        {
            rhs.theSize = 0;
            rhs.theCapacity = 0;
            rhs.object = nullptr;

        }

        Vector & operator=(Vector && rhs){

//            theSize = rhs.theSize;
//            theCapacity = rhs.theCapacity;
//            object = rhs.object;

//            why use swap?
            std::swap(theSize, rhs.theSize);
            std::swap(theCapacity, rhs.theCapacity);
            std::swap(object, rhs.object);
            return *this;
        }

        void resize(int newSize){
            if(newSize > theCapacity)
                reserve(newSize * 2);
            theSize = newSize;
        }

        void reserve(int newCapacity){
            if(newCapacity < theSize)
                return;

            Object *newArray = new Object[newCapacity];
            for (int i = 0; i < theSize; ++i){
//                newArray[i] = object[i];
//                why use move ?
                newArray[i] = std::move(object[i]);
            }
            theCapacity = newCapacity;
            std::swap(object, newArray);
            delete[] newArray;

        }

        Object & operator[](int index){
            return object[index];
        }

        const Object & operator[](int index) const{
            return object[index];
        }

        friend std::ostream& operator<<(std::ostream& output, const Vector& x){
            for (int i = 0; i < x.theSize; ++i) {
                output << x[i] << " ";
            }
            return output;
        }


        bool empty() const{
            return size() == 0;
        }

        int size() const{
            return theSize;
        }

        int capacity() const{
            return theCapacity;
        }

        void push_back(const Object& x){
            if(theSize == theCapacity)
                reserve(theCapacity*2 + 1);
            object[theSize++] = std::move(x);


        }
        void push_back(Object&& x){
            if(theSize == theCapacity)
                reserve(theCapacity * 2 + 1);
            object[theSize++] = x;
        }

        const Object& back() const{
            return object[theSize - 1];
        }

        typedef Object* iterator;
        typedef const Object* const_iterator;

        iterator begin() {
            return &object[0];
        }

        const_iterator begin() const{
            return &object[0];
        }

        iterator end(){
            return &object[size()];
        }

        const_iterator end() const{
            return &object[size()];
        }

    };
}//MySTL


