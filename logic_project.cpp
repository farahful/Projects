#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

int readInteger(const string& message, int minValue, int maxValue);
string readNonEmptyString(const string& message);
int findStateIndex(const vector<string>& states, const string& name);
string readExistingState(const vector<string>& states, const string& message);
void printLine();

int findGroupIndex(const vector<vector<int>>& groups, int stateIndex);

void printOriginalStateTable(
    const vector<string>& states,
    const vector<string>& inputSymbols,
    const vector<vector<int>>& nextState,
    const vector<string>& stateOutput,
    const vector<vector<string>>& transitionOutput,
    int machineType
);

void printMinimizedStateTable(
    const vector<vector<int>>& groups,
    const vector<string>& states,
    const vector<string>& inputSymbols,
    const vector<vector<int>>& nextState,
    const vector<string>& stateOutput,
    const vector<vector<string>>& transitionOutput,
    int machineType
);

int main() {
    cout << "==============================================\n";
    cout << "      State Minimizer - Implication Table      \n";
    cout << "==============================================\n\n";

    cout << "This program minimizes a state machine using\n";
    cout << "the implication table method.\n\n";

    cout << "Choose machine type:\n";
    cout << "1. Moore machine  (output is written inside each state)\n";
    cout << "2. Mealy machine  (output is written on each transition)\n";

    int machineType = readInteger("Enter your choice: ", 1, 2);

    int n = readInteger("\nEnter number of states: ", 1, 50);
    int inputCount = readInteger("Enter number of input symbols: ", 1, 20);

    vector<string> states(n);
    cout << "\nEnter state names. Example: A B C or S0 S1 S2\n";

    for (int i = 0; i < n; i++) {
        while (true) {
            states[i] = readNonEmptyString("State " + to_string(i + 1) + ": ");

            bool repeated = false;
            for (int j = 0; j < i; j++) {
                if (states[j] == states[i]) repeated = true;
            }

            if (!repeated) break;
            cout << "This state name already exists. Please enter a different name.\n";
        }
    }

    vector<string> inputSymbols(inputCount);
    cout << "\nEnter input symbols. Example: 0 1 or x y\n";

    for (int i = 0; i < inputCount; i++) {
        inputSymbols[i] = readNonEmptyString("Input symbol " + to_string(i + 1) + ": ");
    }

    vector<string> stateOutput(n);
    vector<vector<string>> transitionOutput(n, vector<string>(inputCount));

    if (machineType == 1) {
        cout << "\nEnter output of each state.\n";
        for (int i = 0; i < n; i++) {
            stateOutput[i] = readNonEmptyString("Output of state " + states[i] + ": ");
        }
    }

    vector<vector<int>> nextState(n, vector<int>(inputCount));

    cout << "\nNow enter the transition table.\n";

    for (int i = 0; i < n; i++) {
        printLine();
        cout << "Current state: " << states[i] << "\n";

        for (int j = 0; j < inputCount; j++) {
            string nextName = readExistingState(states, "Next state when input is " + inputSymbols[j] + ": ");
            nextState[i][j] = findStateIndex(states, nextName);

            if (machineType == 2) {
                transitionOutput[i][j] = readNonEmptyString("Output on this transition: ");
            }
        }
    }

    vector<vector<bool>> marked(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (machineType == 1) {
                if (stateOutput[i] != stateOutput[j]) {
                    marked[i][j] = true;
                }
            } else {
                for (int k = 0; k < inputCount; k++) {
                    if (transitionOutput[i][k] != transitionOutput[j][k]) {
                        marked[i][j] = true;
                    }
                }
            }
        }
    }

    bool changed = true;

    while (changed) {
        changed = false;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (marked[i][j]) continue;

                for (int k = 0; k < inputCount; k++) {
                    int a = nextState[i][k];
                    int b = nextState[j][k];

                    if (a == b) continue;

                    int high = max(a, b);
                    int low = min(a, b);

                    if (marked[high][low]) {
                        marked[i][j] = true;
                        changed = true;
                        break;
                    }
                }
            }
        }
    }

    cout << "\n\n==================== RESULTS ====================\n";

    printOriginalStateTable(
        states,
        inputSymbols,
        nextState,
        stateOutput,
        transitionOutput,
        machineType
    );

    cout << "\nImplication table result:\n";

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            cout << "(" << states[i] << ", " << states[j] << ") -> ";

            if (marked[i][j]) {
                cout << "Not equivalent\n";
            } else {
                cout << "Equivalent\n";
            }
        }
    }

    vector<bool> used(n, false);
    vector<vector<int>> groups;

    for (int i = 0; i < n; i++) {
        if (used[i]) continue;

        vector<int> group;
        group.push_back(i);
        used[i] = true;

        for (int j = i + 1; j < n; j++) {
            int high = max(i, j);
            int low = min(i, j);

            if (!marked[high][low]) {
                group.push_back(j);
                used[j] = true;
            }
        }

        groups.push_back(group);
    }

    cout << "\nEquivalent state groups:\n";

    for (int i = 0; i < (int)groups.size(); i++) {
        cout << "Group " << i + 1 << ": { ";

        for (int index : groups[i]) {
            cout << states[index] << " ";
        }

        cout << "}\n";
    }

    cout << "\nMinimized state names:\n";

    for (int i = 0; i < (int)groups.size(); i++) {
        cout << "Q" << i << " = { ";

        for (int index : groups[i]) {
            cout << states[index] << " ";
        }

        cout << "}\n";
    }

    printMinimizedStateTable(
        groups,
        states,
        inputSymbols,
        nextState,
        stateOutput,
        transitionOutput,
        machineType
    );

    cout << "\nNumber of states before minimization: " << n << "\n";
    cout << "Number of states after minimization : " << groups.size() << "\n";

    cout << "\nProgram finished successfully.\n";

    return 0;
}

int readInteger(const string& message, int minValue, int maxValue) {
    int value;

    while (true) {
        cout << message;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else if (value < minValue || value > maxValue) {
            cout << "Please enter a number from " << minValue << " to " << maxValue << ".\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string readNonEmptyString(const string& message) {
    string text;

    while (true) {
        cout << message;
        getline(cin, text);

        if (!text.empty()) {
            return text;
        }

        cout << "Input cannot be empty. Try again.\n";
    }
}

int findStateIndex(const vector<string>& states, const string& name) {
    for (int i = 0; i < (int)states.size(); i++) {
        if (states[i] == name) {
            return i;
        }
    }

    return -1;
}

string readExistingState(const vector<string>& states, const string& message) {
    string name;

    while (true) {
        cout << message;
        getline(cin, name);

        if (findStateIndex(states, name) != -1) {
            return name;
        }

        cout << "State not found. Available states are: ";

        for (string s : states) {
            cout << s << " ";
        }

        cout << "\nPlease try again.\n";
    }
}

void printLine() {
    cout << "--------------------------------------------------\n";
}

int findGroupIndex(const vector<vector<int>>& groups, int stateIndex) {
    for (int i = 0; i < (int)groups.size(); i++) {
        for (int state : groups[i]) {
            if (state == stateIndex) {
                return i;
            }
        }
    }

    return -1;
}

void printOriginalStateTable(
    const vector<string>& states,
    const vector<string>& inputSymbols,
    const vector<vector<int>>& nextState,
    const vector<string>& stateOutput,
    const vector<vector<string>>& transitionOutput,
    int machineType
) {
    cout << "\nBefore minimization state table:\n";

    cout << left
         << setw(18) << "Current State"
         << setw(12) << "Input x"
         << setw(18) << "Next State"
         << setw(12) << "Output z"
         << "\n";

    printLine();

    for (int i = 0; i < (int)states.size(); i++) {
        for (int x = 0; x < (int)inputSymbols.size(); x++) {
            cout << left
                 << setw(18) << states[i]
                 << setw(12) << inputSymbols[x]
                 << setw(18) << states[nextState[i][x]];

            if (machineType == 1) {
                cout << setw(12) << stateOutput[i];
            } else {
                cout << setw(12) << transitionOutput[i][x];
            }

            cout << "\n";
        }
    }
}

void printMinimizedStateTable(
    const vector<vector<int>>& groups,
    const vector<string>& states,
    const vector<string>& inputSymbols,
    const vector<vector<int>>& nextState,
    const vector<string>& stateOutput,
    const vector<vector<string>>& transitionOutput,
    int machineType
) {
    cout << "\nAfter minimization state table:\n";

    cout << left
         << setw(18) << "Current State"
         << setw(12) << "Input x"
         << setw(18) << "Next State"
         << setw(12) << "Output z"
         << "\n";

    printLine();

    for (int g = 0; g < (int)groups.size(); g++) {
        int representative = groups[g][0];

        for (int x = 0; x < (int)inputSymbols.size(); x++) {
            int nextOriginalState = nextState[representative][x];
            int nextGroup = findGroupIndex(groups, nextOriginalState);

            cout << left
                 << setw(18) << ("Q" + to_string(g))
                 << setw(12) << inputSymbols[x]
                 << setw(18) << ("Q" + to_string(nextGroup));

            if (machineType == 1) {
                cout << setw(12) << stateOutput[representative];
            } else {
                cout << setw(12) << transitionOutput[representative][x];
            }

            cout << "\n";
        }
    }
}