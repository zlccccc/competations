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
const LL maxn=1e7+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; rREP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int p[maxn/10],tot;
int minp[maxn],ans[maxn];
void init(){
    int i,j;
    FOR(i,2,10000001){
        if (!minp[i]) p[tot++]=i,minp[i]=i;
        REP(j,tot) {
            if (i*p[j]>10000001) break;
            minp[i*p[j]]=p[j];
            if (i%p[j]==0) break;
        }
    } ans[1]=2;
    FOR(i,2,10000000){
        int now=1,x=i;
        // if (i>=10000000) printf("i=%d ",i);
        while (x!=1) {
            int nxt=x,cnt=0;
            while (minp[x]==minp[nxt]) nxt/=minp[nxt],cnt++;
            now=(ll)now*(cnt+1)%M; x=nxt;
            // printf("x=%d; nxt=%d",x,nxt);
        } x=i+1;
        while (x!=1) {
            int nxt=x,cnt=0;
            while (minp[x]==minp[nxt]) nxt/=minp[nxt],cnt++;
            now=(ll)now*((ll)cnt*i%M+1)%M; x=nxt;
        } ans[i]=(ans[i-1]+now)%M;
        // printf("%d : %d\n",i,now);
    }
}
int main() {
    int _,T;
    init();
    scanf("%d",&T);
    FOR(_,1,T) {
        int x; scanf("%d",&x);
        printf("%d\n",ans[x]);
    } char str[100];
    assert(scanf("%s",str)==EOF);
    return 0;
}
/*
*/
