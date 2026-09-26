#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<ctime>
#include<set>
#include<vector>
#include<map>
#include<queue>

#define N 505
#define M 8000005

#define ls (t<<1)
#define rs ((t<<1)|1)
#define mid ((l+r)>>1)

#define mk make_pair
#define pb push_back
#define fi first
#define se second

using namespace std;

int i,j,m,n,k,l;

double f[505][505],p[6][7],fir[6][505][N],none[6][505][505],Ans[505];

void pre(int id) {
	int i,j;
	memset(f,0,sizeof(f));
	f[0][0]=1.;
	for (i=1; i<=500; ++i)
		for (j=0; j<n; ++j)
			for (k=1; k<=6; ++k)
				f[i][(j+k)%n]+=f[i-1][j]*p[id][k];
	for (i=1; i<=500; ++i)
		for (j=0; j<n; ++j)
			if (f[i][j]>1e-8) {
				fir[id][i][j]=f[i][j];
				for (k=1; k<i; ++k)
					fir[id][i][j]-=fir[id][k][j]*f[i-k][0];
			}
	for (i=0; i<n; ++i) none[id][0][i]=1.;
	for (i=1; i<=500; ++i) {
		for (j=0; j<n; ++j) none[id][i][j]=none[id][i-1][j]-fir[id][i][j];
	}
}

int main() {
//		freopen("1.in","r",stdin);
	scanf("%d",&n);
	for (i=0; i<6; ++i)
		for (j=1; j<=6; ++j) scanf("%lf",&p[i][j]);
	for (i=0; i<6; ++i)
		pre(i);
	for (i=0; i<6; ++i)
		for (j=1; j<=500; ++j)
			for (k=0; k<n; ++k)
				if (fir[i][j][k]>1e-8) {
					double cnt=fir[i][j][k];
					for (l=0; l<6; ++l)
						if (i<l) cnt*=none[l][j-1][k];
						else if (i>l) cnt*=none[l][j][k];
					Ans[i]+=cnt;
				}
	for (i=0; i<6; ++i) printf("%.3lf\n",Ans[i]);
}
