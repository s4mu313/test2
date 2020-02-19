#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <stack>
#include <string>

bool
has_lower_precedence(char op1, char op2)
{ return (op1 == '|' && (op2 == '&' || op2 == '!'))
            || (op1 == '&' && op2 == '!'); }

std::string
fill_stack(std::stack<char>& stack, char op)
{
    if (stack.empty() ||
            stack.top() == '(' ||
            !has_lower_precedence(op, stack.top())) {
        stack.push(op);
        return "";
    }

    char c = stack.top();
    stack.pop();
    return c + fill_stack(stack, op);

}

std::string
extract_from_stack(std::stack<char>& stack)
{
    std::string s;
    while (!stack.empty() && stack.top() != '(') {
        s += stack.top();
        stack.pop();
    }
    stack.pop();
    return s;
}

std::string
postfix_notation(const std::string& expr)
{
    std::string result;
    std::stack<char> stack;
    for(const char& c : expr) {
        if (c == '0' || c == '1')
            result += c;
        if (c == '&' || c == '|' || c == '!')
            result += fill_stack(stack, c);
        if (c == '(')
            stack.push(c);
        if (c == ')')
            result += extract_from_stack(stack);
    }
    result += extract_from_stack(stack);
    return result;
}

char
evaluate(const std::string& p_fix_notation)
{
    std::stack<char> stack;
    for(std::size_t i = 0; i < p_fix_notation.size(); ++i) {
        if (p_fix_notation[i] == '!') {
            char c = stack.top();
            stack.pop();
            (c == '0') ? stack.push('1') : stack.push('0');
        } else if (p_fix_notation[i] == '|') {
            char c1 = stack.top();
            stack.pop();
            char c2 = stack.top();
            stack.pop();
            stack.push(c1 | c2);
        } else if (p_fix_notation[i] == '&'){
            char c1 = stack.top();
            stack.pop();
            char c2 = stack.top();
            stack.pop();
            stack.push(c1 & c2);
        } else if (p_fix_notation[i] == '0' || p_fix_notation[i] == '1')
            stack.push(p_fix_notation[i]);
    }
    return stack.top();
}


#endif // SHUNTING_YARD_H
