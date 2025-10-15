#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T>
class ListArray : public List<T> {
private:
    T* arr;
    int max;
    int n;
    static const int MINSIZE = 2;

    void resize(int new_size){
        if(new_size < MINSIZE) new_size = MINSIZE;
        T* new_array = new T[new_size];
        int num = (this->n < new_size) ? this->n : new_size; // reemplaza std::min
        for(int i = 0; i < num; ++i){
            new_array[i] = arr[i];
        }
        delete[] this->arr;
        this->arr = new_array;
        this->max = new_size;
        if(this->n > new_size) this->n = new_size;
    }
public:
    ListArray(){
        this->n = 0;
        this->max = MINSIZE;
        this->arr = new T[this->max];
    }

    ~ListArray(){
        delete[] arr;
    }

    T operator[](int pos){
        if (pos < 0 || pos >= size() ){
            throw std::out_of_range("Posición fuera de rango");
        }
        return arr[pos];
    }

    friend std::ostream& operator<<(std::ostream &out, const ListArray<T> &list) {
        out << "List => [";
        for(int i = 0; i < list.n; ++i){
            out << list.arr[i];
            if (i < list.n - 1) out << ", ";
        }
        out << "]";
        return out;
    }

    void insert(int pos, T e) override{
        if(pos < 0 || pos > this->n){
            throw std::out_of_range("Posición fuera de rango");
        }
        if(this->n + 1 > this->max) resize(this->max * 2);
        for(int i = this->n; i > pos; --i){
            this->arr[i] = this->arr[i-1];
        }
        this->arr[pos] = e;
        this->n++;
    }

    void append(T e) override{
        insert(this->n, e);
    }

    void prepend(T e) override{
        insert(0, e);
    }

    T remove(int pos) override{
        if(pos < 0 || pos >= this->n){
            throw std::out_of_range("Fuera de rango");
        }
        T ele = this->arr[pos];
        for(int i = pos; i < this->n - 1; ++i){
            this->arr[i] = this->arr[i+1];
        }
        this->n--;
        if(this->n > 0 && this->n < this->max/4 && this->max/2 >= MINSIZE){
            resize(this->max / 2);
        }
        return ele;
    }

    T get(int pos) override{
        if(pos < 0 || pos >= this->n){
            throw std::out_of_range("Fuera de rango");
        }
        return this->arr[pos];
    }

    int search(T e) override{
        for(int i = 0; i < this->n; ++i){
            if(this->arr[i] == e) return i;
        }
        return -1;
    }

    bool empty() override{
        return n == 0;
    }

    int size() override{
        return n
    }
};

