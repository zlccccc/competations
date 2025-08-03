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
#include <unordered_set>
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
ll M=1;
const LL maxn=3e5+107;
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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

struct node{
    int hsh,l,r;
}T[maxn*32]; int tot;
void update(int &x,int val,int l,int r,int L,int R) {
    T[++tot]=T[x]; x=tot;
    if (l<=L&&R<=r) {
        T[x].hsh^=val;
        return;
    } int mid=(L+R)/2;
    if (l<=mid) update(T[x].l,val,l,r,L,mid);
    if (mid<r) update(T[x].r,val,l,r,mid+1,R);
}
int query(int x,int pos,int L,int R) {
    if (!x||!pos) return 0;
    int mid=(L+R)/2;
    if (pos<=mid) return T[x].hsh^query(T[x].l,pos,L,mid);
    if (mid<pos) return T[x].hsh^query(T[x].r,pos,mid+1,R);
    return 0;
}
int A[maxn];
vector<int> pos[maxn];
int root[maxn];
int main() {
    int n,i;
    scanf("%d",&n);
    vector<int> V; V.push_back(0);
    FOR(i,1,n) scanf("%d",&A[i]),V.push_back(A[i]);
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    function<int(int)> getid=[&](int x) {
        return lower_bound(V.begin(),V.end(),x)-V.begin();
    };
    tot=0;
    FOR(i,1,n) pos[getid(A[i])].push_back(i);
    FOR(i,1,n) pos[i].push_back(n+1);
    rep(i,1,(int)V.size()) {
        // printf("pos[i] size=%d\n",(int)pos[i].size());
        // for (int v:pos[i]) printf("%d ",v); puts("<- pos[i]");
        root[i]=root[i-1]; int k; int rd=rng();
        REP(k,(int)pos[i].size()-1) {
            update(root[i],rd,pos[i][k],pos[i][k+1]-1,1,n);
            // printf("%d-%d; rd=%d\n",pos[i][k],pos[i][k+1]-1,rd);
            k++;
        }
    }
    int ans=0,q;
    scanf("%d",&q);
    FOR(i,1,q) {
        int a,b;
        scanf("%d%d",&a,&b);
        a^=ans; b^=ans;
        int l=0,r=V.size();
        while (l+1<r) {
            int mid=(l+r)/2;
            // printf("query %d %d %d=%d; %d\n",mid,a,b,query(root[mid],a,1,n),query(root[mid],b,1,n));
            if (query(root[mid],a-1,1,n)==query(root[mid],b,1,n)) l=mid;
            else r=mid;
        }
        ans=V[r]; if (r==(int)V.size()) ans=0;
        printf("%d\n",ans);
    }
}
/*
*/