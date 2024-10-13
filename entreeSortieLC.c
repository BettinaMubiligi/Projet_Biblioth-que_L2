//par Beeverly Gourdette et Bettina Mubiligi

#include <stdlib.h>
#include <stdio.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"
#define MAX_LENGTH 256

/*Fonction permettant de lire n lignes du fichier donné nomfic et crée une bibliothèque contenant des livres
corresponds à chaque ligne du fichier. */
 Biblio* charger_n_entrees(char* nomfic, int n){
    FILE *f = fopen(nomfic,"r");
    if (f == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }
    char buffer[MAX_LENGTH];
    int i = 0; 
    int num;
    char titre[100];
    char auteur[100];
    Biblio * b = creer_biblio();
    if (b == NULL)
        return NULL;
    while(fgets(buffer,MAX_LENGTH,f) && i < n){
        sscanf(buffer,"%d %s %s", &num,titre,auteur);
        inserer_en_tete(b, num, titre, auteur);
        i++;
    }
    fclose(f);
    return b;
 }

 /*Fonction permettant d'enregistrer une bibliothèque sous forme d'un fichier avec chaque ligne correspondant à un livre*/
 void enregistrer_biblio(Biblio *b, char* nomfic){
    FILE *f = fopen(nomfic, "w");
    if (f == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    Livre * current = b->L;
    while(current!= NULL){
        fprintf(f, "%d %s %s \n", current->num, current->titre, current->auteur);
        current = current -> suiv;
    }
    fclose(f);
 }
