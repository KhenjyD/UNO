#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<unistd.h>
#define size 108

struct Carte
{
	int color;
	int type;
	int num;
	int jouable;
	struct Carte * next;
/* 	colors : 0.rouge ; 1.bleu ; 2.vert ; 3.jaune. 
	types :	0.simple ; 1.draw 2 ; 2.reverse ; 3.skip, 4.draw 4, 5.joker.
*/
};
typedef struct Carte carte_t;

struct liste{
    carte_t * first;
};
typedef struct liste liste_t;

struct pile
{
    carte_t * tab[size];
    int top;
};
typedef struct pile pile_t;

struct joueur
{
	int id;
	liste_t * main;
};
typedef struct joueur joueur_t;

struct TabJoueur{
    int nbJoueurs;
    joueur_t * player;
};
typedef struct TabJoueur TabJoueur_t;


//Cartes
void push(pile_t *deck, carte_t * carte);
carte_t * pop(pile_t *deck);
carte_t * new_carte(int color, int type, int num, int jouable);
void init(pile_t *deck);
void affiche_carte(carte_t * carte);
void affiche_all(pile_t *tableau);
void melange(pile_t* tableau, int indice);
carte_t *defausse(pile_t* defausse,pile_t * deck);
void afficheDefausse(pile_t * defausse);
void test(carte_t *from, carte_t *to );
int verif(liste_t *main, pile_t *defausse);
int activation(pile_t *pioche, pile_t * defausse, TabJoueur_t tab, int i);
void remplissage(pile_t * deck, pile_t * defausse);

//Joueurs
TabJoueur_t createTab(int nb);
joueur_t creerJoueur(int id);
void afficherJoueur(TabJoueur_t tab);
void distribution(TabJoueur_t tab, pile_t * deck);
liste_t * creatList();
void pushList(liste_t *hand, carte_t * carte);
void AfficheMain(liste_t* main);
void supprimerCarte(liste_t* hand,carte_t* a);
int length(liste_t * a);
void reverse(TabJoueur_t tab);

//Action
carte_t * choixCarte(liste_t * hand, int choix);
int joue(joueur_t player,pile_t * defausse,pile_t * deck);
