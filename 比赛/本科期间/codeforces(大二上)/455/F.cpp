#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int f[maxn];
int task1(int n){
	if (n&1) return 0*puts("NO");
	puts("YES");
	int m=1,i,j,x=n;
	while (m<n) m<<=1;
	for(;m;m>>=1) if (m<=n){
		FOR(i,m,n){
			f[i]=m-(i-m)-1;
			f[m-(i-m)-1]=i;
		}n=m-(n-m)-1-1;
	}
	FOR(i,1,x) printf("%d%c",f[i]," \n"[i==x]);
//	FOR(i,1,x) printf("%d%c",f[i]&i," \n"[i==x]);
}
int task2(int n){
	if ((n&(n-1))==0) return 0*puts("NO");
	if (n<6) return 0*puts("NO");
	int i;puts("YES");
	if (n==6){
		FOR(i,1,6) f[i]=" 362514"[i]-'0';
	}else{
		FOR(i,1,7) f[i]=" 3625174"[i]-'0';
		for(;i<=n;i+=2) f[i]=i+1,f[i+1]=i;
		if (n%2==0) f[n]=n-2,f[n-1]=n,f[n-2]=n-1;
	}
	FOR(i,1,n) printf("%d%c",f[i]," \n"[i==n]);
//	FOR(i,1,n) printf("%d%c",f[i]&i," \n"[i==n]);
}
int n;
int main(){
	scanf("%d",&n);
	task1(n);
	task2(n); 
}
/*

*/
