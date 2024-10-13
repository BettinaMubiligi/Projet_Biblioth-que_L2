//par Beeverly Gourdette et Bettina Mubiligi

#include <stdlib.h>
#include <stdio.h>
#include "entreeSortieLC.h"
#include "biblioLC.h"
#include "biblioH.h"
#include <time.h>
#define MAX_LENGTH 256

int main(int argc, char** argv){

//Excercice 3 : Mesure du temps de calcul

//Question 1 et 2

    srand(time(NULL));
    clock_t temps_initial, temps_final; //Temps initial et final en micro secondes
    double temps_cpu; // Temps total en secondes 

  BiblioH *biblio1 = charger_n_entreesH("GdeBiblio.txt", 500);
  Biblio *biblio2 = charger_n_entrees("GdeBiblio.txt", 500);  // Charge les 500 premières entrées du fichier

    if ((biblio1 == NULL)) {
        printf("Erreur lors de la création de la bibliothèque 1 à partir du fichier\n");
        return 1;
    }
    if ((biblio2 == NULL)) {
        printf("Erreur lors de la création de la bibliothèque 2 à partir du fichier\n");
        return 1;
    }

// 1.1 Mesure du temps pour la recherche par numéro dans la liste chaînée
    int numero;
    printf("Entrez le numéro du livre à rechercher : ");
    scanf("%d", &numero);
    temps_initial = clock();
    affiche_livre(recherche_num(biblio2, numero));
    temps_final = clock();
    temps_cpu = (double)(temps_final - temps_initial) / CLOCKS_PER_SEC;
    printf("La recherche par numéro prend : %f secondes\n", temps_cpu);

//1.2 Mesure du temps pour la recherche par numéro dans la table de hachage  
    temps_initial = clock();
    affiche_livreH(recherche_numH(biblio1, numero));
    temps_final = clock();
    temps_cpu = (double)(temps_final - temps_initial) / CLOCKS_PER_SEC;
    printf("La recherche par numéro prend avec hachage : %f secondes\n", temps_cpu);

// 2.1 Mesure du temps pour la recherche par titre dans la liste chaînée
    char t[MAX_LENGTH];
    printf("Entrez le titre à rechercher : ");
    scanf("%s", &t);
    temps_initial = clock();
    affiche_livre(recherche_titre(biblio2,t));
    temps_final = clock();
    temps_cpu = (double)(temps_final - temps_initial) / CLOCKS_PER_SEC;
    printf("La recherche par titre prend : %f secondes\n", temps_cpu);

// 2.2 Mesure du temps pour la recherche par titre dans la table de hachage

    temps_initial = clock();
    affiche_livreH(recherche_titreH(biblio1, t));
    temps_final = clock();
    temps_cpu = (double)(temps_final - temps_initial) / CLOCKS_PER_SEC;
    printf("La recherche par titre prend  avec hachage : %f secondes\n", temps_cpu);



 // 3.1 Mesure du temps pour la recherche par auteur dans la liste chaînée
    char aut[MAX_LENGTH];
    printf("Entrez l'auteur à rechercher : ");
    scanf("%s", &aut);
    temps_initial = clock();
    afficher_bibli(recherche_aut(biblio2,aut));
    temps_final = clock();
    temps_cpu = (double)(temps_final - temps_initial) / CLOCKS_PER_SEC;
    printf("La recherche par auteur prend : %f secondes\n", temps_cpu);
    

// 3.2 Mesure du temps pour la recherche par auteur dans la table de hachage
    temps_initial = clock();
    affiche_biblioH(recherche_auteurH(biblio1, aut));
    temps_final = clock();
    temps_cpu = (double)(temps_final - temps_initial) / CLOCKS_PER_SEC;
    printf("La recherche par auteur avec hachage: %f secondes\n", temps_cpu);



//Question 3

    int n;
    //création d'un fichier temps pour stocker les valeurs des temps de calcul.
    FILE *f = fopen("temps.txt", "w");
  
  
    if (f== NULL) {
      printf("Erreur lors de l'ouverture du fichier temps.txt\n");
      return 1;
  }
  double temps_cpu_table, temps_cpu_liste;
  clock_t temps_initial1, temps_final1, temps_initial2, temps_final2;
  BiblioH *b1, *biblio_table;
  Biblio *b2, *biblio_liste;
  
  //boucle pour les valeurs de n croissantes (nombre maximal d'entrées réduit à 3000 par soucis de temps de calcul)
  for (n = 1000; n <= 3000; n += 2) {
  
        // Mesure du temps de calcul avec la structure de table de hachage pour n premières lignes
        biblio_table = charger_n_entreesH("GdeBiblio.txt", n);
        temps_initial1 = clock();
        b1 = recherche_identiquesH(biblio_table);
        temps_final1 = clock();
        temps_cpu_table = ((double)(temps_final1 - temps_initial1)) / CLOCKS_PER_SEC;

        // Mesure du temps de calcul avec la structure de liste chaînée pour n premières lignes
        biblio_liste = charger_n_entrees("GdeBiblio.txt", n);
        temps_initial2 = clock();
        b2 = recherche_identiques(biblio_liste);
        temps_final2 = clock();
        temps_cpu_liste = ((double)(temps_final2 - temps_initial2)) / CLOCKS_PER_SEC;
      
        fprintf(f, " %d %f %f \n", n,  temps_cpu_table, temps_cpu_liste);

    }
  liberer_biblioH(b1);
  liberer_biblio(b2);
  liberer_biblio(biblio_liste);
  liberer_biblioH(biblio_table);
  
  fclose(f);

    return 0;
}
 

