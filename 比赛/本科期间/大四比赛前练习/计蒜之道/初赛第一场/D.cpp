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
const LL maxn=1e6+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int m;
vector<pair<int,int> > edge[maxn];
vector<pair<int,int> > val[maxn];//MAP
int allval[maxn],base[maxn];//base额外算
int nowvx[maxn],nowvy[maxn],nowbasex[maxn],nowsumy[maxn];//rev
int mu[maxn],p[maxn],mark[maxn];
inline int Get(vector<pair<int,int> > &pos,int p) {
	auto it=lower_bound(pos.begin(), pos.end(), make_pair(p,0));
	if (it!=pos.end()&&it->first==p) return it->second;
	return 1;
}
inline void Set(vector<pair<int,int> > &pos,int p,int x) {
	lower_bound(pos.begin(), pos.end(), make_pair(p,0))->second=x;
}
void init(int MAX) {
	int tot=0; int i,j;
	mu[1]=1;
	FOR(i,2,MAX) {
		if (!mark[i]) p[tot++]=i,mu[i]=-1;
		REP(j,tot) {
			//感觉上不会爆,因为是从小往筛的
			if (i*p[j]>MAX) break;
			mark[i*p[j]]=1;
			if (i%p[j]==0) break;
			else mu[i*p[j]]=-mu[i];
		}
	}
}
void dfs(int x,int fa) {
	base[x]=1;
	for (auto e:edge[x]) {
		int v=e.first,k=e.second;
		if (v==fa) continue;
		for (int i=k; i<=m; i+=k) val[x].push_back(make_pair(i,1));
	}
	sort(val[x].begin(), val[x].end());
	val[x].erase(unique(val[x].begin(), val[x].end()),val[x].end());
	for (auto e:edge[x]) {
		int v=e.first,k=e.second;
		if (v==fa) continue;
		dfs(v,x);
		int div=m/k;
		for (int i=k,j=1; i<=m; i+=k,j++) {
			nowvx[j]=Get(val[x],i);//base另外算
			nowvy[j]=(ll)Get(val[v],i)*base[v]%M;
		} //MP:单独维护
		int inv=powMM(allval[v],M-2);
		for (int i=1; i<=div; i++) nowbasex[i]=0,nowsumy[i]=0;
		for (int i=1; i<=div; i++) if (mu[i]) { //if(mu[i])
				for (int j=i; j<=div; j+=i) add_(nowsumy[i],nowvy[j]); //gcd!=1
			}
		for (int i=1; i<=div; i++) if (mu[i]) {
				int now=mu[i]*nowsumy[i]; add_(now,M);
				for (int j=i; j<=div; j+=i) add_(nowbasex[j],now);
			}
		for (int i=1; i<=div; i++) {
			int now=(allval[v]+M-nowbasex[i])%M;
			mul_(now,inv); mul_(now,nowvx[i]);
			Set(val[x],i*k,now);
		}
		mul_(base[x],allval[v]);//other
		vector<pair<int,int> >().swap(val[v]);
		// for (int i=1; i<=div; i++) printf("%d ",nowvx[i]); puts("<- nowvx");
		// for (int i=1; i<=div; i++) printf("%d ",nowvy[i]); puts("<- nowvy");
		// for (int i=1; i<=div; i++) printf("%d ",nowbasex[i]); puts("<- nowbasex");
		// for (int i=1; i<=div; i++) printf("%d ",nowsumy[i]); puts("<- nowsumy");
		// printf("calc %d-%d:\n",x,k);
		// int i;
		// FOR(i,1,m) {
		// 	if (MP[x].count(i)) printf("%lld ",(ll)MP[x][i]*base[x]%M);
		// 	else printf("%d ",base[x]);
		// } puts("");
	}
	allval[x]=m-val[x].size();
	for (auto now:val[x]) add_(allval[x],now.second);
	mul_(allval[x],base[x]);
}
int main() {
	int i,n;
	init(100000);
	scanf("%d%d",&n,&m);
	FOR(i,1,n-1) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		edge[u].push_back(make_pair(v,w));
		edge[v].push_back(make_pair(u,w));
	} dfs(1,0);
	printf("%d\n",allval[1]);
}
/*
3 3
1 2 1
1 3 2
*/