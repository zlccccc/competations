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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,s1,s2;
int a[maxn];
set<int> S;
set<int>::iterator it;
bool check(int x){
	int i;
	S.clear();
	if (abs(s1-s2)>x) return 0;
	S.insert(s1);S.insert(s2);
	FOR(i,1,n){
		bool mark1=0,mark2=0;
		while (S.size()&&abs(a[i]-*S.begin())>x) S.erase(S.begin());
		while (S.size()&&abs(a[i]-*S.rbegin())>x) S.erase(*S.rbegin());
		if (!S.size()) return 0;
		S.insert(a[i]);
	}
	return 1;
}
int l,r,mid;
int main(){
	int i;
	scanf("%d%d%d",&n,&s1,&s2);
	FOR(i,1,n) scanf("%d",&a[i]);
	l=0;r=INF;
	while (l+1<r){
		int mid=(l+r)/2;
		if (check(mid)) r=mid;
		else l=mid;
	}
	printf("%d\n",r);
}
/*
2 0 10
5 6
*/
