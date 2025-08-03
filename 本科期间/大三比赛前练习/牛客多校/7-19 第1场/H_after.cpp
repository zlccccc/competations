#include <bits/stdc++.h>
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
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B){A+=B;(A>=M)&&(A-=M);}
inline void mul(ll &A,ll B){(A*=B)%=M;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m,_m;
char S[maxn];

bool Q;
struct Line {
    mutable LL a,b,k;
    bool operator<(const Line &o)const {
        return Q?k<o.k:a<o.a;
    }
};
struct convexHull:public multiset<Line> {
    LL div(LL a,LL b) {
        return a/b-((a^b)<0&&a%b);
    }
    bool getK(iterator x,iterator y) {
        if (y==end()) {x->k=INFF; return 0;}
        if (x->a==y->a) x->k=x->b>y->b?INFF:-INFF;
        else x->k=div(y->b-x->b,x->a-y->a);
        return x->k>=y->k;
    }
    void insPos(LL a,LL b) {
        auto z=insert({a,b,0}); auto y=z++,x=y;
        while (getK(y,z)) z=erase(z);
        if (y!=begin()&&getK(--x,y)) getK(x,erase(y));
        while ((y=x)!=begin()&&(--x)->k>=y->k)
            getK(x,erase(y));
    }
    LL query(LL x) {
        assert(size());
        Q=1; auto now=lower_bound({0,0,x}); Q=0;
        return now->a*x+now->b;
    }
};
convexHull ConvexHull;
vector<pii> edge[maxn];
ll ans[maxn],ans_down[maxn],ans_other[maxn];//ans_down: choose up_node
void dfs_down(int x,int fa){
	for (auto now:edge[x]){
		int v=now.first;ll len=now.second;
		if (v==fa) continue;
		dfs_down(v,x);
		if (ConvexHull.size())
			ans_down[v]=ConvexHull.query(len*2)+len*len;
		ans[x]=max(ans[x],ans_down[v]);
	} ConvexHull.clear();
	for (auto now:edge[x]){
		int v=now.first;ll len=now.second;
		if (v==fa) continue;
		if (ConvexHull.size())
			ans_other[v]=max(ans_other[v],ConvexHull.query(len*2)+len*len);
		ConvexHull.insPos(-len,ans_down[v]+len*len);
	}reverse(edge[x].begin(), edge[x].end());
	ConvexHull.clear();
	for (auto now:edge[x]){
		int v=now.first;ll len=now.second;
		if (v==fa) continue;
		if (ConvexHull.size())
			ans_other[v]=max(ans_other[v],ConvexHull.query(len*2)+len*len);
		ConvexHull.insPos(-len,ans_down[v]+len*len);
	}
}
void dfs_up(int x,int fa,ll uplen,ll upans){
	for (auto now:edge[x]){
		int v=now.first;;ll len=now.second;
		if (v==fa) continue;
		ll nxtans=ans_other[v];
		if (fa) nxtans=max(nxtans,upans+(uplen-len)*(uplen-len));
		ans[v]=max(ans[v],nxtans);
		dfs_up(v,x,len,nxtans);
	}
}
int TaskA(){
	int i;
	FOR(i,1,n) edge[i].clear();
	FOR(i,1,n) ans[i]=ans_other[i]=ans_down[i]=0;
	FOR(i,1,n-1){
		int u,v,len;
		scanf("%d%d%d",&u,&v,&len);
		edge[u].push_back(make_pair(v,len));
		edge[v].push_back(make_pair(u,len));
	}
	dfs_down(1,0);
	// FOR(i,1,n) debug("%lld ",ans[i]);deputs(" <- ans");
	// FOR(i,1,n) debug("%lld ",ans_down[i]);deputs(" <- ans_down");
	// FOR(i,1,n) debug("%lld ",ans_other[i]);deputs(" <- ans_other");
	dfs_up(1,0,0,0);
	FOR(i,1,n) printf("%lld\n",ans[i]);
    return 0;
}
void initialize(){}
void Task_one(){TaskA();}
void Task_T(){int T;scanf("%d",&T);while (T--) TaskA();}
void Task_more_n(){while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m(){while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string(){while (~scanf("%s",S)) TaskA();}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_more_n();
}
/*
2
1 2 1
4
1 2 1
2 3 2
3 4 1 
*/
