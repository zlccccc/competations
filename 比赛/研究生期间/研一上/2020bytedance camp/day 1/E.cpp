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
#include <unordered_map>
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
template<typename T>inline void pr2(T x,int k=32) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

int ans;
int dp[maxn][4];
struct PAM {
    int next[maxn][27];
    int fail[maxn];
    int len[maxn];//长度
    int S[maxn];//字符
    int last;//上一个字符节点
    int n,tot;//n表示字符位置
    int newnode(int l) {
        memset(next[tot],0,sizeof(next[tot]));
        len[tot]=l;//不是1...
        return tot++;
    }
    void init() {
        tot=0; last=n=0;
        newnode(0); newnode(-1);
        S[n]=-1; fail[0]=1;
    }
    int getfail(int x) {
        while (S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
    int add(int c) {
        S[++n]=c;
        int cur=getfail(last);
        if (!next[cur][c]) {
            int now=newnode(len[cur]+2);
            fail[now]=next[getfail(fail[cur])][c];
            //dp[0]:ans(for anc)
            next[cur][c]=now;//这里一定要在fail后边=_=
            dp[now][1]=(dp[cur][2]+1)%M;//choose this as one
            dp[now][2]=(dp[cur][2]+dp[now][1]+dp[fail[now]][3]*2ll)%M;//to middle
            // if (len[now]==1) dp[now][2]=1;
            // else if (len[now]==2) dp[now][2]=2;
            dp[now][3]=(dp[now][1]+dp[fail[now]][3])%M;//from fail(last at this)
        } last=next[cur][c];
        ans=(ans+dp[last][3])%M;
        // printf("add %d\n",ans);
        return last;
    }
    char a[maxn];
    void dfs(int p,int len=0) {
        int c;
        printf("%-20s (p=%-5d, length=%-5d fail=%-5d dp=%d %d %d)",a,p,this->len[p],fail[p],dp[p][1],dp[p][2],dp[p][3]);
        // if (p>=2) printf("%d len=%lld\n",);
        puts("");
        REP(c,26) if (next[p][c]) {
            a[len]=c+'a';
            dfs(next[p][c],len+1);
            a[len]=0;
        }
    }
} pam;
char str[maxn];
int main() {
    int i;
    scanf("%s",str);
    int len=strlen(str);
    pam.init();
    REP(i,len) pam.add(str[i]-'a');
    // pam.dfs(1);
    // pam.dfs(0);
    printf("%d\n",ans);
}
/*
bonobo
*/