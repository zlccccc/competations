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
const LL maxn=1007+107;
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

bool mark[maxn][maxn][2];
char s[maxn],t[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,k;
        scanf("%s%s",s+1,t+1);
        int n=strlen(s+1),m=strlen(t+1);
        FOR(k,1,m) {
            FOR(i,1,n) {
                mark[k][i][0]=mark[k][i][1]=0;
                if (t[k]==s[i]) {
                    if (k==1) mark[k][i][0]=mark[k][i][1]=1;
                    else {
                        if (i!=1) mark[k][i][0]|=mark[k-1][i-1][0];
                        if (i!=n) mark[k][i][1]|=mark[k-1][i+1][1];
                        mark[k][i][1]|=mark[k][i][0];
                    }
                }
                // if (mark[k][i][0]) printf("%d %d(%d)\n",k,i,0);
                // if (mark[k][i][1]) printf("%d %d(%d)\n",k,i,1);
            }
        }
        bool ans=0;
        FOR(i,1,n) if (mark[m][i][1]) ans=1;
        if (ans) puts("Yes");
        else puts("No");
    }
}
/*
*/