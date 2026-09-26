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

char str[maxn],ans[maxn];
int id[maxn],rid[maxn],pos[maxn];
int cnt[256],nowcnt[256];
bool mark[256];
bool check(int l,int mid,int r) {
    int m;
    rep(m,mid,r) {
        while (l<mid&&str[l]!=str[m]) l++;
        if (l==mid) return 0; else l++;
    } return 1;
}
int solve() {
    int i;
    int left=0;
    scanf("%s",str);
    int n=strlen(str);
    memset(nowcnt,0,sizeof(nowcnt));
    memset(cnt,0,sizeof(cnt));
    memset(mark,0,sizeof(mark));
    rREP(i,n) {
        int now=(int)str[i];
        if (!mark[now]) ans[left++]=now;
        mark[now]=1; cnt[now]++;
    } ans[left]=0;
    reverse(ans,ans+left);
    REP(i,left) {
        int now=ans[i];
        if (cnt[now]%(i+1)!=0) return 0*puts("-1");
        cnt[now]/=i+1;
    }
    // printf("%s",ans); puts(" << ans");
    REP(i,left+1) id[i]=0,rid[i]=n+1;
    REP(i,n) {
        int now=(int)str[i];
        nowcnt[now]++;
        if (nowcnt[now]%cnt[now]==0) {
            max_(id[nowcnt[now]/cnt[now]],i+1);
        } else min_(rid[nowcnt[now]/cnt[now]],i+1);
    }
    // REP(i,left) printf("(%d-%d) ",id[i],rid[i]); puts("<- id");
    REP(i,left) if (rid[i]<id[i]) return 0*puts("-1");
    REP(i,left-1) if (!check(id[i],id[i+1],id[i+2])) return 0*puts("-1");
    str[id[1]]=0;
    printf("%s %s\n",str,ans);
    return 1;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) solve();
}
/*
10
abacabaaacaac
nowyouknowthat
polycarppoycarppoyarppyarppyrpprppp
isi
everywherevrywhrvryhrvrhrvhv
haaha
qweqeewew
aaaaaaaaaba
aaaaaaaaab
*/