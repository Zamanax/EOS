#include "/home/zamani/Documents/WorkspaceRepo/ISN/OS/EOS MK2/drivers/screen.h"

void main() { //ah montre le fichier
  clear_screen();
  fprint("x", 20, 20);
  print_char('d', 2, 5, 0x0f);
  kprint_at("X", 85, 85);
  //kprint_at("Ce texte est sur plusieurs lignes", 75, 10);
  //kprint_at("Il y a un retour a\n la ligne", 0, 20);
  //kprint("Ce texte à un re\ntour a la ligne");
  //kprint_at("Que se passe-t-il quand on n'a plus de place ?", 45, 24);
}
