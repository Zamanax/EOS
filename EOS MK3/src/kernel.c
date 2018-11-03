#include "../include/kb.h"
#include "../include/isr.h"
#include "../include/idt.h"
#include "../include/util.h"
#include "../include/shell.h"
kmain()
{
	isr_install();
	clearScreen();
	print("Bonjour bienvenue sur EOS, veuillez rentrer une commande\n");
    launch_shell();    
}
