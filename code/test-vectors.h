#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
// #include <format>
using namespace std;

int acc(int sum, int next)
{
    return (sum+next);
}

class Point
{
public:
    Point(int x, int y, int z):_x(x),_y(y),_z(z)
    {
        // std::println("created point with ({},{},{})", x,y,z);
        cout << "created point (" <<
        x << ","  <<
        y << ","  <<
        z << ","  <<
        ")" << endl;
    }

    Point(const Point& p)
    {
        cout << "copied point" << endl;
        _x = p._x;
        
    }

    int _x,_y,_z ;
};





int test_vectors_main(int argc, char* argv[])
{

#define ARRAYS_1 0
#if ARRAYS_1 // using std::array

    // Basic declaration and initialization
    std::array<int, 5> arr = {10, 20, 30, 40, 50};
    
    // Access elements using index
    arr[0] = 100;
    arr.at(2) = 300;  // at() performs bounds checking
    
    // Get size (fixed at compile time)
    cout << "Array size: " << arr.size() << endl;
    
    // Iterate using range-based for loop
    for (int& val : arr) {
        cout << val << ' ';  // 100 20 300 40 50
    }
    cout << endl;
    
    // Iterate using iterators
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
    
    // Access front and back
    int first = arr.front();  // 100
    int last = arr.back();     // 50
    
    // Fill the array with a value
    arr.fill(99);
    
    // Check if array is empty (always false for std::array)
    if (!arr.empty()) {
        cout << "Array is not empty" << endl;
    }
    
    // Get pointer to underlying data
    int* data = arr.data();
    cout << "First element via pointer: " << *data << endl;

#endif

#define ARRAYS_2 0
#if ARRAYS_2 // using std::begin and std::end with C-style arrays
    
    // C-style array
    int carray[] = {5, 15, 25, 35, 45};
    
    // std::begin and std::end allow us to use C-style arrays with iterators
    cout << "\nIterating with std::begin and std::end: ";
    for (auto it = std::begin(carray); it != std::end(carray); ++it) {
        cout << *it << ' ';  // 5 15 25 35 45
    }
    cout << endl;
    
    // Can also use with range-based for loop (works because of std::begin/std::end)
    cout << "Range-based for loop on C-array: ";
    for (int val : carray) {
        cout << val << ' ';
    }
    cout << endl;
    


#endif

#define VECTORS_1 0
#if VECTORS_1
    vector<int> v; //create a vector of ints
    v.push_back(10); //put values at end of array
    v.push_back(11);
    v.push_back(12);
    v.push_back(13);
    v[0] = 20; //replace with new values
    v[3] = 23;
    for(int j=0; j<v.size(); j++) //display vector contents
    cout << v[j] << ' '; //20 11 12 23
    cout << endl;

    // diff. bet. back and pop_back
    int last = v.back(); // returns the current last element in the vector
    v.pop_back(); // void: removes the last element of the vector and decrements the size.

    int carray[] = {5, 15, 25, 35, 45};
    // Initialize a vector from C-style array using std::begin and std::end
    vector<int> vfromcarray(std::begin(carray), std::end(carray));
    cout << "Vector initialized from C-array: ";
    for (int val : vfromcarray) {
        cout << val << ' ';
    }
    cout << endl;

#endif



#define VECTORS_2 0
#if VECTORS_2 // iterating on vectors
    int arr[] = { 100, 110, 120, 130 }; //an array of ints
    vector<int> v(arr, arr+4); //initialize vector to array
    cout << "\nBefore insertion: ";
    int j=0;
    for(j=0; j<v.size(); j++) //display all elements
        cout << v[j] << ' ';
    v.insert( v.begin()+2, 115); //insert 115 at element 2
    cout << "\nAfter insertion: ";
    for(j=0; j<v.size(); j++) //display all elements
        cout << v[j] << ' ';
    v.erase( v.begin()+2 ); //erase element 2
    cout << "\nAfter erasure: ";
    for(j=0; j<v.size(); j++) //display all elements
        cout << v[j] << ' ';
    cout << endl;

    cout << "______ reverse iteration _____\n";
    for(auto it = v.rbegin(); it != v.rend(); it++)
    {
        cout << *it << ',' ;
    }
    cout << endl;

    cout << "begin():" << addressof(*v.begin()) << endl;
    cout << "end():" << addressof(*v.end()) << endl;
    cout << "rbegin():" << addressof(*v.rbegin()) << endl;
    cout << "rend():" << addressof(*v.rend()) << endl;




#endif

#define VECTORS_3 0
#if VECTORS_3 // difference between size and capacity

    vector<int> v;
    cout << "size,capacity\n";
    // Add elements
    for (int i = 0; i < 1000; i++) {
        v.push_back(i);
        cout << v.size() << ',' << v.capacity() << '\n';
    }
    // cout << "After push_back 5 elements - Size: " << v.size() << ", Capacity: " << v.capacity() << endl;
    
    // // Add more elements (still within reserved capacity)
    // for (int i = 5; i < 10; i++) {
    //     v.push_back(i * 10);
    // }
    // cout << "After push_back 10 elements - Size: " << v.size() << ", Capacity: " << v.capacity() << endl;
    
    // // Add one more element (exceeds capacity, reallocation occurs)
    // v.push_back(100);
    // cout << "After push_back 11 elements - Size: " << v.size() << ", Capacity: " << v.capacity() << endl;
    
    // // Remove elements (size decreases, capacity remains)
    // v.pop_back();
    // v.pop_back();
    // cout << "After pop_back 2 elements - Size: " << v.size() << ", Capacity: " << v.capacity() << endl;
    
    // // Shrink capacity to fit size
    // v.shrink_to_fit();
    // cout << "After shrink_to_fit() - Size: " << v.size() << ", Capacity: " << v.capacity() << endl;
    
    // KEY DIFFERENCE:
    // size()     = number of elements currently stored
    // capacity() = total allocated memory (in number of elements)
#if 0
    // PITFALL: Vector relocation and dangling pointers
    cout << "\nVector Relocation Pitfall Demo:" << endl;
    vector<int> nums;
    nums.push_back(100);
    
    // Get address of first element
    int* ptr = &nums[0];
    cout << "Address of nums[0]: " << ptr << ", Value: " << *ptr << endl;
    cout << "Vector data pointer: " << nums.data() << endl;
    
    // Add many elements - this will cause reallocation
    for (int i = 0; i < 20; i++) {
        nums.push_back(i);
    }
    
    // Now check the address again
    cout << "\nAfter adding 20 more elements:" << endl;
    cout << "Original pointer address: " << ptr << ", Attempting to dereference..." << endl;
    cout << "Vector data pointer: " << nums.data() << endl;
    
    // The original pointer is now INVALID! Vector reallocated to new memory
    // Dereferencing ptr would be undefined behavior!
    
    // The correct way is to use indices or get fresh pointers
    cout << "Correct approach - use index: nums[0] = " << nums[0] << endl;
    
    // Or get a fresh pointer after modifications
    int* new_ptr = &nums[0];
    cout << "Fresh pointer: " << new_ptr << ", Value: " << *new_ptr << endl;
#endif


#endif

#define VECTORS_4 0
#if VECTORS_4 // Vector iteration pitfall: modifying size during iteration

    cout << "\nVector Iteration Pitfall - INFINITE LOOP DANGER!" << endl;
    
    // WRONG: Checking size in loop condition while modifying vector
    vector<int> bad_vec = {1, 2, 3};
    cout << "Initial vector size: " << bad_vec.size() << endl;
    
    // THIS IS DANGEROUS - DO NOT DO THIS IN REAL CODE!
    // Uncommenting this would cause an infinite loop (commented out to prevent hang)
    /*
    for (int i = 0; i < bad_vec.size(); i++) {  // size keeps growing!
        cout << "i = " << i << ", size = " << bad_vec.size() << endl;
        bad_vec.push_back(i * 10);  // Modifying size during iteration!
        
        // This loop will never end because size() keeps returning a larger value
        // Eventually memory runs out -> crash/overflow
        if (i > 20) break;  // Safety break to prevent actual infinite loop
    }
    */
    cout << "Skipped dangerous infinite loop example (would crash system)" << endl;
    
    // CORRECT: Cache the size before the loop
    cout << "\nCorrect approach - Cache size before loop:" << endl;
    vector<int> good_vec = {10, 20, 30};
    size_t original_size = good_vec.size();  // Cache the original size
    
    for (size_t i = 0; i < original_size; i++) {
        cout << "i = " << i << ", element = " << good_vec[i] << endl;
        // Now it's safe to modify the vector after processing original elements
        good_vec.push_back(good_vec[i] * 2);
    }
    
    cout << "After adding duplicates: ";
    for (int val : good_vec) {
        cout << val << ' ';  // 10 20 30 20 40 60
    }
    cout << endl;
    
    // ALTERNATIVE: Process only elements before modification
    cout << "\nAlternative - Separate logic for original vs new elements:" << endl;
    vector<int> safe_vec = {5, 10, 15};
    
    // Process only original elements
    for (int i = 0; i < 3; i++) {  // Hard-coded original size
        cout << safe_vec[i] << ' ';
    }
    cout << endl;
    
    // Then modify separately
    for (int val : safe_vec) {
        safe_vec.push_back(val + 100);
    }
    cout << "After modification: ";
    for (int val : safe_vec) {
        cout << val << ' ';  // 5 10 15 105 110 115
    }
    cout << endl;

#endif


#define VECTORS_5 0
#if VECTORS_5 // Common vector pitfalls

    cout << "\n=== VECTOR PITFALLS ===" << endl;
    
    // PITFALL 1: Iterator Invalidation
    cout << "\n1. Iterator Invalidation - iterators become invalid after modifications:" << endl;
    {
        vector<int> v = {10, 20, 30, 40, 50};
        auto it = v.begin() + 2;  // Point to 30
        cout << "Before insert: iterator points to " << *it << endl;
        
        v.insert(v.begin() + 1, 15);  // Insert at position 1
        
        // Now 'it' is INVALID! Dereferencing it is undefined behavior
        // cout << "After insert: " << *it << endl;  // DON'T DO THIS!
        
        cout << "After insert: vector is " << v[0] << ' ' << v[1] << ' ' << v[2] << ' ' << v[3] << ' ' << v[4] << ' ' << v[5] << endl;
        cout << "SOLUTION: Re-obtain iterator after modifications" << endl;
        it = v.begin() + 3;  // Get fresh iterator
        cout << "Fresh iterator points to: " << *it << endl;
    }
    
    // PITFALL 2: Out-of-bounds access with operator[]
    cout << "\n2. Out-of-bounds access - operator[] has no bounds checking:" << endl;
    {
        vector<int> v = {10, 20, 30};
        cout << "Vector size: " << v.size() << endl;
        
        // This is undefined behavior - no error, just garbage or crash
        // cout << "v[10] = " << v[10] << endl;  // DON'T DO THIS!
        
        cout << "CORRECT: Use .at() for bounds checking:" << endl;
        try {
            cout << v.at(10);  // Throws std::out_of_range
        } catch (const std::out_of_range& e) {
            cout << "Caught exception: " << e.what() << endl;
        }
    }
    
    // PITFALL 3: Range-based for loop with modifications
    cout << "\n3. Range-based for with erase/insert - invalidates iterator:" << endl;
    {
        vector<int> v = {10, 20, 30, 40, 50};
        cout << "Original: ";
        for (int val : v) cout << val << ' ';
        cout << endl;
        
        cout << "WRONG - Using range-based for with erase:" << endl;
        cout << "for (int val : v) { v.erase(...); }  // Iterator becomes invalid!" << endl;
        
        cout << "CORRECT - Use traditional for loop with index:" << endl;
        vector<int> v2 = {10, 20, 30, 40, 50};
        for (int i = 0; i < v2.size(); i++) {
            if (v2[i] % 20 == 0) {  // Remove even multiples
                v2.erase(v2.begin() + i);
                i--;  // Adjust index after erase
            }
        }
        cout << "After erase: ";
        for (int val : v2) cout << val << ' ';  // 10 30 50
        cout << endl;
    }
    
    // PITFALL 4: Comparing iterators from different vectors
    cout << "\n4. Comparing iterators from different vectors:" << endl;
    {
        vector<int> v1 = {1, 2, 3};
        vector<int> v2 = {1, 2, 3};
        
        cout << "WRONG: v1.begin() < v2.begin()  // Undefined behavior!" << endl;
        cout << "CORRECT: Only compare iterators from the same vector" << endl;
        cout << "v1.begin() < v1.end() = " << (v1.begin() < v1.end()) << endl;
    }
    
    // PITFALL 5: Accessing empty vector
    cout << "\n5. Accessing empty vector - front(), back(), operator[] are unsafe:" << endl;
    {
        vector<int> v;
        
        cout << "Empty vector - accessing without check:" << endl;
        cout << "WRONG: v[0] or v.front() or v.back()  // Undefined behavior!" << endl;
        cout << "CORRECT: Check empty() before access:" << endl;
        
        if (!v.empty()) {
            cout << "Front: " << v.front() << endl;
        } else {
            cout << "Vector is empty, cannot access front/back" << endl;
        }
    }
    
    // PITFALL 6: Performance issue - frequent insertions at front
    cout << "\n6. Performance pitfall - inserting at front is O(n):" << endl;
    {
        vector<int> v = {30, 20, 10};
        cout << "Original: 30 20 10" << endl;
        
        v.insert(v.begin(), 40);  // Inserts at front - O(n) operation!
        v.insert(v.begin(), 50);  // Inserts at front - O(n) operation!
        
        cout << "After 2 front insertions: ";
        for (int val : v) cout << val << ' ';
        cout << endl;
        cout << "WARNING: Each insert at front requires shifting all elements!" << endl;
        cout << "SOLUTION: Use std::deque if frequent front insertions are needed" << endl;
    }
    
    // PITFALL 7: Reference invalidation
    cout << "\n7. Reference invalidation - references become invalid after reallocation:" << endl;
    {
        vector<int> v = {100};
        int& ref = v[0];  // Store reference to first element
        
        cout << "Before reallocation: ref = " << ref << endl;
        
        // Force reallocation by adding many elements
        for (int i = 0; i < 20; i++) {
            v.push_back(i);
        }
        
        // Now ref is INVALID! Using it is undefined behavior
        // cout << "After reallocation: ref = " << ref << endl;  // DON'T DO THIS!
        
        cout << "SOLUTION: Use indices instead of references, or get fresh references:" << endl;
        cout << "v[0] = " << v[0] << endl;
        int& new_ref = v[0];
        cout << "Fresh reference: " << new_ref << endl;
    }
    
    // PITFALL 8: Unintended copies - passing by value
    cout << "\n8. Unintended copies - passing vectors by value is expensive:" << endl;
    {
        auto print_size_by_value = [](vector<int> v) {  // WRONG: copies entire vector!
            return v.size();
        };
        
        auto print_size_by_ref = [](const vector<int>& v) {  // CORRECT: just reference
            return v.size();
        };
        
        vector<int> large_vec(1000, 42);
        
        cout << "Passing by value (copies 1000 elements): inefficient!" << endl;
        cout << "Size: " << print_size_by_value(large_vec) << endl;
        
        cout << "Passing by const reference (no copy): efficient!" << endl;
        cout << "Size: " << print_size_by_ref(large_vec) << endl;
        
        cout << "RULE: Use const vector<T>& for read-only, vector<T>& for modification" << endl;
    }

#endif

#define VECTORS_6 0
#if VECTORS_6 // Capacity growth pattern

    cout << "\n=== CAPACITY GROWTH PATTERN ===" << endl;
    //  "As elements are added, capacity grows in jumps, not linearly with size" << endl;
    
    vector<int> v;
    
    cout << "Size | Capacity | What Happened" << endl;
    cout << "----|----------|---------------" << endl;
    cout << v.size() << "    | " << v.capacity() << "       | Initial empty vector" << endl;
    
    // Add elements one by one and track size/capacity changes
    for (int i = 1; i <= 20; i++) {
        v.push_back(i * 10);
        cout << v.size() << "    | " << v.capacity() << "       | Added element " << i << endl;
    }
    
    cout << "\nKey Observations:" << endl;
    cout << "1. Capacity is always >= size" << endl;
    cout << "2. Capacity grows in jumps (typically 1.5x or 2x growth factor)" << endl;
    cout << "3. When size exceeds capacity, reallocation occurs" << endl;
    cout << "4. Excess capacity exists to avoid frequent reallocations" << endl;
    
    // Additional example showing performance benefit of reserve()
    cout << "\n--- Reserve vs No Reserve Performance Impact ---" << endl;
    
    vector<int> v_with_reserve;
    v_with_reserve.reserve(100);  // Pre-allocate for 100 elements
    
    vector<int> v_without_reserve;  // No pre-allocation
    
    cout << "Vector with reserve(100):" << endl;
    cout << "  Size: " << v_with_reserve.size() << ", Capacity: " << v_with_reserve.capacity() << endl;
    
    cout << "Vector without reserve:" << endl;
    cout << "  Size: " << v_without_reserve.size() << ", Capacity: " << v_without_reserve.capacity() << endl;
    
    // Add 100 elements to both
    for (int i = 0; i < 100; i++) {
        v_with_reserve.push_back(i);
    }
    for (int i = 0; i < 100; i++) {
        v_without_reserve.push_back(i);
    }
    
    cout << "\nAfter adding 100 elements:" << endl;
    cout << "Vector with reserve(100):" << endl;
    cout << "  Size: " << v_with_reserve.size() << ", Capacity: " << v_with_reserve.capacity() << " (no reallocations needed!)" << endl;
    cout << "Vector without reserve:" << endl;
    cout << "  Size: " << v_without_reserve.size() << ", Capacity: " << v_without_reserve.capacity() << " (multiple reallocations)" << endl;
    
    cout << "\nBest Practice:" << endl;
    cout << "- Use reserve() if you know the approximate final size" << endl;
    cout << "- Avoids multiple reallocations and memory copies" << endl;
    cout << "- Improves performance for large vectors" << endl;

#endif

#if 0 // take numbers from command line and sum them
// format: sum 1 2 3 4 5
// output: 15
    vector<int> nums  = {1};
    nums.reserve(argc-1); // capacity
    // for(int i=1; i<argc; i++)
    // {
    //     nums.push_back(stoi(string(argv[i])));
    // }

    // int sum = std::accumulate(nums.begin(), nums.end(), 0, acc);

    // cout << sum << endl;

// format: sum from=2  to=15 # sum the numbers from 2 to 15
// output: 
    int from = 0 ,to = 0 ;
    for(int i=1; i<argc; i++)
    {
        string key,value;
        string arg(argv[i]);
        stringstream ss(arg);
        std::getline(ss, key, '=');
        std::getline(ss, value);

        if(key == "from") from = stoi(value);
        if(key == "to") to = stoi(value);
    }

    for(; from <= to; from++)
    {
        nums.push_back(from);
    }

    int sum = std::accumulate(nums.begin()+2, nums.begin()+5, 0, acc);

    cout << sum << endl;

#endif

#if 1 // implement class Matrix with vectors and operator overloading of +, -, *
// NOTE: try to use only one vector
#endif

#if 1 // read script and exec operations on a vector
// operations include:
// create, insert, erase, append, read, write
// ex: 
//     create 10 20 30 
//     insert 5@2
//     erase 2 // remove element @ index 2
//     append 40
//     read 0 // should print the value at index 0
//     write 5@0 // modify index 0 to be 5
//     

#endif

    vector<Point> points ;
    Point p(1,2,3);
    points.push_back(p);

    points.emplace_back(4,5,6);
}