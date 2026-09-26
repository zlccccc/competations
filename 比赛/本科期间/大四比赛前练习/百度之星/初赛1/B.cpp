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
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int getlength(int x,int y) {
    return (abs(x-y)+1)/2;
}
int checkpos(int x,int L,int R) {
    return min(getlength(x,L),getlength(x,R));
}
int main(){
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,n;
        ll ans=0;
        int L=1,R=1000000;
        scanf("%d",&n);
        FOR(i,1,n) {
            int l,r;
            scanf("%d%d",&l,&r);
            if (max(l,L)<=min(r,R)) {
                L=max(l,L); R=min(r,R);
            } else {
                if (l==r) {
                    ans+=min(getlength(l,L),getlength(r,R));
                    L=R=l;
                } else {
                    int nxtl=1000000,nxtr=0;
                    int getmin=INF;
                    getmin=min(getmin,checkpos(l,L,R));
                    getmin=min(getmin,checkpos(l+1,L,R));
                    getmin=min(getmin,checkpos(r-1,L,R));
                    getmin=min(getmin,checkpos(r,L,R));
                    if (checkpos(l,L,R)==getmin) {
                        nxtl=min(nxtl,l); nxtr=max(nxtr,l);
                    }
                    if (checkpos(l+1,L,R)==getmin) {
                        nxtl=min(nxtl,l+1); nxtr=max(nxtr,l+1);
                    }
                    if (checkpos(r-1,L,R)==getmin) {
                        nxtl=min(nxtl,r-1); nxtr=max(nxtr,r-1);
                    }
                    if (checkpos(r,L,R)==getmin) {
                        nxtl=min(nxtl,r); nxtr=max(nxtr,r);
                    }
                    ans+=getmin;
                    L=nxtl; R=nxtr;
                }
            }
            // printf("%d-%d; ans=%lld\n",L,R,ans);
        }
        printf("%I64d\n",ans);
    }
}