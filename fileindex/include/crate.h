#ifndef __CRATE_H__
#define __CRATE_H__

#include <stddef.h>
#include <cstring>

template<typename T> struct crate_s{
    size_t      size;
    T*          data;
};


/**
 * @brief   Creates a new crate
 */
template<typename T> crate_s<T>* crate_new(){
    crate_s<T>* newCrate = new crate_s<T>;

    newCrate->size = 0;
    newCrate->data = nullptr;
}

/**
 * @brief   Adds the supplied entry to the supplied crate
 * @param   crate           The crate to add the entry to
 * @param   entry           The entry to add
 */
template<typename T> void crate_add(crate_s<T>* crate, T entry){

    //Handle the special case of an empty crate
    if (crate->size == 0){
        crate->size = 1;
        crate->data = new T[1];
        crate->data[0] = entry;
        return;
    }

    T* newData = new T[crate->size+1];

    std::memcpy(newData, crate->data, sizeof(T)*crate->size);
    crate->data[crate->size] = entry;

    crate->size++;
    
    delete crate->data;
    crate->data = newData;
}


#endif
