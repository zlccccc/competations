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
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b,ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

bool used[maxn*2],mark[maxn];
struct node {
	int v,id,nxt;
} edge[maxn*4];
int head[maxn],tot;//only circle
int D[maxn];//du
// vector<node> edge[maxn];
vector<int> nowedge;
void addedge(int x,int y,int id) {
	edge[tot]= {y,id,head[x]}; head[x]=tot++;
}
void dfs(int x) {
	// printf("dfs: %d\n",x);
	for (int &i=head[x]; i!=-1;) {
		node e=edge[i]; i=edge[i].nxt;
		if (used[abs(e.id)]) continue;
		used[abs(e.id)]=1;
		D[e.v]--; D[x]--; dfs(e.v);
		nowedge.push_back(-e.id);//dfs_ed
	}
}
vector<int> nowid;
void dfs_id(int x) {
	mark[x]=1;
	if (D[x]&1) nowid.push_back(x);
	for (int i=head[x]; i!=-1;) {
		node e=edge[i]; i=edge[i].nxt;
		if (mark[e.v]) continue;
		dfs_id(e.v);
	}
}
int printid[maxn*4],cnt=0;
int main() {
	int n,m,i;
	while (~scanf("%d%d",&n,&m)) {
		tot=0;
		FOR(i,1,n) {
			D[i]=mark[i]=0; head[i]=-1;
		}
		FOR(i,1,m) {
			int u,v; scanf("%d%d",&u,&v);
			addedge(u,v,i);
			addedge(v,u,-i);
			D[u]++; D[v]++; used[i]=0;
		}
		int ans=0; cnt=0;
		FOR(i,1,n) if (!mark[i]) {
			nowid.clear();
			dfs_id(i);
			// printf("nowid size=%d\n",nowid.size());
			// for (int v:nowid) printf("%d ",v); puts("<- ids");
			if (nowid.size()) {
				int _;
				REP(_,(int)nowid.size()) {
					if (!(_&1)) {
						addedge(nowid[_],nowid[_+1],m+1+_/2);
						addedge(nowid[_+1],nowid[_],m+1+_/2);
						D[nowid[_]]++; D[nowid[_+1]]++; used[m+1+_/2]=0;
					}
				} nowedge.clear(); dfs(nowid[0]);
				// for (int v:nowedge) printf("%d ",v); puts("  <- nowedge");
				int pre=cnt++,c=0;
				for (int v:nowedge) {
					if (abs(v)>m) {
						printid[cnt++]=0;
						printid[pre]=c;
						c=0; pre=cnt++;
						ans++;
					} else {
						c++;
						printid[cnt++]=v;
					}
				} cnt--;
			} else {
				nowedge.clear(); dfs(i);
				if (nowedge.size()==0) continue;
				int pre=cnt++,c=0;
				for (int v:nowedge) {
					// printf("%d ",v);
					c++; printid[cnt++]=v;
				} printid[pre]=c,c=0;
				ans++; printid[cnt++]=0;
			}
		}
		printf("%d\n",ans);
		int k=printid[0]+1;
		REP(i,cnt) {
			if (printid[i]==0) {
				puts(""); ans--;
				// printf("k=%d\n",k);
				assert(k==0);
				k=printid[i+1]+1;
			} else {
				printf("%d",printid[i]); k--;
				if (printid[i+1]!=0) printf(" ");
			}
		}
		assert(ans==0);
		FOR(i,1,n) assert(D[i]==0);
	}
}
/*
*/