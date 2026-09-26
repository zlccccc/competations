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
const LL maxn=1e7+107;
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

int val[maxn],sum[maxn]; 
int fac[20006007],inv[20006007];
pair<int,int> id[10007];
int now[10007];//last=this的val_sum
LL C(int n,int m){
    return (ll)fac[n]*inv[m]%M*inv[n-m]%M;
}
ll getval(ll n,ll k,ll m) {
    if (n<k*m) return 0;
    return C(n-k*m+k-1,k-1);
}
int main() {
    // startTimer();
    int i,j;
    fac[0]=1;
    FOR(i,1,20006000) fac[i]=(ll)i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,20006000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,20006000) inv[i]=(ll)inv[i]*inv[i-1]%M;// inv(n!)
    // printTimer();
    int L,d,m;
    scanf("%d%d%d",&L,&d,&m);
    val[0]=sum[0]=1;
    FOR(i,1,L) {
    	sum[i]=sum[i-1];
    	if (i>=d) add_(val[i],sum[i-d]);
    	add_(sum[i],val[i]);
    }
    // FOR(i,1,L) printf("%d ",val[i]); puts("<- val");
    // FOR(i,1,L) printf("%d ",sum[i]); puts("<- sum");
    FOR(i,1,m) scanf("%d%d",&id[i].first,&id[i].second);
    sort(id+1,id+1+m);
    int ans=val[L];//i times
    FOR(i,1,m) {//use_this; last=i
        now[i]=M-getval(id[i].second,id[i].first,d);
        FOR(j,1,i-1) if (id[i].first-id[j].first>0&&id[i].second>id[j].second){
            add_(now[i],(M-getval(id[i].second-id[j].second,id[i].first-id[j].first,d))*now[j]%M);
        } add_(ans,now[i]*val[L-id[i].second]%M);
    } printf("%d\n",ans);
}
/*
10 1 0
*/