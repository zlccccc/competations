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

bool mark[maxn];
vector<int> edge[maxn];
int main() {
    int i;
    int n; scanf("%d",&n);
    FOR(i,1,n*2) {
        int x,y;
        scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    ll ans=0;
    FOR(i,1,n*2) if (!mark[i]) {
        vector<int> noww;
        int v=i; mark[i]=1; noww.push_back(i);
        for (int v=edge[i][0];!mark[v];) {
            mark[v]=1; noww.push_back(v);
            for (int k:edge[v]) if (!mark[k]) v=k;
        }
        int lx=n,rx=1,ly=n*2,ry=n+1;
        for (int v:noww) {
            if (v<=n) {min_(lx,v); max_(rx,v);}
            else {min_(ly,v); max_(ry,v);}
        } ans+=(ll)(ly-n)*(n*2-ry+1)*(n-rx+1)*lx*noww.size()/2;
        for (int v:noww) printf("%d ",v); puts("<- circle");
        int st,k;
        REP(st,n) {
            // int px=noww[st],py=noww[(st+noww.size()-1)%noww.size()];
            // if (px>n) swap(px,py); //does not contain this
            int lx=n,rx=1,ly=n*2,ry=n+1;
            // int lx=px-1,rx=px+1,ly=py-1,ry=py+1;
            FOR(k,0,n-1) {//(k+1)/2: okay;
                int pos=k+st,nowval=noww[pos%noww.size()]; //1->
                if (nowval<=n) {min_(lx,nowval); max_(rx,nowval);}
                else {min_(ly,nowval); max_(ry,nowval);}
                // must not contain
                if (k&1) ans+=(ll)(ly-n)*(n*2-ry+1)*(n-rx+1)*lx;
                if (k&1) printf("%d(%d,%d;%d,%d;+%d) ",nowval,lx,rx,ly,ry,(ly-n)*(n*2-ry+1)*(n-rx+1)*lx);
            }
            printf("   nowans=%lld\n",ans);
            puts("  <- nowval");
        }
    }
    printf("%lld\n",ans);
}
/*
*/