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
const LL maxn=2e5+107;
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
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

int A[maxn];
char s[4];
int mat[3][4][4];
int cnt[4][4];
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    REP_(x,3) REP_(i,4) {
        scanf("%s",s);
        REP_(j,4) mat[x][i][j]=(s[j]=='#');
    }
    auto rotate=[&](int mat[4][4]) {
        static int tmp[4][4];
        REP_(i,4) REP_(j,4) {
            tmp[j][3-i]=mat[i][j];
        }
        REP_(i,4) REP_(j,4) mat[i][j]=tmp[i][j];
    };
    function<bool(int)> dfs=[&](int len) {
        if (len==3) {
            REP_(i,4) REP_(j,4) {
                if (cnt[i][j]!=1) return false;
            }
            return true;
        }
        bool ret=0;
        REP_(r,4) {
            FOR_(dx,-4,4) FOR_(dy,-4,4) {
                bool down=1;
                REP_(i,4) REP_(j,4) if (mat[len][i][j]) {
                    if (i+dx<0||j+dy<0||i+dx>=4||j+dy>=4) down=0;
                    else cnt[i+dx][j+dy]++;
                }
                // if (len==0&&down) {
                //     printf("solve %d %d %d\n",r,dx,dy);
                //     printf("len=%d\n",len);
                //     REP_(i,4) REP_(j,4) printf("%d%c",cnt[i][j]," \n"[j==3]);
                // }
                if (down) ret|=dfs(len+1);
                REP_(i,4) REP_(j,4) if (mat[len][i][j]) {
                    if (i+dx<0||j+dy<0||i+dx>=4||j+dy>=4) down=0;
                    else cnt[i+dx][j+dy]--;
                }
            }
            rotate(mat[len]);
        }
        return ret;
    };
    if (dfs(0)) puts("Yes");
    else puts("No");
}
/*
*/