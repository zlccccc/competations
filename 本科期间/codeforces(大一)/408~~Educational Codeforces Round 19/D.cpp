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
map<int,int> mp;
int solve(int x,int le,int ri){
	if (x==-1) return 0;
	int ret=0;
	if (le<=v[x]&&v[x]<=ri) ret+=mp[v[x]],mp[v[x]]=0;
	ret+=solve(l[x],le,min(ri,v[x]-1));
	ret+=solve(r[x],max(le,v[x]+1),ri);
	return ret;
}
int main()
{
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%d%d%d",&v[i],&l[i],&r[i]);
		if (l[i]!=-1) isroot[l[i]]=1;
		if (r[i]!=-1) isroot[r[i]]=1;
		mp[v[i]]++;
	}
	FOR(i,1,n) if (!isroot[i]) root=i;
	printf("%d",n-solve(root,0,1000000000));
}
