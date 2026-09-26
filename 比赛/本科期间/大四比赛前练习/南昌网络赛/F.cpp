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

namespace SAM {
    const static int maxn=4e5+7;
    int next[maxn][26],fail[maxn],len[maxn],cnt,last;
    void init() {
        cnt=0; fail[0]=-1; len[0]=0; last=0;
        memset(next[0],0,sizeof(next[0]));
    }
    int add(int c) {
        int p=last,np=++cnt;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;
        for (; p!=-1&&!next[p][c]; p=fail[p]) next[p][c]=np;
        if (p==-1) fail[np]=0;
        else {
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else {
                int nq=++cnt; len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q]; fail[np]=fail[q]=nq;
                for (; p!=-1&&next[p][c]==q; p=fail[p]) next[p][c]=nq;
            }
        } last=np;
        return np;
    }
};
char str[maxn];
ll prefsum[maxn],A[maxn];
int main() {
    // printf("%lld\n",921456326ll*26*26%M);
    // printf("%lld\n",775263736ll*26*26%M);
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int l,k,n,m,i,j;
        scanf("%d%d%d%d",&l,&k,&n,&m);
        scanf("%s",str);
        FOR(i,0,k) scanf("%lld",&A[i]);
        FOR(i,1,min(n,l+m+1)) {
            ll now=0,ip=1;
            REP(j,k+1) {
                add_(now,ip*A[j]%M);
                mul_(ip,i);
            } prefsum[i]=prefsum[i-1];
            add_(prefsum[i],now*powMM(26,n-i)%M*(n-i+1)%M);
            // printf("%d: now=%lld; %lld\n",i,now,now*powMM(26,n-i)*(n-i+1)%M);
        } SAM::init();
        int ans=0; ll inv=powMM(powMM(26,n),M-2);
        // startTimer();
        REP(i,l+m) {
            if (i>=l) scanf("%s",str+i);
            int p=SAM::add(str[i]-'a');
            {
                int l=SAM::len[SAM::fail[p]],r=SAM::len[p];
                l=min(l,n); r=min(r,n);
                add_(ans,prefsum[r]);
                add_(ans,M-prefsum[l]);
            }
            // printf("%d: l,r=%d %d\n",i,l,r);
            if (i>=l-1) printf("%lld\n",ans*inv%M);
        }
        // printTimer()
    }
}
/*
8 3
88988102
1 8
2 8
1 7

9 1
910288102
1 9

1
1 1 2 100000
a
1 1
b
*/