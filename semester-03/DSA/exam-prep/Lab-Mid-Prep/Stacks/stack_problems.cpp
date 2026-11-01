#include <iostream>
#include <string>
#include <stack>
using namespace std;
/*
- [PROBLEM]    |    2 Stacks in an Array:
    1. Divide the array in 2 sections. First section is from 0 to n/2, second one is from n/2+1 to n-1
        Mid = n/2, Initial states/Underflow states are for 1 = -1, for 2 = mid - 1

    2. Starting from different endpoints.
        1 stack from index 0, other from index n-1
        Overflow condition for both becomes: top_1 < top_2 - 1
        Underflow for both becomes:
        Stack:01 ->  top_1 == -1
        Stack:02 ->  top_2 == size
*/

/*
- [PROBLEM] | Valid Parenthesis:

*/
bool valid_parenthesis(std::string str)
{
    // Check
    if (str.empty())
        return true;
    stack<char> stack;
    for (char c : str)
    {
        if (c == '(' or c == '{' or c == '[')
            stack.push(c);
        else
        {
            if (stack.empty())
                return false;

            char top = stack.top();
            stack.pop();
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '['))
            {
                return false;
            }
        }
    }
    return stack.empty();
}

/*
- [PROBLEM] | Infix is given, convert into post-fix

*/
string to_post_fix(string in_fix)
{
    string post_fix;
    stack<char> st;

    for (char c : in_fix)
    {
        // 1. Operand → go directly to output
        if (isalpha(c) || isdigit(c))
        {
            post_fix += c;
        }
        // 2. Opening parenthesis → push
        else if (c == '(')
        {
            st.push(c);
        }
        // 3. Closing parenthesis → pop until '('
        else if (c == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                post_fix += st.top();
                st.pop();
            }
            if (!st.empty())
                st.pop(); // remove the '('
        }
        // 4. Operator
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            while (!st.empty() && st.top() != '(' &&
                   precedence(st.top()) >= precedence(c))
            {
                post_fix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // 5. Pop remaining operators
    while (!st.empty())
    {
        post_fix += st.top();
        st.pop();
    }

    return post_fix;
}

// Helper function
int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

string to_prefix(std::string infix)
{
    // 1. Reverse the infix
    reverse(infix.begin(), infix.end());

    // 2. Swap ( and )
    for (char &c : infix)
    {
        if (c == '(')
            c = ')';
        else if (c == ')')
            c = '(';
    }

    // 3. Convert to postfix
    string postfix = to_post_fix(infix);

    // 4. Reverse the postfix to get prefix
    reverse(postfix.begin(), postfix.end());

    return postfix;
}