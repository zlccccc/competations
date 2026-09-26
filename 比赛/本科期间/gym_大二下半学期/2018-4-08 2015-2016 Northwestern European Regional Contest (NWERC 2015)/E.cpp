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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

queue<int> Q;
int previous[maxn];
int matching[maxn];
int check[maxn];//matchright
vector<int> edge[maxn];
void addedge(int x,int y){
	edge[x].push_back(y);
	edge[y].push_back(x);
}
int BFS(int n){
	int ans=0,i,j;
	memset(matching,-1,sizeof(matching));
	memset(check,-1,sizeof(check));
	FOR(i,1,n){
		if (matching[i]==-1){
			while (!Q.empty()) Q.pop();
			Q.push(i);
			previous[i]=-1;
			bool flag=false;
			while (!Q.empty()&&!flag){
				int u=Q.front();Q.pop();
				for (j=0;!flag&&j<edge[u].size();j++){
					int v=edge[u][j];
					if (check[v]!=i){
						check[v]=i;
						Q.push(matching[v]);
						if (matching[v]!=-1) previous[matching[v]]=u;
						else{
							flag=1;
							int d=u,e=v;
							while (d!=-1){
								int t=matching[d];
								matching[d]=e;
								matching[e]=d;
								d=previous[d];
								e=t;
							}
						}
					}
				}
			}
			if (matching[i]!=-1) ans++;
		}
	}
	return ans;
}
int N,n;
vector<LL> V;
LL A[maxn],B[maxn];
inline int getid(LL x){
	return lower_bound(V.begin(), V.end(),x)-V.begin()+1+n;
}
int main() {
	scanf("%d",&n);
	int i;
	N=n;
	FOR(i,1,n) {
		scanf("%I64d%I64d",&A[i],&B[i]);
		V.push_back(A[i]*B[i]);
		V.push_back(A[i]-B[i]);
		V.push_back(A[i]+B[i]);
	}sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()),V.end());
	N+=V.size();
	FOR(i,1,n){
		addedge(i,getid(A[i]*B[i]));
		addedge(i,getid(A[i]+B[i]));
		addedge(i,getid(A[i]-B[i]));
	}
	if (BFS(N)!=n) puts("impossible");
	else {
		FOR(i,1,n){
			LL X=V[matching[i]-n-1];
			if (X==A[i]*B[i]){
				printf("%I64d * %I64d = %I64d\n",A[i],B[i],A[i]*B[i]);
			}else if (X==A[i]+B[i]){
				printf("%I64d + %I64d = %I64d\n",A[i],B[i],A[i]+B[i]);
			}else if (X==A[i]-B[i]){
				printf("%I64d - %I64d = %I64d\n",A[i],B[i],A[i]-B[i]);
			}
		}
	}
	return 0;
}
/*
4 1 5 3 3 4 5 -1 -6
4
1 2
1 2
1 2
1 2
5
1000000 -1000000
1000000 -1000000
1000000 -1000000
1 1
1 1
*/
