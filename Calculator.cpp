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
    int myDigitsNumber; 

  public:

  private:
    void AddDigit (int value) {
      if (myDigitsNumber >= myDigits.size()) {
        myDigits.resize(myDigits.size() * 2);
      }
      myDigits[myDigitsNumber] = char('0' + value);
      ++myDigitsNumber;
    }
    
    string ToString() {
      int numberIndex;
      int length = myDigitsNumber;
      string readyString;
      
      if (IsNegative()) {
        readyString = '-';
      }
      
      for (numberIndex = length - 1; numberIndex >= 0; --numberIndex) {
        readyString += char('0' + GetDigit(numberIndex));
      }
      
      return readyString;
    }
    
    int GetDigit(int numberIndex) {
      if (numberIndex >= 0 && numberIndex < myDigitsNumber){
        return myDigits[numberIndex] - '0';
      }
      return 0;
    }
    
    bool IsNegative() {
      return mySign == negative;
    }  
    
    bool IsPositive() {
      return mySign == positive;
    }
    
    void Normalize() {
      int counter;
      int length = myDigitsNumber;
      
      for (counter = length - 1; counter >= 0; --counter) {
        if (GetDigit(counter) != 0) {
          break;
        }
        --myDigitsNumber;
      }
      
      if (counter < 0) {
        myDigitsNumber = 1;
        mySign = positive;
      }
    }
    
  public:
    BigInt(): 
    mySign(positive),
    myDigits(1, '0'),
    myDigitsNumber(1)
    {}

    BigInt(int number): 
    mySign(positive),
    myDigits(1, '0'),
    myDigitsNumber(0)
    {
      if (number < 0) {
        mySign = negative;
        number *= -1;
      }

      do {
        AddDigit(number % 10);
        number /= 10;
      } while (number != 0);

    }

    BigInt(const string& inputString): 
    mySign(positive),
    myDigits(inputString.length(), '0'),
    myDigitsNumber(0)
    {
      int numberIndex;
      int limit = 0;

      if (inputString.size() == 0) {
        myDigits.resize(1);
        AddDigit(0);
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
        AddDigit(inputString[numberIndex] - '0');
      }
      
      Normalize();
    }
    
    void Print(ostream& output) {
      output << ToString();
    }
};

ostream& operator <<(ostream& stream, BigInt& number) {
  number.Print(stream);
  return stream;
}

istream& operator>> (istream& in, BigInt& number) {
  string line;
  in >> line;
  number = BigInt(line);
  return in;
}

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
