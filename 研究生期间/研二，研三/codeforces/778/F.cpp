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
// const int HashNum=3;
ull Hash[maxn][19],Mul[maxn];//this-value,hash
void output(int k) {
    int n=strlen(str),i;
    REP(i,n) putchar(str[k^i]); puts("");
}
int n;
int id[maxn],tmp[maxn];
bool cmp(int i,int j) {
    int depth=n;
    // printf("cmpini %d %d; dep=%d  hash-1=%ull %ull\n",i,j,depth,Hash[i][depth-1],Hash[j][depth-1]);
    // output(i); output(j);
    while (depth) {
        if (Hash[i][depth-1]==Hash[j][depth-1]) i^=1<<(depth-1),j^=1<<(depth-1);//this side same
        depth--;
    } 
    // printf("cmp %d %d; depth=%d; return=%d\n",i,j,depth,str[i]<str[j]);
    return str[i]<str[j];//same
}
void solve(int l,int r,int depth) {
    if (!depth) {id[l]=l; return;}
    int mid=(l+r)/2,i;
    solve(l,mid,depth-1); solve(mid,r,depth-1);
    rep(i,l,r) Hash[i][depth]=Hash[i][depth-1]*Mul[depth]+Hash[i^(1<<(depth-1))][depth-1];
}
int main() {
    int i,j,k,depth;
    scanf("%d",&n); scanf("%s",str);
    srand(time(0));
    FOR(i,0,100) Mul[i]=(rand()<<31)|rand();
    REP(i,(1<<n)) Hash[i][0]=str[i];
    solve(0,1<<n,n);
    REP(i,(1<<n)) if (cmp(i,id[0])) id[0]=i;
    // sort(id,id+(1<<n),cmp);
    // REP(i,(1<<n)) printf("%d ",id[i]);
    output(id[0]);
}
/*
*/