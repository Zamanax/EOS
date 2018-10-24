#include <stdio.h>      //imports
#include <string.h>
#define LENENTRY 50 // Constante contenant la longeur maximale pour qu'une séquence soit interprétée

void viderBuffer();
void traitement(char *, int);  //détection des commandes
int compter(char *);
void detecter(char **, int);

int shell = 1;          //variable boucle infinie

int main(){               //fct main

  while (shell) {         //Boucle infinie
    char read[LENENTRY];       //commande entrée par l'utilisateur
    char *posentre = NULL;
    printf("> ");         //petit curseur
    fgets(read, LENENTRY, stdin);  //pour récupérer les entrées utilisateur

    posentre = strchr(read, '\n');  //remplaçage du \n par le caractère de fin de chaine pour améliorer les performances
    if (posentre != NULL){
      * posentre = '\0';
    }
    else{
      viderBuffer(1);
    }
    int mots = compter(read);   //appel de la fonction pour compter les mots
    traitement(read, mots); //on envois l'entré dans la foncction qui détectera et executera la commande
  }
  return 0;
}

void viderBuffer(int mess) // fonction pour enlever les caractère si l'entrée éxcède la longeur de "LenEntry"
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
    if (mess){
      printf("Une partie de l'entree a ete supprime car trop longue.\
      \nPour plus de details, merci de contacter votre fournisseur.\n\n");
    }
}

void traitement(char str[], int mots) {            //fonction qui met en forme la commande
  char * command[mots];                  // array contenant les mots entrés (max 6 mots)
  int len = strlen(str);               //on change la longeur à la longeur de l"entrée (optimisation) et on initialise k
  if (str[0] == '\0' || str[0] == ' '){                //si l'utilisateur a rien entré, on passe
    return;
  }

  char* temp = strtok(str, " ");      //token qui va appeler chaque éléments séparés par un espace

  int i = 0;
  while(temp != NULL)                 //boucle pour entrer chaques mots dans la variable command
    {
        command[i] = temp;
        i++;
        temp = strtok(NULL, " ");
    }
    detecter(command, mots);
}

int compter(char * str){                              //fonction pour compter le nombre de mots
  int nombre = 1;
  for (int a = 0; a < strlen(str); a++){
    if (str[a] == ' '){
      nombre ++;
    }
  }
  return nombre;
}

void detecter(char **command, int mots){                          //fonction pour lancer une commande suivant l'entrée utilisateur
  char commandes[8][200] = {"exit/sortie", "Commande pour quitter le shell", "echo", "Commande pour afficher quelque chose", "help/aide", "Commande pour afficher l'aide",\
  "pause", "Commande pour faire une pause dans le shell"};      //la liste des commandes

  if ( !strcmp(command[0], "exit") || !strcmp(command[0], "sortie") ){        // commande pour arreter le shell
    shell = 0;
    printf("arret");
  }

  else if (!strcmp(command[0], "echo")){                          // commande pour affichier un message
    for (int j = 1; j < mots; j++){
      printf("%s ", command[j]);
    }
  }

  else if(!strcmp(command[0], "help") || !strcmp(command[0], "aide")) {       //commande d'aide
    for (int i = 0; i < 8; i +=2){
      printf("%s | %s \n", commandes[i], commandes[i+1]);
    }
  }

  else if (!strcmp(command[0], "pause")){                          // commande pour stopper la shell
    printf("Appuyez sur Entree pour continuer : ");
    char pause[2];
    fgets(pause, 2, stdin);
    viderBuffer(0);
  }
  else printf("Commande non-reconnue!\nFaites help ou aide pour obtennir une liste des commades disponibles\n");

  printf("\n");
}
