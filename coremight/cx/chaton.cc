#include <stdio.h>
#include <unistd.h>

int main()
{
  printf("le programme du chaton :3~ (mais qui fait pas encore 'miu-mui')\n");
  printf("by zemiu ezjonas@gmail.com\n");
  char * edt[32] =
    {
      "dodo",
      "m'etirer, bailler comme un lion",
      "bagarrer, jouer, sauter partout",
      "manger",
      "m'aggriper partout",
      "pipi",
      "boire du lait",
      "popo"
    };
  int i = 0;
  while(1)
    {
      sleep(1);
      printf(":3~ %s\n", edt[i++%8]);
    }
}
