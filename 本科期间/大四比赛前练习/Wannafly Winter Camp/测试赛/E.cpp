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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
// char str[maxn];

double _x[maxn],_y[maxn],r[maxn];
double getdis(int i,int j){
    double D=sqrt((_x[i]-_x[j])*(_x[i]-_x[j])+(_y[i]-_y[j])*(_y[i]-_y[j]));
    return max(.0,D-r[i]-r[j]);
} bool vis[maxn];
double dis[maxn];
int main() {
    int i; double C1,C2,A,B;
    scanf("%d%lf%lf%lf%lf",&n,&A,&B,&C1,&C2);
    double ans=abs(C1-C2)/sqrt(A*A+B*B);
    // printf("%f\n",ans);
    FOR(i,1,n) scanf("%lf%lf%lf",&_x[i],&_y[i],&r[i]);
    FOR(i,1,n) dis[i]=max(.0,abs(A*_x[i]+B*_y[i]+C1)/sqrt(A*A+B*B)-r[i]);
    // FOR(i,1,n) printf("%f ",dis[i]);
    dis[0]=INFF;
    FOR(i,1,n) {
        int pos=0,j;
        FOR(j,1,n) if (!vis[j]&&dis[j]<dis[pos]) pos=j;
        vis[pos]=1;
        FOR(j,1,n) if (!vis[j]&&dis[pos]+getdis(pos,j)<dis[j])
            dis[j]=dis[pos]+getdis(pos,j);
    }
    FOR(i,1,n) ans=min(ans,dis[i]+max(.0,abs(A*_x[i]+B*_y[i]+C2)/sqrt(A*A+B*B)-r[i]));
    printf("%f\n",ans+eps);
}
/*
1 1 1 -1 -2
1 1 2
*/
