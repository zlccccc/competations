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
typedef array<int,4> ar4;

ll A[maxn];
vector<int> edge[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int n,i,k;
        scanf("%d%d",&n,&k); // n>1
        FOR(i,1,n) edge[i].clear();
        FOR(i,2,n) {
            int fa; scanf("%d",&fa);
            edge[fa].push_back(i);
        }
        FOR(i,1,n) scanf("%lld",&A[i]);
        vector<ll> maxsub(n+1,0);
        function<ll(int,int)> dfs=[&](int x,int k) {
            ll ret=(ll)A[x]*k;
            maxsub[x]=A[x];
            if (edge[x].size()==0) return ret;
            vector<ll> sub;
            for (int v:edge[x]) {
                ret+=dfs(v,k/edge[x].size());
                sub.push_back(maxsub[v]);
            }
            if (edge[x].size()) {
                k%=edge[x].size();
                // printf("x=%d; k=%d\n",x,k);
                sort(sub.begin(),sub.end());
                reverse(sub.begin(),sub.end());
                for (ll v:sub) {
                    if (k) k--,ret+=v;
                    else max_(maxsub[x],v+A[x]); // single
                }
            }
            return ret;
        }; // ok1: all single path; ok2:
        printf("%lld\n",dfs(1,k));
    }
}
/*
10000
20 1000000000
1 14 13 6 8 2 1 3 4 15 2 2 6 6 15 5 15 7 8
9148 7919 2092 6541 1439 9016 3384 7482 2615 3252 313 9261 6745 1022 1086 8986 4345 3605 8317 6189
20 1000000000
1 2 18 4 5 16 2 15 2 15 18 2 2 1 2 1 11 20 10
2589 9610 387 6819 1917 695 4305 3461 8705 4065 8490 313 2877 2098 5880 9110 971 1237 6819 6433
20 1000000000
13 1 16 11 13 4 15 14 17 16 17 15 13 1 17 1 19 13 19
2396 9486 7306 5677 3679 9750 6607 8704 2340 5338 9880 4390 4363 3175 4505 4273 6138 9681 1296 4497
*/