#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listes.h"
#include "arbres.h"
#include "table.h"
#include "arbresphylo.h"
#include "especes.h"

int DEBUG = 0;

void vider_buffer(){
	char c= 0;
	while (c != '\n'&& c!= EOF) c= getchar();
}

int open(arbre * mon_arbre){
  FILE * f ;
  printf("Entrez le chemin du fichier arbre à ouvrir : \n");
  char nom[1000]={0};
  fscanf(stdin, "%s", nom);
  vider_buffer();
  f = fopen(nom,"r");
  if (f==NULL){
      fprintf (stderr, "Erreur à l'ouverture du fichier `%s'\n", nom);
      perror (nom);
      return 0;
  }

  (*mon_arbre) = lire_arbre (f);
  fclose(f);
  return 1;
}

int opentable(arbre * mon_arbre){
  printf("Entrez le chemin du fichier tableau à ouvrir : \n");
  char nom[1000]={0};
  fscanf(stdin, "%s", nom);
  vider_buffer();
  table_de_correspondance T;
  if (!(lire_csv(nom, &T))) return 0;
  sequence_int lignes;
  for (int i = 0; i< T.noms_esp.longueur ; i++){
    lignes.tab[i]=i;
    lignes.longueur ++;
  }
  sequence_int colonnes;
  for (int i = 0; i< T.noms_car.longueur ; i++){
    colonnes.tab[i]=i;
    colonnes.longueur ++;
  }

  faire_arbre(lignes,colonnes,T, mon_arbre);
  return 1;

}

int ajoutesp(arbre * mon_arbre){
  printf("Entrez le nom de l'espèce à ajouter :\n");
  char espaj[100];
  fscanf(stdin,"%s", espaj);
  vider_buffer();
  printf("Entrez le nombre de caractéristiques de l'espèce :\n");
  int nb;
  fscanf(stdin,"%d", &nb);
  vider_buffer();
  espc espece_a_ajouter = creer_espece(espaj);
  char car[100];
  printf("Entrez les caractéristiques :\n");
  for (int i =0; i<nb ; i++){
    printf("#%d : ", i+1);
    fscanf(stdin, "%s",car);
    vider_buffer();
    ajouter_debut(car, &(espece_a_ajouter.caract));
  }
  return (ajouter_espece(mon_arbre,espece_a_ajouter));
}

int recherchesp(arbre mon_arbre){
  char esp[100];
  printf("Entrez l'espece a rechercher\n");
	scanf("%s", esp);
  vider_buffer();
  espc espece = creer_espece(esp);
	if (!rechercher_espece(mon_arbre, &espece)) return 0; //Met dans la strcture espece la liste des caractéristiques de l'espèce recherchée.)
	printf("Les caractéristiques de cet animal sont : \n");
	cellule_t* courant;
	courant = (espece.caract).tete;
	while(courant != NULL){ // Affiche la séquence.
		printf("%s / ", courant->valeur);
		courant = courant -> suivant;
	}
	printf("\n");
  return 1;
}

//fonction reccursive pour ecrire les noeuds de l'arbre dans le fichier.
void inscription_arbre_fichier(arbre a, FILE *f){ 
  if(a!=NULL){ 
    fprintf(f,"%s",a->valeur.nom); 
    if(a->gauche !=NULL){ 
        fprintf(f,"\n  ("); 
        inscription_arbre_fichier(a->gauche,f); 
        fprintf(f,")\n"); 
    } 
    if(a->droit !=NULL){ 
      fprintf(f,"  ("); 
      inscription_arbre_fichier(a->droit,f); 
      fprintf(f,")\n  "); 
    } 
  }
 
} 

  

int ecrire(arbre a){ 
  char nom_fichier[100];


  fprintf(stdout, "Saisissez le nom du fichier à créer/écraser.\n");
  fscanf(stdin, "%s", nom_fichier);

  FILE *f =fopen(nom_fichier,"w");

  fprintf(f,"("); 
  inscription_arbre_fichier(a,f); 
  fprintf(f,")"); 
  fclose(f); 
  
  char str[150];
  strcpy(str, "indent ");
  strcat(str, nom_fichier);
  system(str);
  return 1;
}


int main(int argc, char* argv[]) {
  arbre mon_arbre = NULL;
  if (argc > 2) { // trop d'arguments
      fprintf (stderr, "Usage:  %s [-d] <fichier>\n", argv[0]);
      fprintf (stderr, "\n");
      fprintf (stderr, "Options:\n");
      fprintf (stderr, "\t-d\tmode debug\n");
      exit(1);
  }
  else { // on ouvre le fichier passé en argument s'il existe
      if (argc == 2){
        FILE * f ;
        f = fopen(argv[1],"r");
        if (f==NULL) {
            fprintf (stderr, "Erreur à l'ouverture du fichier `%s'\n", argv[1]);
            perror (argv[1]);
        }

      mon_arbre = lire_arbre (f);
      fclose(f);
      free(f);
      }
  }



  char commande='n';
  char reponse[100];
  while(commande!='s'){
    printf("\n# o : Ouvrir un arbre\n# u : Ouvrir une table\n# p : Afficher l'arbre\n# a : Ajouter une espèce à l'arbre\n# r : Rechercher une espèce dans l'arbre\n# w : Écrire l'arbre dans un fichier\n# s : Terminer le programme\n");
    fscanf(stdin,"%s", reponse);
    commande = reponse[0];
    vider_buffer();
    switch(commande){
      case 'o' :
        if (open(&mon_arbre)) printf("Ouverture réussie !\n" );
        break;
      case 'u' :
        if (opentable(&mon_arbre)) printf("Ouverture réussie !\n" );
        break;
      case 'p':
        affiche_arbre (mon_arbre);
        printf ("Hauteur de l'arbre: %d\n", hauteur (mon_arbre));
        break;
      case 'a' :
        if (ajoutesp(&mon_arbre)) printf("Ajout réussi !\n" );
        break;
      case 'r' :
        if (!recherchesp(mon_arbre)) printf("L'espèce est introuvable.\n" );
        break;

      case 'w' :
        if (ecrire(mon_arbre))  printf("Enregistrement réussi.\n" );
        break;
      default : break;
    }
  }
  return 0;
}
