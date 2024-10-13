//par Beeverly Gourdette et Bettina Mubiligi

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "biblioLC.h"

/*Fonction de création d'un livre : Allocation mémoire et attributions des valeurs aux champs */
Livre* creer_livre(int num,char* titre,char* auteur){
    Livre * new = (Livre *) malloc (sizeof(Livre));
    if(new == NULL){
        printf("Erreur lors de l'allocation de la mémoire pour le livre\n");
        return NULL;
    }
    new->num=num;
    new->titre = strdup(titre);
    new->auteur = strdup(auteur);
    new->suiv = NULL;
    return new;

}

/*Fonction de libération mémoire d'un livre : libération de la structure et de la mémoire allouée pour les champs auteurs 
et titres.*/
void liberer_livre(Livre* l){
    if (l == NULL)
        /*Cas où le livre n'existe pas.*/
        return;
    free(l->titre);
    free(l->auteur);
    free(l);
}

/*Fonction de création d'une bibliothèque : allocation de la mémoire pour la structure.*/
Biblio* creer_biblio(){ 
    Biblio *b = (Biblio *) malloc (sizeof(Biblio));
    if (b == NULL){
        printf("Erreur lors de l'allocation de la mémoire pour la bibliothèque\n");
        return NULL;
    }
    b->L = NULL;
    return b;
}

/*Fonction de libération mémoire d'une bibliothèque : Libération mémoire de chaque livre*/
void liberer_biblio(Biblio* b){
    if(b == NULL)
        /*Cas où la bibliothèque n'existe pas.*/
        return;
    Livre *del;
    Livre *current =  b->L;
    while(current != NULL){
        del = current;
        current = current->suiv;
        liberer_livre(del);
    }
    free(b);
}

/*Fontion pour créer et insérer un livre dans une bibliothèque.*/
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
    if (b == NULL){
        printf("La bibliothèque n'existe pas.\n");
        return;
    }
    Livre *l = creer_livre(num, titre, auteur);
    if( l == NULL)
        return;
    l -> suiv = b -> L;
    b -> L= l ;
}

/*Fonction pour afficher les inrformations sur le livre*/
void affiche_livre (Livre * l){
    if(l == NULL){
        printf("Le livre n'existe pas.\n");
        return;
    }
    printf("%d %s %s \n", l->num, l->titre, l->auteur);
}

/*Fonction pour afficher les informations sur chaque livre de la bibliothèque. */
void afficher_bibli (Biblio * b){
    if( b == NULL){
        printf("La bibliothèque n'existe pas");
        return;
    }
    Livre * current = b->L; 
    while(current != NULL){
        affiche_livre(current);
        current = current->suiv;
    }
}

/*Fonction pour retourner un livre par son numéro. La fonction retourne NULL si aucun livre ne corresponds*/
Livre * recherche_num (Biblio * b,int numero){
    if (b == NULL){
        printf("La bibliothèque n'existe pas\n");
        return NULL;
    } 
    Livre *current = b->L;
    while(current != NULL){
        if(current->num == numero){
            return current;
        }
        current = current->suiv;
    }
    return NULL;
}

/*Fonction pour retourner un livre par son titre. La fonction retourne NULL si aucun livre ne corresponds*/
Livre * recherche_titre (Biblio * b,char * t){
    if (b == NULL){
        printf("La bibliothèque n'existe pas\n");
        return NULL;
    }
    Livre *current = b->L;
    while(current!= NULL){
        if(strcmp(current->titre,t)==0){
            return current;
        }
        current = current->suiv;
    }
    return NULL;
}

/*Fonction pour renvoyer une bibliothèque avec tous les livres d'un même auteur*/
Biblio * recherche_aut (Biblio * b, char * aut){
    if (b == NULL){
        printf("La bibliothèque n'existe pas\n");
        return NULL;
    }
    Biblio * coll = creer_biblio();
    if (coll == NULL)
        return NULL;
    Livre * current = b->L;
    while(current != NULL){
        if (strcmp(current->auteur, aut)==0){
            inserer_en_tete(coll, current->num, current->titre, current->auteur);
        }
        current = current->suiv;
    }
    return coll;
}

/*Fonction permettant de supprimer un livre d'une bilbiothèque.*/
void suppr (Biblio * b, int num, char * titre, char * aut){
    if (b == NULL){
        printf("La bibliothèque n'existe pas\n");
        return;
    }
    /*current est le livre utilisé pour itérer dans la liste chainée, prev est le livre lui précédant.*/
    Livre *current = b->L; 
    Livre *prev = NULL;
    while(current != NULL){
        if((current -> num == num )&& (strcmp(current->auteur, aut)==0) && (strcmp(current->titre, titre)==0 )){
            if (prev== NULL){
                /*Cas où le livre a supprimé est le premier livre de la bibliothèque*/
                if(current->suiv != NULL) 
                    b->L = current->suiv;
                else
                    b->L = NULL;
            }else{
                prev -> suiv = current ->suiv;
            }
            liberer_livre(current);
            break;
        }else{
            prev = current;
            current = current->suiv; 
        }
    }
}

/*Fonction permettant de fusionner deux bibliothèques. Retourne la première bibliothèque et supprime la deuxième*/
void fusion( Biblio *b1, Biblio *b2){
    if(b1 == NULL || b2 == NULL)
        /*On sort de la fonction si l'une des deux bibliothèques n'existent pas.*/
        return;
    Livre *current = b2->L;
    Livre * del;
    while(current != NULL){
        inserer_en_tete(b1,current->num,current->titre,current->auteur);
        del = current;
        current = current->suiv;
        suppr(b2,del->num,del->auteur,del->titre);
    }
    liberer_biblio(b2);
}

/*Fonction permettant de créer une bibliothèque avce tous les livres possedant un exemplaire dans une bibliothèque donnée*/
Biblio *recherche_identiques(Biblio *b) {
    Biblio* all = creer_biblio();
    Livre * current = b->L;
    Livre * next;
    int found = 0;
    
    while(current != NULL){
        next = current->suiv; 
        while(next != NULL){
            if(strcmp(current->titre,next->titre)== 0 && strcmp(current->auteur,next->auteur) == 0 && recherche_num(all,next->num) == NULL){
                inserer_en_tete(all,next->num,next->titre,next->auteur);
                found = 1;
            }
            next = next->suiv;
        }
        if (found == 1){
            /*Si le livre possède un exemplaire, on l'ajoute également à la bibliothèque : la variable found permet de le savoir.*/
            inserer_en_tete(all,current->num,current->titre,current->auteur);
            found = 0;
        }
        current = current->suiv;
    }
    return all;
}
