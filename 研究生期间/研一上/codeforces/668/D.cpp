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

int mark[maxn];
int id[maxn];
vector<int> edge[maxn];
void dfs(int x,int y) {
    // printf("%d :%d\n",x,y);
    mark[x]=y;
    for (int v:edge[x]) if (mark[v]==-1) dfs(v,y^1);
}
int A[maxn];
int main() {
    int n,i;
    scanf("%d",&n);
    if (n%2==1) {
        puts("Second"); fflush(stdout);
        FOR(i,1,n*2) scanf("%d",&A[i]);
        // puts("???");
        FOR(i,1,n*2) id[A[i]]=i;
        FOR(i,1,n*2) if (id[A[i]]!=i) {
            edge[i].push_back(id[A[i]]);
            edge[id[A[i]]].push_back(i);
        }
        FOR(i,1,n) {edge[i].push_back(i+n); edge[i+n].push_back(i);};
        FOR(i,1,n*2) mark[i]=-1;
        FOR(i,1,n*2) if (mark[i]==-1) dfs(i,0);
        ll ans=0;
        FOR(i,1,n*2) if (mark[i]==0) ans+=i;
        if (ans%(n*2)==0) {
            FOR(i,1,n*2) if (mark[i]==0) printf("%d%c",i," \n"[i==n]);
        } else {
            FOR(i,1,n*2) if (mark[i]==1) printf("%d%c",i," \n"[i==n]);
        }
    } else {
        puts("First");
        FOR(i,1,n*2) printf("%d%c",i%n+1," \n"[i==n*2]);
    }
    fflush(stdout);
    scanf("%*d");
}
/*
3
1 1 2 2 3 3
*/