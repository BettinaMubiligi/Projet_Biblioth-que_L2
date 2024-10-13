//par Beeverly Gourdette et Bettina Mubiligi

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "entreeSortieLC.h"
#include "biblioLC.h"

void essai_bib() {

    /*Test de la création d'un livre : Vérification que la mémoire pour la structure et les champs titre et auteurs ont bien été alloués*/
    Livre * l = creer_livre(99, "Les Metamorphoses", "Ovide");
    assert(l);
    assert(l->auteur);
    assert(l->titre);
    assert(strcmp(l->auteur,"Ovide") == 0);
    assert(strcmp(l->titre,"Les Metamorphoses") == 0);

    /*Test de la création de la bibliothèque*/
    Biblio *b = creer_biblio();
    assert(b != NULL);
    assert(b->L == NULL);

    /*Test de l'insertion d'un livre en tête de la bibliothèque*/
    inserer_en_tete(b,3,"Les Metamorphoses", "Ovide");
    inserer_en_tete(b,2,"Guerre et Paix", "Tolstoi");
    inserer_en_tete(b,1, "Guerre et Paix", "Tolstoi");
    assert(b->L != NULL);
    afficher_bibli(b);


    /*Test de la fonction recherche num*/
    Livre *livre_num = recherche_num(b, 1);
    assert(livre_num != NULL);
    assert(strcmp(livre_num->titre,"Guerre et Paix") == 0);

    /*Test de la recherche d'un livre par titre */
    Livre *livre_titre = recherche_titre(b, "Guerre et Paix");
    assert(livre_titre != NULL);
    assert(strcmp(livre_titre->titre, "Guerre et Paix") == 0);

    /*Recherche des livres d'un auteur*/
    Biblio *b_aut = recherche_aut(b, "Tolstoi");
    assert(b_aut != NULL);
    assert(b_aut->L != NULL);
    assert(b_aut->L->num == 2);

    /*Test de la fusion de deux bibliothèque*/
    Biblio *b2 = creer_biblio();
    inserer_en_tete(b2, 4, "Madame Bovary", "Flaubert");
    fusion(b, b2);
    assert(recherche_num(b, 4) != NULL);

    /*Suppression d'un livre dans une bibliothèque*/
    suppr(b, 1, "Guerre et Paix", "Tolstoi");
    assert(recherche_num(b, 1) == NULL);

    /*Test de recherche_identique */
    inserer_en_tete(b,2,"Guerre et Paix", "Tolstoi");
    Biblio * all = recherche_identiques(b);
    assert(all->L != NULL);
    assert(strcmp(all->L->auteur,"Tolstoi") == 0);

    /*Test de l'écriture d'une bibliothèque dans un fichier*/

    enregistrer_biblio(b,"Bibliotheque.txt");


    /*Libération de la mémoire - Aucun bloc perdu avec valgrind*/
    liberer_biblio(b);
    liberer_biblio(b_aut);
    liberer_biblio(all);
    liberer_livre(l);
}

int main() {

    essai_bib();
    printf("Les tests se sont bien passés.\n");

    return 0;
}
