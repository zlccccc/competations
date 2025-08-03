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

int A[maxn],id[maxn];//id放在哪个位置
int pref[maxn];
int main() {
    int n,k,i,j;
    scanf("%d%d",&n,&k);
    // FOR(i,1,n) A[i]=i;
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) id[A[i]]=i;
    vector<int> val(1<<(k*2+1),INF); // 目前已经用了sta
    val[(1<<k)-1]=0;
    FOR(i,1,n) FOR(j,i+1,n) if (id[i]>id[j]) val[(1<<k)-1]++;
    // printf("base=%d\n",val[(1<<k)-1]);
    FOR(i,1,n) {
        int sta;
        vector<int> nxt(1<<(k*2+1),INF);
        REP(sta,(1<<(k*2+1))) if (val[sta]!=INF) {
            // id在q[n-k] must be true!
            int lft=0; while ((sta>>lft)&1) lft++; //not-used
            // printf("solve %d (%d);left=%d-%d ",i,val[sta],lft,lft+k); pr2(sta,k*2+1); puts("<- ");
            for (int p=lft;p<=lft+k;p++) if (!((sta>>p)&1)) {
                int nxtsta=sta|(1<<p),pos=i+p-k;
                // printf("down i=%d, nxtsta&1=%d ",i,nxtsta&1);
                // pr2(nxtsta,k*2); puts("");
                // assert(p<k*2);
                if (nxtsta&1) { // must-choose! otherwise false
                    // k-k+i
                    int should=0,kv=0;
                    REP(kv,p) if (i+kv-k>0&&id[i+kv-k]>id[pos]) should--;
                    REP(kv,k*2) if (((sta>>kv)&1)&&(id[i+kv-k]>id[pos])) should++;
                    min_(nxt[nxtsta>>1],val[sta]+should);
                    // pr2(nxtsta,k*2); printf("should=%d\n",should);
                }
            }
        }
        nxt.swap(val);
    }
    printf("%d\n",val[(1<<k)-1]);
}
/*
C(16,8)=12870 * n=1
10 8
5000 8
*/