# C++ Course

## Goals of this Course

* Practicality
  * know that practical use of every modern and advanced feature in c++
  * know how and when to use them in each situation
* Professionalism
  * Use known c++ idioms, patterns and tools
  * understand OOP and SOLID principles and how to apply them
* Competency
  * Good system design
  * Good knowledge of design patterns
  * Good analytical and debugging skills

## Contents

0. c++ Tool setup
   1. download gcc (for windows)
   2. install gcc (for windows)
   3. connect with Vscode
   4. make and make files
   5. gdb installation with Vs code
   6. compiler explorer
1. Review some C concepts
   1. Pointers
   2. Structs
   3. Unions
   4. enums
   5. dynamic memory allocation (malloc and free)
2. Transition from C to C++
   1. iostream
   2. Struct Vs Class and Class syntax
      1. constructor syntax
      2. destructor syntax and when to use it
   3. new and delete and RAII
   4. std::string
   5. streams (string stream, file stream)
3. C++ features different from C
   1. pointers Vs references
   2. Function overloading and operator overloading
   3. Function default arguments
   4. enums vs enum class
   5. keyword effects:
      1. static
      2. const vs constexpr vs mutable
      3. auto
      4. inline
   6. Meta programming (templates vs macros)
4. c++ STL
   1. containers
      1. vector
      2. list
      3. stack
      4. queue
      5. map
      6. set
   2. algorithm
      1. copy
      2. sort
   3. Helper containers
      1. pair
      2. tuple
      3. span
   4. Generic type handling
      1. void pointers and their problems
      2. smart pointers (unique vs shared)
      3. variant
      4. any
5. Initialization , Copy and Assignment
   1. different initialization syntax in C++ and std::initializer_list
   2. The different roles and types of constructors and destructors
   3. deep vs shallow copy
   4. move semantics
   5. Class design rules (3, 5, 0)

6. Functional programming
   1. Function pointers
   2. The concept of a Callable object (functor)
   3. lambda expression
   4. std::function<>
   5. Use cases and asynchronous systems
7. Modularity
   1. multi-file projects
   2. Build pipeline
   3. make and CMake
   4. Static Vs dynamic linking
   5. Namespaces
8. Error handling techniques:
   1. Assertions and design by contract
   2. static assertions and compile time type safety (Templates std::enable_if)
   3. using Error codes (enums) and `errno` in C
   4. Exceptions
   5. std::optional (C++17)
   6. std::expected (C++23)
9. OOP concepts
   1. Encapsulation
   2. Inheritance
   3. Polymorphism
   4. OOP origins
   5. OOP trade offs (when OOP is not the best design)
   6. UML diagrams
10. Concurrent programming
    1. std::thread
    2. std::mutex
    3. std::async
11. Design Patterns
    1. Types of patterns
    2. Behavioral: State Machine
    3. Behavioral: Observer
    4. Creational: Factory
    5. Creational: builder
    6. Structural: Singleton
    7. Structural: proxy
    8. Concurrent:
       1. Actor
       2. Reactor