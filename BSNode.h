#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        T elem;			// Elemento almacenado en el nodo
	BSNode<T>* left;	// Puntero al nodo izquierdo
	BSNode<T>* right;	//Puntero al nodo derecho
    

	//Constructor; inicializa el nodo con el elemento y los punteros (nulos por defecto)
	BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr): elem(elem), left(left), right(right) {}

	//Sobrecarga del operador <<
	friend std::ostream& operator<<(std::ostream& out, const BSNode<T>& bsn){
		out << bsn.elem; // Imprime el elemento almacenado
		return out;
	}

};

#endif
