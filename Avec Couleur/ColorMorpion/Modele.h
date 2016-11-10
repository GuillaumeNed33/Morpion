#ifndef MODELE_H
#define MODELE_H

class Modele
{
private:
    int m_joueur;   // 1 ou 2
    int m_tab[3][3];

public:
    Modele();


    // effectue le coup demandé
    // retourne faux si impossible
    bool jouer(int ligne, int colonne);

    // le numéro du joueur dont c'est le tour
    int joueur() const;

    // la grille est elle pleine ?
    bool grille_pleine() const;

    // le numéro du joueur qui a un alignement (0 si aucun)
    int  gagnant() const;

    // contenu d'une case
    int contenu(int ligne, int colonne) const;

    // nouvelle partie
    void reinitialiser();
};

#endif // GRILLE_H
