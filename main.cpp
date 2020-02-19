#include <iostream>
#include <string>
#include <map>

#include "support.h"

bool evaluate(std::string& str,  std::map<std::string, std::string>& map)
{ return (execute(str, map) == '1') ? true : false; }

int main() {
    std::map<std::string, std::string> m;

    std::string e1 = "v0 == 1";
    std::string e2 = "(v0 == 2 || v1 > 10)";
    std::string e3 = "(v0 == 2 || (v1 > 10  && v2 > 3)) && v3 == 0";
    std::string e4 = "(v0 == 2 || (v1 > 10  && v2 > 3)) && v3 == -15.000000001 && !v4";
    std::string e5 = "(v0 == 2 || (v1 > 10  && v2 > 3)) && v3 == -15.000000001 && v4";
    std::string e6 = "((v0 == 2 || (v1 > 10  && v2 > 3)) && v3 == -15.000000001 && v4) && (v5 == !v4)";
    std::string e7 = "true";

    m["v0"] = "1";
    m["v1"] = "15.55";
    m["v2"] = "-10";
    m["v3"] = "-15.000000001";
    m["v4"] = "true";
    m["v5"] = "false";

    bool testCorrect =
            (evaluate(e1, m) &&
             evaluate(e2, m) &&
             !evaluate(e3, m) &&
             !evaluate(e4, m) &&
             !evaluate(e5, m) &&
             !evaluate(e6, m) &&
             evaluate(e7, m));

    std::cout << (testCorrect ? "Good job!" : "Uhm, please retry!") << std::endl;

    return 0;
}


