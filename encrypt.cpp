#include "encrypt.h"
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

void encrypt(char fin_path[], char fout_path[], char public_path[])
{
    ifstream public_file(public_path,ios_base::in | ios_base::binary);
    mpz_t e , n;
    mpz_init_set_ui(e,0);
    mpz_init_set_ui(n,0);
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
    //unsigned char* byte = (unsigned char*)calloc(8,sizeof(char));
    //byte_init(byte);/*is filled fith zeros*/

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
            printf("%f% \r",printf_read);
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
