#define N 2048
#include "time.h"
#include <gmp.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cmath>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include "encrypt.h"
#include "decrypt.h"
#include "gen.h"
#include "BtS.h"

using namespace std;

int main(int argc, char *argv[])
{

for (int i = 0; i < argc; i++)
   printf("%s\n",argv[i]);

setlocale(LC_ALL,"RUS");

if (strcmp(argv[1],"-g") == 0){

 if (argv[2])

   {
     if (check_gen_input(argc,argv[2]))
       return 2;
   }
 else
  {
       return 2;
  }
 gen(to_i(argv[2]),argv[3],argv[4]);
}

if (strcmp(argv[1],"-e") == 0) {
  encrypt(argv[2],argv[3],argv[4]);
}

if (strcmp(argv[1],"-d") == 0) {
    decrypt(argv[2],argv[3],argv[4]);
}
 return 0;
}
