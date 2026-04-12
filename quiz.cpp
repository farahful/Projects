#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    string questions[] = { "What is my name?",
        "What year was I born?",
        "What's my birth month?"
    };
    string choices[][4] = { {"A. Farah", "B. Nour", "C. Sarah", "D. Nada"},
    {"A. 2006", "B. 2005", "C. 2007", "D. 2008"},
    {"A. January", "B. Feburary", "C. December", "D. November"}
    };
    char answers[] = { 'A', 'C', 'A'
    };
    int numOfQ = sizeof(questions) / sizeof(questions[0]);
    int numOfC = sizeof(choices[0]) / sizeof(choices[0][0]);
    int numOfA = sizeof(answers) / sizeof(answers[0]);
    int score = 0;

    for(int i = 0; i < numOfQ; i++) {
        cout << "--------------------------------" << endl;
        cout << "QUESTION "<< i+1 << "! " <<  questions[i] << endl;
        for (int j = 0; j < numOfC; j++) {
            cout << choices[i][j] << endl;
        }
        char guess;
        cout << "\n" << "Enter your guess: ";
        cin >> guess;
        cin.ignore(100, '\n');
        if (toupper(guess) == answers[i]) {
            score++;
            cout << '\n' << "Correct :)" << endl;
        } else {
            cout << '\n' << "Wrong :(" << endl;
        }
        cout << "\n";
        sleep(1);
    }
    cout << "You got " << score << " out of " << numOfQ << " questions correct!" << endl;

    return 0;    
}