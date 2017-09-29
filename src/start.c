#include <cpu.h>
#include <stdio.h>
#include <screen.h>

// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

// une fonction bien connue
uint32_t fact(uint32_t n)
{
    uint32_t res;
    if (n <= 1) {
        res = 1;
    } else {
        res = fact(n - 1) * n;
    }
    return res;
}

void kernel_start(void)
{
    printf("\f");
    for (int i=0; i < SCREEN_HEIGHT - 1; i++) {
      printf("\n");
    }
    printf("Ecriture sur la dernière ligne");
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}
