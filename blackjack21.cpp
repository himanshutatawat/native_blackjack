#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

enum Rank {
    RANK_2 = 2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE
};

enum Suit {
    SUIT_HEART,
    SUIT_DIAMOND,
    SUIT_CLUB,
    SUIT_SPADE
};

struct Card {
    Rank rank;
    Suit suit;
};

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck() {
        for (int suit = SUIT_HEART; suit <= SUIT_SPADE; ++suit) {
            for (int rank = RANK_2; rank <= RANK_ACE; ++rank) {
                Card card = { static_cast<Rank>(rank), static_cast<Suit>(suit) };
                cards.push_back(card);
            }
        }
    }

    void shuffle() {
        std::srand(static_cast<unsigned int>(std::time(0)));
        std::random_shuffle(cards.begin(), cards.end());
    }

    Card dealCard() {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
};

int getCardValue(const Card& card) {
    switch (card.rank) {
        case RANK_2:
        case RANK_3:
        case RANK_4:
        case RANK_5:
        case RANK_6:
        case RANK_7:
        case RANK_8:
        case RANK_9:
        case RANK_10:
            return static_cast<int>(card.rank);
        case RANK_JACK:
        case RANK_QUEEN:
        case RANK_KING:
            return 10;
        case RANK_ACE:
            return 11;
        default:
            return 0;
    }
}

void printCard(const Card& card) {
    switch (card.rank) {
        case RANK_2:
        case RANK_3:
        case RANK_4:
        case RANK_5:
        case RANK_6:
        case RANK_7:
        case RANK_8:
        case RANK_9:
        case RANK_10:
            std::cout << static_cast<int>(card.rank);
            break;
        case RANK_JACK:
            std::cout << 'J';
            break;
        case RANK_QUEEN:
            std::cout << 'Q';
            break;
        case RANK_KING:
            std::cout << 'K';
            break;
        case RANK_ACE:
            std::cout << 'A';
            break;
    }

    switch (card.suit) {
        case SUIT_HEART:
            std::cout << 'H';
            break;
        case SUIT_DIAMOND:
            std::cout << 'D';
            break;
        case SUIT_CLUB:
            std::cout << 'C';
            break;
        case SUIT_SPADE:
            std::cout << 'S';
            break;
    }
}

int main() {
    std::cout << "Welcome to Blackjack!\n";

    Deck deck;
    deck.shuffle();

    int playerScore = 0;
    int dealerScore = 0;

    // Initial dealing of cards
    Card playerCard1 = deck.dealCard();
    Card playerCard2 = deck.dealCard();
    Card dealerCard1 = deck.dealCard();
    Card dealerCard2 = deck.dealCard();

    playerScore += getCardValue(playerCard1);
    playerScore += getCardValue(playerCard2);
    dealerScore += getCardValue(dealerCard1);
    dealerScore += getCardValue(dealerCard2);

    std::cout << "\nYour cards: ";
    printCard(playerCard1);
    std::cout << " ";
    printCard(playerCard2);
    std::cout << "\nYour score: " << playerScore << "\n";

    std::cout << "\nDealer's cards: ";
    printCard(dealerCard1);
    std::cout << " *Hidden*\n";

    // Player's turn
    char choice;
    do {
        std::cout << "\nDo you want to hit or stand? (h/s): ";
        std::cin >> choice;

        if (choice == 'h') {
            Card newCard = deck.dealCard();
            playerScore += getCardValue(newCard);

            std::cout << "\nYou drew a ";
            printCard(newCard);
            std::cout << "\nYour score: " << playerScore << "\n";

            if (playerScore > 21) {
                std::cout << "\nBust! You lose.\n";
                return 0;
            }
        }
    } while (choice != 's');

    // Dealer's turn
    std::cout << "\nDealer's turn: ";
    printCard(dealerCard1);
    std::cout << " ";
    printCard(dealerCard2);
    std::cout << "\nDealer's score: " << dealerScore << "\n";

    while (dealerScore < 17) {
        Card newCard = deck.dealCard();
        dealerScore += getCardValue(newCard);

        std::cout << "\nDealer drew a ";
        printCard(newCard);
        std::cout << "\nDealer's score: " << dealerScore << "\n";

        if (dealerScore > 21) {
            std::cout << "\nDealer busts! You win.\n";
            return 0;
        }
    }

    // Compare scores
    std::cout << "\nFinal scores:\n";
    std::cout << "Your score: " << playerScore << "\n";
    std::cout << "Dealer's score: " << dealerScore << "\n";

    if (playerScore > dealerScore) {
        std::cout << "\nYou win!\n";
    } else if (playerScore < dealerScore) {
        std::cout << "\nYou lose.\n";
    } else {
        std::cout << "\nIt's a tie!\n";
    }

    return 0;
}

