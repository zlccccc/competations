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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
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
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int N;
int A[maxn];
int getans(int x) {
    int now=0,ret=0,i;
    FOR(i,1,N) {
        if (now<A[i]) {
            now=x;
            if (now>=A[i]) ret++;
            else return 0;
        } now-=A[i]+1;
    }
    printf("ret=%d; now=%d\n",ret,now);
    return ret;
}
int n;
int query(int x) {
    printf("? %d\n",x);
    fflush(stdout);
    int ret;
    if (N) ret=getans(x);
    else scanf("%d",&ret);
    if (ret==0) ret=INF/x+1;
    // printf("ret=%d\n",ret);
    return ret;
}
int main() {
    scanf("%d",&n);
    int i;
    // N=n; FOR(i,1,N) scanf("%d",&A[i]);
    int l=1,r=2000*2001;
    while (l<r) {
        int mid=(l+r)/2;
        int val=query(mid);
        if (val==1) r=mid;
        else l=mid+1;
    }
    int ans=r;
    // printf("area=%d\n",r);
    // all-area: r;
    FOR(i,1,min(r+1,n)) {
        int val=r/i; //length of each part
        if (val<=0) continue;
        // if ((r+1)%i!=0) continue;
        // printf("val=%d; r=%d\n",val,r);
        int h=query(val);
        ans=min(ans,h*val);
        // printf("   h=%d; val=%d\n",h,val);
    }
    printf("! %d\n",ans);
}
/*
10 1 1 1 1 1 1 1 1 1 1 1 1
5 1 1 1 1 4
6 1 1 4 4 4 4
*/