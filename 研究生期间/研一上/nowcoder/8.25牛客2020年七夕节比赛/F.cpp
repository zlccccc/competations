
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
const LL maxn=2e5+107;
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


namespace ACM {
    const int maxn=3007;
    int next[maxn][26],fail[maxn],len[maxn],tot;
    int sum[maxn]; //more
    void init() {
        tot=0; len[0]=0; fail[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    void insert(char s[],int val) {
        int i,n=strlen(s),p=0;
        REP(i,n) {
            int c=s[i]-'a';
            if (!next[p][c]) {
                next[p][c]=++tot; len[tot]=len[p]+1; fail[tot]=0;
                memset(next[tot],0,sizeof(next[tot]));
            } p=next[p][c];
        } sum[p]+=val;
    }
    int Q[maxn],ST,ED;
    void buildAC() {
        ST=0; ED=-1; Q[++ED]=0;
        while (ST<=ED) {
            int p=Q[ST++],c;
            REP(c,26) {
                if (next[p][c]) {
                    fail[next[p][c]]=p?next[fail[p]][c]:0;
                    Q[++ED]=next[p][c];
                } else next[p][c]=p?next[fail[p]][c]:0;//否则可能fail=self
            } sum[p]+=sum[fail[p]];
        }
    }
}
char str[maxn];
int dp[1007][2007];
int main() {
	int n,i,j,l;
    scanf("%d%d",&n,&l);
    ACM::init();
    FOR(i,1,n) {
        int val;
        scanf("%s%d",str,&val);
        ACM::insert(str,val);
    } ACM::buildAC();
    FOR(i,0,l) FOR(j,0,ACM::tot) dp[i][j]=-INF;
    dp[0][0]=0;
    FOR(i,0,l-1) {
        FOR(j,0,ACM::tot) {
            int c;
            REP(c,26) {
                max_(dp[i+1][ACM::next[j][c]],dp[i][j]+ACM::sum[ACM::next[j][c]]);
            }
        } 
    } int ans=-INF;
    FOR(j,0,ACM::tot) max_(ans,dp[l][j]);
    printf("%d\n",ans);
}
/*
6 1
1 0 0 1 1 1

6 2
1 0 0 1 1 1
*/