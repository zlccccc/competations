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

const int mod = 998244353;
struct mint {
    ll x;
    mint():x(0) {}
    mint(ll x):x((x%mod+mod)%mod) {}
    // mint(ll x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    mint operator~() const { return mint(1) / *this;}
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
    mint operator+(const mint &a)const { return mint(*this) += a;}
    mint operator-(const mint &a)const { return mint(*this) -= a;}
    mint operator*(const mint &a)const { return mint(*this) *= a;}
    mint operator/(const mint &a)const { return mint(*this) /= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint res = pow(t/2);
        res *= res;
        return (t&1)?res*x:res;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};
int A[maxn],Cx[maxn],Cy[maxn];
int vx[maxn],vy[maxn],id[maxn];
int dfs(int pos,int n,int m,int last) {
    int i;
    if (pos==last+1) {
        // FOR(i,1,m) printf("%d ",id[i]); puts("<- dfs");
        FOR(i,1,n) if (A[i]) return 0;
        // FOR(i,1,m) printf("%d ",id[i]); puts("<- id");
        return 1;
    } int ret=0;
    FOR(i,1,m) {
        id[pos]=i;
        int tmp=A[vx[i]]; A[vx[i]]=vy[i];
        ret+=dfs(pos+1,n,m,last);
        A[vx[i]]=tmp;
    } return ret;
}

//这原来是个ntt启发式合并啊....
namespace NTT {
    const int maxn=1<<20|7;
    const ll MOD=998244353;
    const ll g=3;
    int wn[maxn],invwn[maxn];
    ll mul(ll x,ll y) {
        return x*y%MOD;
    }
    ll poww(ll a,ll b) {
        ll ret=1;
        for (; b; b>>=1ll,a=mul(a,a))
            if (b&1) ret=mul(ret,a);
        return ret;
    }
    void initwn(int l) {
        static int len=0;
        if (len==l) return; len=l;
        ll w=poww(g,(MOD-1)/len); int i;
        ll invw=poww(w,MOD-2); wn[0]=invwn[0]=1;
        rep(i,1,len) {
            wn[i]=mul(wn[i-1],w);
            invwn[i]=mul(invw,invwn[i-1]);
        }
    }
    void ntt(ll *A,int len,int inv) {
        int i,j,k; initwn(len);
        for (i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while (j>=k) j-=k,k/=2;
            if (j<k) j+=k;
        } for (i=2; i<=len; i<<=1) {
            for (j=0; j<len; j+=i) {
                for (k=j; k<(j+i/2); k++) {
                    ll a,b; a=A[k];
                    if (inv==-1) b=mul(A[k+i/2],invwn[(ll)(k-j)*len/i]);
                    else b=mul(A[k+i/2],wn[(ll)(k-j)*len/i]);
                    A[k]=(a+b); (A[k]>=MOD) &&(A[k]-=MOD);
                    A[k+i/2]=(a-b+MOD); (A[k+i/2]>=MOD) &&(A[k+i/2]-=MOD);
                }
            }
        } if (inv==-1) {
            ll vn=poww(len,MOD-2);
            REP(i,len) A[i]=mul(A[i],vn);
        }
    }
}
ll X[1<<20|7],Y[1<<20|7];
void multi(vector<int> &A,vector<int> &B){
    int len=1,n=A.size(),m=B.size(),i;
    while (len<n+m-1) len<<=1;
    REP(i,n) X[i]=A[i]; rep(i,n,len) X[i]=0;
    REP(i,m) Y[i]=B[i]; rep(i,m,len) Y[i]=0;
    NTT::ntt(X,len,1); NTT::ntt(Y,len,1);
    REP(i,len) X[i]=X[i]*Y[i]%M;
    NTT::ntt(X,len,-1);
    A.resize(n+m-1);
    vector<int>().swap(B);
    REP(i,n+m-1) A[i]=X[i];
}

int n,m,k;
int cnt[maxn];
vector<int> value[maxn];//resize_max:k
int solve(int l,int r){
    if (l==r) return l;
    int mid=(l+r)/2;
    int L=solve(l,mid),R=solve(mid+1,r);
    if (!value[R].size()) return L;
    if (!value[L].size()) return R;
    // printf("merge %d %d\n",L,R);
    multi(value[L],value[R]);
    return L;
}
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
int one[maxn],all[maxn];
int main() {
    int n,m,i,k;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)

    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,m) {
        int x,y;
        scanf("%d%d",&x,&y);
        if (!y) one[x]++; all[x]++;
        vx[i]=x; vy[i]=y;
    } int pos=0;
    FOR(i,1,n) {
        if (A[i]||all[i]) {
            int div=one[i]*powMM(all[i],M-2)%M;
            int rev=(M-div)%M;
            if (!A[i]) add_(rev,1);
            pos+=max(1,one[i]);
            value[pos].resize(all[i]+1,0);
            // if (A[i]&&!all[i]) {puts("0"); return;}
            value[pos][0]=rev;
            value[pos][all[i]]=div;
        }
        // printf("i=%d: pos=%d; vec=",i,pos); for (int v:value[pos]) printf("%d ",v); puts("<- i");
    }
    int fin=solve(1,pos);
    // for (int v:value[fin]) printf("%d ",v);
    ll ans=0;
    REP(i,(int)value[fin].size()) {
        ans=(ans+powMM(i,k)*value[fin][i])%M;
    }
    // printf("dfs=%d\n",dfs(1,n,m,k));
    printf("%lld\n",ans);
}
/*
3 4 3
1 1 1
1 0
1 1
2 0
2 1
*/