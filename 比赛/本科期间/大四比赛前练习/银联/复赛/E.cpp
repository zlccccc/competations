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
const LL maxn=3e4+107;
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

string ini[maxn];
int val[maxn];
string getActual(string str) {
	int i; string ret;
	REP(i,(int)str.size()) if (str[i]!='0') break;
	if (i==(int)str.size()) ret="0";
	else while (i<(int)str.size()) ret+=str[i++];
	return ret;
}
string getRev(string str) {
	reverse(str.begin(),str.end());
	return getActual(str);
}
vector<string> V;
bool lessthan(const string &x,const string &y) {
	if (x.size()!=y.size()) return x.size()<y.size();
	return x<y;
}
int getid(const string &x) {
	return lower_bound(V.begin(),V.end(),x,lessthan)-V.begin();
}
int nxt[maxn*3];
int MAX[maxn*4][2];//position
bool tag[maxn*4],couldrev[maxn*4];
void pushup(int x) {
	MAX[x][0]=max(MAX[x<<1][0],MAX[x<<1|1][0]);
	MAX[x][1]=max(MAX[x<<1][1],MAX[x<<1|1][1]);
	couldrev[x]=couldrev[x<<1]&&couldrev[x<<1|1];
}
void change(int x) {
	swap(MAX[x][0],MAX[x][1]); tag[x]^=1;
}
void pushdown(int x) {
	if (tag[x]) {
		change(x<<1); change(x<<1|1);
	} tag[x]=0;
}
void build(int x,int l,int r) {
	if (l==r) {
		MAX[x][0]=val[l];
		MAX[x][1]=nxt[MAX[x][0]];
		couldrev[x]=(nxt[MAX[x][1]]==MAX[x][0]);
		return;
	} int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
	// printf("%d : %d %d %d; could=%d\n",l,MAX[x][0],MAX[x][1],nxt[MAX[x][1]],couldrev[x]);
}
void update(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) {
		// printf("update: %d %d %d %d %d\n",x,l,r,L,R);
		if (L==R) {
			MAX[x][0]=nxt[MAX[x][0]];
			MAX[x][1]=nxt[MAX[x][0]];
			couldrev[x]=(nxt[MAX[x][1]]==MAX[x][0]);
			return;
		} if (couldrev[x]) {
			change(x);
			return;
		} else {
			int mid=(L+R)/2;
			pushdown(x);
			update(x<<1,l,r,L,mid);
			update(x<<1|1,l,r,mid+1,R);
			pushup(x);
			return;
		}
	} int mid=(L+R)/2;
	pushdown(x);
	if (l<=mid) update(x<<1,l,r,L,mid);
	if (mid<r) update(x<<1|1,l,r,mid+1,R);
	pushup(x);
}
int ans;
void query(int x,int l,int r,int o,int L,int R) {
	if (l<=L&&R<=r) {
		// printf("query: %d %d %d %d %d (%d); ans=%d\n",x,l,r,L,R,MAX[x][0],ans);
		ans=max(ans,MAX[x][0]);
		return;
	} int mid=(L+R)/2;
	pushdown(x);
	if (l<=mid) query(x<<1,l,r,o^tag[x],L,mid);
	if (mid<r) query(x<<1|1,l,r,o^tag[x],mid+1,R);
	pushup(x);
}

vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int tot,out[maxn];
void dfs1(int u,int from,int depth){
	int mx=-1;
	sz[u]=1;fa[u]=from;dep[u]=depth;son[u]=0;
	for (int v:edge[u]) {
		if (v==from) continue;
		dfs1(v,u,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x){
	int v,i;
	top[u]=x;id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	REP(i,(int)edge[u].size()){
		v=edge[u][i];
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	} out[u]=tot;
}
inline void Update(int x,int y){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,id[top[x]],id[x],1,tot);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	update(1,id[x],id[y],1,tot);
}
inline void Update(int x){
	update(1,id[x],out[x],1,tot);
}
inline void Query(int x,int y){
	ans=0;
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		query(1,id[top[x]],id[x],0,1,tot);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	query(1,id[x],id[y],0,1,tot);
}
int main() {
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) {
		cin>>ini[i]; ini[i]=getActual(ini[i]);
		string now=ini[i];
		V.push_back(now); now=getRev(now);
		V.push_back(now); now=getRev(now);
		V.push_back(now); now=getRev(now);
	} sort(V.begin(), V.end(), lessthan);
	V.erase(unique(V.begin(), V.end()),V.end());
	// for (auto str:V) cout<<str<<" "; puts("");
	REP(i,(int)V.size()) nxt[i]=getid(getRev(V[i]));
	FOR(i,1,n-1){
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs1(1,0,0); dfs2(1,0);
	// FOR(i,1,n) printf("%d(%d) ",id[i],getid(ini[i])); puts("");
	FOR(i,1,n) val[id[i]]=getid(ini[i]);
	build(1,1,tot);
	int q;
	scanf("%d",&q);
	FOR(i,1,q) {
		int op; scanf("%d",&op);
		if (op==1) {
			int u,v; scanf("%d%d",&u,&v);
			Update(u,v);
		} else if (op==2) {
			int u; scanf("%d",&u);
			Update(u);
		} else {
			int u,v; scanf("%d%d",&u,&v);
			Query(u,v);
			string now=V[ans]; int k,Ans=0;
			// cout<<now<<" <- now\n";
			REP(k,(int)now.size()) Ans=(Ans*10+now[k]-'0')%1000007;
			printf("%d\n",Ans);
		}
	}
}
/*
10
1 2 3 4 5 6 7 8 9 10
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
9
1 1 10
1 1 10
*/