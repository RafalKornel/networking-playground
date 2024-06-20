# -s EXPORTED_FUNCTIONS="['add']"
# -s EXPORTED_RUNTIME_METHODS="['add']"
# emcc src/hello.cpp -o build/example.js -s EXPORTED_FUNCTIONS="['_add']" -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s EXPORT_ES6=1 -s MODULARIZE=1
# emcc src/hello.cpp -o build/example.js -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s EXPORT_ES6=1 -s MODULARIZE=1
# emcc src/**/* -lembind -o build/main.js -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s MODULARIZE=1

g++ -std=c++14 -c src/main.cpp -o build/main.o
g++ -std=c++14 -c src/composer.cpp -o build/composer.o
g++ -std=c++14 -c src/blocks/ethernet.cpp -o build/ethernet.o
g++ -std=c++14 -c src/utilities/utilities.cpp -o build/utilities.o

# g++ -std=c++14 -c src/**/*
# g++ -std=c++14 src/**/*.o -o output

g++ -std=c++14 build/main.o build/utilities.o build/composer.o build/ethernet.o -o output