#include "Modele.h"

/* Tableau 3x3 d'entiers */

Modele::Modele()
{
    // TODO
    reinitialiser();
}

void Modele::reinitialiser()
{
    for(int i=0; i<3;i++)
    {
        for(int j=0; j<3;j++)
        {
            m_tab[i][j]=0;
        }
    }
    m_joueur = 1;
}

int Modele::joueur() const
{
    return m_joueur;
}

bool Modele::grille_pleine() const
{
    bool plein = true;
    int i=0;
    int j;
    while(plein && i<3)
    {
        j=0;
        while(plein && j<3)
        {
            if(m_tab[i][j]==0)
                plein=false;
            else
                j++;
        }
        i++;
    }

    return plein;
}

bool Modele::jouer(int ligne, int colonne)
{
    // vérifier que ligne et colonne entre 0 et 2
    // et que la case est vide
    // sinon retourner faux

    // si ok, mettre le numero du joueur dans la case
    // et donner le tour à l'autre (changer le joueur)

    bool joue = false;
    if(ligne>=0 && ligne < 3 && colonne >=0 && colonne <3)
    {
        if (m_tab[ligne][colonne] == 0)
        {
            joue = true;
            m_tab[ligne][colonne] = m_joueur;

           m_joueur=(m_joueur%2)+1;
        }
    }

    return joue;
}

int Modele::contenu(int ligne, int colonne) const
{
    // le contenu de la case
    return m_tab[ligne][colonne];
}

int Modele::gagnant() const
{
    // chercher un alignement sur les 3 lignes
    for (int l=0; l<3; l++) {
        int j = m_tab[l][0];
        if ((j != 0)
                && (j == m_tab[l][1])
                && (j == m_tab[l][2]))
        {
            return j;
        }
    }

    // idem pour les trois colonnes

    for(int c=0; c<3; c++) {
        int i = m_tab[0][c];
        if ((i != 0)
                && (i == m_tab[1][c])
                && (i == m_tab[2][c]))
        {
            return i;
        }

    }
    // idem pour les deux diagonales

    int k = m_tab[0][0];
    if ((k != 0)
            && (k == m_tab[1][1])
            && (k == m_tab[2][2]))
    {
        return k;
    }

    int m = m_tab[0][2];
    if ((m != 0)
            && (m == m_tab[1][1])
            && (m == m_tab[2][0]))
    {
        return m;
    }

    return 0; // pas d'alignement
}
