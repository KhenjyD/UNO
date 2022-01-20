#include "uno.h"

carte_t * choixCarte(liste_t * hand, int choix)
{
	carte_t * tmp = (carte_t*)malloc(sizeof(carte_t));
	tmp = hand->first;
	for (int i = 0; i < choix; ++i)
	{
		tmp = tmp->next;
	}

	carte_t * carteChoisie = (carte_t*)malloc(sizeof(carte_t));
	carteChoisie = tmp;

	return carteChoisie;
}

int joue(joueur_t player,pile_t * defausse,pile_t * deck)
{
    int choix;
    int valide;
    carte_t * carteChoisie = (carte_t *)malloc(sizeof(carte_t));
    carte_t * new = (carte_t *)malloc(sizeof(carte_t));


    valide = verif(player.main,defausse);
    afficheDefausse(defausse);

    while(carteChoisie->jouable == 0)
    {
        if (valide == 0)
        {
            printf("Aucune carte jouable. Vous piochez une carte.\n");
            remplissage(deck,defausse);
            pushList(player.main,pop(deck));
            sleep(1);
            return 0;
        }

        printf("Choisissez une carte: ");
        scanf("%d", &choix);
        while(choix > length(player.main))
        {
            printf("Vous n'avez que %d carte(s), entrez à nouveau: ",length(player.main));
            scanf("%d",&choix);
        }

        carteChoisie = choixCarte(player.main,choix-1);
        printf("Vous avez joué: ");
        affiche_carte(carteChoisie);

        if (carteChoisie->jouable == 0)
        {
            printf("Cette carte n'est pas jouable. Choisissez-en une autre.\n");
        }
        else
        {
        	new = new_carte(carteChoisie->color,
        				carteChoisie->type,
        				carteChoisie->num,
        				carteChoisie-> jouable);
            push(defausse,new);
            supprimerCarte(player.main,carteChoisie);
            printf("\n\n");
            return 1;
        }
    }
}
