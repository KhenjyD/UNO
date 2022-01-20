#include "uno.h"

int main()
{
    int nb, i=0, victoire = 0;
    int start = 0, active, jouer;
    srand(time(NULL));
    pile_t *deck = (pile_t*)malloc(sizeof(pile_t));
    pile_t *defaussage = (pile_t*)malloc(sizeof(pile_t));
    init(deck);
    
    system("clear");

    printf("Nombre de joueurs: ");
    do{
        scanf("%d",&nb);

        if(nb > 4){
            printf("Trop de joueurs !\n");
            printf("Rentrez votre nombre à nouveau (4 max): ");
        }
        if(nb <= 1){
            printf("Trop peu de joueurs, vous devez être au minimum 2 !\n");
            printf("Rentrez votre nombre à nouveau (2 min): ");
        }
    }while(nb <= 1 || nb > 4);

    melange(deck,size);
    TabJoueur_t tab = createTab(nb);
    distribution(tab, deck);
    defausse(defaussage,deck);

    system("clear");

    while(victoire == 0)
    {
    	for (i = 0; i < nb; ++i)
    	{
    		if(start == 0)
	    	{
	    		active = activation(deck,defaussage,tab,0);
	    		if (active == 3)
	    		{
	    			active = 0;
	    			reverse(tab);
	    			i == nb;
	    		}
	    		start = 1;
	    	}

    		if (active == 1)
    		{
    			active = 0;
    			printf("\nTour du joueur %d passé.\n", tab.player[i].id);
    			i++;
    			if (i >= tab.nbJoueurs)
		    	{
		    		i = 0;
		    	}
		    	sleep(1);
    		}
    		else if(active == 2)
    		{
    			active = 1;
    			printf("\nTour du joueur %d passé.\n", tab.player[i].id);
    			if (i >= tab.nbJoueurs)
		    	{
		    		i = 0;
		    	}
		    	sleep(1);
		    	continue;
    		}
    		else if (active == 3)
    		{
    			reverse(tab);
    			active = 0;
    			if (tab.nbJoueurs == 3)
    			{
    				if (i == 1)
    				{
    					i--;
    				}
    				else if(i == 0)
    				{
    					i++;
    				}
    			}
    			else if(tab.nbJoueurs == 4)
    			{
    				if (i == 1 || i == 3)
    				{
    					i--;
    				}
    				else if(i == 0 || i == 2)
    				{
    					i++;
    				}
    			}

    		}
    		
    		printf("\nJoueur %d\n", tab.player[i].id);
    		AfficheMain(tab.player[i].main);
    		jouer = joue(tab.player[i],defaussage,deck);
    		if (jouer == 0)
    		{
    			continue;
    		}
    		active = activation(deck,defaussage,tab,i+1);
 			
    		if(length(tab.player[i].main) <= 0)
    		{
            	printf("Victoire du joueur %d",tab.player[i].id);
        	    victoire = 1;
        	    break;
        	}
        	sleep(1);
    	}
    }

    printf("\n\n");
    
    return 0;
}