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

int n,m;
char A[107][67][67];
pair<bool,vector<pii>> xtoy(int x,int y) {
    int cmp0=0,cmp1=0,i,j;
    vector<pii> ret;
    FOR(i,1,n) FOR(j,1,m) {
        if (A[x][i][j]!=A[y][i][j]) {
            if (A[x][i-1][j]==A[x][i][j]) cmp1=1; // y is bigger
            if (A[y][i-1][j]==A[y][i][j]) cmp0=1; // x is bigger
            ret.push_back({i,j});
        }
    }
    // printf("cmp %d %d; cmp0=%d\n",x,y,cmp0);
    // for (auto p:ret) printf("(%d %d) ",p.first,p.second); puts("");
    return {cmp0,ret};
}
vector<ar3> ans;
int id[106];
int main() {
    int i,j,k,t;
    scanf("%d%d%d",&n,&m,&k); k++;
    FOR(t,1,k) FOR(i,1,n) scanf("%s",A[t][i]+1);
    FOR(i,1,k) id[i]=i;
    sort(id+1,id+1+k,[&](int i,int j){
        return xtoy(i,j).first;
    });
    FOR(i,2,k) {
        auto p=xtoy(id[i-1],id[i]);
        for (auto v:p.second) ans.push_back({1,v.first,v.second});
        ans.push_back({2,id[i],0});
    }
    printf("%d\n",id[1]);
    printf("%d\n",(int)ans.size());
    for (ar3 p:ans) {
        if (p[0]==1) printf("%d %d %d\n",p[0],p[1],p[2]);
        if (p[0]==2) printf("%d %d\n",p[0],p[1]);
    } 
}
/*
*/