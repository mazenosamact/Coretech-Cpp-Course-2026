#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

int parse_rpn()
{
    stack<int> st;
    string expression;
    std::getline(cin, expression);
#if 0
    int first_token_pos = expression.find(' ');
    string first_token = expression.substr(0, first_token_pos);
    try 
    {
        int first = stoi(first_token);

    }catch(std::exception& e)
    {
        cout << "caught exception:" << e.what() << endl;
    }
#endif
    stringstream ss(expression);
    string token;
    while(ss >> token)
    {
        int number = 0;
        if(isdigit(token[0]))
        {
            number = stoi(token);
            st.push(number);
        }
        else
        {
            switch(token[0])
            {
                case '+': case '-': case '*': case '/':
                    int firstop = st.top();
                    st.pop();
                    int secondop = st.top();
                    st.pop();
                    int result = calc(firstop, secondop, token[0]);
                    st.push(result);
                break;
            }
        }
    }

}

int test_stack_main(int argc, char* argv[])
{
    #if 0
    stack<int> st;

    st.push(15);
    st.push(20);
    st.push(30);

    // for(int i=0; i<st.size(); i++)
    while(!st.empty())
    {
        auto t = st.top();
        st.pop();
        cout << t << ' ' << endl;
    }
    #endif
    parse_rpn();
}