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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,q;
int A[maxn],B[maxn];//sub,fa
inline int lowbit(int x){return x&-x;}
void add(int x,int val,int A[]){
    for (;x<=n;x+=lowbit(x)) A[x]+=val;
}int query(int x,int A[]){
    LL ret=0;for (int i=x;x;x-=lowbit(x)) ret+=A[x];
    return ret;
}
vector<int> edge[maxn];
int nxt[maxn][27],tot;
vector<int> pre[maxn],suf[maxn];
void insert(char s[],int id,int mark){
    int now=0,i=0;
    while (s[i]!='#'){
        if (!nxt[now][s[i]-'a']) nxt[now][s[i]-'a']=++tot;
        now=nxt[now][s[i]-'a'];i++;
    }if (!mark) pre[now].push_back(id);
    else suf[now].push_back(id);
}int cnt;//id
int in[maxn],out[maxn];
LL ans;
void dfs1(int now){
    int i;
    for (int v:pre[now]) in[v]=++cnt;
    REP(i,26) if (nxt[now][i]) dfs1(nxt[now][i]);
    for (int v:pre[now]) out[v]=cnt;
}
void ADD(int x,int val){
    add(in[x],val,A);add(out[x]+1,-val,A);//在子树内
    add(in[x],val,B);//子树贡献
}int QUERY(int x){
    return query(in[x],A)+query(out[x],B)-query(in[x]-1,B);
}
void dfs2(int now){
    int i;
    for (int v:suf[now]) ans+=QUERY(v),ADD(v,1);
    REP(i,26) if (nxt[now][i]) dfs2(nxt[now][i]);
    for (int v:suf[now]) ADD(v,-1);
}
int i,j,k;
char s[maxn];
int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%s",s);
        int len=strlen(s),now=0;
        insert(s,i,0);
        reverse(s,s+len);
        insert(s,i,1);
    }dfs1(0);
//    FOR(i,1,n) printf("%2d ",i);puts("");
//    FOR(i,1,n) printf("%2d ",in[i]);puts("");
//    FOR(i,1,n) printf("%2d ",out[i]);puts("");
    dfs2(0);
    printf("%lld\n",ans);
}
/*
*/
