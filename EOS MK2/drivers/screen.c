#include "screen.h"
#include "ports.h"

//header fonctions privées
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char color);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

// FONCTIONS PUBLIQUES
void kprint_at(char *message, int col, int row){
  //si le curseur est négatif
  int offset;
  if (col >= 0 && row >= 0)                           //si trop loin
    offset = get_offset(col, row); //on place l'offset
  else { //si le curseur est négatif, on le replace
    offset = get_cursor_offset();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  int i = 0;
  while (message[i] != 0){
    offset = print_char(message[i++], col, row, WHITE_ON_BLACK); //moment où on print
    row = get_offset_row(offset); //on calcule la place du curseur pour le charactere suivant
    col = get_offset_col(offset);
  }
}
void kprint(char *message){
  kprint_at(message, -1, -1); // kprint remettra une bonne valeur (offset à 0)
}

// FONCTIONS PRIVÉES

/*Fonction noyau du kernel
c est le charactère à imprimer
col est la colonne
row est la ligne

on returne l'offset du prochain caractère
*/
int print_char(char c, int col, int row, char color){
  char *vidmem = (char*) VIDEO_ADDRESS; //adresse mémoire de VGA
  if (!color) color = WHITE_ON_BLACK; //si la color est invalide, elle est mise par défaut

  if (row >= MAX_ROWS || col >= MAX_COLS){
    //si on essaye d'accéder a un caractère trop loin, on renvois une erreur
    vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';    //cette erreur est un E
    vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE; //écrite en rouge sur blanc
    return get_offset(col, row); //on recalcule l'offset et on le renvois
  }

  int offset;
  if (col >= 0 && row >= 0) offset = get_offset(col, row);
  //si la valeur est valide alors on crée l'offset
  else offset = get_cursor_offset();

  if (c == '\n') {
    //code pour le retour à la ligne
    row = get_offset_row(offset);
    offset = get_offset(0, row+1);
  } else {
    //print d'un charactère normal
    vidmem[offset] = c;
    vidmem[offset+1] = color;
    offset += 2; //offset du charactère suivant
  }
  set_cursor_offset(offset); // on place l'offset du curseur aussi au prochain charactère
  return offset;
}

int get_offset(int col, int row){
  return 2 * (row * MAX_COLS + col);//équation de l'emplacement d'un charactère
}

int get_offset_row(int offset){
  return  offset / (2 * MAX_COLS);
}

int get_offset_col(int offset){ //doute sur logique de process de la fonction
  return 0;
  //return (offset - (offset / (2 * MAX_COLS) * 2 * MAX_COLS)) / 2;
}

int get_cursor_offset(){
  port_byte_out(REG_SCREEN_CTRL, 14);               //high byte
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);               //low byte
  offset +=port_byte_in(REG_SCREEN_DATA);
  return offset * 2;
}

void set_cursor_offset(int offset){
  offset /=2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen(){                          //fonction pour effacer l'écran
  int screen_size = MAX_COLS*MAX_ROWS;        //on calcule le nombre decaractères à l'écran
  char *screen = (char *)(VIDEO_ADDRESS);
  for (int i = 0; i < screen_size; i++){
    screen[i*2] = ' ';                        //on remplace tous les caractère par ' '
    screen[i*2+1] = WHITE_ON_BLACK;
  }
  set_cursor_offset(get_offset(0, 0));        //on recalcule l'offset par défaut
}
