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
const LL maxn=4007+107;
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

int fa[maxn];
int sz[maxn];
inline int getfa(int x) {
    if (x==fa[x]) return x;
    return fa[x]=getfa(fa[x]);
}
char A[4007];
int e[4006];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int n,i,j;
        scanf("%d",&n);
        FOR(i,1,n) e[i]=1;
        FOR(i,1,n) fa[i]=i,sz[i]=1;
        FOR(i,1,n) {
            scanf("%s",A+1);
            FOR(j,1,i-1) if (A[j]=='1') {
                e[i]++; e[j]++;
                int x=getfa(i),y=getfa(j);
                if (x==y) continue;
                fa[x]=y,sz[y]+=sz[x];
            }
        }
        if (sz[getfa(1)]==n) {puts("0"); continue;}
        FOR(i,1,n) getfa(i);
        FOR(i,1,n) if (sz[fa[i]]!=e[i]||e[i]==1) { // only this is just okay
            int k=i;
            FOR(i,1,n) if (fa[i]==fa[k]&&e[i]<e[k]) k=i;
            printf("1\n%d\n",k);
            i=0; break;
        }
        if (i!=n+1) continue;
        FOR(i,1,n) if (i!=fa[i]&&sz[fa[i]]==2) { // only this is just okay
            printf("2\n%d %d\n",i,fa[i]);
            break;
        }
        if (i!=n+1) continue;
        vector<int> v;
        FOR(i,1,n) if (i==fa[i]) v.push_back(i);
        if (v.size()>2) {
            printf("2\n%d %d\n",v[0],v[1]);
        } else {
            int x;
            if (sz[v[0]]<sz[v[1]]) x=v[0]; else x=v[1];
            printf("%d\n",sz[x]);
            FOR(i,1,n) if (fa[i]==x) printf("%d ",i); puts("");
        }
    }
}
/*
1
7
0100000
1000000
0001110
0010100
0011000
0010001
0000010
*/