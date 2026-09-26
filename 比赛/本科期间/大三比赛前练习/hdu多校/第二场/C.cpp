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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

int used[maxn];
vector<pii> edge[maxn];
int D[maxn];
vector<int> ans,now;
int start[maxn],tot;
void dfs(int x){
	rep(start[x],start[x],(int)edge[x].size()){
		int v=edge[x][start[x]].first,pos=edge[x][start[x]].second;
		if (used[abs(pos)]) continue;
		used[abs(pos)]=1; D[v]--; D[x]--;
		dfs(v); now.push_back(pos);
	}
}
int pre=0,mark[maxn];
void dfs_node(int x){
	mark[x]=1;
	if (D[x]&1) now.push_back(x);
	for (auto now:edge[x]) {
		int v=now.first;
		if (!mark[v]) dfs_node(v);
	}
}
int TaskA() {
	int i;
	vector<int>().swap(ans);
	FOR(i,1,n+n) {
		D[i]=0;start[i]=mark[i]=0; 
		vector<pii>().swap(edge[i]);
	}
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v); used[i]=0;
		edge[u].push_back(make_pair(v,i));
		edge[v].push_back(make_pair(u,-i));
		D[u]++; D[v]++;
	} tot=0; int etot=m;
	FOR(i,1,n) if (!mark[i]&&edge[i].size()) {
		now.clear(); dfs_node(i); int j,k;
		REP(j,(int)now.size()/2){
			int u=now[j*2],v=now[j*2+1]; used[++etot]=0;
			edge[u].push_back(make_pair(v,etot));
			edge[v].push_back(make_pair(u,etot));
		} now.clear(); dfs(i); reverse(now.begin(),now.end());
		REP(j,(int)now.size()) if (now[j]>m) break;
		rep(k,j+1,(int)now.size()) {ans.push_back(now[k]); if (now[k]>m) tot++;}
		REP(k,j) ans.push_back(now[k]);
		ans.push_back(m+1); tot++;
	} now.clear();
	printf("%d\n",tot);
	for (int v:ans){
		if (abs(v)<=m) now.push_back(v);
		else {
			printf("%d",(int)now.size());
			for (int v:now) printf(" %d",v);
			puts(""); now.clear();
		}
	}
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_more_n_m();
}
/*
5 3
1 2
3 2
4 5

*/
