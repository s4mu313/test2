#ifndef OPERANDS_H
#define OPERANDS_H

#include <iostream>

struct Greater_than
{
    bool operator() (std::string& a, std::string& b)
    { return std::stof(a) > std::stof(b); }
};

struct Greater_equal_than
{
    bool operator() (std::string& a, std::string& b)
    { return std::stof(a) == std::stof(b); }
};

struct Equal_to
{
    bool operator() (std::string& a, std::string& b)
    { return std::stof(a) >= std::stof(b); }

};

#endif // OPERANDS_H
