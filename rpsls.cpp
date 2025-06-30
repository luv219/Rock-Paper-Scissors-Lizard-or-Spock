#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

// Global scores
int playerScore = 0;
int computerScore = 0;
bool playGame = true;

// Welcome message
const std::string WELCOME_MESSAGE = R"(
************************************************************
*                   Welcome to Rock, Paper, Scissors!    *
*                   ----------------------------------   *
*                   Computer vs. Player                  *
*                   ----------------------------------   *
*                   Choose your weapon:                  *
*                   rock, paper, scissors, lizard, spock *
*                   Type 'rock', 'paper','scissors',     *
*                   'lizard' or 'spock' to make your     *
*                   choice                               *
*                   ----------------------------------   *
*                   The first to 10 points wins!         *
************************************************************
)";

void displayWelcomeMessage() {
    std::cout << WELCOME_MESSAGE;
    std::cout << "\nType 'quit' to exit the game at any time.\n";
    std::cout << "Press Enter to start the game...";
    std::cin.get();
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

int generateComputerChoice() {
    return (rand() % 5) + 1; // 1 to 5
}

std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool isValidChoice(const std::string& choice) {
    return choice == "rock" || choice == "paper" || choice == "scissors" || choice == "lizard" || choice == "spock";
}

// Determine winner
std::string decideWinner(const std::string& player, const std::string& computer) {
    if (player == computer)
        return "draw";

    // Winning conditions for player
    if ((player == "rock"     && (computer == "scissors" || computer == "lizard")) ||
        (player == "paper"    && (computer == "rock"     || computer == "spock")) ||
        (player == "scissors" && (computer == "paper"    || computer == "lizard")) ||
        (player == "lizard"   && (computer == "spock"    || computer == "paper")) ||
        (player == "spock"    && (computer == "scissors" || computer == "rock")))
        return "player";

    return "computer";
}

void playRound() {
    std::string playerChoice;
    std::cout << "\nEnter your choice: ";
    std::cin >> playerChoice;
    playerChoice = toLower(playerChoice);

    if (playerChoice == "quit") {
        playGame = false;
        return;
    }

    if (!isValidChoice(playerChoice)) {
        std::cout << "Invalid choice! Try again.\n";
        return;
    }

    int computerNumber = generateComputerChoice();
    std::string computerChoice = getChoice(computerNumber);

    std::cout << "You chose: " << playerChoice << "\n";
    std::cout << "Computer chose: " << computerChoice << "\n";

    std::string result = decideWinner(playerChoice, computerChoice);

    if (result == "player") {
        playerScore++;
        std::cout << "🎉 You win this round!\n";
    } else if (result == "computer") {
        computerScore++;
        std::cout << "💻 Computer wins this round.\n";
    } else {
        std::cout << "🤝 It's a draw!\n";
    }

    std::cout << "Score — You: " << playerScore << " | Computer: " << computerScore << "\n";

    // Check for winner
    if (playerScore >= 10) {
        std::cout << "\n🏆 Congratulations! You won the game!\n";
        playGame = false;
    } else if (computerScore >= 10) {
        std::cout << "\n😢 Sorry, the computer won the game.\n";
        playGame = false;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    displayWelcomeMessage();

    while (playGame) {
        playRound();

        if (playGame) {
            char choice;
            std::cout << "\nDo you want to play another round? (y/n): ";
            std::cin >> choice;
            if (choice == 'n' || choice == 'N') {
                playGame = false;
            }
        }
    }

    std::cout << "\nThanks for playing! Final Score — You: " << playerScore
              << " | Computer: " << computerScore << "\n";
    return 0;
}
