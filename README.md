# Metrics Stream Handler Example

This directory contains a stream handler example for [pktvisor](https://github.com/ns1labs/pktvisor) module developers.
In order to create your own pktvisor module, you can use this repository as reference.
You can also use the standard modules as reference code for your own module.

This project adds pktvisor project as a git submodule using the command:
```
git submodule add https://github.com/ns1labs/pktvisor.git
```

### Build
To build this project you can simple follow the commands.
```
git clone https://github.com/ns1labs/pktvisor-module-example.git
cd pktvisor-module-example
git submodule  update --init --recursive --progress
mkdir build && cd build

# configure and handle dependencies 
cmake -DCMAKE_BUILD_TYPE=Release ..

# build and run tests
make all test
```

### Artifacts
It will generate a shared object `VisorExampleHandlerDyn.so` and the config file `VisorExampleHandlerDyn.conf` in `build/lib`. 
You can change the folder of those files. Then, to use the Dynamic Module in pktvisord you should pass the folder which contains module files:
```
<bin_path>/pktvisord --module-dir <example_handler_dir>   
```

### Adding new module dependencies on conan
If you want to add new 3rd party libraries through conan, you just need to add it to [conanfile.txt](conanfile.txt).
For instance, the Example Module has a dependency to `sqlite3` which is not an original pktvisor dependency.
