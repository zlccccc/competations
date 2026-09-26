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

namespace ACM {
    const int maxn=1e6+7;
    int next[maxn][26],fail[maxn],len[maxn],tot;
    bitset<507> have[maxn];
    void init() {
        tot=0; len[0]=0; fail[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    void insert(char s[],int val) {
        int i,n=strlen(s),p=0;
        REP(i,n) {
            int c=s[i]-'a';
            if (!next[p][c]) {
                next[p][c]=++tot; len[tot]=len[p]+1; fail[tot]=0;
                memset(next[tot],0,sizeof(next[tot]));
            } p=next[p][c];
        } have[p].set(val);//to_prev_length
        // printf("val=%d\n",val);
    }
    int Q[maxn],ST,ED;
    void buildAC() {
        ST=0; ED=-1; Q[++ED]=0;
        while (ST<=ED) {
            int p=Q[ST++],c;
            REP(c,26) {
                if (next[p][c]) {
                    fail[next[p][c]]=p?next[fail[p]][c]:0;
                    Q[++ED]=next[p][c];
                } else next[p][c]=p?next[fail[p]][c]:0;//否则可能fail=self
            } have[p]|=have[fail[p]];
        }
    }
}
char str[507],tmp[maxn];
bitset<507> S[507];
int len[507][507];
int main() {
    int i,j,k,n,L;
    scanf("%s",str);
    L=strlen(str);
    FOR(n,1,L) {
        rep(i,n,L) if (str[i]!=str[i-n]) break;
        if (i==L) break;
    }
    // printf("p=%d\n",n); L=0;
    int m; scanf("%d",&m);
    ACM::init();
    FOR(i,1,m) {
        scanf("%s",tmp);
        ACM::insert(tmp,strlen(tmp)%n);
    } ACM::buildAC();
    int p=0;
    REP(i,1000000+500) {
        int c=str[i%n]-'a';
        p=ACM::next[p][c];
        S[i%n]|=ACM::have[p];
        // printf("p=%d\n",p);
    } REP(i,n) REP(j,n) len[i][j]=INF;
    REP(i,n) REP(j,n) if (S[i][j]) len[(i-j+n)%n][i]=1;
    // REP(i,n) REP(j,n) if (len[i][j]==1) printf("%d - %d\n",i,j);
    REP(i,n) REP(j,n) REP(k,n) len[i][j]=min(len[i][j],len[i][k]+len[k][j]);
    int ans=INF;
    REP(i,n) ans=min(ans,len[i][i]);
    if (ans!=INF) printf("%d\n",ans);
    else puts("-1");
}
/*
baabaa
3
a
b
c

baabaa
3
ab
b
a
*/