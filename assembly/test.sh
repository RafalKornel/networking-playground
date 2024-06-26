rm  build/tests/*

g++ -std=c++17 -c src/utilities/utilities.cpp -o build/tests/utilities.o

g++ -std=c++17 -c src/blocks/parser.cpp -o build/tests/parser.o 
g++ -std=c++17 -c src/tests/ethernet_physical_parser.test.cpp -o build/tests/ethernet_physical_parser.o 

g++ -std=c++17 -c src/blocks/connections_manager.cpp -o build/tests/connections_manager.o
g++ -std=c++17 -c src/tests/connections_manager.test.cpp -o build/tests/connections_manager.test.o

g++ -std=c++17 -c src/tests/main.cpp -o build/tests/main.o


g++ -std=c++17 build/tests/*.o -o build/tests/output && ./build/tests/output