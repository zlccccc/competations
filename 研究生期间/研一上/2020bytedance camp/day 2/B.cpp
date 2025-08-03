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
const LL maxn=4e5+7;
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
    int l,r,sum;
}T[maxn*32];
int dfn[maxn],lid[maxn],rid[maxn],idx[maxn],tot;
inline void update(int &x,int y,int pos,int l,int r) {
    T[x=++tot]=T[y]; T[x].sum++;
    if (l==r) return;
    int mid=(l+r)/2;
    if (pos<=mid) update(T[x].l,T[y].l,pos,l,mid);
    else update(T[x].r,T[y].r,pos,mid+1,r); 
}
inline int query(int x,int l,int r,int L,int R) {
    if (!x) return 0;
    if (l<=L&&R<=r) return T[x].sum;
    int mid=(L+R)/2,ret=0;
    if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
    if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
    return ret;
}
int l[maxn],r[maxn];
void dfs(int x) {
    if (x==0) return;
    lid[x]=tot+1; dfs(l[x]);
    dfn[x]=++tot; idx[tot]=x;
    dfs(r[x]); rid[x]=tot;
}
set<int> S;
int root[maxn];
vector<int> rs[maxn];
int ans=0,n;
pii query(int pos) {
    int l,r; auto it=S.lower_bound(pos);
    r=*it; it--; l=(*it)+1;
    return make_pair(l,r);
}
int A[maxn];
inline void update(int pos,int val) {
    pii now; int l,r;
    now=query(pos); l=now.first; r=now.second;
    // printf("erase %d %d %d,%d,%d\n",l,pos,r,query(root[pos],pos,r,1,n),query(root[l-1],pos,r,1,n));
    ans-=query(root[pos],pos,r,1,n)-query(root[l-1],pos,r,1,n);
    if (A[pos-1]>A[pos]) S.erase(pos-1);
    if (A[pos]>A[pos+1]) S.erase(pos);
    A[pos]=val;
    if (A[pos-1]>A[pos]) S.insert(pos-1);
    if (A[pos]>A[pos+1]) S.insert(pos);
    now=query(pos); l=now.first; r=now.second;
    // printf("add %d %d %d=%d\n",l,pos,r,query(root[pos],pos,r,1,n)-query(root[l-1],pos,r,1,n));
    ans+=query(root[pos],pos,r,1,n)-query(root[l-1],pos,r,1,n);
    // int i; FOR(i,1,n) printf("%d ",A[i]); puts("  <- A");
    // for (auto now:S) printf("%d ",now); puts(" <- nowok");
    // printf("ans=%d\n",ans);
}
int main() {
    int i,q;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%d%d",&l[i],&r[i]);
    dfs(1);
    S.insert(0); S.insert(n); ans=n;
    A[0]=INF; A[n+1]=-INF;
    // FOR(i,1,n) printf("%d %d  <- p\n",lid[i],rid[i]);
    FOR(i,1,n) rs[lid[i]].push_back(rid[i]);
    FOR(i,1,n) {
        root[i]=root[i-1];
        for (int v:rs[i]) update(root[i],root[i],v,1,n);
    }
    FOR(i,1,n) {
        int k; scanf("%d",&k);
        update(dfn[i],k);
    }
    FOR(i,1,q) {
        int x,y; scanf("%d%d",&x,&y);
        update(dfn[x],y);
        printf("%d\n",ans);
    }
}
/*
6 5
2 3
4 0
5 6
0 0
0 0
0 0
4 1 3 2 2 5
3 3
2 2
3 5
5 4
6 1

8 10
4 5
8 0
0 0
3 7
0 6
0 0
2 0
0 0
7 0 9 3 6 0 6 2
3 0
4 0
8 2
2 3
7 6
1 6
5 7
6 9
1 1
1 7
*/