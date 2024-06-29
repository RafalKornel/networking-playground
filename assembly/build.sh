# -s EXPORTED_FUNCTIONS="['add']"
# -s EXPORTED_RUNTIME_METHODS="['add']"
# emcc src/hello.cpp -o build/example.js -s EXPORTED_FUNCTIONS="['_add']" -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s EXPORT_ES6=1 -s MODULARIZE=1
# emcc src/hello.cpp -o build/example.js -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s EXPORT_ES6=1 -s MODULARIZE=1
# emcc src/**/* -lembind -o build/main.js -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s MODULARIZE=1

rm  build/out/*


g++ -std=c++17 -c src/blocks/parser.cpp -o build/out/parser.o 
g++ -std=c++17 -c src/blocks/connections_manager.cpp -o build/out/connections_manager.o
g++ -std=c++17 -c src/blocks/ethernet.cpp -o build/out/ethernet.o

g++ -std=c++17 -c src/composer.cpp -o build/out/composer.o
g++ -std=c++17 -c src/template_implementations.cpp -o build/out/template_implementations.o
g++ -std=c++17 -c src/main.cpp -o build/out/main.o

g++ -std=c++17 -c src/utilities/utilities.cpp -o build/out/utilities.o

g++ -std=c++17 build/out/*.o -o build/out/output && ./build/out/output

# g++ -std=c++17 -c src/**/*
# g++ -std=c++17 src/**/*.o -o output

# g++ -std=c++17 build/main.o build/utilities.o build/composer.o build/ethernet.o -o build/output && ./build/output