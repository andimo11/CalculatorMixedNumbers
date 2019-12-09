#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H
#include <stdexcept>
#include <string>

class parseexception: public std::logic_error
{
public:
    using std::logic_error::logic_error;
};

#endif // PARSEEXCEPTION_H
