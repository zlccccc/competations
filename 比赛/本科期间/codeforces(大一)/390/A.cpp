#include <cstdio>
#include <cmath>
#define N 10000
int a[N],b[N];
int i,j,k;
int n;
int l,r;
int l0;
int num;
int main()
{
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	for (l=1;l<=n;l=r+1) {
		while (a[l]==0&&l<=n) l++;
		if (l>n) {
			printf("NO");
			return 0;
		}
		r=l+1;
		while (a[r]==0&&r<=n) r++;
		r--;
		num++;
	}
	printf("YES\n%d\n",num);
	for (l=1;l<=n;l=r+1) {
		l0=l;
		while (a[l]==0&&l<=n) l++;
		r=l+1;
		while (a[r]==0&&r<=n) r++;
		r--;
		printf("%d %d\n",l0,r);
	}
}
