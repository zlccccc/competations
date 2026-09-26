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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct Ptree{
    int next[maxn][27];
    int fail[maxn];
    int cnt[maxn];//真正个数
    int len[maxn];//长度
    int diff[maxn];//length(this-fail)
    int slink[maxn];//diff不同的fail,共log个 //slink用来算sans,sabs转移得到ans //用来求的是分成串的个数
    int S[maxn];//字符
    int last;//上一个字符节点
    int n,tot;//n表示字符位置
    int newnode(int l){
        memset(next[tot],0,sizeof(next[tot]));
        cnt[tot]=0;
        len[tot]=l;//不是1...
        return tot++;
    }
    void init(){
        tot=0;last=n=0;
        newnode(0);newnode(-1);
        S[n]=-1;//减少特判
        fail[0]=1;
    }
    int getfail(int x){
        while(S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
    void add(int c){
        c-='a';
        S[++n]=c;
        int cur=getfail(last);
        if (!next[cur][c]){
            int now=newnode(len[cur]+2);
            fail[now]=next[getfail(fail[cur])][c];
            diff[now]=len[now]-len[fail[now]];
            if (diff[now]==diff[fail[now]]) slink[now]=slink[fail[now]];
            else slink[now]=fail[now];
            next[cur][c]=now;
//          num[now]=num[fail[now]]+1;
        }
        last=next[cur][c];
        cnt[last]++;
    }
    void count(){//count完才对
        int i;
        rREP(i,tot) cnt[fail[i]]+=cnt[i];
    }
}T;
int n,m;
int i,j,k;
char a[maxn],b[maxn];
LL f[maxn],sans[maxn];//g:sum; f:sum of sum
int main(){
    scanf("%s",a);
    n=strlen(a);
    if (n%2) return 0*puts(0);
    T.init();m=0;
    REP(i,n/2) b[++m]=a[i],b[++m]=a[n-i-1];
    f[0]=1;
    FOR(i,1,n){
        T.add(b[i]);
        for (int v=T.last;T.len[v]>0;v=T.slink[v]){
            sans[v]=f[i-(T.len[T.slink[v]]+T.diff[v])];
            if (T.diff[v]==T.diff[T.fail[v]])
                (sans[v]+=sans[T.fail[v]])%=M;
            if (!(i&1)) (f[i]+=sans[v])%=M;//f[x]
        }
    }printf("%I64d\n",f[n]);
//    REP(i,T.tot) printf("%c",T.S[i]+'a');puts("  (S)");
//    REP(i,T.tot) printf("%2d ",i);puts("  i");
//    REP(i,T.tot) printf("%2d ",T.S[i]);puts("  S");
//    REP(i,T.tot) printf("%2d ",T.fail[i]);puts("  fail");
//    REP(i,T.tot) printf("%2d ",T.cnt[i]);puts("  cnt");
//    REP(i,T.tot) printf("%2d ",T.len[i]);puts("  len");
//    REP(i,T.tot) printf("%2d ",f[i]);puts("  f");
//    REP(i,T.tot) printf("%2d ",sans[i]);puts("  g");
}
/*
abbababababbab

*/
