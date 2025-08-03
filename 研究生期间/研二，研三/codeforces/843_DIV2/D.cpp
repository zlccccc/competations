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
#include <functional>
#include <random>
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
// const LL M=998244353;
// ll M=1;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
 
int A[maxn];
int pid[maxn];
vector<int> ids[maxn]; //A[i]==i
vector<int> sub[maxn]; //i%k==0
bool vis[maxn];
int main() {
    int n,S,T,i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]),ids[A[i]].push_back(i);
    scanf("%d%d",&S,&T);
    FOR(i,2,3e5+7) if (!sub[i].size()) { // prime
        for (int j=i;j<=3e5+7;j+=i) sub[j].push_back(i);
    }
    queue<int> Q; Q.push(S); pid[S]=S;
    while (Q.size()) {
        int x=Q.front(); Q.pop();
        // printf("x=%d  %d\n",x,A[x]);
        for (int k:sub[A[x]]) if (!vis[k]) { // t=ik
            for (int t=k;t<=3e5+7;t+=k) {
                for (int id:ids[t]) {
                    pid[id]=x; Q.push(id);
                    // printf("push %d  %d\n",,id);
                } ids[t].clear();
            }
            vis[k]=1;
        }
        sub[A[x]].clear();
    }
    if (!pid[T]) return 0*puts("-1");
    vector<int> ans;
    for (int x=T;x!=S;x=pid[x]) ans.push_back(x);
    ans.push_back(S);
    reverse(ans.begin(),ans.end());
    printf("%d\n",(int)ans.size());
    for (int v:ans) printf("%d ",v);
}
/*
*/