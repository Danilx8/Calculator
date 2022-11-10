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

const int BASE = 10;

class bigInt {
  private:
    enum sign {negative, positive};
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

    string toString() const {
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

    int getDigit(int numberIndex) const {
      if (numberIndex >= 0 && numberIndex < myDigitsNumber) {
        return myDigits[numberIndex] - '0';
      }
      return 0;
    }


    void normalize() {
      int numberIndex;
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

    int digitsNumber() const {
      return myDigitsNumber;
    }

    changeDigit(int numberIndex, int value) {
      if (numberIndex >= 0 && numberIndex < myDigitsNumber) {
        myDigits[numberIndex] = char('0' + value);
      } else {
        cout << "ChangeDigit error at " << numberIndex << endl;
      }
    }

  public:
    bigInt():
      mySign(positive),
      myDigits(1, '0'),
      myDigitsNumber(1) {
    }

    bigInt(int number):
      mySign(positive),
      myDigits(1, '0'),
      myDigitsNumber(0) {
      if (number < 0) {
        mySign = negative;
        number *= -1;
      }

      do {
        addDigit(number % BASE);
        number /= BASE;
      } while (number != 0);

    }

    bigInt(const string& inputString):
      mySign(positive),
      myDigits(inputString.length(), '0'),
      myDigitsNumber(0) {
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

    void print(ostream& output) const {
      output << toString();
    }

    bool isNegative() const {
      return mySign == negative;
    }

    bool isPositive() const {
      return mySign == positive;
    }

    bool isEqual(const bigInt& number) const {
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

    bool lessThan(const bigInt& number) const {
      if (isNegative() != number.isNegative()) {
        return isNegative();
      }

      if (digitsNumber() != number.digitsNumber()) {
        return (digitsNumber() < number.digitsNumber() && isPositive()) ||
               (digitsNumber() > number.digitsNumber() && isNegative());
      }

      for (int numberIndex = digitsNumber() - 1; numberIndex >= 0; --numberIndex) {
        if (getDigit(numberIndex) < number.getDigit(numberIndex)) {
          return isPositive();
        }
        if (getDigit(numberIndex) > number.getDigit(numberIndex)) {
          return isNegative();
        }
      }

      return false;
    }

    bigInt& operator += (const bigInt& number) {
      int readySumm;
      int carry = 0;
      int numberIndex;
      int length = digitsNumber();
      bigInt substrahend;

      if (number.isEqual(0)) {
        return *this;
      }

      if (this == &number) {
        *this *= 2;
        return *this;
      }

      if (isNegative() != number.isNegative()) {
        substrahend = number;
        substrahend *= -1;
        *this -= substrahend;
        return *this;
      }

      if (length < number.digitsNumber()) {
        length = number.digitsNumber();
      }

      for (numberIndex = 0; numberIndex < length; ++numberIndex) {
        readySumm = getDigit(numberIndex) + number.getDigit(numberIndex) + carry;
        carry = readySumm / BASE;
        readySumm %= BASE;

        if (numberIndex < myDigitsNumber) {
          changeDigit(numberIndex, readySumm);
        } else {
          addDigit(readySumm);
        }
      }

      if (carry != 0) {
        addDigit(carry);
      }

      return *this;
    }

    bigInt& operator -= (const bigInt& number) {
      int difference;
      int borrow = 0;
      int length = digitsNumber();
      bigInt subtractionHelper;

      if (number.isEqual(0)) {
        return *this;
      }

      if (this == &number) {
        *this = 0;
        return *this;
      }

      if (isNegative() != number.isNegative()) {
        subtractionHelper = number;
        subtractionHelper *= -1;
        *this += subtractionHelper;
        return *this;
      }

      if (isPositive() && (*this).lessThan(number) ||
          isNegative() && !(*this).lessThan(number)) {
        subtractionHelper = number;
        subtractionHelper -= *this;
        *this = subtractionHelper;
        if (isPositive()) {
          mySign = negative;
        } else {
          mySign = positive;
        }
        return *this;
      }

      for (int numberIndex = 0; numberIndex < length; ++numberIndex) {
        difference = getDigit(numberIndex) - number.getDigit(numberIndex) - borrow;
        borrow = 0;
        if (difference < 0) {
          difference += 10;
          borrow = 1;
        }
        changeDigit(numberIndex, difference);
      }

      normalize();
      return *this;
    }

    const bigInt& operator *= (int number) {
      int carry = 0;
      int product;
      int numberIndex;
      int length = digitsNumber();

      if (number == 0) {
        *this = 0;
        return *this;
      }

      if (number > BASE || number < 0) {
        *this *= bigInt(number);
        return *this;
      }

      if (number == 1) {
        return *this;
      }

      for(numberIndex = 0; numberIndex < length; ++numberIndex) {
        product = number * getDigit(numberIndex) + carry;
        carry = product / BASE;
        changeDigit(numberIndex, product % BASE);
      }

      while (carry != 0) {
        addDigit(carry % BASE);
        carry /= BASE;
      }

      return *this;
    }

    const bigInt& operator *= (const bigInt& multiplier) {
      if (isNegative() != multiplier.isNegative()) {
        mySign = negative;
      } else {
        mySign = positive;
      }

      if (multiplier.isEqual(1)) {
        return *this;
      }

      bigInt numberTensTracker(*this);
      bigInt summ(0);
      int numberIndex;
      int length = multiplier.digitsNumber();

      for(numberIndex = 0; numberIndex < length; ++numberIndex) {
        bigInt addend = numberTensTracker;
        addend *= multiplier.getDigit(numberIndex);
        summ += addend;
        numberTensTracker *= 10;
      }
      *this = summ;
      return *this;
    }

    const bigInt& operator /= (bigInt& divisor) {
      bigInt divisorTracker = bigInt(divisor);
      bigInt quotient;
      int wasNegative = 0;

      if (isNegative() || divisor.isNegative()) {
        if (isNegative()) {
          *this *= -1;
          ++wasNegative;
        }
        if (divisor.isNegative()) {
          divisor *= -1;
          ++wasNegative;
        }
      }

      if (isEqual(divisorTracker)) {
        *this = 1;
        return *this;
      }

      bigInt leftmostCollectedDividend;
      bigInt product;
      bigInt dividendSaver;
      int saverIndex;
      int productDigit = 0;

      for (int numberIndex = digitsNumber() - 1; numberIndex >= 0; --numberIndex) {
        if (leftmostCollectedDividend.isEqual(0)) {
          leftmostCollectedDividend += getDigit(numberIndex);
        } else {
          saverIndex = 0;
          dividendSaver = leftmostCollectedDividend;
          leftmostCollectedDividend = getDigit(numberIndex);
          while (saverIndex <= (dividendSaver.digitsNumber() - 1)) {
            leftmostCollectedDividend.addDigit(dividendSaver.getDigit(saverIndex));
            ++saverIndex;
          }

        }
        
        divisorTracker = divisor;
        
        while (divisorTracker.lessThan(leftmostCollectedDividend)) {
          divisorTracker += divisor;
          ++productDigit;
        }

        if (productDigit != 0) {
          if (!divisorTracker.lessThan(leftmostCollectedDividend)) {
            if (divisorTracker.isEqual(leftmostCollectedDividend)) {
              ++productDigit;
            } else {
              divisorTracker -= divisor;
            }
          }
          product.addDigit(productDigit);
          leftmostCollectedDividend -= divisorTracker;
          productDigit = 0;
        } else if (saverIndex > 2 && product.getDigit(1) != 0) {
          product.addDigit(productDigit);
          productDigit = 0;
        }

      }

      *this = product.getDigit(product.digitsNumber() - 1);
      for (int productIndex = product.digitsNumber() - 2; productIndex > 0; --productIndex) {
        addDigit(product.getDigit(productIndex));
      }

      if (wasNegative == 1) {
        *this *= -1;
        mySign = sign(negative);
      }
      return *this;
    }
};

ostream& operator << (ostream& stream, const bigInt& number) {
  number.print(stream);
  return stream;
}

istream& operator >> (istream& in, bigInt& number) {
  string line;
  in >> line;
  number = bigInt(line);
  return in;
}

bool operator == (const bigInt& leftNumber, const bigInt& rightNumber) {
  return leftNumber.isEqual(rightNumber);
}

bool operator < (const bigInt& leftNumber, const bigInt& rightNumber) {
  return leftNumber.lessThan(rightNumber);
}

bool operator > (const bigInt& leftNumber, const bigInt& rightNumber) {
  return !(leftNumber.lessThan(rightNumber) || leftNumber.isEqual(rightNumber));
}

bigInt operator + (const bigInt& leftNumber, const bigInt& rightNumber) {
  bigInt result(leftNumber);
  result += rightNumber;
  return result;
}

bigInt operator - (const bigInt& leftNumber, const bigInt& rightNumber) {
  bigInt result(leftNumber);
  result -= rightNumber;
  return result;
}

bigInt operator * (const bigInt& bigNumber, int number) {
  bigInt result(bigNumber);
  result *= number;
  return result;
}

bigInt operator * (int number, const bigInt& bigNumber) {
  bigInt result(bigNumber);
  result *= number;
  return result;
}

bigInt operator * (const bigInt& leftNumber, const bigInt& rightNumber) {
  bigInt result(leftNumber);
  result *= rightNumber;
  return result;
}

bigInt operator / (const bigInt& leftNumber, bigInt& rightNumber) {
  bigInt result(leftNumber);
  result /= rightNumber;
  return result;
}

int main() {
    bigInt accumulatingVariable = 0;
    bigInt currentNumber;
    char operation = '+'; 
    
    while (operation != '!') {
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
          
        case '<':
          if (accumulatingVariable < currentNumber) {
            cout << "true" << endl;
          } else {
            cout << "true" << endl;
          }
          break;
        
        case '>':
          if (accumulatingVariable > currentNumber) {
            cout << "true" << endl;
          } else {
            cout << "false" << endl;
          }
          break;
          
        case '=':
          if (accumulatingVariable == currentNumber) {
            cout << "true" << endl;
          } else {
            cout << "false" << endl;
          }
          break;
        
        default:
          cout << "error with operator" << endl;
      }
      cout << "--> " << accumulatingVariable << endl;
      cout << "Enter operator (+ - * / < > = (! to quit)): ";
      cin >> operation;
    }
    cout << accumulatingVariable << endl;
  
  system("pause");
  return 0;
  
}
