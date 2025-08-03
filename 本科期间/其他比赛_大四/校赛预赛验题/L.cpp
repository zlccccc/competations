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

struct Point {
    ll x,y;
    double angle;
    Point(ll x = 0 , ll y = 0):x(x),y(y) {
        angle=atan2(y , x);
    }
    void input() {
        scanf("%lld%lld",&x,&y);
        angle=atan2(y , x);
    }
    Point operator + (const Point &R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point &R) const {
        return Point(x - R.x , y - R.y);
    }
    ll operator % (const Point &R) const {
        return x * R.x + y * R.y;
    }
    ll len() {
        return *this % *this;
    }
} p[maxn];
int main() {
    // printf("%f\n",Point(-1,0).angle);
    int n,i;
    scanf("%d",&n);
    FOR(i,1,n) {
        Point x,y;
        x.input(); y.input();
        p[i*2]=y-x;
        p[i*2-1]=x-y;
    } n+=n;
    // FOR(i,1,n) printf("%d %d\n",p[i].x,p[i].y);
    sort(p+1,p+1+n,[](Point x, Point y) {
        return x.angle<y.angle;
    });
    int st=0; ll ans=0;
    p[0]=Point(0,0);
    FOR(i,1,n) p[i]=p[i]+p[i-1];
    FOR(i,1,n) p[i+n]=p[i],ans=max(ans,p[i].len());
    FOR(i,1,n+n) {
        while (st<=i&&(p[st+1]-p[i]).len()>(p[st]-p[i]).len()) st++;
        ans=max(ans,(p[st]-p[i]).len());
        // printf("%d %d  (%d)%d %d\n",p[i].x,p[i].y,st,p[st].x,p[st].y);
    }
    printf("%lld",ans);
}
/*
1
1 1 1 1
*/