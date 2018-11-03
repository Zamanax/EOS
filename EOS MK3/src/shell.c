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
    print("\n> ");         //petit curseur
    read = readStr();  //pour récupérer les entrées utilisateur

    int mots = compter(read);   //appel de la fonction pour compter les mots
    traitement(read, mots); //on envois l'entré dans la foncction qui détectera et executera la commande
  }
}

void traitement(char str[], int mots) {            //fonction qui met en forme la commande
  char * command[2];                  // array contenant les mots entrés (max 6 mots)
  if (str[0] == '\0' || str[0] == ' '){                //si l'utilisateur a rien entré, on passe
    return;
  }

  /*char *temp[20] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};      //variable temporaire qui va stocker chaque mots avant de les atribuer
  int i = 0, j = 0, k = 0;
  for (int i = 0; str[i] != '\n'; i++)                 //boucle pour entrer chaques mots dans la variable command
    {
        if (str[i] != ' ') {
		temp[j] = str[i];
	}
        else{
         command[k] = temp;
         char *temp = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	 k ++;
	 j = 0;
        }
    }*/
command[1] = strchr(str, 32);
char *temp[10];
int len = strlength(str) - strlength(command[1]);
if (command[1] != NULL){
for (int i = 0; (str[i] != ' ') || (i < len); i++){
 temp[i] = str[i];
}
}
command[0] = *temp;
if (command[0] = NULL) command[0] = command[1];

print("\n## debug ##\npremier mot: '");
print(command[0]);
print("'\nreste: '");
print(command[1]);
print("'\n## Fin ##\n");

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

  if (strEql(command[0], "exit") || strEql(command[0], "sortie") ){        // commande pour arreter le shell
    shell = 0;
    print("\narret\n");
  }

  else if (strEql(command[0], "echo")){                          // commande pour affichier un message
    for (int j = 1; j < mots; j++){
      print(command[j]);
    }
   print("\naffiche\n");
  }

  else if(strEql(command[0], "help") || strEql(command[0], "aide")) {       //commande d'aide
      print("\n");
      print("exit/sortie   | Commande pour quitter le shell\n");
      print("echo          | Commande pour afficher quelque chose\n");
      print("help/aide     | Commande pour afficher l'aide\n");
      print("pause         | Commande pour faire une pause dans le shell\n");
      print("clear/effacer | Commande pour effacer l'ecran\n");
  }

  else if (strEql(command[0], "pause")){                          // commande pour stopper le shell
    print("Appuyez sur Entree pour continuer : ");
print("pas hyper fonctionnel");
  }
  
  else if (strEql(command[0], "clear") || strEql(command[0], "effacer")){
    clearScreen();
  }
  else print("\nCommande non-reconnue!\nFaites help ou aide pour obtennir une liste des commades disponibles\n");
}
