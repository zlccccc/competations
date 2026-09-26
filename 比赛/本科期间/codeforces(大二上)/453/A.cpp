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
 
int a[maxn];
int l[maxn];
int n,h,s,N,H,i;
int mark=0;
int main(){
	scanf("%d",&h);
	FOR(i,0,h){
		scanf("%d",&a[i]);
		n+=a[i];
		if (a[i]>1&&a[i-1]>1) mark++;
	}if (!mark) return 0*puts("perfect");
	else{
		puts("ambiguous");
		N=a[0];H=0;s=0;
		FOR(i,1,n) l[i]=-1;
		FOR(i,1,n){
			if (N==0){
				while (l[s]==H) s++;
				H++;N+=a[H];
			}printf("%d ",s);
			l[i]=l[s]+1;N--;
		}puts("");
		N=a[0];H=0;s=0;
		FOR(i,1,n) l[i]=-1;
		FOR(i,1,n){
			if (N==0){
				while (l[s]==H) s++;
				H++;N+=a[H];
			}printf("%d ",s);
			l[i]=l[s]+1;N--;
			while (l[s+1]==H) s++;
		}
	}
}
/*
*/
