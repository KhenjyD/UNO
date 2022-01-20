#include "uno.h"

TabJoueur_t createTab(int nb)
{
	TabJoueur_t tab;
	int i, id = 1;

	tab.player = (joueur_t *)malloc(nb * sizeof(joueur_t));
	assert(tab.player);
	tab.nbJoueurs = nb;

	for (i = 0; i < tab.nbJoueurs; ++i)
	{
		tab.player[i] = creerJoueur(id);
		id++;
	}
	return tab;
}

joueur_t creerJoueur(int id)
{
	joueur_t new;
	new.id = id;
	new.main = creatList();

	return new;
}

void afficherJoueur(TabJoueur_t tab)
{
	int i;
	joueur_t player;

	for (i = 0; i < tab.nbJoueurs; ++i)
	{
		printf("ID: %d\n", tab.player[i].id);
		AfficheMain(tab.player[i].main);
		printf("\n");
	}
}

void distribution(TabJoueur_t tab, pile_t * deck){
	int i =0;
	int j =0;
	for(i=0; i < tab.nbJoueurs;i++){
		for(j=0;j<7;j++){
			pushList(tab.player[i].main,pop(deck));
		}
	}
}

liste_t * creatList()
{
	liste_t * l = (liste_t *)malloc(sizeof (liste_t));

	l->first = NULL;

	return l;
}

void pushList(liste_t *hand, carte_t * carte)
{
	if (hand->first == NULL)
	{
		hand->first = carte;
		return;
	}
	carte->next = hand->first;
	hand->first = carte;
}

void AfficheMain(liste_t* main)
{
	int pos = 1;
    if(main->first == NULL){
        printf("liste vide\n");
        return;
    }
    carte_t * tmp = main->first;
    while(tmp){
    	printf("%d - ", pos);
        affiche_carte(tmp);
        tmp = tmp ->next;
        pos++;
    }
    printf("\n");
}

void supprimerCarte(liste_t* hand,carte_t* a)
{
	if(a==NULL)
    	return;

  	carte_t* tmp = hand->first;
  	carte_t* tmp2;
  	if (tmp == a)
  	{
  		hand->first = hand->first->next;
  		return;
  	}

  	while (tmp->next != a){
  		tmp2 = tmp;
    	tmp = tmp->next;
  	}

  	if(tmp->next == NULL){
  		tmp = tmp2;
    	return;
  	}
 
	tmp->next = a->next;
	
}

int length(liste_t * a){
    carte_t * tmp = a->first;
    int count = 0;
    if(!tmp)
        return count;
    else{
        while(tmp){
            count++;
            tmp = tmp->next;
        }
        return count;
    }
}

void reverse(TabJoueur_t tab1)
{
	int i, j;
	int nbr = tab1.nbJoueurs;
	TabJoueur_t tab2;  

	tab2.player = (joueur_t *)malloc(nbr * sizeof(joueur_t));

	for (i = nbr - 1, j = 0; i >= 0; i--, j++)
        tab2.player[j] = tab1.player[i];

    for (i = 0; i < nbr; i++)
        tab1.player[i] = tab2.player[i];
}