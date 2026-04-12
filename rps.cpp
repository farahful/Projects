#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::transform;

int scorePlayer = 0;
int scoreCompu = 0;

string playerChoice();

string compChoice(); 

void displayWinner(string player, string computer);

bool bestOfThree() ;

int main()
{
    srand(time(NULL));
    cout << "------ Rock Paper Scissors Game! ------" << endl;
    do
    {
        string player = playerChoice();
        string computer = compChoice();

        cout << "Your choice is " << player << endl;
        cout << "Computer's choice is " << computer << endl;

        sleep(1);
        displayWinner(player, computer);
        cout << "The score is " << scorePlayer << "-" << scoreCompu << endl << endl;
    } while (bestOfThree());
    return 0;
}
string playerChoice()
{
    string choice;
    do
    {
        cout << "Choose [Rock - Paper - Scissors]: ";
        cin >> choice;
        cin.ignore(100, '\n');
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
    } while (choice != "rock" && choice != "paper" && choice != "scissors");
    return choice;
}

string compChoice()
{
    int num = (rand() % 3) + 1;
    if (num == 1)
    {
        return "rock";
    }
    else if (num == 2)
    {
        return "paper";
    }
    else
    {
        return "scissors";
    }
}

void displayWinner(string player, string computer)
{
    if (player == computer)
    {
        cout << "It's a tie!" << endl;
    }
    else if ((player == "rock" && computer == "scissors") ||
             (player == "paper" && computer == "rock") ||
             (player == "scissors" && computer == "paper"))
    {
        cout << "You win!" << endl;
        scorePlayer++;
    }
    else
    {
        cout << "Computer wins!" << endl;
        scoreCompu++;
    }
}
bool bestOfThree()
{
    if (scorePlayer == 3)
    {
        cout << "You win the match!" << endl;
        return false;
    }
    else if (scoreCompu == 3)
    {
        cout << "The computer wins the match!" << endl;
        return false;
    }
    else
    {
        return true;
    }
}