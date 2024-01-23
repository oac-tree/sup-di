# Example of dependency injection using XML

This folder contains an example of how XML based dependency injection can be used. It contains a library, generated from the following files:

* `client.h`: this file contains the code that will be registered in `registration.cpp`. It implements a very simple class and global function that represent the user code. Note that this code does not in any way depend on `sup-di`.
* `registration.cpp`: this file handles the actual registration of the previously mentioned class and function to the `sup::di::ObjectManager`.
* `CMakeLists.txt`: cmake file to compile the library and link it to `libsup-di`.

To compile the library:

```bash
# make sure the current working directory contains this readme file
mkdir .build
cd .build
# find out the required cmake path to be able to find `sup-di-config.cmake`. This is
# typically in the library path + '/cmake', e.g. /usr/lib/cmake.
cmake -DCMAKE_PREFIX_PATH=<cmake-path> ..
make
```

Now we can use this library by calling the `sup-di-composer` executable with the file `example.xml`:

```bash
<install-path>/sup-di-composer -f ../example.xml
```

If all is working correctly, this should print out a `Client`'s data using the injected values for its name, id and timestamp.
