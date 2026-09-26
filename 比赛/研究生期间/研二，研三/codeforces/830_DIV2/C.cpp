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

int A[maxn];
int XOR[maxn];
int L_0[maxn],R_0[maxn];//right-nonzero
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int n,i,q;
        scanf("%d%d",&n,&q);
        FOR(i,1,n) scanf("%d",&A[i]),XOR[i]=A[i]^XOR[i-1];
        R_0[n+1]=n+1; L_0[0]=0;
        FOR(i,1,n) if (A[i]==0) L_0[i]=L_0[i-1]; else L_0[i]=i;
        rFOR(i,1,n) if (A[i]==0) R_0[i]=R_0[i+1]; else R_0[i]=i;
        while (q--) {
            int l,r,L,R;
            scanf("%d%d",&L,&R);//length,l,r
            int allxor=XOR[R]^XOR[L-1],leftxor=0,rightxor=0;
            r=R; l=L;
            while (r>l&&!(rightxor&A[r])&&((A[r]&allxor)==A[r])) { // could-remove
                rightxor^=A[r];
                r=L_0[r-1]; r=max(r,l); // to min-pos
            }
            pii ans={r-l+1,l};
            // printf("initial %d -> %d\n",l,r);
            while (R_0[l+1]<=R&&!(leftxor&A[l])&&((A[l]&allxor)==A[l])) { // could-remove
                leftxor^=A[l]; l=min(R_0[l+1],R);
                // l++;
                while ((l>r||(rightxor&leftxor))&&r<R) {
                    r=R_0[r+1]; rightxor^=A[r];
                }
                // printf("solve %d -> %d  %d %d\n",l,r,leftxor,rightxor);
                ans=min(ans,make_pair(r-l+1,l));
            }
            printf("%d %d\n",ans.second,ans.first+ans.second-1);
        }
    }
}
/*
*/