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
const LL maxn=1.2e6+107;
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

int Dig[17],top;
int A[maxn],n;
int ans;
bool mrk[2][17];
int c[2][17],tot[2];
void dfs(int op,int val,int pos) {
    // if (top==n) {
    //     int i; FOR(i,0,top-1) printf("%d%c",Dig[i]," \n"[i==top-1]); printf(" n=%d; top=%d; val=%d <- tmp\n",n,top,val);
    // }
    // cnt++;
    if (top==n) {
        ans=min(ans,val); return;
        // int i; FOR(i,0,top-1) printf("%d%c",Dig[i]," \n"[i==top-1]); puts("<- inside");
    }
    int x,nxtval;
    rep(x,pos,tot[op]) if (!mrk[op][x]){
        if (op==0) {nxtval=val+c[op][x]; if (nxtval>M) nxtval-=M;}
        else nxtval=(ll)val*c[op][x]%M;
        Dig[top++]=x;
        mrk[op][x]=1;
        dfs(op,nxtval,x+1);
        mrk[op][x]=0;
        top--;
    }
    op^=1;
    rep(x,0,tot[op]) if (!mrk[op][x]){
        if (op==0) {nxtval=val+c[op][x]; if (nxtval>M) nxtval-=M;}
        else nxtval=(ll)val*c[op][x]%M;
        Dig[top++]=x+n;
        mrk[op][x]=1;
        dfs(op,nxtval,x+1);
        mrk[op][x]=0;
        top--;;
    }
}
char s[3];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int x,i;
        scanf("%d%d",&n,&x);
        memset(mrk,0,sizeof(mrk));
        tot[0]=tot[1]=0;
        FOR(i,1,n) {
            scanf("%s%d",s,&A[i]);
            if (s[0]=='+') c[0][tot[0]++]=A[i];
            else c[1][tot[1]++]=A[i];
        } ans=M; top=0;
        dfs(0,x,0);
        // printf("cnt=%d")
        printf("%d\n",ans);
    }
}
/*
*/