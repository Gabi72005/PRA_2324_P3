#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree; // ABB con elementos TableEnntry

    public:
	// Implementando los metodos abstractos de Dict.h
        void insert(std::string key, V value) override {
		tree->insert(TableEntry<V>(key, value));
	}

	V search(std::string key) override{
		return tree->search(TableEntry<V>(key));
	}

	V remove(std::string key) override{
		TableEntry<V> entry = search(TableEntry<V>(key));
		tree->remove(entry);
		return entry.value;
	}

	int entries() override {
		return tree->size();
	}
	// Ahora vamos a definir los métodos propios del BSTREEDict
	
	// Constructor
	BSTreeDict(){
		tree = new BSTree<TableEntry<V>>();
	}


	// Destructor
	~BSTreeDict(){
		delete tree;
	}

	// Sobrecarga <<
	friend std::ostream& operator<<(std::ostream out, const BSTreeDict<V>& bs){
		out << *(bs.tree);
		return out;
	}

	// Sobrecarga de []
	V operator[](std::string key){
		return tree -> search(TableEntry<V>(key)).value;
	}


};

#endif
