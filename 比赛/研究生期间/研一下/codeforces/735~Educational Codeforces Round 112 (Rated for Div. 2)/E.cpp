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

int val[maxn*4],MIN[maxn*4];
void update(int x,int l,int r,int value,int L,int R) {
    if (l<=L&&R<=r) {val[x]=MIN[x]=value; return;}
    if (val[x]) {
        val[x<<1]=MIN[x<<1]=val[x];
        val[x<<1|1]=MIN[x<<1|1]=val[x];
        val[x]=0;
    }
    int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,value,L,mid);
    if (mid<r) update(x<<1|1,l,r,value,mid+1,R);
    MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}
pair<int,pii> A[maxn];
int main() {
    int n,m,i;
    // REP(j,6) puts(s[j]);
    scanf("%d%d",&n,&m); m--;
    FOR(i,1,n) scanf("%d%d%d",&A[i].second.first,&A[i].second.second,&A[i].first),A[i].second.second--;
    sort(A+1,A+1+n);
    int ans=INF;
    FOR(i,1,n) {
        update(1,A[i].second.first,A[i].second.second,A[i].first,1,m);
        if (MIN[1]) ans=min(ans,A[i].first-MIN[1]);
        // printf("update %d(%d-%d:%d) : %d\n",i,A[i].second.first,A[i].second.second,A[i].first,MIN[1]);
    } printf("%d\n",ans);
}
/*
5 4
baacb
1 3
1 5
4 5
2 3
*/