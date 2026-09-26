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
const LL M=998244353;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

// gray编码
// https://codeforces.com/contest/1553/problem/H
// 最近写题好慢好丢人啊
struct node{
    int min,max,ans;
}T[maxn*4]; int tot=1;
inline node merge(const node &x,const node &y,int val) {
    return node{x.min,y.max+val,min(min(x.ans,y.ans),y.min-x.max+val)};
}
inline node merge(int x,int y,int val) {
    if (!y) return T[x];
    if (!x) return node{T[y].min+val,T[y].max+val,T[y].ans};
    return merge(T[x],T[y],val);
}
int NXT[maxn*4][2];
void insert(int x,const int val,const int dep) {
    if (!x) return;
    if (dep==-1) {T[x]={0,0,INF}; return;}
    int o=(val>>dep)&1;
    if (!NXT[x][o]) NXT[x][o]=++tot;
    insert(NXT[x][o],val,dep-1); //&(~(1<<dep))
    T[x]=merge(NXT[x][0],NXT[x][1],1<<dep);
    // pr2(val,dep+1);
    // printf("x=%d << %d; o=%d depth=%d: (%d -> %d); %d; nxt=%d %d\n",x,val,o,dep,T[x].min,T[x].max,T[x].ans,NXT[x][0],NXT[x][1]);
}
void print(int x,int k,int depth) {
    if (depth==-1) printf("%d ",k);
    if (NXT[x][0]) print(NXT[x][0],k<<1,depth-1);
    if (NXT[x][1]) print(NXT[x][1],k<<1|1,depth-1);
}
void rebuild(int x,int revVal,const int dep) {
    if (!revVal||dep==-1) return;
    int o=(revVal>>dep)&1;
    if (o) swap(NXT[x][0],NXT[x][1]);
    rebuild(NXT[x][0],revVal&(~(1<<dep)),dep-1);
    rebuild(NXT[x][1],revVal&(~(1<<dep)),dep-1);
    T[x]=merge(NXT[x][0],NXT[x][1],1<<dep);
}
inline gray(int x) {return x^(x>>1);}
inline int rev(int x,int depth) {
    int i,ret=0; REP(i,depth) ret=ret<<1|(x&1),x>>=1; return ret;
}
int ans[maxn];
int main() {
    int n,i,k;
    scanf("%d%d",&n,&k);
    // reversed add
    FOR(i,1,n) {int x; scanf("%d",&x); insert(1,x,k-1);}
    REP(i,(1<<k)) {
        // pr2(gray(i),k); puts("<- gray");
        int fx=rev(gray(i),k);
        if (i) rebuild(1,fx^rev(gray(i-1),k),k-1);
        ans[fx]=T[1].ans;
        // if (i) {pr2(fx^rev(gray(i-1),k),k); puts("<- swap");}
        // print(1,0,k-1); puts("<<- after swap");
        // printf("getans %d %d\n",fx,T[1].ans);
    }
    REP(i,(1<<k)) printf("%d%c",ans[i]," \n"[i==(1<<k)-1]);
}
/*
*/