# Objetivo por defecto
all: bin/testTableEntry bin/testBSTree bin/testHashTable

# Regla para testTableEntry
bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -Wall -std=c++17 -o bin/testTableEntry testTableEntry.cpp

# Regla para testBSTree
bin/testBSTree: testBSTree.cpp BSTree.h
	mkdir -p bin
	g++ -Wall -std=c++17 -o bin/testBSTree testBSTree.cpp

# Regla para testHashTable
bin/testHashTable: testHashTable.cpp HashTable.h Dict.h TableEntry.h
	mkdir -p bin
	g++ -Wall -std=c++17 -o bin/testHashTable testHashTable.cpp

# Regla para limpiar
clean:
	rm -rf bin *.o *.gch    
