#include "uno.h"

void push(pile_t *deck, carte_t * carte) {
	if (deck->top >= size - 1)
	    return;
	deck->top++;
	deck->tab[deck->top] = carte;
}

carte_t * pop(pile_t *deck) {
	if (deck->top == -1)
		return;
	carte_t * carte = (carte_t *)malloc(sizeof(carte_t));
	carte = deck->tab[deck->top];
	deck->top--;

	return carte;
}

carte_t * new_carte(int color, int type, int num, int jouable){
	carte_t * new = (carte_t *)malloc(sizeof(carte_t));
	new->color=color;
	new->type=type;
	new->num=num;
	new->jouable = jouable;
	return new;
}

void init(pile_t *deck){
	int i,j,k,m,n,oui = -1;

	//Boucle pour la couleur
	for(i=0;i<4;i++){
		push(deck,new_carte(i,0,0,0));
		//Boucle pour les numéros
		for(j=1;j<10;j++){
			//Boucle pour creer 2 cartes par numero sauf le 0
			for(k=0;k<2;k++){
				push(deck, new_carte(i,0,j,0));
			}
		}
		//Boucle pour creer les cartes special
		for(n=1;n<4;n++){
			//Boucle pour doubler les cartes special
			for(m=0;m<2;m++){
				push(deck, new_carte(i,n,oui,0));
				oui--;
			}
		}
		//Creer joker et +4
		push(deck, new_carte(0,5,oui,0));
		oui--;
		push(deck, new_carte(0,4,oui,0));
		oui--;
	}
}

void affiche_carte(carte_t * carte){
	if(carte->type==0 && carte->color==0 ){
		printf("Rouge : %d\n",carte->num);
	}else if(carte->type==0 && carte->color==1 ){
		printf("Bleu : %d\n",carte->num);
	}else if(carte->type==0 && carte->color==2 ){
		printf("Vert : %d\n",carte->num);
	}else if(carte->type==0 && carte->color==3 ){
		printf("Jaune : %d\n",carte->num);
	}
// les draw +2
	else if(carte->type==1 && carte->color==0 ){
		printf("Rouge : pioche +2\n");
	}else if(carte->type==1 && carte->color==1 ){
		printf("Bleu : pioche +2\n");
	}else if(carte->type==1 && carte->color==2 ){
		printf("Vert : pioche +2\n");
	}else if(carte->type==1 && carte->color==3 ){
		printf("Jaune : pioche +2\n");
// Les reverse
	}else if(carte->type==2 && carte->color==0 ){
		printf("Rouge : reverse\n");
	}else if(carte->type==2 && carte->color==1 ){
		printf("Bleu : reverse\n");
	}else if(carte->type==2&& carte->color==2 ){
		printf("Vert : reverse\n");
	}else if(carte->type==2 && carte->color==3 ){
		printf("Jaune : reverse\n");
// Les skip
	}else if(carte->type==3 && carte->color==0 ){
		printf("Rouge : skip\n");
	}else if(carte->type==3 && carte->color==1 ){
		printf("Bleu : skip\n");
	}else if(carte->type==3 && carte->color==2 ){
		printf("Vert : skip\n");
	}else if(carte->type==3 && carte->color==3 ){
		printf("Jaune : skip\n");
// les jokers et les draw +4	
	}else if(carte->type==4){
		printf("Carte : draw +4\n");
	}else if(carte->type==5){
		printf("Carte : Joker\n");
	}
}

void affiche_all(pile_t *tableau){
    int i =0;
    for(i=0;i<=tableau->top;i++){
        printf("%d: ",i);
        affiche_carte(tableau->tab[i]);
    }
}

void melange(pile_t* tableau, int indice){
    int i=0;
    int ra;
    carte_t * tmp = (carte_t *)malloc(sizeof(carte_t));
    for(i=0;i<indice;i++){
        tmp=tableau->tab[i];
        do{
            ra=rand()% tableau->top;
        }while(ra == i );
        tableau->tab[i]=tableau->tab[ra];
        tableau->tab[ra]=tmp;
    }
}

carte_t *defausse(pile_t* defausse,pile_t * deck){
    carte_t * carte = malloc(sizeof(carte_t));
    carte = pop(deck);
    push(defausse,carte);
}

void afficheDefausse(pile_t * defausse){
    printf("Defausse - ");
    affiche_carte(defausse->tab[defausse->top]);
    printf("\n\n");
}

void test(carte_t * from, carte_t * to )
{
	/* 	colors : 0.rouge ; 1.bleu ; 2.vert ; 3.jaune. 
		types :	0.simple ; 1.draw 2 ; 2.reverse ; 3.skip, 4.draw 4, 5.joker.
	*/
	if(from->type == 4 || from->type == 5){
		from->jouable = 1;
	}else if(from->num == to->num || from->color==to->color){
		from->jouable = 1;
	}else if(from->type == to->type && from->type >0){
		from->jouable = 1;
	}else{
		from->jouable = 0;
	}
}

int verif(liste_t *main, pile_t *defausse)
{
	carte_t * tmp = main->first;
	int valide = 0;
	while(tmp)
	{
		test(tmp,defausse->tab[defausse->top]);
		if (tmp->jouable == 1)
		{
			valide = 1;
		}
		tmp = tmp->next;
	}
	return valide;
}

//types :	0.simple ; 1.draw 2 ; 2.reverse ; 3.skip, 4.draw 4, 5.joker.
int activation(pile_t *pioche, pile_t * defausse, TabJoueur_t roster,int i){
    if(defausse->tab[defausse->top]->type == 1){ //draw +2
    	if (i >= roster.nbJoueurs)
    	{
    		i = 0;
    	}
    	else if (i < 0)
		{
			i = roster.nbJoueurs;
		}
        pushList(roster.player[i].main,pop(pioche));
        pushList(roster.player[i].main,pop(pioche));
        return 1;
    }else if(defausse->tab[defausse->top]->type == 2){ //reverse
    	return 3;
    }else if(defausse->tab[defausse->top]->type == 3){ //skip
    	return 2;
    }else if(defausse->tab[defausse->top]->type == 4){ //draw +4
    	if (i >= roster.nbJoueurs)
    	{
    		i = 0;
    	}
    	else if (i < 0)
		{
			i = roster.nbJoueurs;
		}
        pushList(roster.player[i].main,pop(pioche));
        pushList(roster.player[i].main,pop(pioche));
        pushList(roster.player[i].main,pop(pioche));
        pushList(roster.player[i].main,pop(pioche));
        int new_color;
        printf("choisir une couleur: 0->rouge; 1->bleu; 2->vert; 3->jaune: ");
        scanf("%d",&new_color);
        defausse->tab[defausse->top]->color= new_color;
        return 1;
    }else if(defausse->tab[defausse->top]->type == 5){ //joker
        int new_color1;
        printf("choisir une couleur: 0->rouge; 1->bleu; 2->vert; 3->jaune: ");
        scanf("%d",&new_color1);
        defausse->tab[defausse->top]->color= new_color1;
        return 0;
    }
}

void remplissage(pile_t * deck, pile_t * defausse)
{
	int top = defausse->top;
	if(deck->top == -1)
	{
	    carte_t * a = (carte_t *) malloc(sizeof(carte_t));
	    a = pop(defausse);
	    for(int i = 0; i < top; i++){
	        push(deck,pop(defausse));
	    }
	    push(defausse,a);
	    melange(deck,size);
	}
}
