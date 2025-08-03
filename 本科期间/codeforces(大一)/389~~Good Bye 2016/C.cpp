#include <cstdio>
#include <cmath>
const int N=200000;
const int INF=20000000;
int n,i;
int T;
int a[N],b[N];
bool l2;
int max=INF,min=-INF;
int main()
{
	scanf("%d",&T);
	for (i=0;i<T;i++){
		scanf("%d%d",&a[i],&b[i]);
		n+=a[i];
		if (b[i]==2) l2=1;
	}
	if (!l2) printf("Infinity");
	else{
		bool mark=0;
		max++;
		while (min+1<max)
		{
			mark=0;
			n=(min+max)/2;
			for (int i=0;i<T;i++){
				if (n>=1900&&b[i]==2){
					max=(min+max)/2;
					mark=1;
					break;
				}
				if (n<1900&&b[i]==1){
					min=(min+max)/2;
					mark=1;
					break;
				}
				n+=a[i];
			}
			if (!mark) min=(min+max)/2;
		}
		n=min;
		mark=0;
			for (int i=0;i<T;i++){
				if (n>=1900&&b[i]==2){
					mark=1;
					break;
				}
				if (n<1900&&b[i]==1){
					mark=1;
					break;
				}
				n+=a[i];
			}
		if (!mark) printf("%d",n);
		else  printf("Impossible");
	}
}
