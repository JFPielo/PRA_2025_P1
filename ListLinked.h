#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : List<T> {
	private:
		Node<T>* first;
		int n;

	public:
		ListLinked(){
			this->first = nullptr;
			this->n=0;
		}
		~ListLinked(){
			while (this->first != nullptr) {
				Node<T>* aux = this->first->next;
				delete this->first;
				this->first = aux;
			}
			this->n = 0; 
		}	
		T operator[](int pos){
			if(pos < 0 || pos > this->size() - 1){
				throw std::out_of_range("Fuera de rango");
			}
			return this->get(pos);
			
		}
		friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list){
			out << "List -> [";
			Node<T>* aux = list.first;
			while(aux != nullptr){
				out << aux->data;
                if(aux->next != nullptr){
                    out << ", ";
                }
				aux = aux -> next;
			}
			out << "]";
			return out;
		
		}

		void insert(int pos, T e) override {
			if(pos < 0 || pos > this->n) 
             {throw std::out_of_range("Posición fuera de rango");}
             else{
				if(pos == 0){
					first = new Node<T>(e, first);
				}else{
					Node<T>* prev = first;
					for(int i = 0; i < pos - 1; ++i) {
						prev = prev->next;
					    }
					prev->next = new Node<T>(e, prev->next);
				    }
			        n++;
                }
    }

    void append(T e) override {
        insert(n, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    T remove(int pos) override {
        if(pos < 0 || pos >= n) {
            throw std::out_of_range("Fuera de rango");
        }
        Node<T>* aux;
        T val;
        if(pos == 0){
            aux = first;
            first = first->next;
        } else {
            Node<T>* prev = first;
            for(int i = 0; i < pos - 1; ++i) {
				prev = prev->next;
			}

            aux = prev->next;
            prev->next = aux->next;
        }
        val = aux->data;
        delete aux;
        n--;
        return val;
    }

    T get(int pos) override {
        if(pos < 0 || pos >= n) {
			throw std::out_of_range("Fuera de rango");
        }
        Node<T>* aux = this->first;
        for(int i = 0; i < pos; ++i) {
            aux = aux -> next;
        }
        return aux->data;
    }

    int search(T e) override {
        Node<T>* aux = first;
        int pos = 0; 
        while(aux != nullptr){
            if(aux->data == e) {
                return pos;
            }
            aux = aux->next;
            pos++;
        }
        return -1;
    }
    bool empty() override {
        return n == 0; 
    }  

    int size() override {
        return n;
    }

};
