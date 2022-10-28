/********************************
*                               *
*        Danil Lugovskih        *
*            PI-221             *
*   Calculator of big numbers   *
*                               *
********************************/

#include <iostream>
using namespace std;

int main() {
  int accumulatingVariable = 0;
  int currentNumber;
  char operation = '+';

  while (operation != '=') {
    cout << "enter value: ";
    cin >> currentNumber;

    switch (operation) {
      case '+':
        accumulatingVariable += currentNumber;
        break;

      case '-':
        accumulatingVariable -= currentNumber;
        break;

      case '*':
        accumulatingVariable *= currentNumber;
        break;
      
      case '/':
        accumulatingVariable /= currentNumber;
        break;
          
      default:
        cout << "error with operator" << endl;
    }
    cout << "--> " << accumulatingVariable << endl;
    cout << "Enter operator (+ - * / (= to quit)): ";
    cin >> operation;
  }
  cout << accumulatingVariable;
  return 0;
}
