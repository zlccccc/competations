#include <sstream>
#include <fstream>
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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5007+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

queue<int> Q;
vector<int>edge[maxn];
int matching[maxn];//结果
int check[maxn];//matchright
int BFS(int n) {
	static int prev[maxn];//两格
	int ans=0,i,j;
	memset(matching,-1,sizeof(matching));
	memset(check,-1,sizeof(check));
	FOR(i,1,n) {
		if (matching[i]==-1) {
			while (!Q.empty()) Q.pop();
			Q.push(i);
			prev[i]=-1;
			bool flag=false;
			while (!Q.empty()&&!flag) {
				int u=Q.front(); Q.pop();
				for (j=0; !flag&&j<(int)edge[u].size(); j++) {
					int v=edge[u][j];
					if (check[v]!=i) {
						check[v]=i;
						Q.push(matching[v]);
						if (matching[v]!=-1) prev[matching[v]]=u;
						else {
							flag=1;
							int d=u,e=v;
							while (d!=-1) {
								int t=matching[d];
								matching[d]=e;
								matching[e]=d;
								d=prev[d];
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
inline int lowbit(int x){
	return x&-x;
}
int choose[maxn];//0,1,-1
void dfs(int x) {
	choose[x]=1;
	for (int v:edge[x]) if (!choose[v]){
		choose[v]=-1;//not choose
		dfs(matching[v]);//choose
	}
}
int A[maxn];
int main() {
	int i,j,n;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n) {
		FOR(j,i+1,n) if ((A[i]^A[j])==lowbit(A[i]^A[j])) {
			edge[i].push_back(j);
			edge[j].push_back(i);
		}
	}
	int ans=n-BFS(n);
	printf("%d\n",ans);
	FOR(i,1,n) if (matching[i]==-1) dfs(i);//must
	FOR(i,1,n) if (choose[i]==0) dfs(i);//must
	FOR(i,1,n) if (choose[i]==1) printf("%d ",A[i]),ans--;
	assert(ans==0);
}
/*
5
3 1 4 2 5
*/