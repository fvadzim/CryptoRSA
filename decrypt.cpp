#include "decrypt.h"
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

void decrypt(char fin_path[], char fout_path[], char private_path[])
{

  ifstream private_file(private_path,ios_base::in | ios_base::binary);
  mpz_t  d , n;
  mpz_init_set_ui(d,0);
  mpz_init_set_ui(n,0);
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
