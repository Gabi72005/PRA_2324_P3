#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "/home/gabriel/Desktop/UPV/pra/practicas/practica1/PRA_2324_P1/ListLinked.h"



template <typename V>
class HashTable : public Dict<V> {
private:
    int n; // Número actual de elementos almacenados
    int max; // Número total de cubetas en la tabla hash
    ListLinked<TableEntry<V>>* table; // Tabla hash implementada con listas enlazadas

    // Calcula el índice de la tabla para una clave
    int h(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c); // Suma los valores ASCII de los caracteres
        }
        return sum % max; // Índice basado en el tamaño de la tabla
    }

public:
    // Constructor: inicializa la tabla con el número de cubetas especificado
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor: libera la memoria reservada para la tabla
    ~HashTable() {
        delete[] table;
    }

    // Devuelve el número total de cubetas en la tabla
    int capacity() {
        return max;
    }

    // Imprime el contenido de la tabla hash
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
        out << "==============\n";
        for (int i = 0; i < th.max; i++) {
            out << "== Cubeta " << i << " ==\n";
            out << "List => " << th.table[i] << "\n";
        }
        out << "==============\n";
        return out;
    }

    // Devuelve el valor asociado a una clave; lanza una excepción si no existe
    V operator[](std::string key) {
        int index = h(key);
        TableEntry<V> entry(key);
        int pos = table[index].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Clave no encontrada");
        }
        return table[index].get(pos).value;
    }

    // Inserta un nuevo par clave-valor; lanza una excepción si la clave ya existe
    void insert(std::string key, V value) override {
        int index = h(key);
        TableEntry<V> entry(key);
        int pos = table[index].search(entry);
        if (pos != -1) {
            throw std::runtime_error("Clave '" + key + "' ya existe");
        }
        table[index].prepend(TableEntry<V>(key, value)); // Inserta al inicio de la lista para mantener orden
        n++;
    }

    // Busca el valor asociado a una clave; lanza una excepción si no existe
    V search(std::string key) override {
        int index = h(key);
        TableEntry<V> entry(key);
        int pos = table[index].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Clave '" + key + "' no encontrada");
        }
        return table[index].get(pos).value;
    }

    // Elimina una clave de la tabla y devuelve su valor; lanza una excepción si no existe
    V remove(std::string key) override {
        int index = h(key);
        TableEntry<V> entry(key);
        int pos = table[index].search(entry);
        if (pos == -1) {
            throw std::runtime_error("Clave '" + key + "' no encontrada");
        }
        V removedValue = table[index].get(pos).value;
        table[index].remove(pos);
        n--;
        return removedValue;
    }

    // Devuelve el número de elementos actualmente almacenados en la tabla
    int entries() override {
        return n;
    }
};

#endif

