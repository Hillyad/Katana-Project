#include "Joueur.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>

std::vector<Joueur> ListeJoueur;

Joueur::Joueur() : shuffledCharacters() {
    for (const auto& card : charCards) {
        shuffledCharacters.push_back(card.getName());
    }
}

void Joueur::mainjoueurs(int nombreJoueurs) {

    initializeRoles(nombreJoueurs);
    // Input player names
    for (int i = 0; i < nombreJoueurs; ++i) {
        std::string playerName;
        std::string character;
        int hp;

        std::cout << "Enter the name of Player " << i + 1 << ": ";
        std::cin >> playerName;

        std::string role = Rndrole();
        std::tie(character, hp) = Rndcharacter();

        // Create a player and add to the vector
        ListeJoueur.push_back(Joueur(playerName, role, character, hp, false, Honeurpoints(role, nombreJoueurs), {}, {}));
    }
};

void Joueur::initializeRoles(int nombreJoueurs) {
    shuffledRoles.clear();

    // Duplicate roles based on the number of players
    for (int i = 0; i < nombreJoueurs; ++i) {
        shuffledRoles.push_back(roles.roles[i]);
    }

    // Shuffle roles only once
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffledRoles.begin(), shuffledRoles.end(), g);
}

std::string Joueur::Rndrole() {
    std::string tmp = shuffledRoles[0];
    shuffledRoles.erase(shuffledRoles.begin());
    return tmp;
};

std::tuple<std::string, int> Joueur::Rndcharacter() {

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(shuffledCharacters.begin(), shuffledCharacters.end(), g);

    std::string name = shuffledCharacters[0];
    shuffledCharacters.erase(shuffledCharacters.begin());

    int hp = 0;
    for (const auto& card : charCards) {
        if (card.getName() == name) {
            hp = card.getHp();
            break;
        }
    }

    return std::make_tuple(name, hp);
};

int Joueur::Honeurpoints(std::string role, int nombreJoueurs) {
    if (nombreJoueurs != 3) {
        if (role == "shogun") {
            return 5;
        }
        else if (nombreJoueurs > 5) {
            return 3;
        }
        else if (nombreJoueurs <= 5) {
            return 4;
        }
    } else {
        if (role == "shogun") {
            return 6;
        }
        else {
            return 3;
        }
    };
};

void Joueur::distribcartes() {

    // Find shogun dans le vecteur players
    auto shogun = std::find_if(ListeJoueur.begin(), ListeJoueur.end(), [](const Joueur& joueur) {
        return joueur.role == "shogun";
        });

    // Si Shogun est trouver mettre tout les joueurs apres lui en debut de liste
    if (shogun != ListeJoueur.end()) {
        std::rotate(ListeJoueur.begin(), shogun, ListeJoueur.end());
    }

    // Shuffle deck
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(totCards.begin(), totCards.end(), g);

    // Number of cards to distribute to each player
    std::vector<int> cardsPerPlayer = { 4, 5, 5, 6, 6, 7, 7 };
    int f = -1;

    // Distribute cards to each player's hand
    for (Joueur& joueur : ListeJoueur) {
        f++;
        for (int j = 0; j < cardsPerPlayer[f]; j++) {
            joueur.main.push_back(totCards[0]);
            totCards.erase(totCards.begin());
        }
    }
    for (size_t i = 0; i < ListeJoueur.size(); ++i) {
        std::cout << "Player " << i + 1 << " hand: ";
        for (Cardtot& card : ListeJoueur[i].main) {
            std::cout << card.getName() << " ";
        }
        std::cout << std::endl;
    }
}