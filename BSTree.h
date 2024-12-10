#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
	// Atributos privados
	int nelem;		// Número de elementos
	BSNode<T>* root;	//Nodo que apunta a la raíz
				
	// Métodos privados
	BSNode<T>* search(BSNode<T>* n, T e)const;
	BSNode<T>* insert(BSNode<T>* n, T e);
	BSNode<T>* remove(BSNode<T>* n, const T& e);
	T max(BSNode<T>* n) const;
	BSNode<T>*remove_max(BSNode<T>* n);
	void print_inorder(std::ostream& out, BSNode<T>* n)const;
	void delete_cascade(BSNode<T>* n);


    public:
       //Métodos públicos
       //Constructor
       BSTree() : nelem(0), root(nullptr) {}

       //Destructor
       ~BSTree(){
	       delete_cascade(root);
       }

       // DEvuelve el tamaño del arbol
       int size() const{
	       return nelem;
       }

       //Busqueda
       T search(T e)const{
	       BSNode<T>* result = search(root, e);
	       return result->elem;
       }

       //Insertar
       void insert(T e){
	       root = insert(root, e);
       }

       //Quitar
       void remove(T e){
	       root = remove(root, e);

       }

       // Sobrecarga operador <<
       friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst){
	       bst.print_inorder(out, bst.root);
	       return out;
       }

       T operator[](T e)const{
	       return search(e);
	      }

    
};


	//Implementación de los métodos privados
	
	//Busqueda recursiva viendo a ver si es mator o menor que el elemento en el que estas. Si acaba en el puntero nulo lanza una excepción. Si es igual devuelve el puntero al nodo en cuestión
	template<typename T>
	BSNode<T>* BSTree<T>::search(BSNode<T>* n, T e) const{
		if(n == nullptr){
			throw std::runtime_error("Elemento no encontrado en el árbol");
		}
		if (e < n->elem) {
			return search(n->left, e);
		}else if (e> n->elem){
			return search(n->right, e);
		}else{
			return n;
		}
	}

	//Inserción recursiva
	template<typename T>
	BSNode<T>* BSTree<T>::insert(BSNode<T>* n, T e){
		if(n == nullptr){
			//Si el puntero es nulo, es que has llegado a donde hay que insertarlo
			++nelem;
			return new BSNode<T>(e);

                }
		if(e < n->elem){
			n->left = insert(n->left, e);
		}else if(e> n->elem){
			n->right = insert(n->right, e);
		}else{
			throw std::runtime_error("No se ha podido insertar en el árbol");
		}
		return n;
	}


	//Eliminación recursiva
	template <typename T>
BSNode<T>* BSTree<T>::remove(BSNode<T>* n, const T& e) {
    if (n == nullptr) {
        throw std::runtime_error("Element not found in BST.");
    }
    if (e < n->elem) {
        n->left = remove(n->left, e);
    } else if (e > n->elem) {
        n->right = remove(n->right, e);
    } else {
        // Nodo encontrado
        if (n->left == nullptr && n->right == nullptr) {
            delete n;
            --nelem;
            return nullptr;
        } else if (n->left == nullptr) {
            BSNode<T>* temp = n->right;
            delete n;
            --nelem;
            return temp;
        } else if (n->right == nullptr) {
            BSNode<T>* temp = n->left;
            delete n;
            --nelem;
            return temp;
        } else {
            n->elem = max(n->left);
            n->left = remove_max(n->left);
        }
    }
    return n;
}

// Encontrar el máximo en la rama en cuestion
	template <typename T>
	T BSTree<T>::max(BSNode<T>* n) const {
    	if (n->right == nullptr) {
        	return n->elem;
    	}
    		return max(n->right);
}

//Elimina el máximo en el subarbol

template <typename T>
BSNode<T>* BSTree<T>::remove_max(BSNode<T>* n) {
    if (n->right == nullptr) {
        BSNode<T>* temp = n->left;
        delete n;
        --nelem;
        return temp;
    }
    n->right = remove_max(n->right);
    return n;
}

// Recorrido inorden recursivo
template <typename T>
void BSTree<T>::print_inorder(std::ostream& out, BSNode<T>* n) const {
    if (n != nullptr) {
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }
}

template <typename T>
void BSTree<T>::delete_cascade(BSNode<T>* n) {
    if (n != nullptr) {
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }
}



#endif
