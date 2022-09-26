#ifndef __DARRAY_H__
#define __DARRAY_H__

#include <cstddef>
#include <cstring>

#ifndef DARRAY_DEFAULT_CHUNK_SIZE
    #define DARRAY_DEFAULT_CHUNK_SIZE 32
#endif

template <typename T>
class DArray{

public:
    DArray(){

    }

    ~DArray(){
        delete _data;
    }

    /**
     * @brief   Adds the supplied entry to the array
     * @param   t           The entry to add
     */
    void add(T t){
        while(_size+1 >= _allocated)
            expand();

        _data[_size] = t;
        _size++;
    }

    /**
     * @brief   Expands the array by the supplied amount of slots
     * @param   amount      The amount of slots to add (DARRAY_DEFAULT_CHUNK_SIZE)
     */
    void expand(size_t amount = DARRAY_DEFAULT_CHUNK_SIZE){
        size_t newAllocated = _allocated + amount;
        T* newData = new T[newAllocated];

        //std::memcpy(newData, _data, _size*sizeof(T));
        for (size_t i = 0; i < _size; i++)
            newData[i] = _data[i];

        delete _data;
        _data = newData;
        _allocated = newAllocated;
    }

    void clean(){
        delete _data;
        _size = 0;
        _allocated = 0;
    }

    size_t lastID(){
        return _size-1;
    }

    size_t size(){
        return _size;
    }

    /**
     * @brief   The amount of allocated slots
     */
    size_t              _allocated = 0;

    /**
     * @brief   The amount of used slots
     */
    size_t              _size = 0;

    /**
     * @brief   The core array
     */
    T*                  _data = nullptr;

};

#endif
