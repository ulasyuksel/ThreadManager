# ThreadManager
This is a console application to manage creted threads. 
It is built via github workflows for Linux (ubuntu), Windows and Mac platforms. 
[[Build Status]](https://github.com/ulasyuksel/ThreadManager/actions) can be checked from the link.

*To Build:*

```$cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug```

```$cmake --build build --config Debug```

*To Run tests:*

```ctest --test-dir build```

*To Run ThreadManager:*

```$./ThreadManager -N  5```

Where 5 is the number of threads to be cretared as an example. This can be any number greater than zero 
