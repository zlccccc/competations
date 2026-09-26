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
const LL maxn=5e5+107;
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

int n;
char str[maxn]; int A[maxn];
int nxt[maxn][27];
unsigned Rd0[47],Rd1[47];
unsigned H[maxn][27];//H:right-kth
void output(int pos) {
    int i;
    for (i=pos;i<=n;i=nxt[i][0]) printf("%c",str[i]);
}
inline int cmp(int x,int y) {
    int i;
    rREP(i,20) if (H[x][i]==H[y][i]) x=nxt[x][i],y=nxt[y][i];//right
    return A[x]<A[y];
}
int Ans[maxn],OK[47][47];
int S[maxn],Min[maxn],top;//S: nxt-to-remove (right-max)
int main() {
    int i,j,k;
    FOR(i,0,40) Rd0[i]=rand(),Rd1[i]=rand();
    scanf("%d%d",&k,&n);
    FOR(i,1,k) FOR(j,1,k) scanf("%1d",&OK[i][j]);
    scanf("%s",str+1); S[0]=n+1;
    FOR(i,1,n) A[i]=str[i]-'a'+1;
    // FOR(i,1,n) printf("%d ",A[i]); puts("<- A");
    // REP(k,20) nxt[n+1][k]=n+1;
    // H[n+1][0]=Rd1[0];//Right
    // rep(k,1,20) H[n+1][k]=H[n+1][k-1]*(Rd0[k]+1);
    rFOR(i,1,n) {
        int nowmin=i+1;
        while (top&&OK[A[i]][A[S[top]]]) {
            // printf("check %d %d; %d\n",A[i],A[S[top]],Min[top]);
            if (cmp(Min[top],nowmin)) nowmin=Min[top]; top--;
        }
        H[i][0]=Rd1[A[i]]; nxt[i][0]=nowmin;//Right
        rep(k,1,20) nxt[i][k]=nxt[nxt[i][k-1]][k-1];
        rep(k,1,20) H[i][k]=H[i][k-1]*Rd0[k]+H[nxt[i][k-1]][k-1];
        if (cmp(i,nowmin)) nowmin=i;//remove i
        // printf("solve %d: right=%d; nowmin=%d\n",i,S[top]-1,nowmin);
        S[++top]=i; Min[top]=nowmin;
        // FOR(j,1,top) printf("(%d %d),",S[j],Min[j]); puts("<- S-top");
    }
    output(1);
}
/*
3 7
010
001
100
abacaba

3 7
110
001
100
aaaaaaa
*/