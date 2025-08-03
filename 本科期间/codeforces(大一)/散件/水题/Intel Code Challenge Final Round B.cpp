#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=25;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}


int a[N][N];
int n,m;
int i,j;

bool check(int ii,int jj){
	int i,j;
	int k;
	FOR(i,1,n){
		swap(a[i][ii],a[i][jj]);
		k=0;
		FOR(j,1,m) if (a[i][j]!=j) k++;
		swap(a[i][ii],a[i][jj]);
		if (k>2) return 0;
	}
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);
	FOR(i,1,n)
		FOR(j,1,m) scanf("%d",&a[i][j]);
	FOR(i,1,m)
		FOR(j,i,m) if (check(i,j)){
			printf("YES");
			return 0;
		}
	printf("NO");
	return 0;
}
/*
*/
