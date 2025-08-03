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
const LL maxn=1e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
int u,v,q;
int dfn[maxn];
queue<int> Q;
vector<int> edge[maxn];
int main(){
	scanf("%d%d%d",&n,&m,&q);
	FOR(i,1,m){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	while (q--){
		int t,s;
		scanf("%d%d",&t,&s);s++;
		while (Q.size()) Q.pop();
		FOR(i,1,n) dfn[i]=0;
		FOR(i,1,t){
			scanf("%d",&u);
			if (dfn[u]) continue;
			Q.push(u);dfn[u]=1;
		}
//		if (s==0) printf("%d",1);
//		else{
			int ans=0;
			while (Q.size()){
				ans++;
				int u=Q.front();Q.pop();
				if (dfn[u]==s) continue;
				for (int v:edge[u]) if (!dfn[v]){
					Q.push(v);dfn[v]=dfn[u]+1;
				}
			}printf("%d\n",ans);
//			printf("OK,%d\n",ans);
//		}
	}
}
/*
*/
