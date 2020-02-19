#ifndef SUPPORT_H
#define SUPPORT_H

#include <string>
#include <map>
#include <algorithm>
#include <stack>
#include <sstream>

#include "operands.h"
#include "shunting_yard.h"

std::string
get_rhv(const std::string& str,
        const std::string& delimiter_set,
        std::size_t index)
{ return str.substr(index, str.find_first_of(delimiter_set, index) - index); }

std::string
get_lhv(const std::string& str,
        const std::string& delimiter_set,
        std::size_t index)
{
    if (index == 0)
        return str.substr(0, index + 1);

    std::size_t i_copy = index;
    while (index > 0 && delimiter_set.find(str[--index]) == std::string::npos) {}
    return str.substr(index + 1, i_copy - index);
}

void
replace_all(std::string& str,
            const std::string& src,
            const std::string& dst)
{
    std::size_t index = 0;
    while (true)
        if (index = str.find(src, index); index != std::string::npos)
            str.replace(index, src.size(), dst);
        else
            return;
}

std::string
get_result(std::string lhv,
           std::string rhv,
           std::string operand)
{
    if (lhv == "!true") lhv = "false";
    if (lhv == "!false") lhv = "true";
    if (rhv == "!true") rhv = "false";
    if (rhv == "!false") rhv = "true";

    if (operand == "==")
        return (lhv == rhv) ? "true" : "false";

    if (operand == "!=")
        return (lhv != rhv) ? "true" : "false";

    if (operand == ">")
        return (Greater_than()(lhv, rhv)) ? "true" : "false";

    if (operand == ">=")
        return (Greater_equal_than()(lhv, rhv)) ? "true" : "false";

    if (operand == "<")
        return (Greater_equal_than()(lhv, rhv)) ? "false" : "true";

    if (operand == "<=")
        return (Greater_than()(lhv, rhv)) ? "false" : "true";

    return "false";
}

void
calculate(std::string& expr)
{
    std::string operands { "<>=" };

    std::size_t i = 0;
    while (true) {
        if (i >= expr.size())
            break;

        if (operands.find(expr[i]) != std::string::npos) {

            std::string op { expr[i] };
            std::string lhv, rhv;

            if (expr[i + 1] == '=') {
                op += "=";
                lhv = get_lhv(expr, ")(&|", i - 1);
                rhv = get_rhv(expr, ")(&|", i + 2);
            } else if (expr[i - 1] == '!') {
                op = "!" + op;
                lhv = get_lhv(expr, ")(&|", i - 1);
                rhv = get_rhv(expr, ")(&|", i + 2);
            } else {
                lhv = get_lhv(expr, ")(&|", i - 1);
                rhv = get_rhv(expr, ")(&|", i + 1);
            }
            expr.replace(i - lhv.size(), lhv.size() + rhv.size() + op.size(), get_result(lhv, rhv, op));

        }
        ++i;
    }
}

void
substitute_variable(std::string& expr,
                    const std::map<std::string, std::string>& values)
{
    expr.erase(std::remove_if(expr.begin(), expr.end(), isspace), expr.end());

    for (const auto& pair : values)
        replace_all(expr, pair.first, pair.second);

}

char
execute(std::string str,
        const std::map<std::string,
        std::string>& values)
{
    substitute_variable(str, values);
    calculate(str);
    std::map<std::string, std::string> m;
    m["true"] = "1";
    m["false"] = "0";
    m["&&"] = "&";
    m["||"] = "|";
    substitute_variable(str, m);

    return evaluate(postfix_notation(str));
}

#endif // SUPPORT_H
