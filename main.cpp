#define N 2048
#include"time.h"
#include <gmp.h>
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

void  encrypt(ifstream& fin,ofstream& fout, mpz_t e,mpz_t n)
{
 char buff[4096];
 mpz_t c;
 mpz_init(c);
 long long  len = sizeof(fin);
 char data;

 while (!(feof(fin))
 {

   fin >> data;
   mpz_set_ui(c,(int)data);//присваеваем с номер ASCII символа
   mpz_powm(c, c , e , n);
   ///mpz_set(C[i],c);

   mpz_get_str(buff, 10, c);

   cout <<  (int)data << data << "   "<< buff << "  ZNAKOV :" << strlen(buff)<<endl;
   fout << buff<< "       "<< endl;


 }
}

int main()

{
 //ofstream fout;
 //fout.open("Crypt.txt",ios_base::in);

 //ifstream fin("read_from.txt",ios_base::out|ios_base::binary); // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)
 //if (!fin.is_open()) // если файл не открыт
  //      cout << "Файл не может быть открыт!\n";

//cout<<"Size of read : "<<sizeof(fin)<<endl;


 char buff[4096];
 srand(time(0));


 mpz_t p , q , p_non_pr,q_non_pr;
 mpz_init2(p, N);
 mpz_init2(q, N);
 mpz_init2(p_non_pr, N);
 mpz_init2(q_non_pr, N);
 srand(time(0));

 gmp_randstate_t r_state;

 gmp_randinit_mt(r_state);

 mpz_urandomb(p_non_pr, r_state , N);
 mpz_get_str(buff, 10, p_non_pr);
 cout << "Succsesful! p_non_pr:" << buff << "  ZNAKOV :" << strlen(buff)<<endl;


 mpz_nextprime( p,p_non_pr);

 mpz_get_str(buff, 10, p);
 cout << "Succsesful!  P: " << buff << " p  ZNAKOV :" << strlen(buff)<<endl;

 mpz_urandomb(q_non_pr, r_state , N);
 mpz_get_str(buff, 10, q_non_pr);
 cout << "Succsesful! q_non_pr:" << buff << "  ZNAKOV :" << strlen(buff)<<endl;


 mpz_nextprime( q,q_non_pr);

 mpz_get_str(buff, 10, q);
 cout << "Succsesful!  q: " << buff << " p  ZNAKOV :" << strlen(buff)<<endl;

 mpz_t n;
 mpz_init2(n,3*N);
 mpz_mul(n , p ,q);
 mpz_get_str(buff, 10, n);
//cout << "Succsesful!  n: " << buff << " n  ZNAKOV :" << strlen(buff)<<endl;


 mpz_t fi_n;
 mpz_init2(fi_n,3*N);
 mpz_sub_ui(p_non_pr,p,1); //используем p_no_pr как p-1
 mpz_sub_ui(q_non_pr,q,1); //то же с q
 mpz_mul(fi_n, p_non_pr ,q_non_pr);

 mpz_get_str(buff, 10, fi_n);
 cout << "Succsesful!  fi_n: " << buff << " fi_n  ZNAKOV :" << strlen(buff)<<endl;

 mpz_t e;//закрытый ключ
 mpz_init_set_ui(e,65531); //
 gmp_randinit_mt(r_state);
 mpz_t g;
 mpz_init(g);
 /*mpz_urandomb(d, r_state , N);//срандомили закрытый ключ

 mpz_init2(g,3*N);

 while (mpz_cmp_ui(g , 1 )  != 0)
 S{
    //srand(time(NULL));
    //gmp_randinit_mt(r_state);
    mpz_urandomb(d, r_state , N);
    //mpz_get_str(buff, 10, d);
   // cout << "Succsesful!  d: " << buff << " d ZNAKOV :" << strlen(buff)<<endl;
    mpz_gcd(g,fi_n,d);
  }
 mpz_get_str(buff, 10, d);
 cout << "Succsesful!  d: " << buff << " d ZNAKOV :" << strlen(buff)<<endl;
*/

 mpz_t x , d;
 mpz_init( x );//коэффицент
 mpz_init( d );//как коэффицент

 mpz_gcdext (g, x, d, fi_n, e);

 //mpz_get_str(buff, 10, d);
 //cout << "Succsesful!  d: " << buff << " d ZNAKOV :" << strlen(buff)<<endl;
 if (mpz_sgn(e)  == -1)
 {
  mpz_add(e,e,fi_n);
  mpz_get_str(buff, 10, e);
  //cout << "Succsesful!  e: " << buff << " e ZNAKOV :" << strlen(buff)<<endl;
 }
 mpz_get_str(buff, 10, e);
 /*cout << "Succsesful!  e: " << buff << " e ZNAKOV :" << strlen(buff)<<endl;
 cout << "enter MASSAGE \n";
 char MASSAGE[1000];
 cin >> MASSAGE;*/



   mpz_t D;
   mpz_init(D);
   long long  len = sizeof(fin);

   char data;
   //mpz_powm(D, c , d , n);



 fout.close();
 return 0;
}
