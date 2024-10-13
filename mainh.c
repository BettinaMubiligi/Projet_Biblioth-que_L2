//par Beeverly Gourdette et Bettina Mubiligi

#include <stdlib.h>
#include <stdio.h>
#include "biblioH.h"
#define MAX_LENGTH 256

void menu(){
    printf("Gestion de la Bibliothèque : \n");
    printf("0 - Sortie du programme \n1 - Affichage de la Bibliothèque\n2 - Insérer ouvrage \n3 - Suppression d'un ouvrage  \n");
    printf("4 - Livres par auteur\n5 - Recherche livre par titre\n6 - Recherche livre par numéro\n7 - Livres avec plusieurs exemplaires\n");
}

int main(int argc, char** argv){


    /*Fin du programme si le nombre d'argument n'est pas suffisant.*/
    if (argc  < 3){
        printf("Veillez fournir le nom d'un fichier existant suivi du nombre de lignes à lire s'il vous plaît.\n");
        return 1;
    }

    BiblioH *B = charger_n_entreesH(argv[1], atoi(argv[2]));
    if (B == NULL)
        /*Fin du programme s'il y a eu une erreur lors de la création de la bibliothèque B*/
        return 1;
    int rep;
    int num;
    char buffer[MAX_LENGTH];
    char titre[MAX_LENGTH];
    char auteur[MAX_LENGTH];

    do {
        printf("==================\n");
        menu();
        printf("\nEntrez votre choix :");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &rep);


        switch(rep){
            case 1:
                printf("Affichage :\n");
                affiche_biblioH(B);
                break;
            case 2:
                printf("Veillez écrire le numéro, le titre et l'auteur de 'l'ouvrage.\n");
                fgets(buffer,sizeof(buffer),stdin);
                if(sscanf(buffer," %d %s %s",&num,titre,auteur) == 3){
                    inserer(B,num,titre,auteur);
                    printf("Ajout effectué avec succès.\n");
                }
                else printf("Erreur format\n");
                break;
            case 3:
                printf("Veillez écrire le numéro, le titre et l'auteur de 'l'ouvrage à supprimer.\n");
                fgets(buffer,sizeof(buffer),stdin);
                if(sscanf(buffer," %d %s %s",&num,titre,auteur) == 3){
                    supprH(B,num,titre,auteur);
                    printf("Suppression effectué avec succès.\n");
                }
                else printf("Erreur format\n");
                break;
            case 4: 

                printf("Veillez écrire de quel auteur vous voulez obtenir la collection.\n");
                fgets(buffer,sizeof(buffer),stdin);
                if(sscanf(buffer,"%s", auteur) == 1){
                    BiblioH * coll = recherche_auteurH(B,auteur);
                    printf("Collection de l'auteur %s\n", auteur);
                    affiche_biblioH(coll);
                    liberer_biblioH(coll);
                }
                else printf("Erreur format\n");
                break;
            case 5:
                printf("Veillez écrire le titre du livre que vous recherchez \n");
                fgets(buffer,sizeof(buffer),stdin);
                if(sscanf(buffer,"%s", titre) == 1){
                affiche_livreH(recherche_titreH(B,titre));
                }
                else printf("Erreur format\n");
                break;
            case 6: 
                printf("Veillez écrire le numéro du livre que vous recherchez\n");
                fgets(buffer,sizeof(buffer),stdin);
                if (sscanf(buffer,"%d",&num) == 1) {
                    affiche_livreH(recherche_numH(B,num));
                }
                else printf("Erreur format\n");
                break;
            case 7:
                printf("Livres avec plusieurs exemplaires\n");
                BiblioH * all = recherche_identiquesH(B);
                affiche_biblioH(all);
                liberer_biblioH(all);
                break;
        }
        printf("==================\n");
    }while(rep!=0);
    printf("Merci et au revoir. \n");
    liberer_biblioH(B);
    return 0; 
}
