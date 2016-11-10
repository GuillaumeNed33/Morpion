#ifndef APPLI_H
#define APPLI_H
#include <SFML/Graphics.hpp>
#include "Modele.h"

class Appli
{
public:
    Appli();
    void run(bool &replay);

private:

    sf::RenderWindow   m_fenetre;
    sf::RectangleShape m_cadre;
    sf::RectangleShape m_repere;


    sf::Text info;
    sf::Text rules;
    sf::Text info_quit;
    sf::String coul_joueur;
    sf::String coul_gagnant;


    sf::Font police;

    Modele m_modele;

    int m_l, m_c;

    void traiter_evenements(int &gagnant, bool &replay, bool &fin);
    void dessiner();

    static const float MARGE_HAUT;
    static const float MARGE_GAUCHE;
    static const float EPAISSEUR;
    static const float DIMENSION;

    static sf::Vector2f position(int l, int c);
};

#endif // APPLI_H
