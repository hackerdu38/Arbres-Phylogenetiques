#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "arbresphylo.h"

int DEBUG = 0;

int main(int argc, char* argv[])
{
  char *fichier = NULL;
	char esp[100];

    if (argc < 2) {
        fprintf (stderr, "Usage:  %s [-d] <fichier>\n", argv[0]);
        fprintf (stderr, "\n");
        fprintf (stderr, "Options:\n");
        fprintf (stderr, "\t-d\tmode debug\n");
        exit(1);
    }
    else {
        int arg=1;

        while (arg < argc) {
            if (!strncmp(argv[arg], "-d", 2)) {
                DEBUG = 1;
                arg++;
                continue;
            }
            if (fichier == NULL) {
                fichier = argv[arg];
                arg++;
                continue;
            } else {
                fprintf (stderr, "Trop de fichiers sur la ligne de commande !\n");
                exit(1);
            }
        }
    }

    debug ("Ouverture de %s\n", fichier);
    FILE* f = fopen (fichier, "r");
    if (!f) {
        fprintf (stderr, "Erreur à l'ouverture du fichier `%s'\n", fichier);
        perror (fichier);
        exit(1);
    }
    
  //printf("Que voulez-vous faire ? \n   [1] : afficher l'arbre\n   [2]afficher la hauteur" 
  //pourquoi ne pas clarifier un peu ?
  
  arbre mon_arbre = lire_arbre (f);
	affiche_arbre (mon_arbre);    
  printf ("Hauteur de l'arbre: %d\n", hauteur (mon_arbre));
  
  
  //caractérististiques sur une profondeur.
  int pr;
	liste_t* caracts = malloc(sizeof(*caracts));
  printf("entrez la profondeur dont vous voulez obtenir les caractéristiques : (entier)\n");
	scanf("%d", &pr);
	
	// récupération des caractéristiques dans caracts
	caract_profondeur(mon_arbre, pr, caracts); 
	
	printf("Les caractéristiques à la profondeur %d sont : \n", pr);
	cellule_t* caract_courant;
	caract_courant = caracts->tete;
	while(caract_courant != NULL){ //Affiche la séquence.
		printf("%s / ", caract_courant->valeur);
		caract_courant = caract_courant -> suivant;
	}
	printf("\n");
	
	
	
	

    //arbre mon_arbre = lire_arbre (f);

	affiche_arbre (mon_arbre);

    printf ("Hauteur de l'arbre: %d\n", hauteur (mon_arbre));


	printf("Entrez l'espece a rechercher\n");
	scanf("%s", esp);
	//espc* espece =(espc *)malloc(sizeof(espc));
  espc espece = creer_espece(esp);
	rechercher_espece(mon_arbre, &espece); //Met dans la séquence seq la liste des caractéristiques de l'espèce recherchée.
	printf("Les caractéristiques de cet animal sont : \n");
	cellule_t* courant;
	courant = (espece.caract).tete;
	while(courant != NULL){ //Affiche la séquence.
		printf("%s / ", courant->valeur);
		courant = courant -> suivant;
	}
	printf("\n");

  printf("Entrez le nom de l'espèce à ajouter :\n");
  char espaj[100];
  fscanf(stdin,"%s", espaj);
  printf("Entrez le nombre de caractéristiques de l'espèce :\n");
  int nb;
  fscanf(stdin,"%d", &nb);
  espc espece_a_ajouter = creer_espece(espaj);
  char car[100];
  printf("Entrez les caractéristiques :\n");
  for (int i =0; i<nb ; i++){
    printf("#%d : ", i+1);
    fscanf(stdin, "%s",car);
    ajouter_debut(car, &(espece_a_ajouter.caract));
  }
  if (ajouter_espece(&mon_arbre,espece_a_ajouter)) affiche_arbre (mon_arbre);




  return 0;
}
