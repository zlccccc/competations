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

int Rmax[maxn*4],sz[maxn*4];
void update(int x,int pos,int val,int L,int R) {
    // printf("val=%d\n",val);
    if (L==R) {
        sz[x]+=val;
        Rmax[x]=L+sz[x]-1;
        if (!sz[x]) Rmax[x]=0;
        return;
    } int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    else update(x<<1|1,pos,val,mid+1,R);
    Rmax[x]=max(Rmax[x<<1]+sz[x<<1|1],Rmax[x<<1|1]);
    sz[x]=sz[x<<1]+sz[x<<1|1];
    if (!sz[x]) Rmax[x]=0;
    // printf("update %d(%d-%d): %d %d; va=%d\n",x,L,R,Rmax[x],sz[x],val);
}
set<pii> points;
int main() {
    points.clear();
    int i,n,k,m; scanf("%d%d%d",&n,&k,&m);
    FOR(i,1,m) {
        int x,y; scanf("%d%d",&x,&y);
        int now=y+abs(x-k);
        // printf("%d\n",points.count(make_pair(x,y)));
        if (!points.count(make_pair(x,y))) {
            points.insert(make_pair(x,y));
            update(1,now,1,1,n*2);
        } else {
            points.erase(make_pair(x,y));
            update(1,now,-1,1,n*2);
        }
        // printf("now=%d; R=%d\n",now,Rmax[1]);
        printf("%d\n",max(0,Rmax[1]-n));
    }
}
/*
*/