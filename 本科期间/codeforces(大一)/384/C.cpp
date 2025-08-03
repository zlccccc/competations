#include <iostream>
#include <cstdio>
#define MIN(a,b) ((a)<(b)?(a):(b))
using namespace std;
int main()
{
	long long n;
	long long a,b,c;
    scanf("%I64d",&n);
    for (a=n/2+1;a<3*n/2;a++)
    {
    	for (b=n*a/(2*a-n)+1;b<MIN(2*n*a/(2*a-n),1e9);b++)
    	{
    		if (n*a*b/(2*a*b-n*b-n*a)>1e9) continue;
    		if (n*a*b%(2*a*b-n*b-n*a)==0)
    		{
    			c=n*a*b/(2*a*b-n*b-n*a);
    			printf("%I64d %I64d %I64d",a,b,c);
    			return 0;
			}
		}
	}
	printf("-1");
    return 0;
}
