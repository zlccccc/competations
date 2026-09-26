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

struct SAM {
    const static int maxn=2e5+7;
    int next[maxn][26],fail[maxn],len[maxn],cnt,pos[maxn],Pos[maxn];
    void init() {
        cnt=0; fail[0]=-1; len[0]=0; pos[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    int add(int p,int c,int id) {
        int np=++cnt; pos[np]=Pos[np]=id;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;
        for (; p!=-1&&!next[p][c]; p=fail[p]) next[p][c]=np;
        if (p==-1) fail[np]=0;
        else {
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else {
                int nq=++cnt; len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q]; pos[nq]=pos[q]; Pos[nq]=0;
                fail[np]=fail[q]=nq;
                for (; p!=-1&&next[p][c]==q; p=fail[p]) next[p][c]=nq;
            }
        }
        return np;
    }
    char a[maxn];
    void dfs(int x,int Len){
         int i;
         if (Len==len[x])
            printf("%-20s  x=%d fail=%d Len=%d\n",a,x,fail[x],len[x]);
         REP(i,26){
             if (next[x][i]) {
                 a[Len]=i+'a';
                 dfs(next[x][i],Len+1);
                 a[Len]=0;
             }
         }
    }
}sam;
char str[maxn];
int len[maxn];
int pos[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i; int n,m;
        scanf("%d%d",&n,&m);
        scanf("%s",str+1);
        sam.init();
        int t=0;
        FOR(i,1,n) t=sam.add(t,str[i]-'a',i);
        sam.dfs(0,0);
        rFOR(i,1,sam.cnt) {
            // printf("%d ",);
            len[i]=sam.len[i]-sam.len[sam.fail[i]];
        }
        // printf("%d\n",ans);
    }
}
/*
10
18 5
huaweihuaweihuawei
10
20 0
bbbbaaaaaaaaaaaaaaaaa
*/