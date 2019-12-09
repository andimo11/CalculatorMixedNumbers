#include "streamutilities.h"

bool streamUtilities::hasNextInt(std::istream &in) {
    consumeWhitespace(in);
    if(in.good()) {
        char nextChar = static_cast<char>(in.peek());
        if(nextChar >= '0' && nextChar <= '9') {
            return true;
        }
    }
    return false;
}

void streamUtilities::consumeWhitespace(std::istream &in) {
    while(in.good() && in.peek() == ' ') {
        in.ignore();
    }
}

bool streamUtilities::hasNextFraction(std::istream &in) {
    int charExtractedCount = 0;
    bool inputValid = true;
    bool forwardSlashFound = false;
    bool firstChar = true;
    char nextChar;

    in.peek();
    while(in.good() && inputValid && !forwardSlashFound) {
        nextChar = static_cast<char>(in.get());
        charExtractedCount++;
        if(!forwardSlashFound) {
            if(firstChar) {
                // First char; valid chars: 1-9, -
                firstChar = false;
                if(nextChar != '-' && !isNumber19(nextChar)) {
                    inputValid = false;
                }
            } else {
                // After first char; valid chars: 0-9, /
                if(!isNumber09(nextChar) && nextChar != '/') {
                    inputValid = false;
                } else if(nextChar == '/') {
                    forwardSlashFound = true;
                }
            }
        } else {
            // After /; valid chars: 1-9
            if(isNumber19(static_cast<char>(in.peek()))) {
                break;
            } else {
                inputValid = false;
            }
        }
        in.peek();
    }

    if(!in.good()) {
        inputValid = false;
    }
    in.clear();

    for(int i = 0; i < charExtractedCount; i++) {
        in.unget();
    }
    return inputValid;
}


bool streamUtilities::isNumber19(char n) {
    return n >= '1' && n <= '9';
}

bool streamUtilities::isNumber09(char n) {
    return n >= '0' && n <= '9';
}

bool streamUtilities::isOperator(char n) {
    return n == '+' || n == '-' || n == '*' || n == '/';
}
