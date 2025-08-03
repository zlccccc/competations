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
// const LL M=585698298;
const LL M=998244353;
// const LL M=1e9+7;
// ll M=1;
const LL maxn=2e6+107;
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

// 二分答案check; 考虑x-max<=MAX的时候y-min是多少就可以了
int main() {
    int n,m,i,j;
    scanf("%d%d",&n,&m);
    vector<vector<int>> A(n+1,vector<int>(m+1));
    vector<vector<int>> revA(m+1,vector<int>(n+1));
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&A[i][j]),revA[j][i]=A[i][j];
    vector<int> bestx,besty;
    function<bool(int)> work=[&](int val) {
        bool ok=0;
        for (int o=0;o<2;o++) {
            vector<vector<int>> lv(n+1,vector<int>(m+1));
            vector<vector<int>> rv(n+1,vector<int>(m+1));
            vector<int> x(n+1);
            FOR(i,1,n) x[i]=i;
            FOR(i,1,n) FOR(j,1,m) {
                lv[i][j]=max(1,A[i][j]-val);
                rv[i][j]=A[i][j]+val;
            }
            // printf("tmp=%d\n",val);
            const int MAX=5e4;
            while (x[n]<=MAX) {
                int i,j;
                bool changed=0;
                // initialize
                vector<int> ly(m+2,-INF);
                vector<int> ry(m+2,INF*2);
                // int ry=INF*2,id;
                int id;
                FOR(i,1,n) {
                    rFOR(j,1,m) {
                        int nowl=max(1,(lv[i][j]+x[i]-1)/x[i]);
                        int nowr=rv[i][j]/x[i];
                        // ly[i][yi]-yi > ry[j][yj]-yj (all)
                        max_(ly[j],nowl);
                        min_(ry[j],nowr);
                        min_(ry[j],ry[j+1]-1);
                    }
                }
                rFOR(i,1,n) {
                    FOR(j,1,m) {
                        int nowl=max(1,(lv[i][j]+x[i]-1)/x[i]);
                        if (nowl>ry[j]) changed=1,id=i;
                    }
                }
                if (changed) {
                    x[id]++;
                    int k=id;
                    while (k<n&&x[k]==x[k+1]) {
                        k++; x[k]++;
                    }
                }
                // if (!changed) {
                //     vector<int> ly(m+2,-INF);
                //     vector<int> ry(m+2,INF*2);
                //     FOR(i,1,n) {
                //         FOR(j,1,m) {
                //             int nowl=max(1,(lv[i][j]+x[i]-1)/x[i]);
                //             int nowr=rv[i][j]/x[i];
                //             max_(ly[j],nowl);
                //             min_(ry[j],nowr);
                //             min_(ry[j],ry[j+1]-1);
                //             // if (nowl>ry[j]) changed=1,id=i;
                //             printf("%d,%d ",nowl,nowr);
                //         } puts("");
                //     }
                //     FOR(i,1,n) printf("%d ",x[i]); puts("<- x");
                //     FOR(i,1,m) printf("%d ",ly[i]); puts("<- ly");
                //     FOR(i,1,m) printf("%d ",ry[i]); puts("<- ry");
                // }
                if (!changed) break;
            }
            // puts("checked");
            if (x[n]<=MAX) {
                bestx.clear(); bestx.resize(n+1,0);
                besty.clear(); besty.resize(m+1,0);
                FOR(i,1,n) bestx[i]=x[i];
                FOR(i,1,n) FOR(j,1,m) besty[j]=max(besty[j],max(1,(lv[i][j]+x[i]-1)/x[i]));
                FOR(j,1,m) besty[j]=max(besty[j],besty[j-1]+1);
                ok=1;
            }
            // puts("done");
            // printf("mid=%d\n",val);
            // FOR(i,1,n) printf("%d ",x[i]); puts("<- x");
            // FOR(i,1,n) FOR(j,1,m)
            //     printf("%d-%d%c",ly[i][j],ry[i][j]," \n"[j==m]);
            // rotate
            swap(n,m);
            swap(bestx,besty);
            swap(A,revA);
        }
        return ok;
    };
    // int l=-1,r=10;
    int l=-1,r=INF;
    while (l+1<r) {
        int mid=(l+r)/2;
        if (work(mid)) r=mid;
        else l=mid;
    }
    work(r);
    printf("%d\n",r);
    FOR(i,1,n) printf("%d ",bestx[i]); puts("");
    FOR(i,1,m) printf("%d ",besty[i]); puts("");
}
/*

*/