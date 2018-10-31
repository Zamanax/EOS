#include "../include/shell.h"
#define LENENTRY 50

void viderBuffer();
void traitement(char *, int);  //détection des commandes
int compter(char *);
void detecter(char **, int);
int shell = 1;          //variable boucle infinie

void launch_shell()
{

while (shell) {         //Boucle infinie
    char *read;       //commande entrée par l'utilisateur
    char *posentre = NULL;
    print("> ");         //petit curseur
    read = readStr();  //pour récupérer les entrées utilisateur

    posentre = strchr(read, '\n');  //remplaçage du \n par le caractère de fin de chaine pour améliorer les performances
    if (posentre != NULL){
      * posentre = '\0';
    }
    int mots = compter(read);   //appel de la fonction pour compter les mots
    traitement(read, mots); //on envois l'entré dans la foncction qui détectera et executera la commande
  }
}

void traitement(char str[], int mots) {            //fonction qui met en forme la commande
  char * command[mots];                  // array contenant les mots entrés (max 6 mots)
  int len = strlength(str);               //on change la longeur à la longeur de l"entrée (optimisation) et on initialise k
  if (str[0] == '\0' || str[0] == ' '){                //si l'utilisateur a rien entré, on passe
    return;
  }

  char *temp[30];      //token qui va appeler chaque éléments séparés par un espace

  int i = 0, j = 0, k = 0;
  for (int i = 0; str[i] != '\n'; i++)                 //boucle pour entrer chaques mots dans la variable command
    {
        if (str[i] != '\n') temp[j] = str[i];
        else{
         command[k] = temp;
k ++;
j = 0;
        }
    }
    detecter(command, mots);
}

int compter(char * str){                              //fonction pour compter le nombre de mots
  int nombre = 1;
  for (int a = 0; a < strlength(str); a++){
    if (str[a] == ' '){
      nombre ++;
    }
  }
  return nombre;
}

void detecter(char **command, int mots){                          //fonction pour lancer une commande suivant l'entrée utilisateur
  char commandes[8][200] = {"exit/sortie", "Commande pour quitter le shell", "echo", "Commande pour afficher quelque chose", "help/aide", "Commande pour afficher l'aide",\
  "pause", "Commande pour faire une pause dans le shell"};      //la liste des commandes

  if (strEql(command[0], "exit") || strEql(command[0], "sortie") ){        // commande pour arreter le shell
    shell = 0;
    print("arret");
  }

  else if (strEql(command[0], "echo")){                          // commande pour affichier un message
    for (int j = 1; j < mots; j++){
      print(command[j]);
    }
  }

  else if(strEql(command[0], "help") || strEql(command[0], "aide")) {       //commande d'aide
    for (int i = 0; i < 8; i +=2){
char aff[4] = {commandes[i], '|', commandes[i+1], '\n'};
      print(aff);
    }
  }

  else if (strEql(command[0], "pause")){                          // commande pour stopper la shell
    print("Appuyez sur Entree pour continuer : ");
print("pas hyper fonctionnel");
  }
  
  else if (strEql(command[0], "clear") || strEql(command[0], "effacer")){
    clearScreen();
  }
  else print("\nCommande non-reconnue!\nFaites help ou aide pour obtennir une liste des commades disponibles\n");

  print("\n");
}
