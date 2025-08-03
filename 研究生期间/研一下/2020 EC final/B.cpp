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
const LL maxn=1e4+107;
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

// int f[507][507][507];
int f[507][507];
int A[507],S[507],tid[507],fa[507],top;
ll sz[507],ans[507];
int id[507][507];
ll Ans[250007];
int main() {
    int n,m,i,j,k;
    scanf("%d%d",&n,&m);
    FOR(i,1,n*m) {
        int x,y;
        scanf("%d%d",&x,&y);
        id[x][y]=i;
    }
    // FOR(k,1,n) {
    //     FOR(i,1,m) {
    //         f[k][i][i-1]=INF;
    //         FOR(j,i,m) f[k][i][j]=min(f[k][i][j-1],id[k][j]);
    //     }
    // }
    FOR(i,1,m) FOR(j,i,m) {
        FOR(k,1,n) {
            if (j==i) f[k][i]=id[k][j];
            else f[k][i]=min(f[k][i],id[k][j]);
        }
        FOR(k,1,n) A[k]=f[k][i];
        int tot=0,top=0;
        FOR(k,1,n) { // 笛卡尔树
            int now=0;
            while (top&&A[S[top]]>A[k]) {
                if (now) fa[now]=S[top],tid[++tot]=now;
                now=S[top]; top--;
            } S[++top]=k;
            if (now) fa[now]=S[top],tid[++tot]=now;
        } int now=0;
        while (top) {
            if (now) fa[now]=S[top],tid[++tot]=now;
            now=S[top]; top--;
        } fa[now]=0; tid[++tot]=now;
        // reverse(tid+1,tid+1+n);
        FOR(k,1,n) sz[k]=ans[k]=0;
        FOR(k,1,n) {
            int id=tid[k],f=fa[id];
            // printf("id=%d f=%d;",id,f);
            sz[id]+=1;
            ans[id]+=sz[id]*(sz[id]+1)/2;
            Ans[A[id]]+=ans[id];
            if (f) {
                sz[f]+=sz[id];
                ans[f]-=sz[id]*(sz[id]+1)/2;
            }
        }
        // FOR(k,1,n) printf("%d ",A[k]); printf(" <- A %d %d\n",i,j);
        // FOR(k,1,n) printf("%lld ",ans[k]); printf(" <- ans\n");
    }
    rFOR(i,1,n*m) Ans[i]+=Ans[i+1];
    FOR(i,2,n*m+1) printf("%lld\n",Ans[i]);
}
/*
*/