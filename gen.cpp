#include "gen.h"
#include <fstream>
#include <iostream>
#include "BtS.h"
#include <gmp.h>
#include <string.h>
#include <cmath>
#include <locale.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

void  gen(int size_N, char public_name[], char private_name[])
{
 srand(time(0));


 mpz_t p , q , p_non_pr , q_non_pr ;
 mpz_init2(p, size_N);
 mpz_init2(q, size_N);
 mpz_init2(p_non_pr, size_N);
 mpz_init2(q_non_pr, size_N);
 srand(time(0));

 gmp_randstate_t r_state;
 gmp_randinit_mt(r_state);

 mpz_urandomb(p_non_pr, r_state , size_N);
 mpz_nextprime(p , p_non_pr);

 mpz_urandomb(q_non_pr, r_state , size_N);
 mpz_nextprime(q , q_non_pr);

 mpz_t n;
 mpz_init2(n,3*size_N);
 mpz_mul(n , p , q);

 mpz_t fi_n; /*Euler function for N == p_prime *q_prime  */
 mpz_init(fi_n);
 mpz_sub_ui(p_non_pr, p ,1); /*use p_no_pr как p-1*/
 mpz_sub_ui(q_non_pr, q ,1); /*the same*/
 mpz_mul(fi_n, p_non_pr ,q_non_pr);

 mpz_t e;

 mpz_init_set_ui(e,131071); /* Mersenne number is easy to pow*/
 gmp_randinit_mt(r_state);
 mpz_t g;
 mpz_init(g);


 mpz_t x , d;
 mpz_init( x );
 mpz_init( d );

 mpz_gcdext (g, x, d, fi_n, e);

 if (mpz_sgn(d)  == -1)
 {
  mpz_add(d,d,fi_n);
 }

 ofstream public_file(public_name,ios_base::out | ios_base::binary); // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)
 ofstream private_file(private_name,ios_base::out | ios_base::binary);
 char buff_n[15000], buff_d[15000], buff_e[15000];
 mpz_get_str(buff_n,10,n);
 mpz_get_str(buff_d,10,d);
 mpz_get_str(buff_e,10,e);
 public_file  << buff_e << "\n" << buff_n;
 private_file << buff_d << "\n" << buff_n;
 public_file.close();
 private_file.close();
}
int   check_gen_input(int cnt,char *key_n)
{
  if (cnt < 4)
    return 1;

  for (int j = 0;j < strlen(key_n);j++)
 {
     if (!(int)( ((key_n[j]) >= 48) && ((key_n[j]) <= 57)))
     {
       printf(" Invalid data input. \n To gen new keys input : ""-g SIZE_of_KEY public_key_file private_key_file ") ;
       return 1;
    }
 if (to_i(key_n) < 512 )
       {
          printf("The length of key is not secure.Choose number between 512 adn 2048. \nBigger number are possible but don't make sense\n");
          return 2;
       }
 }
 return 0;
}
