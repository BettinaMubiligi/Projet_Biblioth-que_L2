//par Beeverly Gourdette et Bettina Mubiligi

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "biblioH.h"
#define MAX_LENGTH 256

/*Fonction permettant de retourner un nombre entier correspondant à la somme ASCII
de chaque lettre d'un auteur*/
int fonctionClef(char* auteur){
    int ascii_sum = 0;
    for (int i = 0; i < strlen(auteur); i++){
        ascii_sum += auteur[i];
    }
    return ascii_sum;
}

/*Fonction de création d'un livre : Allocation mémoire et attributions des valeurs aux champs */
LivreH* creer_livreH(int num, char* titre, char * auteur){
    LivreH * new = (LivreH *) malloc(sizeof(LivreH));
    new->clef = fonctionClef(auteur);
    new->num = num;
    new->auteur = strdup(auteur);
    new->titre = strdup(titre);
    new->suivant = NULL;
    return new;
}

/*Fonction de libération mémoire d'un livre : libération de la structure et de la mémoire allouée pour les champs auteurs 
et titres.*/
void liberer_livreH(LivreH* l){
    if (l == NULL)
        /*Cas où le livre n'existe pas.*/
        return;
    free(l->auteur);
    free(l->titre);
    free(l);
}

/*Fonction de création d'une bibliothèque : allocation de la mémoire pour la structure*/
BiblioH * creer_biblioH(int m){
    BiblioH * lib = (BiblioH * ) malloc(sizeof(BiblioH));
    if (lib == NULL){
        printf("Erreur lors de l'allocation de la mémoire pour la bibliothèque\n");
        return NULL;
    }
    lib->m = m;
    lib->nE = 0;
    lib->T = (LivreH ** ) malloc(m * sizeof(LivreH*));
    for (int i = 0; i < m; i++){
        /*Initialisation de chaque case de T à NULL*/
        lib->T[i] = NULL;
    }
    return lib;
} 

/*Fonction de libération mémoire pour la bibliothèque*/
void liberer_biblioH(BiblioH *b) {

    if (b == NULL)
        /*Cas ou la bibliothèque n'existe pas*/
        return;
    LivreH * current;
    LivreH * del;
    for (int i = 0; i < b->m; i++){
        current = b->T[i];
        while(current != NULL){
            del = current;
            current = current->suivant;
            liberer_livreH(del);
        }
    }
    free(b->T);
    free(b);
}

/*Fonction permettant de retourner un entier correspondant à la clé associé à un livre*/
int fonctionHachage(int cle, int m){
    int a =  (sqrt(5)-1)/2;
    return floor(m * ((cle * a ) - (floor(cle * a)))); 
}

/*Fonction permettant d'insérer un livre dans une bibliothèque selon ses information.*/
void inserer(BiblioH * b, int num, char * titre, char * auteur){
    if (b == NULL){
        printf("La bibliothèque n'existe pas\n");
        return;
    }
    LivreH * new = creer_livreH(num,titre,auteur);
    if (new == NULL)
        return;
    int key = fonctionHachage(new->clef,b->m);
    if(b->T[key] ==NULL) 
        /*Cas ou la case correspondant à la clé est vide : la première case devient new*/
        b->T[key] =  new;
    else{
        /*sinon, new devient la première case et est suivi des autres livres.*/
        new->suivant = b->T[key];
        b->T[key] = new;
    }
    /*Le nombre d'éléments dans le tableau augment. */
    b->nE++;
}


/*Fonction permettant de lire n lignes du fichier donné nomfic et crée une bibliothèque contenant des livres
corresponds à chaque ligne du fichier. */
BiblioH * charger_n_entreesH(char * nom_fic, int n){
    FILE *f  = fopen(nom_fic, "r");
    if (f == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }
    BiblioH * lib = creer_biblioH(n);
    if (lib == NULL)
        return NULL;
    char buffer[MAX_LENGTH];
    int i = 0;
    int num;
    char titre[100];
    char auteur[100];
    while(fgets(buffer,MAX_LENGTH,f) && i < n){
        sscanf(buffer,"%d %s %s", &num,titre,auteur);
        inserer(lib,num,titre,auteur);
        i++;
    }
    fclose(f);
    return lib;
}

 /*Fonction permettant d'enregistrer une bibliothèque sous forme d'un fichier avec chaque ligne correspondant à un livre*/
void enregistrer_biblioH(BiblioH *b, char * nom_fic){
    FILE *f = fopen(nom_fic, "w");
    if (f == NULL){
        printf("Erreur lors de l'ouverture du fichier \n");
        return;
    }
    LivreH * livre;
    for (int i = 0; i < b->m; i++){
        livre = b->T[i];
        while(livre != NULL){
            fprintf(f," %d %s %s\n",livre->num, livre->titre, livre->auteur);
            livre = livre->suivant;
        }
    }
    fclose(f);
}

/*Fonction permettant d'afficher les informations du livres*/
void affiche_livreH(LivreH * l){
    if ( l == NULL){
        printf("Le livre n'existe pas\n");
        return;
    }
    printf(" %d %s %s \n", l->num, l->titre, l->auteur);
}

/*Fonction permettant d'afficher les informations de chaque livre de la bibliothèque*/
void affiche_biblioH(BiblioH *b){
    if(b == NULL){
        printf ("La bibliothèque n'existe pas\n");
        return;
    }
    LivreH * livre;
    for (int i = 0; i < b->m; i++){
        livre = b->T[i];
        while(livre != NULL){
            affiche_livreH(livre);
            livre = livre->suivant;
        }
    }
}

/*Fonction permettant de retourner un livre par son numéro. Retourne NULL si aucun livre ne corresponds.*/
LivreH * recherche_numH(BiblioH * b, int num){
    if( b == NULL){
        printf("La bibliothèque n'existe pas");
        return NULL;
    }
    for (int i = 0; i < b->m ; i++){
        LivreH * livre = b->T[i];
        while(livre != NULL){
            if (livre->num == num)
                return livre;
            livre = livre->suivant;
        }
    }
    return NULL;
}

/*Fonction permettant de retourner un livre par son titre. Retourne NULL si aucun livre ne corresponds.*/
LivreH * recherche_titreH(BiblioH * b, char * titre){
    if (b == NULL){
        printf("La bibliothèque n'existe pas\n");
        return NULL;
    }
    for (int i = 0; i < b->m ; i++){
        LivreH * livre = b->T[i];
        while(livre != NULL){
            if (strcmp(livre->titre, titre) == 0)
                return livre;
            livre = livre->suivant;
        }
    }
    return NULL;
}

/*Fonction permettant de retourner une bibliothèque composé de livre ayant plusieurs exemplaires*/
BiblioH * recherche_auteurH (BiblioH * b, char * auteur){
    if (b == NULL){
        printf("La bibliothèque n'existe pas.\n");
        return NULL;
    }
    int key = fonctionHachage(fonctionClef(auteur), b->m);
    BiblioH * coll = creer_biblioH(b->m);
    LivreH * livre = b->T[key];
    
    while(livre != NULL){
        if (strcmp(livre->auteur, auteur) == 0){
            inserer(coll,livre->num, livre->titre, livre->auteur);
        }
        livre = livre->suivant;
    }
    return coll;
}   

/*Fonction permettant de supprimer un livre de la bibliothèqye */
void supprH ( BiblioH * b, int num, char * auteur, char * titre){
    int key = fonctionHachage(fonctionClef(auteur), b->m);
    LivreH * current = b->T[key];
    LivreH * prev = NULL; 

    while(current != NULL){
        if(num == current->num && strcmp(auteur,current->auteur) == 0 && strcmp(titre, current->titre) == 0){
            if(prev == NULL)
                b->T[key] = current->suivant;
            else
                prev->suivant = current->suivant;
            liberer_livreH(current);
            return;
        } else {
            prev = current;
            current = current->suivant;
        }
    }
    b->nE--;
}

/*Fonction permettant de fusionner deux bibliothèques. Retourne la première bibliothèque et supprime la deuxième*/
void fusionH (BiblioH * b1, BiblioH * b2){

    if( b1 == NULL || b2 == NULL ){
        /*Cas ou l'une des deux bibliothèques n'existent pas.*/
        return;
    }
    LivreH * livre;
    LivreH * del;
    for(int i = 0; i < b2->m ; i++){
        livre = b2->T[i];
        while(livre != NULL){
            inserer(b1,livre->num,livre->titre,livre->auteur);
            del = livre;
            livre = livre->suivant;
            supprH(b2,del->num,del->auteur,del->titre);
        }
    }
    liberer_biblioH(b2);
}

/*Fonction permettant de créer une bibliothèque avce tous les livres possedant un exemplaire dans une bibliothèque donnée*/
BiblioH * recherche_identiquesH(BiblioH * b){
    BiblioH * all = creer_biblioH(b->m);
    LivreH * current;
    LivreH * next;
    int found = 0;

    for (int i = 0; i < b->m; i++){
        current = b->T[i];
        while(current != NULL){
            next = current->suivant;
            while(next != NULL){
            if(strcmp(current->titre,next->titre)== 0 && strcmp(current->auteur,next->auteur) == 0 && recherche_numH(all,next->num) == NULL){
                inserer(all,next->num,next->titre,next->auteur);
                found = 1;
            }
            next = next->suivant;
            }
            if (found == 1){
                /*Si le livre possède un exemplaire, on l'ajoute également à la bibliothèque : la variable found permet de le savoir.*/
                inserer(all,current->num,current->titre,current->auteur);
                found = 0;
            }
        current = current->suivant;
        }
    }
    return all;
}
