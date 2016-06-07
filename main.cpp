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

using namespace std;

void byte_init(char byte[]);
unsigned char* int_to_bit_str(int a);
unsigned char str_to_int_to_char( char str[]);/////////// unsigned /
unsigned char str_byte_to_char(unsigned char byte[]);

void  encrypt(char fin_path[], char fout_path[], char public_path[]);
void  decrypt(char fin_path[], char fout_path[], char private_path[]);
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

int to_i(char s[])
{
    int res = 0, len = strlen(s);
    for (int i = 0; i < len; i++)
      res = res*10+(int)s[i]-48;
    return res;
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

void byte_init(unsigned char* byte)
{
   for (int i=0; i < 7; i++)
   byte[ i ] = '0';
}

unsigned char str_to_int_to_char( char str[])/////////// unsigned /
{
        int len = 0, j = 0, k = 1;
        unsigned char result = 0;
        len = strlen(str) - 1;

        for(j = len; j >= 0;j--)
        {
         result = result + k*((int)(str[j])-48);
         k*=10;
        }
        return (unsigned char)result;
}

unsigned char str_byte_to_char(unsigned char byte[])/* convert char[8] to char*/
{
  int k = 1;
  int res = 0;
  for(int i  = 7; i >= 0;i--)
   {
        res += ((int)byte[ i ]-48)*k;
        k *=2;
   }
   return (unsigned char)res;
}
unsigned char* int_to_bit_str(int a) /*convert int to char[8](binary representation of 0-255 numbers)*/
{
   int j = 7;
   unsigned char *result =  (unsigned char*)calloc( 8 , sizeof(unsigned char) );
   while (a > 0)
    {
      result[j] =(unsigned char)(48 + a % 2);
      j--;
      a = a / 2;
    }
   if (j >= 0)
   {
     for (int i = j; i >= 0; i--)
     {
       result[ i ] = '0';
     }
   }
 return result;
}

void encrypt(char fin_path[], char fout_path[], char public_path[])
{
    ifstream public_file(public_path,ios_base::in | ios_base::binary);
    mpz_t e , n;
    char buff_e[15000], buff_n[15000], test[15000];

    public_file >> buff_e;
    mpz_set_str(e,buff_e,10);
    public_file  >> buff_n;
    mpz_set_str(n,buff_n,10);

    public_file.close();
    cout<< "Length of key : " << strlen(buff_n) << endl;

    ifstream fin(fin_path,ios_base::in | ios_base::binary);

    fin.seekg(0,std::ios::end);
    float size_of_file = fin.tellg();
    fin.seekg(0,std::ios::beg);
    float size_of_read = 0;
    float  printf_read = 0;
    float size_of_buff_n =strlen(buff_n);

    ofstream fout(fout_path,ios_base::out | ios_base::binary);


    cout <<" e :" << buff_e << endl;
    cout <<" n :" << buff_n << endl;

    char  buff[ 15000 ];
    unsigned char* byte = (unsigned char*)calloc(8,sizeof(char));
    byte_init(byte);/*is filled fith zeros*/

    unsigned char  data;
    int i = 0;
    int j = 0;


    mpz_t c, t, _c;
    mpz_init_set_ui( c ,1);/*avoid situation ,when the first byte == 0000.0000. we get 1.0000.0000*/
    mpz_init_set_ui(_c ,1);
    mpz_init_set_ui(t , (1 << 8));/*add 8 zero numbers at th end*/
    printf("Encrypted : \n");
    while   ( !fin.eof() )
    {
       data = fin.get();

        if (fin.eof())
           break;

        mpz_mul(_c , c , t);

        mpz_t data_t;
        mpz_init_set_ui(data_t,(int)data);
        mpz_xor(_c, _c, data_t);/* add byte to c*/


        if (mpz_cmp(_c , n) < 0)
        {
            mpz_set(c,_c);
            mpz_get_str(buff, 2 ,c);
        }
        else
        {
            mpz_powm(c,  c , e , n);
            mpz_get_str(buff, 10 ,c);
            fout << buff << endl;
            mpz_get_str(buff,2,c);

            mpz_set_ui(c ,1);
            mpz_mul(c, c ,t);
            mpz_xor(c, c ,data_t);

            size_of_read += strlen(buff)/8 - 0.125;
            printf_read = size_of_read / size_of_file * 100;
            printf("%f %\r",printf_read);
        }
    }

    if (mpz_cmp_ui(c , 1) > 0) /*check residual buffer */
    {

        //mpz_get_str(buff, 2 , c);
        //cout << buff << endl;
        //cout <<"last length of buff: "<<strlen(buff) << endl;
        mpz_powm(c, c , e , n);
        mpz_get_str(buff, 10 ,  c);
        fout << buff << endl ;
        mpz_set_ui( c , 1 );
    }

  printf("100.000000%");
  fin.close();
  fout.close();
  public_file.close();
}
void decrypt(char fin_path[], char fout_path[], char private_path[])
{

  ifstream private_file(private_path,ios_base::in | ios_base::binary);
  mpz_t  d , n;
  char buff_d[10000], buff_n[10000];
  private_file >> buff_d;
  //cout << buff_d << endl;
  mpz_set_str(d,buff_d,10);
  private_file  >> buff_n;
  //cout << buff_n << endl;
  cout<< "Length of key : " << strlen(buff_n) << endl;

  mpz_set_str(n,buff_n,10);

  private_file.close();

  ifstream fin(fin_path,ios_base::in | ios_base::binary);
    fin.seekg(0,std::ios::end);
    float size_of_file = fin.tellg();
    fin.seekg(0,std::ios::beg);
    float size_of_read = 0;
    float printf_read  = 0;
  ofstream fout(fout_path,ios_base::out | ios_base::binary);

  char buff[10000] ;
  mpz_t m;
  mpz_init(m) ;
  unsigned char data;
  unsigned char* byte = (unsigned char*)calloc(8,sizeof(unsigned char));
  for (int i = 0 ; i <= 7 ; i++)
  {
    byte[i] = '0' ;
  }
  printf("Decrypted : \n");

  while (!fin.eof())
  {
    //getline(cin,buff);
    fin >> buff ;
    //cout << buff << "\n";
    if (fin.eof()) break;

    size_of_read +=(strlen(buff));
    printf_read = size_of_read/size_of_file*100;
    printf("%f%\r",printf_read);

    mpz_init_set_str( m , buff , 10 );
    if (mpz_cmp(m , n) > 0  )
    {

      cout << "БОЛЬШЕЕ ЧИСЛО m > n" << endl;
    }

   //mpz_set_ui(m,(int)data);//присваеваем с номер ASCII символа
    mpz_powm(m, m , d , n);
    mpz_get_str( buff , 2 , m );
    //cout <<"decrypt bitmask :" << buff<<endl;
    //cout <<"bitmask length "<< strlen(buff) <<endl;
    int i = 1;
    int j = 0;

    int str_len_buff = strlen(buff);

    while (i < str_len_buff)
     {
        for (j = 0; j<=7 ;j++ )
         byte[ j ] = buff[ i +  j];
         i+=8;
         data = str_byte_to_char(byte);
         fout << data;
      }
    }

    printf("100.000000%");
    fin.close();
    fout.close();
    private_file.close();
}

