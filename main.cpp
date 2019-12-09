#include <iostream>
#include <vector>
//#include <random> // TODO Remove when done testing
#include "calculate.h"
#include "mixednumber.h"
#include "parseexception.h"
#include "parser.h"

using namespace std;

void printIntroMessage();
void doCalculations();

int main()
{
  printIntroMessage();
  doCalculations();
  return 0;
}


void printIntroMessage() {
  cout << "Mixed Number RPN Calculator" << endl
       << "Enter an algebraic expression consisting of" << endl
       << "  integers, fractions, decimal numbers, standard" << endl
       << "  mathematical operators (+, -, *, /) and parentheses." << endl;
  cout << "Your algebraic expression will be repeated in" << endl
       << "  Reverse Polish Notation, and the result will be" << endl
       << "  displayed." << endl;
  cout << endl;
}

void doCalculations() {
  string expression;
  vector<string> expressionBits;
  string result;

  while(true) {
    cout << "EXPRESSION: ";
    getline(cin, expression);

    try {
      expressionBits = parser::parseToRPN(expression);
      result = calculate::getAnswer(expressionBits);

      for(unsigned int i = 0; i < expressionBits.size(); i++) {
        cout << expressionBits.at(i) << " ";
      }
      cout << "= ";
      cout << result << endl;
    } catch (parseexception& e) {
      cout << "ERROR: " << e.what() << endl;
    } catch (fraction::ERRORS e) {
      if(e == fraction::DIVIDE_BY_ZERO) {
        cout << "ERROR: Cannot divide by zero" << endl;
      }
    } catch(...) {
      cout << "ERROR: Unknown error." << endl;
    }
    cout << endl;
  }
}
