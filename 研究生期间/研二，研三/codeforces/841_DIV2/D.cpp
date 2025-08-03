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
// const LL M=998244353;
const ll M=1e9+7;
const LL maxn=1e5+107;
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

int n,m;
vector<vector<int> > A;
bool solve(int k) {
    // printf("k=%d\n",k);
    vector<vector<int>> B(n+1,vector<int>(m+1,0));
    int i,j;
    FOR(i,1,n) {
        deque<int> Q;
        FOR(j,1,m) {
            if (Q.size()&&j-*Q.begin()==k) Q.pop_front();
            while (Q.size()&&A[i][*Q.rbegin()]>=A[i][j]) Q.pop_back();
            Q.push_back(j);
            B[i][j]=A[i][*Q.begin()];
        }
    }
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",B[i][j]," \n"[j==m]);
    vector<vector<int>> C(n+1,vector<int>(m+1,0));
    FOR(i,1,m) {
        deque<int> Q;
        FOR(j,1,n) {
            if (Q.size()&&j-*Q.begin()==k) Q.pop_front();
            while (Q.size()&&B[*Q.rbegin()][i]>=B[j][i]) Q.pop_back();
            Q.push_back(j);
            C[j][i]=B[*Q.begin()][i];
        }
    }
    // FOR(i,1,n) FOR(j,1,m) printf("%d%c",C[i][j]," \n"[j==m]);
    FOR(i,k,n) FOR(j,k,m) if (C[i][j]>=k) return 1;
    return 0;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,j;
        scanf("%d%d",&n,&m);
        A.clear();
        A.resize(n+1,vector<int>(m+1,0));
        FOR(i,1,n) FOR(j,1,m) scanf("%d",&A[i][j]);
        int l=1,r=min(n,m)+1; // r:not_okay
        while (l+1<r) {
            int mid=(l+r)/2;
            if (solve(mid)) l=mid;
            else r=mid;
        } printf("%d\n",l);
    }
}
/*
10
3 4
1 1 1 0
0 0 1 0
1 0 0 1
4 3
1 0 0
0 1 1
0 0 1
0 0 0
2 2
0 0
0 1
2 2
0 0
0 0
*/