#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


int n,m;
int i,j,k,tot;
int u,v;
int f[maxn];
int pos[maxn];
vector<int> a[maxn];
set<int> b[maxn];
int getfather(int i){
	if (i==f[i]) return i;
	return f[i]=getfather(f[i]);
}
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) f[i]=i;
	REP(i,m){
		scanf("%d%d",&u,&v);
		if (getfather(u)!=getfather(v)) f[getfather(v)]=getfather(u);
		if (u==v){
			puts("NO");
			return 0;
		}
		b[u].insert(v);
		b[v].insert(u);
	}
	FOR(i,1,n) pos[i]=-1;
	FOR(i,1,n){
		if (pos[getfather(i)]==-1){
			pos[getfather(i)]=tot;
			tot++;
		}
//		printf("get=%d %d\n",getfather(i),pos[getfather(i)]);
		a[pos[getfather(i)]].push_back(i);
	}
//	FOR(i,1,n) printf("%d ",f[i]);
//	puts("");
	REP(i,tot){
		for (j=0;j<a[i].size();j++)
			for (k=0;k<a[i].size();k++){
//				printf("%d %d   %d %d\n",j,k,a[i][j],a[i][k]);
				if (j!=k&&!b[a[i][j]].count(a[i][k])){
//				printf("%d %d   %d %d\n",j,k,a[i][j],a[i][k]);
					puts("NO");
					return 0;
				}
			}
	}
	puts("YES");
}
/*
6 7
1 2
2 3
1 4
3 4
3 1
5 6
2 4
*/
