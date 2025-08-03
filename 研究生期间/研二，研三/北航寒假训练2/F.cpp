#include <sstream>
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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=1e6+1007;
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

int n;
int A[1007][1007];
int MIN[maxn*4*2];
int more=0;
void solve(int x,int l,int r,int val,int L,int R) {
    if (MIN[x]>=val) return;
    if (l<=L&&R<=r) {
        // printf("x=%d: MIN=%d (%d-%d)\n",x,MIN[x],L,R);
        more=max(more,val-MIN[x]);
        MIN[x]=max(MIN[x],val); // setmax
        return;
    }
    MIN[x<<1]=max(MIN[x<<1],MIN[x]);
    MIN[x<<1|1]=max(MIN[x<<1|1],MIN[x]);
    int mid=(L+R)/2;
    if (l<=mid) solve(x<<1,l,r,val,L,mid);
    if (mid<r) solve(x<<1|1,l,r,val,mid+1,R);
    MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}
int main() {
    int n,i,j; int vx,vy;
    scanf("%d%d%d",&n,&vx,&vy);
    REP(i,n) REP(j,n) scanf("%d",&A[i][j]);
    vector<ar4> arr;
    vector<int> vec;
    REP(i,n) REP(j,n) {
        int l=INF,r=-INF; int a,b;
        REP(a,2) REP(b,2) {
            l=min(l,(i+a)*vy-(j+b)*vx),r=max(r,(i+a)*vy-(j+b)*vx);
        }
        arr.push_back({vx*i+vy*j,A[i][j],l,r-1});// left
        // printf("solve %d,%d: %d %d %d %d\n",i,j,vx*i+vy*j,A[i][j],l,r);
        vec.push_back(l); vec.push_back(r-1); //smaller than r
        vec.push_back(r);
    }
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(), vec.end()),vec.end());
    function<int(int)> getid=[&](int x) {
        return lower_bound(vec.begin(),vec.end(),x)-vec.begin()+1;
    };
    sort(arr.begin(),arr.end());
    ll ans=0;
    // printf("vecsize %d ",vec.size());
    for (auto val:arr) {
        int l=getid(val[2]),r=getid(val[3]);
        // if (val[1]) printf("solve insert p=%d; %d %d (%d)\n",val[0],l,r,val[1]);
        more=0; solve(1,l,r,val[1],1,vec.size());
        // printf("more=%d\n",more);
        ans+=more;
    }
    printf("%lld\n",ans);
}
/*
1 7500
2 6000
5 4000
*/