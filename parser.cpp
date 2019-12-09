#include "parser.h"

std::vector<std::string> parser::strToVector(std::string input)
{
    //remove any spaces except for fractions
    char before, next;
    for(std::string::iterator i = input.begin(); i != input.end(); i++)
    {
        std::string::iterator j = i + 1;
        std::string::iterator k = i - 1;

        if(*i == ' ' && ((i==input.begin())
                         || *j == '+' || *j == '-' || *j == '*' || *j == '/' ||
                         *j == ' '
                         || *k == '+' || *k == '-' || *k == '*' || *k == '/'
        ))
            input.erase(i);
        before = *i;
    }

    std::vector<std::string> expVect;

    std::queue<char> line;
    std::string send;

    //put input into a queue
    for(int i = 0; i < input.size(); i ++)
        line.push(input[i]);

    char firstCheck = line.front();

    //in case first number is negative
    if(firstCheck == '-')
    {
        send += firstCheck;
        line.pop();
    }
    firstCheck = ' ';

    char check;
    //go through queue and add to expVect, string to vector
    do
    {
        check = line.front();
        if(isdigit(check) || check == '.' || check == ' ')
        {
            if(check == ' ')
            {
                send += check;
                line.pop();
                check = line.front();
                do
                {
                    if(check != ' ')
                        send += check;
                    line.pop();
                    check = line.front();
                }while(check != '/');
            }
            send += check;
            line.pop();
        }
        else
        {
            if(!send.empty())
            {
                expVect.push_back(send);
                send.clear();
            }
            send += check;
            expVect.push_back(send);
            send.clear();
            line.pop();
            char c;
            c = line.front();
            if(c == '-' || c == ' ')
                do
                {
                    if(c == '-')
                    {
                        send += c;
                        line.pop();
                    }
                    else
                    {
                        line.pop();
                        c = line.front();
                    }
                }while(c == ' ');
        }
    }while(!line.empty());

    if(!send.empty())
        expVect.push_back(send);

    return expVect;
}

std::vector<std::string> parser::toRPN(std::vector<std::string> exp)
{
    std::vector<std::string> RPNVect;

    std::stack<std::string> LIFO;
    std::queue<std::string> FIFO;

    char last;

    for(int i = 0; i < exp.size(); i++)
    {
        std::string check = exp[i];
        char next = check[0];

        if(isdigit(next) || (next == '-' && check.size() > 1))
        {
            FIFO.push(check);
        }
        else if(LIFO.empty() && !isdigit(next))
        {
            LIFO.push(check);
        }
        else if(check =="+" || check =="-" || check =="*" || check =="/")
        {
            int inStack, nextValue;
            inStack = getPrecedence(LIFO.top());
            nextValue = getPrecedence(check);
            if(inStack < nextValue)
                LIFO.push(check);
            else
            {
                do
                {
                    FIFO.push(LIFO.top());
                    LIFO.pop();
                    if(!LIFO.empty())
                        inStack = getPrecedence(LIFO.top());
                }while(inStack >= nextValue && !LIFO.empty());
                LIFO.push(check);
            }
        }
        else if(check == "(" || check == ")")
        {
            switch(next)
            {
                case '(':
                    if(isdigit(last))
                        LIFO.push("*");
                    LIFO.push(check);
                    break;
                case ')':
                    do
                    {
                        FIFO.push(LIFO.top());
                        LIFO.pop();

                    }while(LIFO.top() != "(");
                    if(LIFO.top() == "(")
                    {
                        LIFO.pop();
                    }
                    break;
            }
        }
        else
        {
            throw TRANSLATE_ERROR;
        }
        last = next;
    }
    if(!LIFO.empty())
    {
        do
        {
            FIFO.push(LIFO.top());
            LIFO.pop();
        }while(!LIFO.empty());
    }
    do{
        RPNVect.push_back(FIFO.front());
        FIFO.pop();

    }while(!FIFO.empty());

    return RPNVect;
}

int parser::getPrecedence(std::string str)
{
    char s = str[0];
    switch(s)
    {
        case '+':
            return 0;
            break;
        case '-':
            return 0;
            break;
        case '*':
            return 1;
            break;
        case '/':
            return 1;
            break;
        default:
            return -1;
    }
}

std::vector<std::string> parser::parseToRPN(const std::string  &input)
{
    std::vector<std::string> send;
    ensureInputValid(input);
    send = toRPN(strToVector(input));
    return send;
}

void parser::ensureInputValid(const std::string &input) {
    int leftParenCount = 0;
    int rightParenCount = 0;
    std::stringstream ss;
    ss << input;


    // Flags
    bool mixedNumberFound = false;
    bool operatorFound = false;
    bool leftParenFound = false;
    bool rightParenFound = false;
    bool emptyExpression = true;


    mixedNumber trash;
    char nextChar;
    ss.peek();

    while(ss.good()) {
        nextChar = static_cast<char>(ss.get());
        if(nextChar == ' ') {
        } else if(streamUtilities::isNumber09(nextChar) ||
                  (nextChar == '-' && streamUtilities::isNumber09(static_cast<char>(ss.peek())))) {
            ss.unget();
            try {
                ss >> trash;
            } catch (fraction::ERRORS e) {
                if(e == fraction::DIVIDE_BY_ZERO) {
                    throw parseexception("Divisor of zero");
                }
            };

            if(rightParenFound && nextChar != '-') {
                throw parseexception("Number after right parenthesis"); // ie. (3 + 5) 44
            }
            if(mixedNumberFound && nextChar != '-') {
                throw parseexception("Consecutive numbers"); // ie. 1 2 3 or 1 + 2 3
            }

            mixedNumberFound = true;
            operatorFound = false;
            leftParenFound = false;
            emptyExpression = false;

        } else if(streamUtilities::isOperator(nextChar)) {
            if(operatorFound || leftParenFound) {
                if(!(nextChar == '-' && streamUtilities::isNumber09(static_cast<char>(ss.peek())))) {
                    if(leftParenFound) {
                        throw parseexception("Operator after left parenthesis"); // ie. ( + 3) or (- 2 + 2)
                    } else if(operatorFound) {
                        throw parseexception("Operator after operator"); // ie. 5 + * or 3 / /
                    }
                }
            }
            mixedNumberFound = false;
            operatorFound = true;
            leftParenFound = false;
            rightParenFound = false;

        } else if(nextChar == '(') {
            leftParenCount++;
            mixedNumberFound = false;
            operatorFound = false;
            leftParenFound = true;
            rightParenFound = false;
            emptyExpression = false;

        } else if(nextChar == ')') {
            rightParenCount++;
            if(rightParenCount > leftParenCount) {
                throw parseexception("Unmatched right parenthesis"); // ie. 5 + 3 ) + 2
            }
            if(operatorFound) {
                throw parseexception("Right parenthesis after operator"); // ie. ( 5 + ) * 3
            }

            mixedNumberFound = false;
            leftParenFound = false;
            rightParenFound = true;
        } else {
            std::string error = "Invalid character: '";
            error += nextChar;
            error += '\'';
            throw parseexception(error);
        }
        ss.peek();
    }

    if(emptyExpression) {
        throw parseexception("Empty expression");
    }

    if(operatorFound) {
        throw parseexception("Dangling operator"); // ie. 5 +
    }

    if(leftParenCount != rightParenCount) {
        throw parseexception("Unmatched left parenthesis"); // ie. (( 5 + 3 ) + 2
    }

}
