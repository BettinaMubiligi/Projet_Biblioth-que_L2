//par Beeverly Gourdette et Bettina Mubiligi

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "biblioH.h"

void essai_bibH() {
    /*Création d'une bibliothèque avec une taille m*/
    BiblioH *b = creer_biblioH(10);
    assert(b != NULL);


    /*Test de l'insertion des livres dans la bibliothèque*/
    inserer(b,3,"Les Metamorphoses", "Ovide");
    inserer(b,2,"Guerre et Paix", "Tolstoi");
    inserer(b,1, "Guerre et Paix", "Tolstoi");
    assert(b->nE == 3);
    affiche_biblioH(b);

    /*Test de la fonction de hachage*/
    int key = fonctionClef("Tolstoi");
    assert(b->T[fonctionHachage(key,b->m)] != NULL);

    /*Vérification de la recherche par numéro*/
    LivreH *livre_num = recherche_numH(b, 2);
    assert(livre_num != NULL);
    assert(livre_num->num == 2);
    assert(strcmp(livre_num->titre,"Guerre et Paix") == 0);

    /*Vérification de la recherche d'un livre par son titre*/
    LivreH *livre_titre = recherche_titreH(b, "Guerre et Paix");
    assert(livre_titre != NULL);
    assert(strcmp(livre_titre->titre, "Guerre et Paix") == 0);

    /*recherche des livres d'un auteur*/
    BiblioH *b_aut = recherche_auteurH(b, "Tolstoi");
    assert(b_aut != NULL);
    assert(b_aut->nE == 2);

    /*Test de la suppression d'un livre*/
    supprH(b, 3, "Les Metamorphoses", "Ovide");
    assert(b->nE == 2);

    /*Test de la fusion de deux bibliothèque*/
    BiblioH *b2 = creer_biblioH(10);
    inserer(b2, 4, "Madame Bovary", "Flaubert");
    fusionH(b, b2);
    assert(recherche_numH(b, 4) != NULL);

    /*Test de la fonction recherche_identiquesH*/
    BiblioH *all = recherche_identiquesH(b);
    assert(all != NULL);
    assert(all->nE == 2);

    /*Test de l'écriture d'une bibliothèque dans un fichier*/
    enregistrer_biblioH(b,"BibliothequeHH.txt");

    /*Libération de la mémoire*/
    liberer_biblioH(b);
    liberer_biblioH(b_aut);
    liberer_biblioH(all);
}

int main() {
    essai_bibH();
    printf("Les tests se sont bien passés.\n");

    return 0;
}
