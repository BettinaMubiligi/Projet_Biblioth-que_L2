//par Beeverly Gourdette et Bettina Mubiligi

#ifndef BIB
#define BIB

typedef struct livre {
    int num ;
    char * titre ;
    char * auteur ;
    struct livre * suiv ;
} Livre ;

typedef struct { /* Tete fictive */
    Livre * L ; /* Premier element */
} Biblio ;

Livre* creer_livre(int num,char* titre,char* auteur);
void liberer_livre(Livre* l);
Biblio* creer_biblio();
void liberer_biblio(Biblio* b) ;
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur);
Biblio *recherche_identiques(Biblio *b);
void afficher_bibli (Biblio * b);
void suppr (Biblio * b, int num, char * titre, char * aut);
Livre * recherche_titre (Biblio * b,char * t);
Biblio * recherche_aut (Biblio * b, char * aut);
void affiche_livre (Livre * l);
void fusion( Biblio *b1, Biblio *b2);
Livre * recherche_num (Biblio * b,int numero);


#endif