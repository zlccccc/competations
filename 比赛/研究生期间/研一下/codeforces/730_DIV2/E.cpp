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

vector<int> edge[maxn];
int value[maxn],Pos[maxn],color[maxn];
bool mark[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,i,k;
        scanf("%d",&n);
        REP(i,(1<<n)) edge[i].clear(),Pos[i]=-1;
        REP(i,(n<<(n-1))) {
            int u,v; scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        } int sta; //rebuild
        REP(sta,(1<<n)) {
            int l=-1,r=-1;
            if (sta==0) {value[0]=Pos[0]=0; continue;}
            REP(i,n) if ((sta>>i)&1) {if (l==-1) l=i; r=i;}
            if (l==r) {//2^k
                for (int v:edge[value[0]]) if (Pos[v]==-1) {
                    Pos[v]=sta,value[sta]=v; break;
                }
            } else {
                int x=value[sta^(1<<l)],y=value[sta^(1<<r)];
                // printf("solve %d: x,y=%d %d\n",sta,x,y);
                for (int v:edge[x]) if (Pos[v]==-1) mark[v]=1;
                for (int v:edge[y]) if (mark[v]) Pos[v]=sta,value[sta]=v;
                for (int v:edge[x]) mark[v]=0;
            }
        }
        REP(sta,(1<<n)) printf("%d%c",value[sta]," \n"[sta==(1<<n)-1]);
        //color=edge*(n-1) %n=0;
        if (n&(n-1)) puts("-1");
        else {
            REP(sta,(1<<n)) {
                color[sta]=0;
                REP(i,n) if ((Pos[sta]>>i)&1) color[sta]^=i;
            }
            REP(sta,(1<<n)) printf("%d%c",color[sta]," \n"[sta==(1<<n)-1]);
        }
    }
}
/*
2
10 2 0
10 3 0
*/