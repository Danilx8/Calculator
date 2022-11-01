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

class bigInt {
  private:
    enum sign {positive, negative};
    sign mySign;
    vector<char> myDigits;
    int myDigitsNumber; 

  private:
    void addDigit (int value) {
      if (myDigitsNumber >= myDigits.size()) {
        myDigits.resize(myDigits.size() * 2);
      }
      myDigits[myDigitsNumber] = char('0' + value);
      ++myDigitsNumber;
    }
    
    string toString() {
      int numberIndex;
      int length = myDigitsNumber;
      string readyString;
      
      if (isNegative()) {
        readyString = '-';
      }
      
      for (numberIndex = length - 1; numberIndex >= 0; --numberIndex) {
        readyString += char('0' + getDigit(numberIndex));
      }
      
      return readyString;
    }
    
    int getDigit(int numberIndex) {
      if (numberIndex >= 0 && numberIndex < myDigitsNumber){
        return myDigits[numberIndex] - '0';
      }
      return 0;
    }
    
    bool isNegative() {
      return mySign == negative;
    }  
    
    bool isPositive() {
      return mySign == positive;
    }
    
    void normalize() {
      int counter;
      int length = myDigitsNumber;
      
      for (numberIndex = length - 1; numberIndex >= 0; --numberIndex) {
        if (getDigit(numberIndex) != 0) {
          break;
        }
        --myDigitsNumber;
      }
      
      if (numberIndex < 0) {
        myDigitsNumber = 1;
        mySign = positive;
      }
    }
    
    int digitsNumber() {
      return myDigitsNumber;
    }
    
  public:
    bigInt(): 
    mySign(positive),
    myDigits(1, '0'),
    myDigitsNumber(1)
    {}

    bigInt(int number): 
    mySign(positive),
    myDigits(1, '0'),
    myDigitsNumber(0)
    {
      if (number < 0) {
        mySign = negative;
        number *= -1;
      }

      do {
        addDigit(number % 10);
        number /= 10;
      } while (number != 0);

    }

    bigInt(const string& inputString): 
    mySign(positive),
    myDigits(inputString.length(), '0'),
    myDigitsNumber(0)
    {
      int numberIndex;
      int limit = 0;

      if (inputString.size() == 0) {
        myDigits.resize(1);
        addDigit(0);
        return;
      }

      if (inputString[0] == '-') {
        mySign = negative;
        limit = 1;
      }

      if (inputString[0] == '+') {
        limit = 1;
      }

      for (numberIndex = inputString.size() - 1; numberIndex >= limit; --numberIndex) {
        addDigit(inputString[numberIndex] - '0');
      }
      
      normalize();
    }
    
    void print(ostream& output) {
      output << toString();
    }
    
    bool isEqual(bigInt& number) {
      if (myDigitsNumber != number.digitsNumber() || isNegative() != number.isNegative()) {
        return false;
      }
      
      int counter;
      int length = myDigitsNumber;
      
      for (counter = 0; counter < length; ++counter) {
        if (getDigit(counter) != number.getDigit(counter)) {
          return false;
        }
      }
      
      return true;
    }
    
    bool lessThan(bigInt& number) {
      if (isNegative() != number.isNegative()){
         return isNegative();    
      }
      
      if (digitsNumber() != number.digitsNumber()) {
        return (digitsNumber() < number.digitsNumber() && isPositive()) ||
               (digitsNumber() > number.digitsNumber() && isNegative());
      }
      
      for (int numberIndex = digitsNumber(); numberIndex >= 0; --numberIndex) {
        if (getDigit(numberIndex) < number.getDigit(numberIndex)) {
          return !isNegative();
        }
      }
      
      return false;
    }
};

ostream& operator << (ostream& stream, bigInt& number) {
  number.print(stream);
  return stream;
}

istream& operator >> (istream& in, bigInt& number) {
  string line;
  in >> line;
  number = bigInt(line);
  return in;
}

bool operator == (bigInt& leftNumber, bigInt& rightNumber) {
  return leftNumber.isEqual(rightNumber);
}

bool operator < (bigInt& leftNumber, bigInt& rightNumber) {
  return leftNumber.lessThan(rightNumber);
}

bool operator > (bigInt& leftNumber, bigInt& rightNumber) {
  return (leftNumber.lessThan(rightNumber ) && !leftNumber.isEqual(rightNumber));
}

int main() {
  bigInt num1 = bigInt(2);
  bigInt num2 = bigInt(5);
  
  bool less = (num1 > num2);
  cout << less;
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
