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

int A[maxn],B[maxn];
int in[maxn];
vector<int> edge[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,i,k;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) edge[i].clear(),in[i]=0;
        FOR(i,1,n) scanf("%d",&A[i]);
        FOR(i,1,m) {
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            in[v]++;
        }
        bool mark=0;
        FOR(k,1,n+1) {
            mark=1;
            FOR(i,1,n) B[i]=A[i];
            FOR(i,1,n) if (A[i]) {
                B[i]--; mark=0;
                for (int v:edge[i]) B[v]++;
            }
            FOR(i,1,n) A[i]=B[i];
            if (mark) break;
        }
        if (mark) {printf("%d\n",k-1); continue;}
        // puts("??");
        int val=k-1;
        queue<int> Q;
        FOR(i,1,n) if (!in[i]) Q.push(i);
        FOR(i,1,n) A[i]%=M;
        while (Q.size()) {
            int x=Q.front(); Q.pop();
            // printf("x=%d\n",x);
            for (int v:edge[x]) {
                add_(A[v],A[x]); in[v]--;
                if (!in[v]) Q.push(v);
            }
        }
        FOR(i,1,n) if (!edge[i].size()) printf("%lld\n",(A[i]+val)%M);
    }
}