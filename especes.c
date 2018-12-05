#include "especes.h"
#include <string.h>
espc creer_espece(char *nom){
  espc espece;
  strcpy(espece.nom, nom);
  (espece.caract).tete= NULL;
  return espece;
}

int est_espece(val_n esp){
  return esp.nature==ESPECE; 
}
