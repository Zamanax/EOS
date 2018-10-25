#include "../drivers/screen.h"

void main() { //fonction principale de l'os
  clear_screen();
  char test[2] = {'e', '\0'};  //pour le test, on créé une vairable "à la main"
  fprint(test, 2, 1);         //fonctionne
  kprint_at(test, 2, 3);      //rien
  
  print_char('d', 2, 5, 0x0a); //fonctionne
  //kprint_at("d", 3, 1);
  //kprint_at("Ce texte est sur plusieurs lignes", 75, 10);
  //kprint_at("Il y a un retour a\n la ligne", 0, 20);
  //kprint("Ce texte à un re\ntour a la ligne");
  //kprint_at("Que se passe-t-il quand on n'a plus de place ?", 45, 24);
}
