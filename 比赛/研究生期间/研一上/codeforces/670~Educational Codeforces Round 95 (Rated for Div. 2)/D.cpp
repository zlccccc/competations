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

multiset<int> S,A;
int all=0;//max=a.rbegin()
void Insert(int x) {
    int pre=0,nxt=0;
    auto it=S.lower_bound(x);
    if (it!=S.end()) nxt=*it;
    if (it!=S.begin()) {it--; pre=*it;}
    if (pre&&nxt) A.erase(A.lower_bound(nxt-pre)),all-=nxt-pre;
    if (nxt) A.insert(nxt-x),all+=nxt-x;
    if (pre) A.insert(x-pre),all+=x-pre;
    S.insert(x);
}
void Remove(int x) {
    int pre=0,nxt=0;
    S.erase(S.lower_bound(x));
    auto it=S.lower_bound(x);
    if (it!=S.end()) nxt=*it;
    if (it!=S.begin()) {it--; pre=*it;}
    if (pre&&nxt) A.insert(nxt-pre),all+=nxt-pre;
    if (nxt) A.erase(A.lower_bound(nxt-x)),all-=nxt-x;
    if (pre) A.erase(A.lower_bound(x-pre)),all-=x-pre;
}
void output() {
    int ans=all;
    if (A.size()) ans-=*(A.rbegin());
    printf("%d\n",ans);
}
int main() {
    int n,q,i;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) {
        int k;
        scanf("%d",&k);
        Insert(k);
    } output();
    FOR(i,1,q) {
        int op,k; scanf("%d%d",&op,&k);
        if (op==1) Insert(k);
        else Remove(k);
        output();
    }
}
/*
2
2 1
2 1
*/