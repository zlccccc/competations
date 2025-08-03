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
 
inline int addx(int A,int B,int MOD) {A+=B; (A>=MOD) &&(A-=MOD); return A;}
int m;
int A[maxn];
int L[maxn][27],R[maxn][27];
int ans[maxn];
void solve(int l,int r,const vector<pair<pii,int> > &Q) {
    int i,k,mid=(l+r)/2;
    vector<pair<pii,int> > Ql,Qr,Qn;
    for (auto now:Q) {
        if (now.first.second<mid) Ql.push_back(now);
        else if (now.first.first>mid) Qr.push_back(now);
        else Qn.push_back(now);
    }
    // printf("%d-%d:",l,r);
    // for (auto now:Q) printf("(%d %d) ",now.first.first,now.first.second); puts("<- now");
    REP(k,m) R[mid-1][k]=0; R[mid-1][0]=1;
    FOR(i,mid,r) REP(k,m) R[i][k]=(R[i-1][k]+R[i-1][addx(k,m-A[i],m)])%M;
    REP(k,m) L[mid][k]=0; L[mid][0]=1;
    rFOR(i,l,mid-1) REP(k,m) L[i][k]=(L[i+1][k]+L[i+1][addx(k,m-A[i],m)])%M;
    for (auto now:Qn) {
        int nowans=0;
        // printf("%d-%d\n",now.first.first,mid-1);
        // REP(k,m) printf("%d ",L[now.first.first][k]); puts("<-L");
        // printf("%d-%d\n",mid,now.first.second);
        // REP(k,m) printf("%d ",R[now.first.second][k]); puts("<-R");
 
        REP(k,m) nowans=(nowans+(ll)L[now.first.first][k]*R[now.first.second][(m-k)%m])%M;
        ans[now.second]=nowans;
    }
    if (l==r) return;
    solve(l,mid,Ql); solve(mid+1,r,Qr);
}
vector<pair<pii,int> > Q;
int main() {
    int n,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&A[i]),A[i]%=m;
    int q; scanf("%d",&q);
    FOR(i,1,q) {
        int l,r; scanf("%d%d",&l,&r);
        Q.push_back(make_pair(make_pair(l,r),i));
    } solve(1,n,Q);
    FOR(i,1,q) printf("%d\n",ans[i]);
}
/*
4 3
5 1 3 2
6
1 2
1 3
1 4
2 4
2 2
3 3
*/