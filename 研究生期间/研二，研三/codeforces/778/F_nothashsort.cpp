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

char str[maxn];
void output(int k) {
    int n=strlen(str),i;
    REP(i,n) putchar(str[k^i]); puts("");
}
int n;
int Rank[maxn],tmprank[maxn];
vector<int> V;
vector<pii> VV;
int main() {
    int i,k;
    scanf("%d",&n); scanf("%s",str);
    REP(i,(1<<n)) Rank[i]=str[i]-'a';
    REP(i,(1<<n)) V.push_back(Rank[i]);
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    REP(i,(1<<n)) Rank[i]=lower_bound(V.begin(),V.end(),Rank[i])-V.begin();
    REP(k,n) {
        VV.clear();
        REP(i,(1<<n)) VV.push_back({Rank[i],Rank[i^(1<<k)]});
        sort(VV.begin(),VV.end());
        VV.erase(unique(VV.begin(),VV.end()),VV.end());
        REP(i,(1<<n)) tmprank[i]=lower_bound(VV.begin(),VV.end(),pii{Rank[i],Rank[i^(1<<k)]})-VV.begin();
        REP(i,(1<<n)) Rank[i]=tmprank[i];
    }
    int id=min_element(Rank,Rank+(1<<n))-Rank;
    output(id);
}
/*
*/