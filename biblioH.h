//par Beeverly Gourdette et Bettina Mubiligi

#ifndef BIBH
#define BIBH


typedef struct livreh {
    int clef ;
    int num ;
    char * titre ;
    char * auteur ;
    struct livreh * suivant ;
} LivreH ;

typedef struct table {
    int nE ; 
    int m ; 
    LivreH ** T ;
} BiblioH ;


int fonctionClef(char* auteur);
void enregistrer_biblioH(BiblioH *b, char * nom_fic);
BiblioH * charger_n_entreesH(char * nom_fic, int n);
LivreH* creer_livreH(int num,char* titre,char* auteur);
void liberer_livreH(LivreH* l);
BiblioH* creer_biblioH(int m);
void liberer_biblioH(BiblioH* b) ;
void inserer(BiblioH* b,int num,char* titre,char* auteur);
BiblioH *recherche_identiquesH(BiblioH *b);
void affiche_biblioH (BiblioH * b);
void supprH (BiblioH * b, int num, char * titre, char * aut);
LivreH * recherche_titreH (BiblioH * b,char * t);
BiblioH * recherche_auteurH (BiblioH * b, char * aut);
void affiche_livreH (LivreH * l);
LivreH * recherche_numH (BiblioH * b,int numero);
int fonctionHachage(int cle, int m);
void fusionH (BiblioH * b1, BiblioH * b2);

#endif
