# C++ Practical Exercises Collection

**A comprehensive set of 30 practice files covering all major C++ concepts with real-world scenarios.**

## 📚 What You'll Find Here

This collection contains **~90 complete, working C++ exercises** organized by topic. Each exercise:

✓ Addresses a specific C++ concept  
✓ Includes a real-world context (embedded systems, Linux, or backend)  
✓ Provides complete, compilable source code  
✓ Demonstrates best practices  
✓ Includes practical applications  

## 🚀 Quick Start

### Start Here First
1. Read [INDEX.md](INDEX.md) for a complete overview
2. Choose a learning path based on your goals
3. Work through exercises in order within each category

### Running the Exercises

Each exercise is a complete, standalone C++ program:

```bash
# Compile an exercise
g++ -std=c++17 -o program_name 01_Pointers_Exercises.md

# Or use a C++ IDE (VS Code, CLion, Visual Studio)
# Copy-paste the code and run
```

## 📖 File Organization

```
exercises/
├── 01_Pointers_Exercises.md           (Core Concepts)
├── 02_Structs_Exercises.md
├── 03_Unions_Exercises.md
├── 04_Enums_Exercises.md
├── 05_Dynamic_Memory_Exercises.md
├── 06_IOStream_Exercises.md           (C to C++ Transition)
├── 07_Classes_Exercises.md
├── 08_Constructors_Destructors_Exercises.md
├── 09_New_Delete_Exercises.md
├── 10_String_Exercises.md
├── 11_References_vs_Pointers_Exercises.md  (Advanced Features)
├── 12_Overloading_Exercises.md
├── 13_Lambda_Exercises.md
├── 14_Vector_Exercises.md             (STL Containers)
├── 15_SmartPointers_Exercises.md
├── 16_Exceptions_Exercises.md
├── 17_STLAlgorithms_Exercises.md
├── 18_Map_Exercises.md
├── 19_Set_Exercises.md
├── 20_PairTuple_Exercises.md
├── 21_List_Exercises.md
├── 22_Stack_Exercises.md
├── 23_Queue_Exercises.md
├── 24_Optional_Exercises.md           (Modern C++)
├── 25_Const_Exercises.md
├── 26_Static_Exercises.md
├── 27_DefaultArguments_Exercises.md
├── 28_Constexpr_Exercises.md
├── 29_Namespaces_Exercises.md
├── 30_Inheritance_Exercises.md
├── INDEX.md                             (Complete Guide)
└── README.md                            (This File)
```

## 🎯 Learning Paths

### For Beginners
```
Pointers → Structs → Enums → Dynamic Memory
    ↓        ↓        ↓           ↓
Classes → Constructors → Strings → References
    ↓
Inheritance
```

### For Embedded Systems
```
Pointers (GPIO) → Unions (Registers) → Dynamic Memory (Buffers)
    ↓
Smart Pointers (Resource Safety) → Lambda (Event Handling)
```

### For Backend Development
```
Classes → IOStream → Containers (Vector, Map, List, Set)
    ↓
STL Algorithms → Exception Handling → Polymorphism
```

### For System Software
```
Memory Management → Exception Safety → Constexpr
    ↓
Smart Pointers → Static Variables → Const Correctness
```

## 💡 Tips for Learning

1. **Read the Context First**
   - Understand the real-world scenario
   - Think about why the pattern matters

2. **Study the Solution**
   - Follow the explanatory comments
   - Understand the design choices

3. **Modify and Experiment**
   - Change input values
   - Add new features
   - Break it intentionally to learn

4. **Compile and Run**
   - Execute each exercise
   - See the output
   - Verify understanding

5. **Challenge Yourself**
   - Try exercises without looking at the solution
   - Combine concepts from multiple exercises
   - Create your own variations

## 📊 Exercise Breakdown

| Category | Files | Exercises | Focus |
|----------|-------|-----------|-------|
| Core Concepts | 5 | 15 | Fundamentals |
| Transition | 5 | 15 | C to C++ |
| Advanced | 3 | 9 | Features |
| Containers | 10 | 30 | STL |
| Smart Ptrs & Exceptions | 2 | 6 | Safety |
| Modern C++ | 5 | 15 | Recent Features |
| OOP | 2 | 6 | Design |
| **TOTAL** | **30** | **~90** | **Professional Code** |

## 🎓 Learning Outcomes

By working through these exercises, you will:

✅ Understand pointers and memory management  
✅ Master object-oriented design  
✅ Use STL containers appropriately  
✅ Write exception-safe code  
✅ Apply modern C++ features  
✅ Solve real-world problems  
✅ Write maintainable code  
✅ Understand performance implications  
✅ Apply design patterns  
✅ Build professional applications  

## 🔧 Compilation

### Using g++
```bash
# Basic compilation
g++ -std=c++17 filename.md -o program

# With warnings
g++ -std=c++17 -Wall -Wextra filename.md -o program

# With optimization
g++ -std=c++17 -O2 filename.md -o program
```

### Using Visual Studio
1. Create new C++ Console Application
2. Copy exercise code into main.cpp
3. Build and Run (Ctrl+F5)

### Using VS Code with CodeRunner
1. Install Code Runner extension
2. Right-click and select "Run Code"
3. Output appears in terminal

## 📝 Exercise Structure

Each exercise typically contains:

1. **Title + Context**
   - Real-world scenario
   - Why this matters

2. **Problem Statement**
   - What to build
   - Requirements
   - Expected behavior

3. **Complete Solution**
   - Working C++ code
   - Explanatory comments
   - Example output

4. **Learning Points**
   - Key concepts
   - Best practices
   - Common pitfalls

## 🚨 Troubleshooting

### Code Won't Compile
- Check C++ standard (use `-std=c++17` or newer)
- Verify all includes are present
- Check for typos

### Output Doesn't Match
- Verify input values
- Check for timing-dependent results
- Run the exact code from the exercise

### Need Help Understanding
- Read the explanatory comments in code
- Check the Problem statement
- Review the Context section
- Compare with similar exercises

## 🔗 Resources

### C++ References
- [cppreference.com](https://cppreference.com) - Comprehensive C++ documentation
- [cpp.skillbox.com](https://cpp.skillbox.com) - Interactive learning
- [learncpp.com](https://learncpp.com) - Detailed tutorials

### Tools
- [GCC](https://gcc.gnu.org) - Free C++ compiler
- [Clang](https://clang.llvm.org) - Alternative compiler
- [MSVC](https://visualstudio.microsoft.com) - Visual Studio

## 📞 Questions?

- Review the exercise context and problem statement
- Compare your approach with the solution
- Try debugging step by step
- Create simpler test cases to isolate issues

---

**Happy Coding! 🎉**

Start with [INDEX.md](INDEX.md) to begin your learning journey!
