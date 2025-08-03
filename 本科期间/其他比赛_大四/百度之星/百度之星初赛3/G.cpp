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
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>MOD) &&(A-=MOD);}
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

int getcount(int x,int y,int z) {
    int mincount=3000; int i;
    FOR(i,0,1000) {
        int rem_y=1000-z*i;
        int rem_z=1000-y*i;
        if (rem_z+y<=0||rem_y+z<=0) continue;//last_value
        int cnt_xy=(max(0,rem_y)+x-1)/x;
        int cnt_xz=(max(0,rem_z)+x-1)/x;
        if (max(y*min(cnt_xy,1),z*min(cnt_xz,1))+1000-cnt_xy*y-cnt_xz*z<=0) continue;//dead
        if (mincount>i+cnt_xy+cnt_xz) {
            // printf("count=%d %d %d\n",i,cnt_xy,cnt_xz);
            // printf("%d %d %d  %d %d; last=%d\n",i,cnt_xy,cnt_xz,i*z+cnt_xy*x,i*y+cnt_xz*x,max(y*min(cnt_xy,1),z*min(cnt_xz,1))+1000-cnt_xy*y-cnt_xz*z);
            assert(1000<=i*z+cnt_xy*x);
            assert(1000<=i*y+cnt_xz*x);
        }
        min_(mincount,i+cnt_xy+cnt_xz);
    } return mincount;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        int ans=3000;
        min_(ans,getcount(x,y,z));
        min_(ans,getcount(y,x,z));
        min_(ans,getcount(z,x,y));
        printf("%d\n",ans);
    }
}
/*
1000
1000 1 1
*/