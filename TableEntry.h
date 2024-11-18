#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V> 
class TableEntry {
    public:
	std::string key; //La clave del diccionario
	V value;          //Valor asociado


	// Comenzamos a definir todos los métodos
	
	// Constructor
	TableEntry(std::string key, V value): key(key), value(value) {}

	// Entrada solo con clave
	TableEntry(std::string key): key(key),value(V{}) {}

	// Crea una entrada sin clave y sin valor
	TableEntry(): key(""), value(V{}) {}

	// Sobrecarga del operador ==
	friend bool operator ==(const TableEntry<V> &te1, const TableEntry<V> &te2){
		return te1.key == te2.key;
	}

	// Sobrecarga del operador !=
	friend bool operator !=(const TableEntry<V> &te1, const TableEntry<V> &te2){
		return !(te1 == te2);
	}

	// Sobrecarga del operador <<
	friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te){
		out << "Key: " << te.key << ", Value: " << te.value;
        	return out;
	}

		

    
};

#endif
