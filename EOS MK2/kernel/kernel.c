#include "/home/zamani/Documents/WorkspaceRepo/ISN/OS/EOS MK2/drivers/ports.h"

void main() {
  port_byte_out(0x3d4, 14); // demande à VGA le highbyte du curseur
  int position = port_byte_in(0x3d5); //adresse de retour de VGA
  position = position << 8; //on décale le highbyte pour l'utiliser

  port_byte_out(0x3d4, 15); // demande du lowbyte
  position += port_byte_in(0x3d5);

  int offset_from_vga = position * 2; //valeur du curseur sans VGA

  char *vga = 0xb8000; //adresse mémoire de VGA
  vga[offset_from_vga] = 'X'; //charactere à imprimer
  vga[offset_from_vga+1] = 0x0f; //couleur blanc sur noir
}
