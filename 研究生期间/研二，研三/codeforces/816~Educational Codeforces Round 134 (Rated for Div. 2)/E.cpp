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

int nxt[maxn][27];
int fail[maxn];
char str[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,q,i,j;
        scanf("%s",str+1);
        n=strlen(str+1);
        memset(nxt[0],0,sizeof(nxt[0]));
        FOR(i,1,n) {
            fail[i]=nxt[i-1][str[i]-'a'];
            nxt[i-1][str[i]-'a']=i;
            memcpy(nxt[i],nxt[fail[i]],sizeof(nxt[i]));
        }
        scanf("%d",&q);
        FOR(j,1,q) {
            scanf("%s",str+n+1);
            int mor=strlen(str+n+1);
            int pval=nxt[n][str[n+1]-'a'];
            FOR(i,n+1,n+mor) {
                fail[i]=nxt[i-1][str[i]-'a'];
                nxt[i-1][str[i]-'a']=i;
                memcpy(nxt[i],nxt[fail[i]],sizeof(nxt[i]));
            }
            // FOR(i,1,n) printf("%d(%d %d %d) ",fail[i],nxt[i][0],nxt[i][1],nxt[i][2]);
            FOR(i,n+1,n+mor) printf("%d ",fail[i]); puts("");
            nxt[n][str[n+1]-'a']=pval;
        }
    }
}
/*
*/