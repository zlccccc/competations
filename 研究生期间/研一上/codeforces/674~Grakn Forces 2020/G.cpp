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
const LL maxn=1.5e6+107;
const double pi=acos(-1.0);
const double eps=1e-7;
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

vector<pii> v[maxn];
int fa[maxn],sz[maxn],cnt[maxn];
int C[1607][1607];
inline int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int tmp[maxn];
int main() {
    int n,i,j;
    scanf("%d",&n);
    FOR(i,1,n) {
        FOR(j,1,n) {
            int val; scanf("%d",&val);
            v[val].push_back(make_pair(i,j));
        }
    }
    FOR(i,1,n) fa[i]=i,sz[i]=1;
    FOR(i,0,n*n/2) {
        for (auto now:v[i]) {
            int x=now.first,y=now.second;
            // printf("solve merge %d %d\n",x,y);
            x=getfa(x); y=getfa(y);
            if (x!=y) {
                int j,k;
                FOR(j,1,sz[x]+sz[y]) tmp[j]=0;
                FOR(j,1,sz[x]) FOR(k,1,sz[y]) {
                    add_(tmp[j+k],(ll)C[x][j]*C[y][k]%M);
                }
                FOR(j,1,sz[x]+sz[y]) C[y][j]=tmp[j];
                fa[x]=y; sz[y]+=sz[x]; cnt[y]+=cnt[x];
            } x=getfa(x);
            cnt[x]++;
            if (cnt[x]==sz[x]*sz[x]) C[x][1]++;
            // printf("solve merge %d; cnt=%d\n",x,cnt[x]);
        }
    } int x=getfa(1);
    FOR(i,1,n) printf("%d%c",C[x][i]," \n"[i==n]);
}
/*
*/