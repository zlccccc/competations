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

struct node{
    int val,l,r;
}T[maxn*32];
int ntot=0;;
void update(int &x,int pos,int L,int R) {
    if (!x) x=++ntot;
    T[x].val++;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,L,mid);
    if (mid<pos) update(T[x].r,pos,mid+1,R);
}
int query(int x,int l,int r,int L,int R) {
    if (!x) return 0;
    if (l<=L&&R<=r) return T[x].val;
    int ret=0,mid=(L+R)/2;
    if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
    if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
    return ret;
}
vector<int> edge[maxn];
int in[maxn],out[maxn],tot=0;
void dfs(int x) {
    in[x]=++tot;
    for (int v:edge[x]) {
        dfs(v);
    } out[x]=tot;
}
set<pii> S;
int root[maxn],fa[maxn];
int main() {
    int n,m,i;
    scanf("%d",&n);
    FOR(i,2,n) scanf("%d",&fa[i]),edge[fa[i]].push_back(i);
    dfs(1);
    scanf("%d",&m);
    FOR(i,1,m) {
        int x,y,op;
        scanf("%d%d%d",&op,&x,&y);
        // printf("%d -> %d\n",in[x],out[x]);
        if (op==1) {
            if (S.count(make_pair(x,y))) continue;
            S.insert(make_pair(x,y));
            update(root[y],in[x],1,n);
        } else {
            printf("%d\n",query(root[y],in[x],out[x],1,n));
        }
    }
}
/* 
1 4
*/