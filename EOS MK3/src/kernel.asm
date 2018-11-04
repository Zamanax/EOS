bits    32
section         .text
        align   4
        dd      0x1BADB002
        dd      0x00
        dd      - (0x1BADB002+0x00)

global start
extern kmain            ; cette fonction sera située dans notre code en c (kernel.c)
start:
        cli             ;vidage des interrupts
        call kmain      ;demande au processeur de continuer l'execution sur la fonction kmain
        hlt             ;on arrete l'execution de cette adresse par le processeur
