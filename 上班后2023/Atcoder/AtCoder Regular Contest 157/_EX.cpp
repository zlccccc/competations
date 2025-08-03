// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
// const LL M=1e9+7;
const LL M=998244353;
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

ll Ans[607][157][157];
int A[307],B[307];
int main() {
    int N,M; ll mor=0;
    scanf("%d%d",&N,&M);
    FOR_(i,1,N) scanf("%d",&A[i]);
    FOR_(i,1,M) scanf("%d",&B[i]);
    sort(A+1,A+1+N);
    sort(B+1,B+1+M);
    if (N&1) {
        if (M&1) mor+=A[N];
        FOR_(i,1,M) mor+=B[i];
        N--;
    }
    if (M&1) {
        FOR_(i,1,N) mor+=A[i];
        M--;
    }
    vector<pair<int,int>> Ani;
    FOR_(i,1,N) Ani.push_back({A[i],0});
    FOR_(i,1,M) Ani.push_back({B[i],1});
    sort(Ani.begin(), Ani.end());
    // reverse(Ani.begin(), Ani.end());
    memset(Ans,0x3f,sizeof(Ans));
    Ans[0][0][0]=0;
    int dog=0,cat=0;
    REP_(_,(int)Ani.size()) {
        pii p=Ani[_];
        ll val=p.first; int o=p.second;
        if (o==0) {
            FOR_(i,0,min(dog,N/2)) {
                FOR_(j,0,min(cat,M/2)) {
                    min_(Ans[_+1][i+1][j],Ans[_][i][j]+val*(M-j*2));
                    min_(Ans[_+1][i][j],Ans[_][i][j]+val*(M-(cat-j)*2));
                }
            }
            dog++;
        } else {
            FOR_(i,0,min(dog,N/2)) {
                FOR_(j,0,min(cat,M/2)) {
                    min_(Ans[_+1][i][j+1],Ans[_][i][j]+val*(N-i*2));
                    min_(Ans[_+1][i][j],Ans[_][i][j]+val*(N-(dog-i)*2));
                }
            }
            cat++;
        }
        // printf("solve %lld %d\n",val,o);
        // FOR_(i,0,min(dog,N/2)) {
        //     FOR_(j,0,min(cat,M/2)) {
        //         printf("%lld ",Ans[_+1][i][j]);
        //     } puts("");
        // }
    }
    printf("%lld\n",Ans[Ani.size()][N/2][M/2]+mor);
}
/*
*/