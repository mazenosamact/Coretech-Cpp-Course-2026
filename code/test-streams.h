


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;


class CUartConfig {
    int     m_baudrate;
    int     m_stopbits;
    int     m_slaveaddr;
    string  m_parity;
public:
    int load(){
        int error_code = 0 ;
        string line;
        string key,value;
        while(std::getline(cin, line))
        {
            stringstream parser(line);
            std::getline(parser, key, '='); // key=value
            std::getline(parser, value);

            cerr << "key: " << key << " ,value: " << value << endl;
            if(key == "baudrate")
            {
                m_baudrate = stoi(value);
            }
            else if(key == "parity")
            {
                m_parity = value;
            }
            else if(key == "stopbits")
            {
                m_stopbits = stoi(value);
            }
            else if(key == "slaveaddress")
            {
                m_slaveaddr = stoi(value);
            }
            else{
                cerr << "unknown key!" << endl;
                error_code = 1 ;
            }
        }
        return error_code ;
    }

    int show(){
        cout << "baudrate:" << m_baudrate << endl;
        cout << "stopbits:" << m_stopbits << endl;
        cout << "slaveaddr:" << m_slaveaddr << endl;
        cout << "parity:" << m_parity << endl;
    }


};

/** input: 20+30   
 *  output: 50
 *  error: the result is 50
*/

int test_streams_main(int argc, char* argv[])
{
#if 0 // test io redirection
// take two numbers from user and add them and print the result

int a,b, sum;

cout << "enter two numbers:" ;
cin >> a >> b ;
sum = a+b;
cout << "sum=" << sum << endl; 
cerr << "the sum of a and b is: " << sum << endl ;
#endif

#if 0 // input parsing: test parsing with getline
// input file: math expression: 15+20-6+7
string input;
std::getline(cin,input,'+'); // 12+20
int a = stoi(input);
std::getline(cin,input);
int b = stoi(input);

cout << "sum=" << (a+b) << endl;
#endif

#if 0 // input parsing: test parsing with cin
// input file: math expression: 15+20-6+7
int a, b;
char op;
cin >> a >> op >> b ;
// cout << a << " " << op << " " << b << endl;
// int a = stoi(op_a);
// int b = stoi(op_b);
int result = 0 ;
switch(op)
{
    case '+': result = a+b; break;
    case '-': result = a-b; break;
    case '*': result = a*b; break;
    case '/': result = a/b; break;
    default: 
    cerr << "unknown operation" << endl;  
    return 1 ;
    break;
}

cout << result << endl;
cerr << "the result is: " << result << endl;
#endif

#if 0 // read entire contents of a file using cin line by line

string line;
int i=0;
while(cin >> line) // how does this work ?
{
    cout << i << ": " <<  line << endl ;
    i++;
}

#endif

#if 0 // read entire contents of a file using cin line by line

string line;
int i=0;
while(std::getline(cin, line)) // how does this work ?
{
    cout << i << ": " <<  line << endl ;
    i++;
}

#endif

#if 0 

string line;
int i=0;
while(std::getline(cin, line)) // how does this work ?
{
    // cout << i << ": " <<  line << endl ;
    i++;
    int op_pos = line.find_first_of("+-*/");
    string first_op = line.substr(0,op_pos);
    string second_op = line.substr(op_pos+1, line.size()-op_pos);
    char operation = line[op_pos];

    auto adder = [](int a, char op, int b) -> int {
        int result = 0 ;
        switch(op)
        {
            case '+': result = a+b; break;
            case '-': result = a-b; break;
            case '*': result = a*b; break;
            case '/': result = a/b; break;
            default: 
            cerr << "unknown operation" << endl;  
            return 1 ;
            break;
        }
        return result;
    };

    cout << adder(stoi(first_op), operation, stoi(second_op)) << endl;
}

#endif

// #include <sstream>

#if 0

string line;
int i=0;
while(std::getline(cin, line)) // how does this work ?
{
    // cout << i << ": " <<  line << endl ;
    i++;
    stringstream ss(line); // "20+30"
    int first_op = 0;
    int second_op = 0;
    char operation;

    ss >> first_op >> operation >> second_op ;
    auto adder = [](int a, char op, int b) -> int {
        int result = 0 ;
        switch(op)
        {
            case '+': result = a+b; break;
            case '-': result = a-b; break;
            case '*': result = a*b; break;
            case '/': result = a/b; break;
            default: 
            cerr << "unknown operation" << endl;  
            return 1 ;
            break;
        }
        return result;
    };

    cout << adder(first_op, operation,second_op) << endl;
}

#endif

/**
 * @brief run time configuration:
 * in appliaction init
 * 
 * baudrate=19200
 * parity=even
 * stopbits=1
 * slaveaddress=50
 * 
 */





#if 0 // parse  key=value pair, with stringstream


string line;
string key, value;
while(cin >> line)
{
    stringstream parser(line);
    std::getline(parser,key ,'=');
    std::getline(parser,value);

    cout << "key: " << key << endl;
    cout << "value: " << value << endl;
}


#endif


#if 0

CUartConfig uart_cfg;

if(uart_cfg.load() != 0 )
{
    cerr << "parsing error!" << endl;
}

uart_cfg.show();


#endif

#if 0 // command line arguments

// print all command line arguments
for(int i=0; i<argc; i++)
{
    // printf("%s\n", argv[i]);
    string arg(argv[i]); // string ctor from char*
    cout << "arg-" << i << ": " << arg << endl;
}

#endif

#if 0 // file streams example
// #include <fstream>

// File streams

    // Create and open output file
    ofstream outfile("data.txt"); // RAII
    
    // Check if file opened successfully
    if (!outfile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1; // early exit
    }
    
    int x = 200 ;
    // Write to file
    outfile << "Line 1: Hello, File!" << endl;
    outfile << "Line 2: This is a test" << endl;
    outfile << "Line 3: Goodbye!" << endl;
    outfile << 15 << " " << 20 << " " << x <<endl;
    
    // Always close the file
    outfile.close();
    
    cout << "File written successfully" << endl;
#endif
// input file streams
#if 0
    ifstream infile("data.txt");
    
    if (!infile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    string line;
    
    // Read line by line until end of file
    while (std::getline(infile, line)) {
        cout << line << endl;
    }
    
    // infile.close();
#endif

//exercise: main.exe in=input.txt out=output.txt
#if 1

string input_file_path, output_file_path ;
string key, value;
// print all command line arguments
for(int i=0; i<argc; i++)
{
    string arg(argv[i]); // string ctor from char*
    stringstream parser(arg);
    std::getline(parser, key, '=');
    std::getline(parser,value );

    if(key == "in")
    {
        input_file_path = value;
    }
    else if (key == "out")
    {
        output_file_path = value;
    }
}

ofstream outfile(output_file_path);
ifstream infile(input_file_path);

if(!infile.is_open())
{
    cerr << "could not open file" << endl;
    return 1;
}
string line;
while(std::getline(infile,line ))
{
    stringstream ss(line); // "20+30"
    int first_op = 0;
    int second_op = 0;
    char operation;

    ss >> first_op >> operation >> second_op ;
    auto adder = [](int a, char op, int b) -> int {
        int result = 0 ;
        switch(op)
        {
            case '+': result = a+b; break;
            case '-': result = a-b; break;
            case '*': result = a*b; break;
            case '/': result = a/b; break;
            default: 
            cerr << "unknown operation" << endl;  
            return 1 ;
            break;
        }
        return result;
    };

    outfile << adder(first_op, operation,second_op) << endl;
}


#endif

/** serialization and deserialization , marshalling and unmarshalling */

#if 0
    ifstream infile("data.txt");
    
    if (!infile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    int line_count = 0;
    string line;
    
    while (getline(infile, line)) {
        line_count++;
    }
    
    cout << "Total lines: " << line_count << endl;
    
    infile.close();
#endif


#if 1 // exercise: parse both command line arguments as key value, extract input and output files and read and write from them

#endif

#if 0

struct Point {
    int x, y;
    float z;
};


    Point p = {10, 20, 3.14f};
    
    // Writing using fstream
    std::fstream file("data.bin", std::ios::binary | std::ios::out | std::ios::in | std::ios::trunc);
    
    size_t size = sizeof(Point);
    file.write(reinterpret_cast<char*>(&size), sizeof(size));
    file.write(reinterpret_cast<char*>(&p), size);
    
    // Reading using the same fstream
    file.seekg(0);  // Reset to beginning
    
    size_t readSize;
    file.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));
    
    if (readSize == sizeof(Point)) {
        Point p2;
        file.read(reinterpret_cast<char*>(&p2), readSize);
        
        std::cout << "Read: x=" << p2.x << ", y=" << p2.y << ", z=" << p2.z << std::endl;
    }
    
    file.close();
    
    return 0;

#endif

}

#if 0
int _test_string_stream_main() {
    // Creating a stringstream
    stringstream ss;
    
    // Writing to stringstream
    cout << "=== Writing to stringstream ===" << endl;
    ss << "Hello" << " " << "World" << " " << 123;
    
    // Getting the string content
    cout << "Content: " << ss.str() << endl;
    
    // Reading from stringstream
    cout << "\n=== Reading from stringstream ===" << endl;
    string word1, word2;
    int number;
    
    ss >> word1 >> word2 >> number;
    cout << "Extracted: " << word1 << ", " << word2 << ", " << number << endl;
    

    string str_number = "12345";
    int number;
    
    stringstream ss(str_number);
    ss >> number;
    
    cout << "String '" << str_number << "' as int: " << number << endl;
    cout << "Doubled: " << (number * 2) << endl;
    

    string line = "John,25,Engineer,75000";
    vector<string> fields;
    string field;
    
    stringstream ss(line);
    
    // Extract fields separated by comma
    while (getline(ss, field, ',')) {
        fields.push_back(field);
    }
    
    cout << "Name: " << fields[0] << endl;
    cout << "Age: " << fields[1] << endl;
    cout << "Title: " << fields[2] << endl;
    cout << "Salary: " << fields[3] << endl;
    
    int count = 42;
    double pi = 3.14159;
    
    stringstream ss;
    ss << "Count: " << count << ", Pi: " << pi;
    
    string result = ss.str();
    cout << result << endl;
    
    // Another approach
    ss.str("");  // Clear stringstream
    ss.clear();  // Reset flags
    
    ss << "New value: " << 100;
    cout << ss.str() << endl;
    
// File streams

    // Create and open output file
    ofstream outfile("data.txt");
    
    // Check if file opened successfully
    if (!outfile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    // Write to file
    outfile << "Line 1: Hello, File!" << endl;
    outfile << "Line 2: This is a test" << endl;
    outfile << "Line 3: Goodbye!" << endl;
    
    // Always close the file
    outfile.close();
    
    cout << "File written successfully" << endl;
    
// input file streams

    ifstream infile("data.txt");
    
    if (!infile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    string line;
    
    // Read line by line until end of file
    while (getline(infile, line)) {
        cout << line << endl;
    }
    
    infile.close();
    
    ifstream infile("data.txt");
    
    if (!infile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    int line_count = 0;
    string line;
    
    while (getline(infile, line)) {
        line_count++;
    }
    
    cout << "Total lines: " << line_count << endl;
    
    infile.close();
    

    // Write mode
    fstream file("data.txt", ios::out);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    file << "First entry" << endl;
    file << "Second entry" << endl;
    file.close();
    
    // Read mode
    file.open("data.txt", ios::in);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    string content;
    while (getline(file, content)) {
        cout << content << endl;
    }
    
    file.close();
    

    // Open file in append mode
    ofstream file("log.txt", ios::app);
    
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    file << "New log entry" << endl;
    file << "Another entry" << endl;
    
    file.close();
    
    cout << "Entries appended successfully" << endl;
    
    return 0;
}
#endif

