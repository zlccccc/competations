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

int op; pii val;
pii T[maxn<<2],lz[maxn<<2];
pii solve(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) {if (op) T[x]=max(T[x],val),lz[x]=max(lz[x],val); return T[x];}
    int mid=(L+R)/2; pii ret=make_pair(0,0);
    if (lz[x].first) {
        T[x<<1]=max(T[x<<1],lz[x]); lz[x<<1]=max(lz[x<<1],lz[x]);
        T[x<<1|1]=max(T[x<<1|1],lz[x]); lz[x<<1|1]=max(lz[x<<1|1],lz[x]);
        lz[x]=make_pair(0,0);
    }
    if (l<=mid) ret=max(ret,solve(x<<1,l,r,L,mid));
    if (mid<r) ret=max(ret,solve(x<<1|1,l,r,mid+1,R));
    T[x]=max(T[x<<1],T[x<<1|1]);
    // printf("solve %d %d %d: %d %d; op=%d; ret=%d %d\n",x,L,R,T[x].first,T[x].second,op,ret.first,ret.second);
    return ret;
}
vector<int> V;
inline int getid(int x) {return lower_bound(V.begin(),V.end(),x)-V.begin()+1;}
pii Prev[maxn],last;
vector<pii> Q[maxn];
bool mark[maxn];
int main() {
    int n,i,m;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) {
        int i,l,r;
        scanf("%d%d%d",&i,&l,&r);
        Q[i].push_back(make_pair(l,r));
        V.push_back(l); V.push_back(r);
    } sort(V.begin(), V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    int N=V.size();
    FOR(i,1,n) {
        op=0;
        for (auto p:Q[i]) {
            int l=getid(p.first),r=getid(p.second);
            pii ans=solve(1,l,r,1,N);
            Prev[i]=max(Prev[i],ans);
        }
        op=1; val=Prev[i];
        val.first++; val.second=i;
        for (auto p:Q[i]) {
            int l=getid(p.first),r=getid(p.second);
            pii ans=solve(1,l,r,1,N);
            last=max(last,ans);
            // printf("%d: (%d %d): %d %d -> %d %d\n",i,l,r,Prev[i].first,Prev[i].second,ans.first,ans.second);
        }
    }
    printf("%d\n",n-last.first);
    for (int x=last.second;x;x=Prev[x].second) mark[x]=1;
    FOR(i,1,n) if (!mark[i]) printf("%d ",i);
    //     for (auto now:Q[i]) printf("%d ",now.second);
    // }
}
/*
*/