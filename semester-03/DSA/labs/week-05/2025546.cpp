/*
    --- CS-214-LAB:4 ---
    NAME:   M HUSNAIN AFZAL
    REG:    2025-546
    SEC:    CS-H2
*/
#include <iostream>
#include <string>
#include <stack>
// --- Task:01 ---
bool isBalanced(const std::string &parenthesis)
{
    /*
    Concept:
    we see a opening bracket '(' we push it onto the stack.
    we see a ending bracket ')' we check that the stack is not empty, then pop the top element.
    we continue this till the string ends.
    if the stack is empty when we see a ')' we return false as there is a ending bracket with no starting counterpart.
    if the string ends and the stack is not empty we return false as there were too many starting brackets and not equal ending ones.
    */
    // Check:01
    if (parenthesis.empty())
        return true;
    // Simple-Algorithm
    bool valid = true;
    std::stack<char> bracket_stack;
    for (char c : parenthesis)
    {
        if (c == '(') // Push
            bracket_stack.push(c);
        else if (c == ')') // Pop
        {
            // Check-01
            if (bracket_stack.empty())
            {
                valid = false; // more closing brackets than starting ones.
                break;
            }
            // Get the char at the top of the stack
            char top_element = bracket_stack.top();
            // The top must be the matching opening bracket, then we pop it out.
            if (top_element != '(')
            {
                valid = false;
                break;
            }
            bracket_stack.pop();
        }
        else // no other char should be in the string.
        {
            valid = false;
            break;
        }
    }
    // Check-02
    if (!bracket_stack.empty())
    {
        valid = false; // more starting brackets than closing ones.
    }
    return valid; // Perfectly valid parenthesis combination.
}
// --- Task:02 ---
std::string reverseString(const std::string &input)
{
    // Initial check.
    if (input.empty())
        return "";
    // We first store the entire string in a std::stack.
    std::stack<char> str_stack;
    // Loop over each char and push into the stack.
    for (char c : input)
    {
        str_stack.push(c);
    }
    // Keep popping out the elements till the stack is empty.
    // The last char pushed comes out first (LIFO), which gives us the reversed string.
    std::string reversed;
    while (!str_stack.empty())
    {
        reversed += str_stack.top();
        str_stack.pop();
    }
    return reversed;
}
// --- Demo-Main ---
int main()
{
    // NOTE: Demo main is AI generated.
    // std::boolalpha formats boolean outputs as "true" or "false" instead of "1" or "0"
    std::cout << std::boolalpha;

    std::cout << "--- LAB Activity#01 Tests ---\n";
    std::string bal1 = "((()))";
    std::string bal2 = "((())";

    // Testing the balanced string example from the lab
    std::cout << "Input: " << bal1 << "\nOutput: " << isBalanced(bal1) << "\n\n";

    // Testing the unbalanced string example from the lab
    std::cout << "Input: " << bal2 << "\nOutput: " << isBalanced(bal2) << "\n\n";

    std::cout << "--- LAB Activity#02 Tests ---\n";
    std::string rev1 = "Hello";

    // Testing the string reversal example from the lab
    std::cout << "Input: " << rev1 << "\nOutput: " << reverseString(rev1) << "\n";

    return 0;
}