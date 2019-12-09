#ifndef PARSER_H
#define PARSER_H
#include <cstdlib>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <vector>
#include "streamutilities.h"
#include "parseexception.h"
#include "mixednumber.h"

class parser
{
public:
    enum ERRORS {TRANSLATE_ERROR};

    // Takes in algebraic expression, returns RPN expression
    // Throws parseexpression when invalid
    static std::vector<std::string> parseToRPN(const std::string &input);

private:
    //takes in expression and returns RPN
    static std::vector<std::string> toRPN(std::vector<std::string>);
    //used by RPN during equality comparisons
    static int getPrecedence(std::string);
    //product is sent to toRPN
    static std::vector<std::string> strToVector(std::string);

    // Determines if algebraic expression is valid
    // Throws parseexception if input not valid
    static void ensureInputValid(const std::string &input);
    // Translates algebraic expression to RPN expression
    static std::string toRPN(const std::string &input);


    parser() {}
};

#endif // PARSER_H
