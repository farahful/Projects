#include <iostream>
#include <ctime>

using namespace std;

void tttBoard (char* spaces);
void playerMove(char* spaces, char player);
void compMove(char* spaces, char comp);
bool checkWinner(char* spaces, char player, char comp);
bool checkTie (char* spaces);

int main() {
    srand(time(0));
    char spaces[9] = {' ', ' ', ' ',' ', ' ', ' ',' ', ' ', ' '};
    bool running = true;
    char player = 'X'; char comp = 'O';

    cout << "**************** Tic Tac Toe Game ****************" << endl << endl;
    while (running) {
        tttBoard(spaces);
        playerMove(spaces, player);
        if(checkWinner(spaces, player, comp)) {
            running = false;
            break;
        } else if (checkTie(spaces)) {
            cout << "IT'S A TIE!" << endl;
            running = false;
            break;
        }
        tttBoard(spaces);
        compMove(spaces, comp);
        if(checkWinner(spaces, player, comp)) { 
            running = false;
            break;
        } else if (checkTie(spaces)) {
            cout << "IT'S A TIE!" << endl;
            running = false;
            break;
        }
    }
    return 0;
}

void tttBoard (char* spaces) {
    cout << "     |" << "     " << "|     " << endl;
    cout << "  " << spaces[0] << "  |" << "  " << spaces[1] <<"  " << "|  "<< spaces[2] << "  " << endl;
    cout << "_____|" << "_____|" << "_____" << endl;
    cout << "     |" << "     " << "|     " << endl;
    cout << "  " << spaces[3] << "  |" << "  " << spaces[4] <<"  " << "|  "<< spaces[5] << "  " << endl;
    cout << "_____|" << "_____|" << "_____" << endl;
    cout << "     |" << "     " << "|     " << endl;
    cout << "  " << spaces[6] << "  |" << "  " << spaces[7] <<"  " << "|  "<< spaces[8] << "  " << endl;
    cout << "     |" << "     |" << "     " << endl;
    cout << '\n';
}
void playerMove(char* spaces, char player) {
    int move;
    do {
    cout << "Enter your move [1-9]: ";
    cin >> move;
    cin.ignore(100, '\n');
    } while(move > 9 || move < 1);
    spaces[move-1] = player; 
}
void compMove(char* spaces, char comp) {
    int move;
    do {
    move = rand() % 9;
    } while(spaces[move] != ' ');
    spaces[move] = comp;
}
bool checkWinner(char* spaces, char player, char comp) {
    if(spaces[0] != ' ' && spaces[0] == spaces[1] && spaces[1] == spaces[2]) {
        spaces[0] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOST!" << endl;
    }
    else if (spaces[3] != ' ' && spaces[3] == spaces[4] && spaces[4] == spaces[5]) {
        spaces[3] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOST!" << endl;
    }
    else if (spaces[6] != ' ' && spaces[6] == spaces[7] && spaces[7] == spaces[8]) {
        spaces[6] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOST!" << endl;
    }
    else if(spaces[0] != ' ' && spaces[0] == spaces[3] && spaces[3] == spaces[6]) {
        spaces[0] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOST!" << endl;
    }
    else if (spaces[1] != ' ' && spaces[1] == spaces[4] && spaces[4] == spaces[7]) {
        spaces[1] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOST!" << endl;
    }
    else if (spaces[2] != ' ' && spaces[2] == spaces[5] && spaces[5] == spaces[8]) {
        spaces[2] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOST!" << endl;
    }
    else if (spaces[0] != ' ' && spaces[0] == spaces[4] && spaces[4] == spaces[8]) {
        spaces[0] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOST!" << endl;
    }
    else if (spaces[2] != ' ' && spaces[2] == spaces[4] && spaces[4] == spaces[6]) {
        spaces[2] == player ? cout << "YOU WIN!" << endl : cout << "YOU LOST!" << endl;
    }
    else {
        return false;
    }
    return true;
}
bool checkTie (char* spaces) {
    for(int i = 0; i < 9; i++) {
        if(spaces[i] == ' ') {
            return false;
        }
    }
    return true;
}