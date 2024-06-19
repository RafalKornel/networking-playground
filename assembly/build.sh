# -s EXPORTED_FUNCTIONS="['add']"
# -s EXPORTED_RUNTIME_METHODS="['add']"
# emcc src/hello.cpp -o build/example.js -s EXPORTED_FUNCTIONS="['_add']" -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s EXPORT_ES6=1 -s MODULARIZE=1
# emcc src/hello.cpp -o build/example.js -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s EXPORT_ES6=1 -s MODULARIZE=1
emcc src/hello.cpp -lembind -o build/example.js -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s EXPORT_ES6=1 -s MODULARIZE=1

