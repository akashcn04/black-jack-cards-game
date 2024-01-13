#include <iostream>
#include <vector>

using namespace std;

// Define card ranks and suits
const string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
const string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };

// Function to generate a deck of cards
vector<string> generateDeck() {
    vector<string> deck;
    for (const string &suit : suits) {
        for (const string &rank : ranks) {
            deck.push_back(rank + " of " + suit);
        }
    }
    return deck;
}

// Function to shuffle the deck
void shuffleDeck(vector<string> &deck) {
    for (int i = 0; i < deck.size(); i++) {
        int j = rand() % deck.size();
        swap(deck[i], deck[j]);
    }
}

// Function to calculate the value of a hand
int calculateHandValue(const vector<string> &hand) {
    int value = 0;
    int aceCount = 0;

    for (const string &card : hand)       //it will declare variable card and represent elements if hand 
    {
        string rank = card.substr(0, card.find(" "));
        if (rank == "A") {
            value += 1; // Ace can be 11 or 1
            aceCount++;
        } else if (rank == "K" || rank == "Q" || rank == "J") {
            value += 10;
        } else {
            value += stoi(rank);
        }
    }

    return value;
}

int main() {
    cout << "Welcome to Blackjack!" << endl;
    int playerMoney = 100;  // Starting money
    int bet = 0;

    while (playerMoney > 0) {
        vector<string> deck = generateDeck();
        shuffleDeck(deck);

        vector<string> playerHand;
        vector<string> dealerHand;

        // Initial deal
        playerHand.push_back(deck.back());
        deck.pop_back();
        dealerHand.push_back(deck.back());
        deck.pop_back();
        playerHand.push_back(deck.back());
        deck.pop_back();
        dealerHand.push_back(deck.back());
        deck.pop_back();

        cout << "\nYou have $" << playerMoney << ". Place your bet: ";
        cin >> bet;

        if (bet > playerMoney || bet <= 0) {
            cout << "Invalid bet. Please place a valid bet." << endl;
            continue;
        }

        cout << "\nYour hand: ";
        for (const string &card : playerHand) {
            cout << card << ", ";
        }
        cout << "Total Value: " << calculateHandValue(playerHand) << endl;

        cout << "Dealer's face-up card: " << dealerHand[1] << endl;

        if (calculateHandValue(playerHand) == 21) {
            cout << "Blackjack! You win $" << bet * 1.5 << "!" << endl;
            playerMoney += bet * 1.5;
        } else {
            while (true) {
                char choice;
                cout << "Do you want to 'hit' or 'stand'? ";
                cin >> choice;

                if (choice == 'h') {
                    playerHand.push_back(deck.back());
                    deck.pop_back();
                    cout << "Your hand: ";
                    for (const string &card : playerHand) {
                        cout << card << ", ";
                    }
                    cout << "Total Value: " << calculateHandValue(playerHand) << endl;

                    if (calculateHandValue(playerHand) > 21) {
                        cout << "Bust! You lose $" << bet << "!" << endl;
                        playerMoney -= bet;
                        break;
                    }
                } else if (choice == 's') {
                    while (calculateHandValue(dealerHand) < 17) {
                        dealerHand.push_back(deck.back());
                        deck.pop_back();
                    }

                    cout << "\nDealer's hand: ";
                    for (const string &card : dealerHand) {
                        cout << card << ", ";
                    }
                    cout << "Total Value: " << calculateHandValue(dealerHand) << endl;

                    if (calculateHandValue(dealerHand) > 21 || calculateHandValue(dealerHand) < calculateHandValue(playerHand)) {
                        cout << "You win $" << bet << "!" << endl;
                        playerMoney += bet;
                    } else if (calculateHandValue(dealerHand) > calculateHandValue(playerHand)) {
                        cout << "You lose $" << bet << "!" << endl;
                        playerMoney -= bet;
                    } else {
                        cout << "It's a tie. Your money is returned." << endl;
                    }

                    break;
                } else {
                    cout << "Invalid choice. Please enter 'h' for hit or 's' for stand." << endl;
                }
            }
        }
    }

    cout << "Out of money! Game over." << endl;



    return 0;
}