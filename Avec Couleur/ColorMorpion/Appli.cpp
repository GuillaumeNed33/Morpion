#include "Appli.h"
#include "Modele.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <unistd.h>

using namespace std;

/*
 constantes et fonction auxiliaires
 pour l'implémentation de Appli
*/

const float Appli::MARGE_HAUT   = 90.0;
const float Appli::MARGE_GAUCHE = 100;
const float Appli::EPAISSEUR = 3.0;
const float Appli::DIMENSION = 100.0;


sf::Vector2f Appli::position(int l, int c)
{
    return {MARGE_GAUCHE + c * DIMENSION,
                MARGE_HAUT   + l * DIMENSION};
}

// ---------------------------------------

Appli::Appli()
    : m_fenetre {sf::VideoMode {500, 500, 32},
                 "TicTacToe",
                 sf::Style::Close
                 }
    , m_cadre({DIMENSION-3,DIMENSION-3})
    , m_repere({DIMENSION-3.5, DIMENSION-3.5})
    , m_l {0}
    , m_c {0}

{
    assert(police.loadFromFile("arial.ttf"));

    m_fenetre.setFramerateLimit(50);

    m_cadre.setFillColor(sf::Color::Transparent);
    m_cadre.setOutlineThickness(EPAISSEUR);
    m_cadre.setOutlineColor(sf::Color::White);

    m_repere.setFillColor(sf::Color::Transparent);
    m_repere.setOutlineThickness(EPAISSEUR+2);

    rules.setFont(police);
    rules.setColor(sf::Color::White);

    info.setFont(police);
    info.setColor(sf::Color::White);

    info_quit.setString("Escape to quit");
    info_quit.setFont(police);
    info_quit.setColor(sf::Color::White);

}

// ---------------------------------------

void Appli::run(bool &replay)
{
    int gagnant =0;
    replay = false;
    bool fin = false;

    while (m_fenetre.isOpen())
    {
        while ((gagnant == 0) && ! m_modele.grille_pleine() && !fin)
        {
            dessiner();
            traiter_evenements(gagnant, replay, fin);
            info.setString("");
            rules.setString("Au tour du joueur : " + coul_joueur);
            rules.setPosition(90,25);

        }
        dessiner();
        traiter_evenements(gagnant, replay,fin);
        rules.setPosition(140,25);
        info.setString("Press Enter to replay");


        if(gagnant!=0)
        {
            if(gagnant==1)
            {
                coul_gagnant="Rouge";
            }
            else
            {
                coul_gagnant="Bleu";
            }

            rules.setString("Gagnant : " + coul_gagnant );

        }
        else
        {
            rules.setString("Match Nul !");
        }
        usleep(700000);
    }
}


// ---------------------------------------

void Appli::traiter_evenements(int &gagnant, bool &replay, bool &fin)
{
    sf::Event evenement;
    while (m_fenetre.pollEvent(evenement)) {
        switch (evenement.type) {
        case sf::Event::Closed :
            m_fenetre.close();
            fin=true;
            break;

        case  sf::Event::KeyPressed :
            switch (evenement.key.code) {
            case  sf::Keyboard::Escape :
                m_fenetre.close();
                fin=true;
                break;
            case  sf::Keyboard::Up   :
                if(gagnant ==0 && !m_modele.grille_pleine())
                {
                    if (m_l > 0) m_l--;
                }
                break;
            case  sf::Keyboard::Down : if(gagnant ==0 && !m_modele.grille_pleine())
                {
                    if (m_l < 2) m_l++;
                }
                break;
            case  sf::Keyboard::Left : if(gagnant ==0 && !m_modele.grille_pleine())
                {
                    if (m_c > 0) m_c--;
                }
                break;
            case  sf::Keyboard::Right: if(gagnant ==0 && !m_modele.grille_pleine())
                {
                    if (m_c < 2) m_c++;
                }
                break;

            case  sf::Keyboard::Space:
                if(gagnant ==0 && !m_modele.grille_pleine())
                {
                    if (m_modele.jouer(m_l, m_c))
                        gagnant = m_modele.gagnant();
                    else
                    {
                        info.setString("Impossible de jouer ici");
                        m_fenetre.draw(info);
                        m_fenetre.display();
                        usleep(700000);
                    }
                }
                break;

            case sf::Keyboard::Return:
                if(gagnant !=0 || m_modele.grille_pleine())
                {
                    m_modele.reinitialiser();
                    replay = true;
                    gagnant=0;
                    break;
                }
            }
        }
    }
}


// ---------------------------------------

void Appli::dessiner()
{
    m_fenetre.clear(sf::Color::Black);

    for (int l=0; l<3; l++) {
        for (int c=0; c<3; c++) {

            m_cadre.setPosition(position(l,c));

            if(m_modele.contenu(l,c)==0)
                m_cadre.setFillColor(sf::Color::Black);

            else if(m_modele.contenu(l,c)==1)
            {
                m_cadre.setFillColor((sf::Color::Red));
            }
            else if(m_modele.contenu(l,c)==2)
            {
                m_cadre.setFillColor(sf::Color::Blue);
            }

            m_fenetre.draw(m_cadre);
        }
    }

    m_repere.setPosition(position(m_l, m_c));
    info.setPosition(102,400);
    info_quit.setPosition(15,450);

    if(m_modele.joueur()==1)
    {
        m_repere.setOutlineColor(sf::Color::Red);
        coul_joueur="Rouge";
    }
    else
    {
        m_repere.setOutlineColor(sf::Color::Blue);
        coul_joueur="Bleu";
    }

    m_fenetre.draw(info_quit);
    m_fenetre.draw(rules);
    m_fenetre.draw(info);
    m_fenetre.draw(m_repere);

    m_fenetre.display();

}
