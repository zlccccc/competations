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

int n,q,s,d;
set<pii> S;
int A[maxn];
int cnt[maxn];//in the set
priority_queue<pair<int,pii> > Q;
void push(int x,int y) {
    int dis=abs(d-abs(A[x]-A[y]));
    Q.push(make_pair(-dis,make_pair(x,y)));
    cnt[x]++;
}
void findpos(int pos,int id) {
    pii x=make_pair(pos,id);
    auto it=S.lower_bound(x);
    if (it!=S.end()) push(id,it->second);
    if (it!=S.begin()) it--,push(id,it->second);
}
int val[maxn];//idx; time
int main() {
    int i;
    scanf("%d%d%d%d",&n,&q,&s,&d);
    FOR(i,1,n) scanf("%d",&A[i]),S.insert(make_pair(A[i],i));
    memset(val,0xff,sizeof(val));
    int k=0; Q.push(make_pair(0,make_pair(s,s))); cnt[s]++;
    while (Q.size()) {
        k=max(k,-Q.top().first);
        pii edge=Q.top().second; Q.pop();
        int x=edge.first,y=edge.second;
        if (val[y]!=-1) continue;
        val[y]=k;
        S.erase(S.lower_bound(make_pair(A[y],0)));
        findpos(A[y]-d,y),findpos(A[y]+d,y);
        findpos(A[x]-d,x),findpos(A[x]+d,x);
    }
    // FOR(i,1,n) printf("%d ",val[i]); puts("<- i");
    FOR(i,1,q) {
        int pos,k; scanf("%d%d",&pos,&k);
        puts(val[pos]<=k?"Yes":"No");
    }
}
/*
10
3 -20 26
4 -3 5
42 -33 55
69 -42 146
*/
