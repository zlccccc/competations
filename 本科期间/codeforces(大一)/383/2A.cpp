#include <cstdio>
#include <iostream>
using namespace std;
int main()
{
	int n,m;
	int i,j,k; 
	scanf("%d",&n);
	if (n==0) printf("1");
	else if (n%4==0) printf("6");
	else if (n%4==1) printf("8");
	else if (n%4==2) printf("4");
	else if (n%4==3) printf("2");
	return 0;
}
