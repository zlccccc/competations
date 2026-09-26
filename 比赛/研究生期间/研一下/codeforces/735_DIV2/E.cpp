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
const LL maxn=1e6+107;
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
vector<int> edge[maxn];
int d[maxn];//du
int cnt[maxn];//inside
vector<int> maybe;
bool check(int value) {
    queue<int> Q; int i;
    FOR(i,1,n) d[i]=edge[i].size();
    FOR(i,1,n) if (d[i]==1) Q.push(i);
    FOR(i,1,n) cnt[i]=0;
    while (Q.size()) {
        int x=Q.front(); Q.pop(); d[x]=-1;
        // printf("check %d virtex %d: %d\n",value,x,cnt[x]);
        if ((cnt[x]+1)%value==0) {
            bool mark=0;
            for (int v:edge[x]) if (d[v]!=-1) {
                d[v]--; if (d[v]==1) Q.push(v);
                mark=1;
                // printf("type 1 -> %d %d\n",v,cnt[v]);
            } if (!mark) return 0;//not the last virtex
        }//not add cnt
        else if (cnt[x]%value==0) {
            for (int v:edge[x]) if (d[v]!=-1) {
                cnt[v]++; d[v]--; if (d[v]==1) Q.push(v);
                // printf("type 2 -> %d %d\n",v,cnt[v]);
            }
        } else return 0;
    } return 1;
}
int ans[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,j;
        scanf("%d",&n);
        FOR(i,1,n) edge[i].clear();
        FOR(i,1,n) ans[i]=cnt[i]=d[i]=0;
        FOR(i,1,n-1) {
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
            d[u]++; d[v]++;
        }
        if (n==2) {puts("2 0"); continue;}
        ans[1]=powMM(2,n-1);
        FOR(i,1,n) if (d[i]==1) d[i]=-1;
        FOR(i,1,n) if (d[i]==-1) {//remove leaf
            for (int v:edge[i]) d[v]--,cnt[v]++;
        }
        maybe.clear();
        FOR(i,1,n) if (d[i]==1||d[i]==0) {
            FOR(j,2,cnt[i]+1) if (cnt[i]%j==0||(cnt[i]+1)%j==0)
                maybe.push_back(j);
            break;
        }
        // FOR(i,1,n) printf("%d ",d[i]); puts("<- d");
        // for (int v:maybe) printf("%d ",v); puts("<- maybe v");
        for (int v:maybe) if (check(v)) ans[v]=1;
        rFOR(i,2,n) if (ans[i]) {
            for (j=i+i;j<=n;j+=i) if (ans[j]) ans[i]=0;
            if (ans[i]) add_(ans[1],M-1);
        } FOR(i,1,n) printf("%d%c",ans[i]," \n"[i==n]);
    }
}
/*
10
7
1 2
1 3
1 4
2 5
2 6
2 7
*/