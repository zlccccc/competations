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
const int SIZE=450;
int block[maxn];
int n,k,i,q;
int L[507],R[507];
vector<pair<int,int> > g[maxn];
int f[107];
void change(int x){
	int i;
	FOR(i,1,100) f[i]=i;
	rREP(i,g[x].size()){
		auto now=g[x][i];
		f[now.first]=f[now.second];
	}FOR(i,L[x],R[x]) a[i]=f[a[i]];
	g[x].clear();
}
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n){
		block[i]=i/SIZE;
		if (!L[i/SIZE]) L[i/SIZE]=i;
		R[i/SIZE]=i;
	}scanf("%d",&q);
	while(q--){
		int l,r,x,y;
		scanf("%d%d%d%d",&l,&r,&x,&y);
		change(block[l]);change(block[r]);
		for (;l<=r&&l!=L[block[l]];l++) if (a[l]==x) a[l]=y;
		for (;l<=r&&r!=R[block[r]];r--) if (a[r]==x) a[r]=y;
		if (l<=r){
			l=block[l];r=block[r];
			FOR(i,l,r){
				g[i].push_back(make_pair(x,y));
				if (g[i].size()>50000) change(i);
			}
		}
	}FOR(i,0,n/SIZE) change(i);
	FOR(i,1,n) printf("%d ",a[i]);
}
/*
*/
