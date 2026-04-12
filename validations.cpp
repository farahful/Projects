#include <iostream>

using namespace std;

// using Luhn Algorithm

int getDigit (int number);
int sumOddDigits(string cardno);
int sumEvenDigits(string cardno);
bool validation(int sumOdd, int sumEven);

int main() {
    string cardNumber;
    bool validNo;

    do {
        cout << "Enter your card number: ";
        cin >> cardNumber;
        
        validNo = true;
        for (char c : cardNumber) {
            if (!isdigit(c)) {
                validNo = false;
                break;
            }
        }

        if (!validNo) {
            cout << "Invalid input! Try again.\n";
        }
    }while(!validNo);

    int sumOdd = sumOddDigits(cardNumber);
    int sumEven = sumEvenDigits(cardNumber);
    if(validation(sumOdd, sumEven)) {
        cout << "Card number is valid :)" << endl;
    } else {
        cout << "Card number is NOT valid!" << endl;
    }
}

int getDigit (const int num) {
    return num % 10 + num / 10 % 10;
}
int sumOddDigits(const string cardno) {
    int sum = 0;
    for(int i = cardno.size() - 2; i >= 0; i -= 2) {
        int digit = 2 * (cardno[i] - '0');
        sum += getDigit(digit);
    }
    return sum;
}
int sumEvenDigits(const string cardno) {
    int sum = 0;
    for(int i = cardno.size() - 1; i >= 0; i -= 2) {
        sum += (cardno[i] - '0');
    }
    return sum;
}
bool validation(int sumOdd, int sumEven) {
    return (sumOdd + sumEven) % 10 == 0;
}