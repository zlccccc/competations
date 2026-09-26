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
const LL maxn=2e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
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
    void mul(ll *A,ll *B,ll *C,int len) { //C=A*B
        int i;
        ntt(A,len,1); ntt(B,len,1);
        REP(i,len) C[i]=mul(A[i],B[i]);
        ntt(C,len,-1);
    }
    static ll A[maxn],B[maxn],C[maxn];
    void multiply(const vector<int> &a,const vector<int> &b,vector<int> &ans,int n,int m) {//C=A*B(actual)
        int len=1,i;
        while (len<n+m-1) len<<=1; 
        REP(i,n) A[i]=a[i]; rep(i,n,len) A[i]=0;
        REP(i,m) B[i]=b[i]; rep(i,m,len) B[i]=0;
        mul(A,B,C,len);
        REP(i,n+m-1) ans[i]=C[i];
    }
}
complex X[1<<20|7],Y[1<<20|7];
vector<int> multi(vector<int> &A,vector<int> &B){
    int x=A.size(),y=B.size();
    vector<int> ret(x+y-1);
    NTT::multiply(A,B,ret);
}
struct node{
    int pos,length;
    node(int _p,int _l):pos(_p),length(_l){}
    bool operator < (const node &A)const{
        if (length!=A.length) return length>A.length;
        return pos<A.pos;
    }
};
vector<int> value[maxn];//resize_max:k
priority_queue<node> Q;

int n;
int Val[maxn];
int A[maxn];//g:prefix-sum
int id[maxn];
int solve() {
    set<int> S;
    int i,m,x,y;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) S.insert(i);
    FOR(i,1,n) A[i]=Val[i]=0;
    FOR(i,1,m) scanf("%d%d",&x,&y),A[x]=y;
    rFOR(i,1,n) {
        int pos;
        if (A[i]) pos=*S.lower_bound(A[i]);
        else pos=*S.lower_bound(i); id[pos]=i;
        S.erase(pos);
        // update(pos);
    } int cnt=0;
    FOR(i,1,n) if (A[i]<A[i-1]||i==n) {
        value[i].push_back(1);
        int k;
        FOR(k,1,n)
        Q.push(node(i,value[i].size()));
    } else cnt++;
    while (Q.size()>1){
        node A=Q.top();Q.pop();
        node B=Q.top();Q.pop();
//        for (auto now:value[A.pos]) printf("%-3d",now);puts("");
//        for (auto now:value[B.pos]) printf("%-3d",now);puts("");
        multi(value[A.pos],value[B.pos]);
//        for (auto now:value[A.pos]) printf("%-3d",now);puts(" <- ans");
        Q.push(node(A.pos,value[A.pos].size()));
    } node A=Q.top();Q.pop();
    FOR(i,1,n) printf("%d ",id[i]); puts("<- id"); //make_pair(val[i],i)的id
    return 0;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) solve();
}
/*
6 100000000
*/