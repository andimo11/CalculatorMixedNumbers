#include "calculate.h"

std::string calculate::getAnswer(std::vector<std::string> input)
{
    std::string send;
    send = doCalculations(input);
    return send;
}

std::string calculate::doCalculations(std::vector<std::string> input)
{
    std::stack<mixedNumber> mixed;
    std::stack<char> ops;

    for(int i = 0; i < input.size(); i ++)
    {
        std::string check = input[i];
        char next = check[0];

        if(isdigit(next) || (next == '-' && check.size() > 1))
        {
            std::stringstream ss;
            ss<<check;
            mixedNumber A;
            ss>>A;
            mixed.push(A);
        }
        else if(next == '+' || next == '-' || next == '*' || next == '/')
        {
            mixedNumber B = mixed.top();
            mixed.pop();
            mixedNumber A = mixed.top();
            mixed.pop();

            switch(next)
            {
                case '+':
                    A = A + B;
                    break;
                case '-':
                    A = A - B;
                    break;
                case '*':
                    A = A * B;
                    break;
                case '/':
                    A = A / B;
                    break;
            }
            mixed.push(A);
        }
    }


    mixedNumber give = mixed.top();
    std::string send;

    std::stringstream ss;
    ss<<give;
    getline(ss, send);

    return send;

}



