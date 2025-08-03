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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

set<int> SET; 
set<int>::iterator it;
int n,m,t;
int i;
int len;
int mx; 
char a[maxn],s[maxn];
int main(){
	scanf("%d",&n);
	FOR(i,0,2e6) SET.insert(i);
	while (n--){
		scanf("%s",s);
		len=strlen(s);
		scanf("%d",&m);
		while (m--){
			scanf("%d",&t);
			t--;
			for(it=SET.lower_bound(t);it!=SET.end()&&*it<t+len;it=SET.lower_bound(t)){
				a[*it]=s[*it-t];
				if (mx<*it) mx=*it;
				SET.erase(it);
			}
		}
	}
	REP(i,mx+1){
		if (a[i]) putchar(a[i]);
		else putchar('a');
	}
}
/*
*/
