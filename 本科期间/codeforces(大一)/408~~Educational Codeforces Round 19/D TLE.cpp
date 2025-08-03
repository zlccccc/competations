#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
int i,ans,root;
bool isroot[maxn];
int v[maxn],l[maxn],r[maxn];
bool find(int x,int i){
	if (i==-1) return 1;
	if (v[i]==x) return 0;
	if (x<v[i]) return find(x,l[i]);
	else return find(x,r[i]);
}
vector<int> V;
int main()
{
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%d%d%d",&v[i],&l[i],&r[i]);
		isroot[l[i]]=isroot[r[i]]=1;
		V.push_back(v[i]);
	}
	FOR(i,1,n) if (!isroot[i]) root=i;
	REP(i,V.size()){
		ans+=find(V[i],root);
	}
	printf("%d",ans);
}
