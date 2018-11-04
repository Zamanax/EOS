#include "../include/shell.h"
#define LENENTRY 50

void traitement(char *, int);  //détection des commandes
int compter(char *);
void detecter(char **, int);
int shell = 1;          //variable boucle infinie

void launch_shell()
{

while (shell) {         //Boucle infinie
    char *read;       //commande entrée par l'utilisateur
    char *posentre = NULL;
    print(">> ");         //petit curseur
    read = readStr();  //pour récupérer les entrées utilisateur

    int mots = compter(read);   //appel de la fonction pour compter les mots
    traitement(read, mots); //on envois l'entré dans la foncction qui détectera et executera la commande
  }
}

void traitement(char str[], int mots) {            //fonction qui met en forme la commande
  char * command[2];                                 // array contenant les mots entrés
  command[0] = "          ";                          //on réinitialise la variable command[0]
  if (str[0] == '\0' || str[0] == ' '){                //si l'utilisateur a rien entré, on passe
    print("\n");
    return;
  }

  command[1] = strchr(str, 32);             //on isole la partie a afficher
  if (command[1] != NULL){                    //si la partie n'est pas nulle
   for (int i = 0; str[i] != ' '; i++){       //on rempli command[0]
     command[0][i] = str[i];
   }
  }

  for (int i = 0; i < strlength(command[0]); i++) { //on enlève les éspaces supplémentaires à command[0]
    if (command[0][i] == ' '){
      command[0][i] = '\0';
    }
  }

  if (mots == 1){
    command[0] = command[1]; //si il n'y a qu'une sule commande, elle sera copiée dans command[1], on la copie donc dans command[0]
    command[1] = " VIDE!";   //atribution d'une valeur pour command[1] à afficher
  }

  detecter(command, mots);
}

int compter(char * str){                    //fonction pour compter le nombre de mots
  int nombre = 1;
  for (int a = 0; a < strlength(str); a++){
    if (str[a] == ' '){                     //on compte le nombre d'espaces et on renvois cette valeur
      nombre ++;
    }
  }
  return nombre;
}

void detecter(char **command, int mots){                          //fonction pour lancer une commande suivant l'entrée utilisateur

  if (strEql(command[0], "exit") || strEql(command[0], "sortie") ){        // commande pour arreter le shell
    shell = 0;
    print("\narret\n"); //on affiche seulement arret et on stoppe la boucle
  }

  else if (strEql(command[0], "echo")){                          // commande pour affichier un message
   print("\n->");
   print(command[1]); //affichage du reste de la commande
  }

  else if(strEql(command[0], "help") || strEql(command[0], "aide")) {       //commande d'aide
      print("\n");
      print("exit/sortie   | Commande pour quitter le shell\n");
      print("echo [texte]  | Commande pour afficher quelque chose\n");
      print("help/aide     | Commande pour afficher l'aide\n");
      print("pause         | Commande pour faire une pause dans le shell\n");
      print("clear/effacer | Commande pour effacer l'ecran\n");
  }

  else if (strEql(command[0], "pause")){                          // commande pour stopper le shell
    print("\nAppuyez sur Entree pour continuer : ");
    readStr();
  }

  else print("\nCommande non-reconnue!\nFaites help ou aide pour obtennir une liste des commades disponibles\n");

  if (strEql(command[0], "clear") || strEql(command[0], "effacer")){ //commande pour éffacer l'écran
    clearScreen();
  }
  else print("\n"); //retour à la ligne pour faire beau et aéré
}
