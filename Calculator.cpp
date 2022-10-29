/********************************
*                               *
*        Danil Lugovskih        *
*            PI-221             *
*   Calculator of big numbers   *
*                               *
********************************/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class BigInt {
  private:
    enum Sign {positive, negative};
    Sign mySign;
    vector<char> myDigits;
    int myDigitsNumber; // = myNumDigits

  public:

  private:
    void AddDigit (int value) {
      if (myDigitsNumber >= myDigits.size()) {
        myDigits.resize(myDigits.size() * 2);
      }
      myDigits[myDigitsNumber] = char('0' + value);
      ++myDigitsNumber;
    }
    
  
  public:
    BigInt() {
      mySign(positive);
      myDigits(1, '0');
      myDigitsNumber(0);
    }

    BigInt(int number) {
      mySign(positive);
      myDigits(inputString.length(), '0');
      myDigitsNumber(0);
      
      if (number < 0) {
        mySign = negative;
        number *= -1;
      }

      do {
        AddDigit(number % 10);
        number /= 10;
      } while (number != 0);

    }

    BigInt(const string& inputString) {
      mySign(positive);
      myDigits(inputString.length(), '0');
      myDigitsNumber(0);
      int numberIndex;
      int limit = 0;

      if (inputString.size()) == 0) {
        myDigits.resize(1);
        AddDigit(0);
        return;
      }

      if (s[0] == '-') {
        mySign = negative;
        limit = 1;
      }

      if (s[0] == '+') {
        limit = 1;
      }

      for (numberIndex = inputString.size(); numberIndex >= limit; --k) {
        AddDigit(s[k] - '0');
      }
    }
    
    istream& operator>> (istream& in, BigInt& number) {
      string line;
      in >> line;
      number = BigInt(line);
      return line;
    }

    /*void Print(ostream& out) {
      int len = numDigits
    }*/

};

int main() {
  int num = 5;
  BigInt();

  /*
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
  */
  return 0;
}
