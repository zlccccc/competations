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
const LL maxn=8e6+7;
const double pi=acos(-1.0);
const double eps=1e-15;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int nxt[maxn][2],id[maxn],ord[2007];
int fa[2007][4007],tot,cnt;//pid
vector<int> ans;
void insert(char str[],int id){//could not like
	int i,p=0;
	REP(i,m) {
		int c=str[i]-'0'; fa[id][i]=p;//pos
		if (!nxt[p][c]) nxt[p][c]=++tot;
		p=nxt[p][c];
	} fa[id][m]=p; ::id[p]=id;
	assert(tot<maxn);
}
void dfs(int x){
	if (id[x]) ord[id[x]]=++cnt;
	if (nxt[x][0]) dfs(nxt[x][0]);
	if (nxt[x][1]) dfs(nxt[x][1]);
}
int A[4007];
int main() {
	int _t,T; scanf("%d",&T);
	FOR(_t,1,T){
		int i;
		scanf("%d%d%d",&n,&m,&q); tot=0;
		FOR(i,1,n) {scanf("%s",str); insert(str,i);} dfs(0);
		// FOR(i,1,n) printf("%d ",ord[i]); puts("");
		printf("Case #%d:\n",_t);
		while (q--) {
			int k;
			scanf("%d",&k);
			FOR(i,1,k) scanf("%d",&A[i]),A[i]++;
			sort(A+1,A+1+k,[](int i,int j){
				return ord[i]<ord[j];
			}); ans.clear();
			FOR(i,1,k-1) {
				int l=0,r=m+1;
				while (l+1<r){
					int mid=(l+r)/2;
					if (fa[A[i]][mid]==fa[A[i+1]][mid]) l=mid;
					else r=mid;
				} 
				// FOR(l,1,m) printf("%d ",fa[A[i]][l]); printf(" <- %d\n",A[i]);
				ans.push_back(r);
			} sort(ans.begin(), ans.end());
			ans.erase(unique(ans.begin(), ans.end()),ans.end());
			printf("%d",(int)ans.size());
			for (int v:ans) printf(" %d",v-1); puts("");
		}
		FOR(i,0,tot) nxt[i][0]=nxt[i][1]=id[i]=0; tot=cnt=0;//rev
	}
}
/*
*/