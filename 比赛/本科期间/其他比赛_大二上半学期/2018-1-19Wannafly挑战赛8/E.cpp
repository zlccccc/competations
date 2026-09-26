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
#include <cassert>
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
const LL M=998244353;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int c[maxn*8],b[maxn*4];
int p[maxn*8];
bool solve(int n){//manacher
    int i;
//    c[0]=-2;
//    c[1]=-1;
//	REP(i,n+1){
//		c[i*2+2]=b[i];
//		c[i*2+3]=-1;
//	}int len=n*2+2;
	FOR(i,1,n) c[i]=b[i-1];
    int len=n;
	int id=0,mx=0;
	FOR(i,1,len-1){
		if (mx>i) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while (c[i+p[i]]==c[i-p[i]]) p[i]++;
		if (p[i]+i>mx){
			mx=p[i]+i;
			id=i;
		}
	}int ans=0;
//	REP(i,n) printf("%2d ",b[i]);puts(" <- b");
//	REP(i,len) printf("%2d ",c[i]);puts(" <- c");
//	REP(i,len) printf("%2d ",p[i]);puts(" <- p");
    REP(i,len) ans=max(ans,p[i]);
//    printf("%d %d\n",n/2,ans*2-1);
    if (ans*2-1>=n/2) return 1;
    return 0;
}
int a[maxn*4];
bool check(int k,int n){//k:st,n:ed
    int s,i,j;
    REP(s,k){
        REP(i,n*2) b[i]=a[s+i*k+k]^a[s+i*k];
        if (solve(n*2)) return 1;
    }return 0;
}
int main(){
    int i,j,n;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i]),a[i+n]=a[i+n+n]=a[i];
    FOR(i,1,n*3) a[i]^=a[i-1];
    FOR(i,1,n) if (n%i==0&&check(i,n/i)) return 0*printf("%d\n",n/i);
}
/*
*/
