#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

class NumberGuessingGame {
private:
    int secretNumber;
    int attempts;

    void generateSecretNumber() {
        secretNumber = rand() % 100 + 1;  
    }

public:
    NumberGuessingGame() : attempts(0) {
        srand(static_cast<unsigned>(time(0))); 
    }

    void logResults(const string& filename, const string& playerName, int attempts) {
        ofstream file(filename, ios::app); 
        if (file.is_open()) {
            file << playerName << " guessed the number in " << attempts << " attempts." << endl;
            file.close();
        } else {
            cerr << "Error opening file for logging." << endl;
        }
    }

    void displayPreviousScores(const string& filename) {
        ifstream file(filename);
        string line;
        if (file.is_open()) {
            cout << "Previous Scores:" << endl;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cerr << "Error opening file to read scores." << endl;
        }
    }

    void playGame() {
        generateSecretNumber();
        int guess;
        int guessCount = 0;
        int difficultyChoice;
        int playerChoice;
        const string filename = "game_result.txt";
        
        cout << "\n\t\t\tWelcome to GuessTheNumber game!" << endl;
        cout << "You have to guess a number between 1 and 100. "
             << "You'll have limited choices based on"
             << " the level you choose. Good Luck!" << endl;
        
        string playerName;
        cout << "Enter your name: ";
        getline(cin, playerName);

        while (true) {
            cout << "\nEnter the difficulty level: \n";
            cout << "1 for easy!\t";
            cout << "2 for medium!\t";
            cout << "3 for difficult!\t";
            cout << "0 for ending the game!\n" << endl;

            cout << "Enter the number: ";
            cin >> difficultyChoice;

            int maxChoices = 0;
            if (difficultyChoice == 1) {
                maxChoices = 10;
            } else if (difficultyChoice == 2) {
                maxChoices = 7;
            } else if (difficultyChoice == 3) {
                maxChoices = 5;
            } else if (difficultyChoice == 0) {
                exit(0);
            } else {
                cout << "Wrong choice, Enter valid choice to "
                        "play the game! (0,1,2,3)" << endl;
                continue;
            }

            int choicesLeft = maxChoices;
            for (int i = 1; i <= maxChoices; i++) {
                attempts++;
                cout << "\n\nEnter the number: ";
                cin >> playerChoice;

                if (playerChoice == secretNumber) {
                    cout << "Well played! You won, " << playerChoice
                         << " is the secret number" << endl;
                    cout << "\t\t\t Thanks for playing...." << endl;
                    cout << "Play the game again with us!!\n\n" << endl;
                    logResults(filename, playerName, attempts);
                    break;
                } else {
                    cout << "Nope, " << playerChoice
                         << " is not the right number\n";
                    if (playerChoice > secretNumber) {
                        cout << "The secret number is "
                                "smaller than the number "
                                "you have chosen" << endl;
                    } else {
                        cout << "The secret number is "
                                "greater than the number "
                                "you have chosen" << endl;
                    }
                    choicesLeft--;
                    cout << choicesLeft << " choices left." << endl;
                    if (choicesLeft == 0) {
                        cout << "You couldn't find the secret number, it was "
                             << secretNumber << ". You lose!!\n\n";
                        logResults(filename, playerName, attempts);
                        cout << "Play the game again to win!!!\n\n";
                    }
                }
            }
            attempts = 0; 
        }
    }
}; 

int main() {
    char playAgain;
    const string filename = "game_result.txt";
    NumberGuessingGame game;
    game.displayPreviousScores(filename);
    game.playGame();
    return 0;

}