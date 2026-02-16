# Standard Library Algorithms - Practical Exercises

## Exercise 1: Sorting and Searching (Data Processing)
**Context:** Process and search through large datasets efficiently.

**Problem:**
```cpp
// Implement data processing:
// 1. Sort data by different criteria
// 2. Binary search on sorted data
// 3. Find first/last occurrence
// 4. Remove duplicates
// 5. Partition by condition
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Student {
    string name;
    int score;
    
    Student(const string &n, int s) : name(n), score(s) {}
};

int main() {
    cout << "=== STL Algorithms: Sorting and Searching ===" << endl;
    
    vector<int> scores = {45, 78, 23, 89, 56, 89, 12, 67, 34, 89};
    
    cout << "\n--- Original data ---" << endl;
    for (int s : scores) cout << s << " ";
    cout << endl;
    
    cout << "\n--- Sorting ---" << endl;
    vector<int> sorted_scores = scores;
    sort(sorted_scores.begin(), sorted_scores.end());
    for (int s : sorted_scores) cout << s << " ";
    cout << endl;
    
    cout << "\n--- Sorting in descending order ---" << endl;
    sort(scores.begin(), scores.end(), greater<int>());
    for (int s : scores) cout << s << " ";
    cout << endl;
    
    cout << "\n--- Finding maximum ---" << endl;
    int max_score = *max_element(scores.begin(), scores.end());
    cout << "Maximum: " << max_score << endl;
    
    cout << "\n--- Finding occurrence count ---" << endl;
    int target = 89;
    int count = std::count(scores.begin(), scores.end(), target);
    cout << "Score " << target << " appears " << count << " times" << endl;
    
    cout << "\n--- Finding positions ---" << endl;
    auto it = find(scores.begin(), scores.end(), target);
    if (it != scores.end()) {
        cout << "First occurrence at position: " << distance(scores.begin(), it) << endl;
    }
    
    cout << "\n--- Removing duplicates (preserve order) ---" << endl;
    vector<int> unique_scores = scores;
    sort(unique_scores.begin(), unique_scores.end());
    auto new_end = unique(unique_scores.begin(), unique_scores.end());
    unique_scores.erase(new_end, unique_scores.end());
    cout << "Unique scores: ";
    for (int s : unique_scores) cout << s << " ";
    cout << endl;
    
    cout << "\n--- Partitioning (scores >= 50) ---" << endl;
    auto partition_point = partition(scores.begin(), scores.end(),
                                    [](int x) { return x >= 50; });
    cout << "High scores: ";
    for (auto it = scores.begin(); it != partition_point; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "\n✓ Algorithms operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 2: Transformations and Filtering (Data Transformation)
**Context:** Transform and filter data for different representations.

**Problem:**
```cpp
// Implement transformations:
// 1. Transform data (square, double, convert)
// 2. Filter by predicate
// 3. Accumulate/reduce
// 4. Map and flatten
// 5. Custom processing pipelines
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

int main() {
    cout << "=== STL Algorithms: Transformations ===" << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "\n--- Original numbers ---" << endl;
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    cout << "\n--- Transform: double each number ---" << endl;
    vector<int> doubled(numbers.size());
    transform(numbers.begin(), numbers.end(), doubled.begin(),
              [](int x) { return x * 2; });
    for (int n : doubled) cout << n << " ";
    cout << endl;
    
    cout << "\n--- Transform: square each number ---" << endl;
    vector<int> squared(numbers.size());
    transform(numbers.begin(), numbers.end(), squared.begin(),
              [](int x) { return x * x; });
    for (int n : squared) cout << n << " ";
    cout << endl;
    
    cout << "\n--- Filter: even numbers ---" << endl;
    vector<int> evens;
    copy_if(numbers.begin(), numbers.end(), back_inserter(evens),
            [](int x) { return x % 2 == 0; });
    for (int n : evens) cout << n << " ";
    cout << endl;
    
    cout << "\n--- Accumulate: sum ---" << endl;
    int sum = accumulate(numbers.begin(), numbers.end(), 0);
    cout << "Sum: " << sum << endl;
    
    cout << "\n--- Accumulate: product ---" << endl;
    int product = accumulate(numbers.begin(), numbers.end(), 1,
                            [](int a, int b) { return a * b; });
    cout << "Product: " << product << endl;
    
    cout << "\n--- Chain transformations ---" << endl;
    vector<int> pipeline = numbers;
    
    // Filter evens
    vector<int> temp1;
    copy_if(pipeline.begin(), pipeline.end(), back_inserter(temp1),
            [](int x) { return x % 2 == 0; });
    
    // Double them
    vector<int> temp2(temp1.size());
    transform(temp1.begin(), temp1.end(), temp2.begin(),
              [](int x) { return x * 2; });
    
    cout << "After filter (evens) + double: ";
    for (int n : temp2) cout << n << " ";
    cout << endl;
    
    cout << "\n✓ Transformation operations complete" << endl;
    
    return 0;
}
```

---

## Exercise 3: Complex Data Processing (Real-World Pipeline)
**Context:** Process sensor data with multiple transformations.

**Problem:**
```cpp
// Create data pipeline:
// 1. Read sensor readings
// 2. Filter outliers
// 3. Transform to different units
// 4. Aggregate statistics
// 5. Generate report
```

**Solution:**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

struct SensorReading {
    float temperature;
    float humidity;
    
    SensorReading(float t, float h) : temperature(t), humidity(h) {}
};

class DataAnalyzer {
private:
    vector<SensorReading> readings;
    
public:
    void addReading(float temp, float humidity) {
        readings.push_back(SensorReading(temp, humidity));
    }
    
    // Filter outliers (temperature outside ±3 sigma)
    void filterOutliers() {
        float avg_temp = accumulate(readings.begin(), readings.end(), 0.0f,
                                   [](float sum, const SensorReading &r) {
                                       return sum + r.temperature;
                                   }) / readings.size();
        
        cout << "Average temperature: " << avg_temp << endl;
        
        // Simple outlier detection: keep within ±5 degrees of average
        auto new_end = remove_if(readings.begin(), readings.end(),
                                [avg_temp](const SensorReading &r) {
                                    return abs(r.temperature - avg_temp) > 5.0f;
                                });
        
        int removed = distance(new_end, readings.end());
        readings.erase(new_end, readings.end());
        cout << "Removed " << removed << " outliers" << endl;
    }
    
    // Convert Celsius to Fahrenheit
    vector<float> convertToFahrenheit() {
        vector<float> farenheit(readings.size());
        transform(readings.begin(), readings.end(), farenheit.begin(),
                 [](const SensorReading &r) {
                     return (r.temperature * 9.0f / 5.0f) + 32.0f;
                 });
        return farenheit;
    }
    
    void printStatistics() {
        cout << "\n=== Temperature Statistics ===" << endl;
        
        float temps[readings.size()];
        transform(readings.begin(), readings.end(), temps,
                 [](const SensorReading &r) { return r.temperature; });
        
        float min_temp = *min_element(temps, temps + readings.size());
        float max_temp = *max_element(temps, temps + readings.size());
        float avg_temp = accumulate(temps, temps + readings.size(), 0.0f) / readings.size();
        
        cout << "Min: " << min_temp << "°C" << endl;
        cout << "Max: " << max_temp << "°C" << endl;
        cout << "Avg: " << avg_temp << "°C" << endl;
        cout << "Count: " << readings.size() << endl;
    }
    
    void printReadings() {
        cout << "\nReadings:" << endl;
        for (size_t i = 0; i < readings.size(); i++) {
            cout << "  [" << i+1 << "] Temp: " << readings[i].temperature
                 << "°C, Humidity: " << readings[i].humidity << "%" << endl;
        }
    }
};

int main() {
    cout << "=== Complex Algorithm Pipeline: Sensor Data ===" << endl;
    
    DataAnalyzer analyzer;
    
    cout << "\n--- Adding readings ---" << endl;
    analyzer.addReading(22.5, 45);
    analyzer.addReading(23.0, 48);
    analyzer.addReading(22.8, 46);
    analyzer.addReading(50.0, 50);  // Outlier
    analyzer.addReading(23.2, 47);
    analyzer.addReading(22.9, 45);
    
    cout << "Total readings: 6" << endl;
    analyzer.printReadings();
    
    cout << "\n--- Filtering outliers ---" << endl;
    analyzer.filterOutliers();
    analyzer.printReadings();
    
    cout << "\n--- Converting to Fahrenheit ---" << endl;
    auto fahrenheit = analyzer.convertToFahrenheit();
    cout << "Fahrenheit readings: ";
    for (float f : fahrenheit) {
        cout << f << "°F ";
    }
    cout << endl;
    
    analyzer.printStatistics();
    
    cout << "\n✓ Data processing pipeline complete" << endl;
    
    return 0;
}
```
