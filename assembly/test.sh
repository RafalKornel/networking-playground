g++ -std=c++14 -c src/blocks/parser.cpp -o build/tests/parser.o 
g++ -std=c++14 -c src/tests/ethernet.test.cpp -o build/tests/ethernet.o 


g++ -std=c++14 build/tests/ethernet.o build/tests/parser.o -o build/tests/output && ./build/tests/output