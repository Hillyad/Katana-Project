#pragma once
#include <iostream>
#include <vector>
#include "Cartes.h"


#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

class Joueur
{
	private:
		std::string name;
		std::string role;
		std::string character;
		int vie;
		bool incapacite;
		int honeur;
		std::vector<Cardtot> main;
		std::vector<std::string> shuffledCharacters;
		std::vector<std::string> shuffledRoles;
		std::vector<Cardtot> carteperm;

	public:

		Joueur();

		Joueur(std::string names, std::string roles, std::string charact, int vies, bool incapacite, int honeurs, std::vector<Cardtot> cardes, std::vector<Cardtot> cartesperm)
			: name(names), role(roles), character(charact), vie(vies),incapacite(incapacite), honeur(honeurs), main(cardes), carteperm(cartesperm) {}

		// (Getter) Prendre les valeurs
		std::string getName() const { return name; }
		std::string getRole() const { return role; }
		std::string getCharacter() const { return character; }
		int getVie() const { return vie; }
		bool getIncapacite() const { return incapacite; }
		int getHoneur() const { return honeur; }
		std::vector<Cardtot> getMain() const { return main; }
		std::vector<Cardtot> getPerm() const { return carteperm; }

		// (Setter) changer des valeurs
		void setVie(int newVie) { vie = newVie; }
		void setHoneur(int newHoneur) { honeur = newHoneur; }
		void setIncapacite(bool newIncapacite) { incapacite = newIncapacite; }


		void mainjoueurs(int nombreJoueurs);

		void initializeRoles(int nombreJoueurs);

		std::string Rndrole();

		std::tuple<std::string, int> Rndcharacter();

		int Honeurpoints(std::string role, int nombreJoueurs);

		void distribcartes();

		int trouverIndice(const std::vector<int>& ListeJoueur, const Joueur& joueur) {
	    		auto it = std::find(ListeJoueur.begin(), ListeJoueur.end(), joueur.getName());
	    		if (it != ListeJoueur.end()) {
	        		return std::distance(ListeJoueur.begin(), it);
	    		}
	    		else {
	        		return -1;
	    		}
		}

};

extern std::vector<Joueur> ListeJoueur;

#endif
