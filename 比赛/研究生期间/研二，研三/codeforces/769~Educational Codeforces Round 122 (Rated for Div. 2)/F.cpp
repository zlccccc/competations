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
const LL maxn=2e5+107;
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

vector<pii> edge[maxn];
int son[maxn],sz[maxn],top[maxn],tot,dep[maxn],id[maxn];
int e_val[maxn],fa[maxn],rid[maxn];
void dfs1(int x,int father,int depth) {
    int mx=-1; fa[x]=father;
    sz[x]=1; dep[x]=depth; son[x]=0;
    for (auto now:edge[x]) if (now.first!=father) {
        int v=now.first;
        dfs1(v,x,depth+1);
        sz[x]+=sz[v]; e_val[v]=now.second;
        if (sz[v]>mx) mx=sz[v],son[x]=v;
    }
}
void dfs2(int x,int Top) {
    top[x]=Top; id[x]=++tot; rid[tot]=x;
    if (son[x]) dfs2(son[x],Top);
    for (auto now:edge[x]) {
        int v=now.first;
        if (v==fa[x]||v==son[x]) continue;
        dfs2(v,v);
    }
}
int mark[maxn<<2][2],lz[maxn<<2];
ll sum[maxn<<2][2];
void upd(int x) {
    lz[x]^=1;
    swap(mark[x][0],mark[x][1]);
    swap(sum[x][0],sum[x][1]);
}
void pushup(int x) {
    mark[x][0]=mark[x<<1][0]+mark[x<<1|1][0];
    mark[x][1]=mark[x<<1][1]+mark[x<<1|1][1];
    sum[x][0]=sum[x<<1][0]+sum[x<<1|1][0];
    sum[x][1]=sum[x<<1][1]+sum[x<<1|1][1];
}
void update1(int x,int p,int L,int R) {
    if (L==R) {
        // printf("update: x=%d; lz=%d; p=%d; e_val=%d\n",x,lz[x],p,e_val[p]);
        sum[x][lz[x]]+=e_val[rid[p]];
        mark[x][lz[x]]++; return;
    }
    int mid=(L+R)/2;
    if (lz[x]) upd(x<<1),upd(x<<1|1),lz[x]=0;
    if (p<=mid) update1(x<<1,p,L,mid);
    else update1(x<<1|1,p,mid+1,R);
    pushup(x);
    // printf("sum, val (%d->%d)=%d %d; %d %d\n",L,R,sum[x][0],sum[x][1],mark[x][0],mark[x][1]);
}
void update2(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) {
        // printf("update2 x=%d %d %d\n",x,L,R);
        upd(x); return;
    }
    int mid=(L+R)/2;
    if (lz[x]) upd(x<<1),upd(x<<1|1),lz[x]=0;
    if (l<=mid) update2(x<<1,l,r,L,mid);
    if (mid<r) update2(x<<1|1,l,r,mid+1,R);
    pushup(x);
    // printf("sum, val (%d->%d)=%d %d; %d %d\n",L,R,sum[x][0],sum[x][1],mark[x][0],mark[x][1]);
}
vector<int> ans;
void solve(int x,int L,int R) {
    if (L==R) {if (lz[x]) ans.push_back(e_val[rid[L]]); return;}
    int mid=(L+R)/2;
    if (lz[x]) upd(x<<1),upd(x<<1|1),lz[x]=0;
    solve(x<<1,L,mid); solve(x<<1|1,mid+1,R);
    pushup(x);
}
int n;
void modify(int x){
    update1(1,id[x],1,n);
    while (x) {
        // printf(" update-2: %d-%d\n",id[top[x]],id[x]);
        update2(1,id[top[x]],id[x],1,n); //区间swap
        x=fa[top[x]];
    }
}
int Q[(int)(1e7+7)];
vector<int> pos; int nowpos;
int main() {
    int i;
    scanf("%d",&n);
    FOR(i,1,n-1) {
        int u,v; scanf("%d%d",&u,&v);
        edge[u].push_back(make_pair(v,i));
        edge[v].push_back(make_pair(u,i));
    } dfs1(1,0,0);
    dfs2(1,1);
    int op;
    modify(1);
    while (~scanf("%d",&op)) {
        if (op==3) break;
        if (op==1) {
            int x; scanf("%d",&x); modify(x);
            if (mark[1][0]!=mark[1][1]) puts("0");
            else printf("%lld\n",sum[1][1]);
        } else if (op==2) {
            if (mark[1][0]!=mark[1][1]) puts("0");
            else {
                ans.clear();
                solve(1,1,n);
                printf("%d",(int)ans.size());
                sort(ans.begin(),ans.end());
                for (int v:ans) printf(" %d",v);
                puts("");
            }
        }
        fflush(stdout);
        // printf("now_value-%d %d; sum=%d %d\n",mark[1][0],mark[1][1],sum[1][0],sum[1][1]);
    }
}
/*
*/