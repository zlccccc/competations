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

int A[maxn];
int id[maxn];
int fa[maxn];
inline int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
set<int> sub[maxn];
set<int> S[maxn];
int ans[maxn];
int mark[maxn];
int main() {
    int n,q,i;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%d",&A[i]),id[A[i]]=i;
    FOR(i,1,1000007) fa[i]=i;
    FOR(i,2,1000007) if (!mark[i]){
        vector<int> now;
        for (int j=i;j<=1000007;j+=i) {
            mark[j]=1;
            if (id[j]) {
                int x=getfa(j),y=getfa(i);
                if (getfa(x)==getfa(y)) continue;
                fa[x]=y;
                // printf("merge %d %d\n",x,y);
            }
        }
    }
    FOR(i,1,n) {
        vector<int> v1,v2; int t;
        t=A[i];
        for (int k=2;k<=t/k;k++) if (t%k==0) {
            while (t%k==0) t/=k; v1.push_back(k);
        } if (t!=1) v1.push_back(t);
        t=A[i]+1;
        for (int k=2;k<=t/k;k++) if (t%k==0) {
            while (t%k==0) t/=k; v2.push_back(k);
        } if (t!=1) v2.push_back(t);
        for (int x:v1) sub[getfa(A[i])].insert(getfa(x));
        for (int x:v1) for (int y:v2) S[getfa(x)].insert(getfa(y));
        for (int x:v1) for (int y:v2) S[getfa(y)].insert(getfa(x));
        for (int x:v2) for (int y:v2) S[getfa(x)].insert(getfa(y));
        // for (int x:v1) for (int y:v2) printf("i=%d: idx %d %d\n",A[i],getfa(x),getfa(y));
    }
    FOR(i,1,q) {
        int x,y,_x,_y;
        scanf("%d%d",&_x,&_y);
        x=getfa(A[_x]); y=getfa(A[_y]);
        if (x==y) ans[i]=0;
        else {
            ans[i]=2;
            for (int u:sub[x]) for (int v:sub[y]) {
                // printf("check: %d %d\n",u,v);
                // printf("check: %d %d\n",getfa(u),getfa(v));
                if (S[getfa(u)].count(getfa(v))) ans[i]=1;
            }
        }
    }
    FOR(i,1,q) printf("%d%c",ans[i],"\n\n"[i==q]);
}
/*
*/