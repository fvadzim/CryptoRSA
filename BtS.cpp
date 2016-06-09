#include "BtS.h"
#include <fstream>
#include <iostream>
#include <gmp.h>
#include <string.h>
#include <cmath>
#include <locale.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

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
int to_i(char s[])
{
    int res = 0, len = strlen(s);
    for (int i = 0; i < len; i++)
      res = res*10+(int)s[i]-48;
    return res;
}
