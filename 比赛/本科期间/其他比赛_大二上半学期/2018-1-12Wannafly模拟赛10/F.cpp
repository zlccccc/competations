#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
//#include <cassert>
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

int poww(int a,int b,int m){
    int ret=1;
    for (;b;b>>=1,a=1ll*a*a%m)
        if (b&1) ret=1ll*ret*a%m;
    return ret;
}
struct node{
    int l,r,p,id;
}Q[maxn];
int pre[maxn],suf[maxn];
inline void insert(int x){
    int u=0,v=suf[0];
    pre[x]=u;suf[x]=v;
    suf[u]=x;pre[v]=x;
}
inline void erase(int x){
    pre[suf[x]]=pre[x];
    suf[pre[x]]=suf[x];
}
int n,i,j,m;
int a[maxn];
int cnt[maxn];//value
int num[maxn];//value_cnt
LL all[maxn];
const int BLOCK=300;
int block[maxn];
int powk[500],pow1[500];
bool cmp(node a,node b){
    if (block[a.l]==block[b.l]) return a.r<b.r;
    return a.l<b.l;
}
void change(int x,int y){
    int _cnt,id;x=a[x];
    if (cnt[x]){
        _cnt=cnt[x];all[_cnt]-=x;
        num[_cnt]--;
        if (!num[_cnt]) erase(_cnt);
    }cnt[x]+=y;
    if (cnt[x]){
        _cnt=cnt[x];all[_cnt]+=x;
        if (!num[_cnt]) insert(_cnt);
        num[_cnt]++;
    }
}
int ans[maxn];
int L,R;
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&a[i]);
    FOR(i,1,100000) block[i]=i/BLOCK;
    FOR(i,1,m) scanf("%d%d%d",&Q[i].l,&Q[i].r,&Q[i].p),Q[i].id=i;
    sort(Q+1,Q+m+1,cmp);
    L=1;R=0;
    FOR(i,1,m){
        while (L<Q[i].l){change(L,-1);L++;}
        while (L>Q[i].l){L--;change(L,1);}
        while (R<Q[i].r){R++;change(R,1);}
        while (R>Q[i].r){change(R,-1);R--;}
        LL ANS=0;int len=Q[i].r-Q[i].l+1,p=Q[i].p;
        int powblock=poww(2,BLOCK,p),powall=poww(2,len,p);
        powk[0]=1;pow1[0]=1;int k;
        rep(k,1,400){
            powk[k]=1ll*powk[k-1]*powblock%p;
            pow1[k]=pow1[k-1]*2%p;
        }for (k=suf[0];k;k=suf[k])
            (ANS+=all[k]%p*(powall-1ll*powk[(len-k)/BLOCK]*pow1[(len-k)%BLOCK]%p+p))%=p;
        ans[Q[i].id]=ANS;
    }FOR(i,1,m) printf("%d\n",ans[i]);
}
/*
*/
