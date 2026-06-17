#include <iostream>
#include <string>
#include <cctype>

using namespace std;

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define GRAY    "\033[1;37m"
#define RESET   "\033[0m"

// using Luhn Algorithm

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string cleanCardNumber(const string& input);
bool isValidLuhn(const string& cardNumber);
string getCardType(const string& cardNumber);

int main() {
    bool running = true;

    while (running) {
        string input;
        cout << CYAN << "\n------ Credit Card Validator ------\n" << RESET;
        cout << BLUE << "Enter your card number: " << RESET;
        getline(cin, input);
        string cardNumber = cleanCardNumber(input);

        if (cardNumber.empty()) {
            cout << RED << "Invalid input! Card number must contain digits only.\n" << RESET;
        }
        else if (!isValidLuhn(cardNumber)) {
            cout << RED << "Card number is NOT valid.\n" << RESET;
        } else {
            cout << GREEN << "Card number is valid.\n" << RESET;
            cout << CYAN << "Card Type: " << getCardType(cardNumber) << RESET << endl;
        }
        cout << YELLOW << "\nWould you like to enter another card number? (yes/no): " << RESET;
        string answer;
        getline(cin, answer);
        for (char &c : answer) {
            c = tolower(c);
        }
        if (answer == "no" || answer == "n") {
            running = false;
            cout << GREEN << "\nThank you for using Credit Card Validator!\n"
                << RESET;
        }
    }

    return 0;
}

string cleanCardNumber(const string& input) {
    string result;
    for (char c : input) {
        if (isdigit(c)) {
            result += c;
        } else if (c != ' ' && c != '-') {
            return "";
        }
    }
    return result;
}

bool isValidLuhn(const string& cardNumber) {
    int sum = 0;
    bool doubleDigit = false;
    for (int i = cardNumber.length() - 1; i >= 0; i--) {
        int digit = cardNumber[i] - '0';
        if (doubleDigit) {
            digit *= 2;

            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        doubleDigit = !doubleDigit;
    }
    return sum % 10 == 0;
}

string getCardType(const string& cardNumber) {
    int length = cardNumber.length();
    if (length == 15 && 
        (cardNumber.substr(0, 2) == "34" || cardNumber.substr(0, 2) == "37")) {
        return "American Express";
    }
    if (length == 16 && cardNumber[0] == '5') {
        char secondDigit = cardNumber[1];
        if (secondDigit >= '1' && secondDigit <= '5') {
            return "MasterCard";
        }
    }
    if ((length == 13 || length == 16) && cardNumber[0] == '4') {
        return "Visa";
    }
    return "Unknown card type";
}