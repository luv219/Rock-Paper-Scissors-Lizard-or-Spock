#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

int player1Score = 0;
int player2Score = 0;
int computerScore = 0;
bool playGame = true;

enum GameMode { PVP, PVC };
GameMode gameMode;

const std::string WELCOME_MESSAGE = R"(
╔════════════════════════════════════════════════════════════╗
║                                                            ║
║              ROCK PAPER SCISSORS LIZARD SPOCK              ║
║                                                            ║
║        ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░       ║
║                                                            ║
║         🎮 MODES:                                          ║
║           • Player vs Player (👥)                          ║
║           • Player vs Computer (💻)                        ║
║                                                            ║
║         🎯 INSTRUCTIONS:                                   ║
║           • Type one of: rock, paper, scissors,            ║
║             lizard, or spock                               ║
║           • Type 'quit' to exit anytime                    ║
║           • First to 10 points wins the game               ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝
)";


void displayWelcomeMessage() {
    std::cout << WELCOME_MESSAGE;
    std::cout << "\nType 'quit' to end early.\n";
    std::cout << "Press Enter to start...";
    std::cin.get();
}

std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

std::string getChoice(int number) {
    switch (number) {
        case 1: return "rock";
        case 2: return "paper";
        case 3: return "scissors";
        case 4: return "lizard";
        case 5: return "spock";
        default: return "invalid";
    }
}

bool isValidChoice(const std::string& choice) {
    return choice == "rock" || choice == "paper" || choice == "scissors" ||
           choice == "lizard" || choice == "spock";
}

int generateComputerChoice() {
    return (rand() % 5) + 1;
}

std::string decideWinner(const std::string& p1, const std::string& p2) {
    if (p1 == p2) return "draw";

    if ((p1 == "rock"     && (p2 == "scissors" || p2 == "lizard")) ||
        (p1 == "paper"    && (p2 == "rock"     || p2 == "spock")) ||
        (p1 == "scissors" && (p2 == "paper"    || p2 == "lizard")) ||
        (p1 == "lizard"   && (p2 == "spock"    || p2 == "paper")) ||
        (p1 == "spock"    && (p2 == "scissors" || p2 == "rock")))
        return "p1";

    return "p2";
}

std::string getPlayerChoice(const std::string& playerLabel) {
    std::string choice;
    while (true) {
        std::cout << playerLabel << ", enter your choice: ";
        std::cin >> choice;
        choice = toLower(choice);
        if (choice == "quit") {
            playGame = false;
            return "quit";
        }
        if (isValidChoice(choice)) {
            return choice;
        } else {
            std::cout << "Invalid choice! Try again.\n";
        }
    }
}

void playRound() {
    std::string p1Choice = getPlayerChoice("Player 1");
    if (!playGame) return;

    std::string p2Choice;

    if (gameMode == PVP) {
        p2Choice = getPlayerChoice("Player 2");
        if (!playGame) return;
    } else {
        int compNum = generateComputerChoice();
        p2Choice = getChoice(compNum);
        std::cout << "Computer chose: " << p2Choice << "\n";
    }

    std::cout << "Player 1 chose: " << p1Choice << "\n";
    if (gameMode == PVP)
        std::cout << "Player 2 chose: " << p2Choice << "\n";

    std::string result = decideWinner(p1Choice, p2Choice);

    if (result == "p1") {
        std::cout << "🎉 Player 1 wins this round!\n";
        player1Score++;
    } else if (result == "p2") {
        if (gameMode == PVP) {
            std::cout << "🎉 Player 2 wins this round!\n";
            player2Score++;
        } else {
            std::cout << "💻 Computer wins this round!\n";
            computerScore++;
        }
    } else {
        std::cout << "🤝 It's a draw!\n";
    }

    // Display scores
    std::cout << "\nScoreboard:\n";
    std::cout << "Player 1: " << player1Score << "\n";
    if (gameMode == PVP)
        std::cout << "Player 2: " << player2Score << "\n";
    else
        std::cout << "Computer: " << computerScore << "\n";

    // Check for game end
    if (player1Score >= 10 || player2Score >= 10 || computerScore >= 10) {
        std::cout << "\n🏁 Game Over!\n";
        if (player1Score >= 10)
            std::cout << "🏆 Player 1 wins the game!\n";
        else if (gameMode == PVP && player2Score >= 10)
            std::cout << "🏆 Player 2 wins the game!\n";
        else
            std::cout << "💻 Computer wins the game!\n";
        playGame = false;
    }
}

void chooseGameMode() {
    int mode;
    std::cout << "Choose Game Mode:\n1. Player vs Player\n2. Player vs Computer\nChoice: ";
    std::cin >> mode;
    gameMode = (mode == 1) ? PVP : PVC;
    std::cin.ignore(); // Clear newline from buffer
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    displayWelcomeMessage();
    chooseGameMode();

    while (playGame) {
        playRound();
        if (playGame) {
            char again;
            std::cout << "\nPlay another round? (y/n): ";
            std::cin >> again;
            if (again == 'n' || again == 'N') {
                playGame = false;
            }
        }
    }

    std::cout << "\nThanks for playing! Final Score:\n";
    std::cout << "Player 1: " << player1Score << "\n";
    if (gameMode == PVP)
        std::cout << "Player 2: " << player2Score << "\n";
    else
        std::cout << "Computer: " << computerScore << "\n";

    return 0;
}
