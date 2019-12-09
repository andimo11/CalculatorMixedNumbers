#ifndef STREAMUTILITIES_H
#define STREAMUTILITIES_H
#include <iostream>

class streamUtilities
{
public:
    static bool hasNextInt(std::istream &in);
    static void consumeWhitespace(std::istream &in);
    static bool hasNextFraction(std::istream &in);
    static bool isNumber19(char n);
    static bool isNumber09(char n);
    static bool isOperator(char n);

private:
    streamUtilities() {}
};

#endif // STREAMUTILITIES_H