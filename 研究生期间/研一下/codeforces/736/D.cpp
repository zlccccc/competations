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
const LL maxn=3e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

pii A[maxn];
int Count[2][2];
int main() {
    int n,i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",&A[i].first,&A[i].second);
    FOR(i,1,n) Count[(A[i].first/2)&1][(A[i].second/2)&1]++;
    // S=a+b/2-1;
    // a=S-b/2+1;
    // (da*db/2)^(db*dc/2)^(dc*da/2)=0
    // only calculate gcd
    int ix,iy,jx,jy,kx,ky;
    ll ans=0;
    // REP(ix,2) REP(iy,2) printf("(%d,%d): %d\n",ix,iy,Count[ix][iy]);
    REP(ix,2) REP(iy,2) REP(jx,2) REP(jy,2) REP(kx,2) REP(ky,2) {
        int fi=Count[ix][iy],idi=ix+iy*2;
        int fj=Count[jx][jy],idj=jx+jy*2;
        int fk=Count[kx][ky],idk=kx+ky*2;;
        if (idi<=idj&&idj<=idk) {
            int now=1; ll nowans;
            now^=max(ix^jx,iy^jy);//gcd
            now^=max(jx^kx,jy^ky);//gcd
            now^=max(ix^kx,iy^ky);//gcd
            if (!(now&1)) continue;
            if (idi==idj&&idj==idk) {
                fj--; fk-=2;
                nowans=(ll)fi*fj*fk/6;
            } else {
                if (idi==idj) fj--,nowans=(ll)fi*fj*fk/2;
                else if (idj==idk) fk--,nowans=(ll)fi*fj*fk/2;
                else nowans=(ll)fi*fj*fk;
            } ans+=nowans;
            // printf("solve (%d,%d),(%d %d),(%d %d) %lld; %d %d %d\n",ix,iy,jx,jy,kx,ky,nowans,fi,fj,fk);
        }
    } printf("%lld\n",ans);
}
/*

*/