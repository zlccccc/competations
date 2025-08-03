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

int st[2];
int nxt[17],pre[17];//next-position
int A[maxn];
int Dig[17],top=0;
int ans;
void dfs(int op,int val,int same) {
    // int i; FOR(i,1,top) printf("%d%c",Dig[i]," \n"[i==top]); puts("<- tmp");
    // for (i=st[0];i;i=nxt[i]) printf("%d ",i); puts("<- remain +");
    // for (i=st[1];i;i=nxt[i]) printf("%d ",i); puts("<- remain *");
    if (!st[0]&&!st[1]) {
        ans=min(ans,val);
        // int i; FOR(i,1,top) printf("%d%c",Dig[i]," \n"[i==top]); puts("<- inside");
    }
    for (int x=same;x;x=nxt[x]) {
        int tmpst=st[op],tmpnxt=nxt[pre[x]],tmppre=pre[nxt[x]],nxtval;
        if (x==st[op]) st[op]=nxt[x]; nxt[pre[x]]=nxt[x]; pre[nxt[x]]=pre[x];//change link
        if (op==0) {nxtval=val+A[x]; if (nxtval>M) nxtval-=M;}
        else nxtval=(ll)val*A[x]%M;
        // Dig[top++]=x;
        dfs(op,nxtval,nxt[x]);
        // top--;
        st[op]=tmpst; nxt[pre[x]]=tmpnxt; pre[nxt[x]]=tmppre;
    }
    op^=1;
    for (int x=st[op];x;x=nxt[x]) {
        int tmpst=st[op],tmpnxt=nxt[pre[x]],tmppre=pre[nxt[x]],nxtval;
        if (x==st[op]) st[op]=nxt[x]; nxt[pre[x]]=nxt[x]; pre[nxt[x]]=pre[x];//change link
        if (op==0) {nxtval=val+A[x]; if (nxtval>M) nxtval-=M;}
        else nxtval=(ll)val*A[x]%M;
        // Dig[top++]=x;
        dfs(op,nxtval,nxt[x]);
        // top--;
        st[op]=tmpst; nxt[pre[x]]=tmpnxt; pre[nxt[x]]=tmppre;
    }
}
char s[3];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,x,i;
        scanf("%d%d",&n,&x);
        st[0]=st[1]=0;
        FOR(i,1,n) nxt[i]=pre[i]=0;
        FOR(i,1,n) {
            scanf("%s%d",s,&A[i]);
            if (s[0]=='+') pre[st[0]]=i,nxt[i]=st[0],st[0]=i;
            else pre[st[1]]=i,nxt[i]=st[1],st[1]=i;
        } ans=M;
        dfs(0,x,st[0]);
        printf("%d\n",ans);
    }
}
/*
*/