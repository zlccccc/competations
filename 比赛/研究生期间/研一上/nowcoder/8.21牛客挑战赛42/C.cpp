
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

vector<int> edge[maxn];
int dfl[maxn],dfr[maxn],tot;//and get kth-father
int fa[maxn][22],dep[maxn];
vector<pii> root[maxn];
void dfs(int x,int father,int depth) {
    dfl[x]=++tot; dep[x]=depth;
    root[depth].push_back(make_pair(tot,x));
    int i; fa[x][0]=father;
    rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int v:edge[x]) if (v!=father) dfs(v,x,depth+1);
    dfr[x]=tot;
}
int kthfa(int x,int k) {
    int i;
    rREP(i,20) if ((k>>i)&1) x=fa[x][i];
    return x;
}
struct node{
    int l,r,val;
}T[maxn*23];//update once
void update(int &x,int y,int pos,int L,int R) {
    T[x=++tot]=T[y]; T[x].val++;
    // printf("upd: %d %d\n",tot,T[x].val);
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,T[y].l,pos,L,mid);
    if (mid<pos) update(T[x].r,T[y].r,pos,mid+1,R);
}
int query(int x,int y,int k,int L,int R) {
    // printf("query: %d %d %d %d %d  %d-%d\n",x,y,k,L,R,T[x].val,T[y].val);
    if (L==R) return L;
    int mid=(L+R)/2;
    int lcnt=T[T[x].l].val-T[T[y].l].val;
    // printf("lcnt=%d; k=%d\n",lcnt,k);
    if (lcnt>=k) return query(T[x].l,T[y].l,k,L,mid);
    return query(T[x].r,T[y].r,k-lcnt,mid+1,R);
}
int A[maxn];
int main() {
    int n,m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    } dfs(1,0,1);
    tot=0;
    FOR(i,1,n) {
        int rt=0; int k;
        rREP(k,(int)root[i].size()) {
            auto now=root[i][k];
            // printf("%d(%d,v=%d) ",now.first,now.second,A[now.second]);
            update(rt,rt,A[now.second],1,n+1);
            root[i][k].second=rt;
        }
        // puts(" << xroot");
    }
    FOR(i,1,n+1) root[i].push_back(make_pair(n+2,0));//lower_bound
    int lastans=0;
    FOR(i,1,m) {
        int a,k; scanf("%d%d",&a,&k);
        int x=(a^lastans)%n+1;
        int f=kthfa(x,k);
        // printf("query: %d %d; f=%d\n",x,k,f);
        if (f==0) {puts("?"); continue;}
        int l=dfl[f],r=dfr[f]; r++;//ansl-ansr
        // printf("l and r=%d %d\n",l,r);
        auto _l=*lower_bound(root[dep[x]].begin(),root[dep[x]].end(),make_pair(l,0));
        auto _r=*lower_bound(root[dep[x]].begin(),root[dep[x]].end(),make_pair(r,0));
        // printf("%d %d  ----  %d %d\n",_l.first,_l.second,_r.first,_r.second);
        int v=query(_l.second,_r.second,k,1,n+1);
        if (v>n) {puts("?"); continue;}
        lastans=v;
        printf("%d\n",lastans);
    }

}
/*
6 1
1 0 0 1 1 1

6 2
1 0 0 1 1 1
*/