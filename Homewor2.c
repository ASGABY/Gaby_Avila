#include<stdio.h>
#include<math.h>
#define K 10
void prime(int y);
void binary(int a);
int main()
{
  prime(K);
  return 0;
}

void binary(int a)
{
    int c=0;
    int base[7]={0};

    while(a>0)
    {
	base[c]= a%2;
	a/=2;
	++c;
    }

    for(int x=6;x>=0;--x)
    {
       printf("%01d",base[x]);
    }
     printf("\n");
}

void prime(int k)
{
  int count, c, flag, sr;
  int y=1;
  count = 1;

  while(count <= k)
  {
    sr = sqrt(y);
    flag = 0;
    for(c=2; c<= sr; c++)
    {
      if(y%c==0)
      {
        flag = 1;
        break;
      }

    }

    if(flag==0)
    {
      binary(y);
      count++;
    }
    y++;
  }
}
