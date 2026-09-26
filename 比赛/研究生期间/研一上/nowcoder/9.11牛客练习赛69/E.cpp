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


int lowbit(int x){
    return x&-x;
}
int c[maxn];
int presum(int x){
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=c[x];
    return ret;
}
int sum(int l,int r){
    int ret=presum(r);
    if (l-1) ret-=presum(l-1);
    return ret;
}
void add(int x,int d){//修改不如add有效 
    for (;x<=1000000;x+=lowbit(x)) c[x]+=d;
}
int A[maxn];
vector<pii> V;
vector<pii> upd[maxn];
int L[maxn],R[maxn];
int main() {
    int n,i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    V.push_back(make_pair(INF,0));
    FOR(i,1,n) {
        while (V.rbegin()->first<=A[i]) V.pop_back();//lower
        // printf("size=%d\n",(int)V.size());
        V.push_back(make_pair(A[i],i));
        // for (auto v:V) printf("%d(%d) ",v.first,v.second);puts("");
        // printf("size=%d\n",(int)V.size());
        //get
        int pos=lower_bound(V.begin(),V.end(),make_pair(i,INF),greater<pii>())-V.begin();
        if (pos==(int)V.size()||V[pos].first!=i) continue;
        int l=V[pos-1].second+1,r=V[pos].second;
        L[i]=l; R[i]=r;
    }
    V.clear();

    V.push_back(make_pair(-INF,n+1));
    rFOR(i,1,n) {
        while (V.rbegin()->first>=A[i]) V.pop_back();//lower
        // printf("size=%d\n",(int)V.size());
        V.push_back(make_pair(A[i],i));
        // printf("size=%d\n",(int)V.size());
        //get
        int pos=lower_bound(V.begin(),V.end(),make_pair(i,-INF))-V.begin();
        // printf("pos=%d\n",pos);
        if (pos==(int)V.size()||V[pos].first!=i) continue;
        int l=V[pos].second,r=V[pos-1].second-1;
        upd[l].push_back(make_pair(i,1)); upd[r+1].push_back(make_pair(i,-1));
        // printf("l=%d: pos=%d-%d\n",i,l,r);
    }
    ll ans=0;
    FOR(i,1,n) {
        for (auto now:upd[i]) add(now.first,now.second);
        if (L[i]) ans+=sum(L[i],R[i]);
    }printf("%lld\n",ans);
}
/*
5
5 4 3 2 1
9
8 5  4 6 7 5 9 2 1 3
*/