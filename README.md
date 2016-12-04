Ludum Dare #37 goes here
====

Theme not yet released, just framework building for the moment.

Requirements
----

SFML 2.4+
Angelscript 2.31+

A recent compiler supporting C++11/14

Instructions
---

### Linux:

Building:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Running:
```
$ build/bin/LD37
```

### Windows:

Generate VS solutions with CMake. (Only tested with Visual Studio 2015.)
Set `Debugging -> Working Directory` to `$(SolutionDir)..` for the LD37 Project.
