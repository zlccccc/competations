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
const LL maxn=1e5+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,q;
int i,j,k;
int val[maxn];
struct node{
    LL lr,lm,rm,max;
    bool lmark,rmark;
    node(){lm=rm=lr=-INFF;}
}T[maxn<<2];
node merge(node A,node B){
    node ret;
    ret.lm=A.lm;ret.rm=B.rm;
    ret.lmark=A.lmark;
    ret.rmark=B.rmark;
    ret.max=max(A.max,B.max);
    if (A.rmark!=B.lmark){
        ret.max=max(ret.max,A.rm+B.lm);
        ret.lm=max(ret.lm,A.lr+B.lm);
        ret.rm=max(ret.rm,A.rm+B.lr);
        ret.lr=max(ret.lr,A.lr+B.lr);
    }else ret.lr=-INFF;
    ret.max=max(ret.max,ret.lr);
    ret.max=max(ret.max,ret.lm);
    ret.max=max(ret.max,ret.rm);
    return ret;
}
void update(int x,int pos,int L,int R){
    if (L==R){
        T[x].lr=T[x].lm=T[x].rm=T[x].max=val[L];
        T[x].lmark=T[x].rmark=val[L]&1;
        return;
    }int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    else update(x<<1|1,pos,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}node query(int x,int l,int r,int L,int R){
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2;
    if (l<=mid&&mid<r) return merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
    if (l<=mid) return query(x<<1,l,r,L,mid);
    if (mid<r) return query(x<<1|1,l,r,mid+1,R);
    assert(0);
    return node();
}
int main(){
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%d",&val[i]);
    FOR(i,1,n) update(1,i,1,n);
    while (q--){
        int op,l,r;
        scanf("%d%d%d",&op,&l,&r);
        if (op==0){
            node x=query(1,l,r,1,n);
            printf("%lld\n",x.max);
        }else{
            val[l]=r;
            update(1,l,1,n);
        }
//        FOR(i,1,n) printf("%d ",val[i]);puts("");
    }
}
/*
10 20
1 1 1 1 1 1 1 1 2 1
0 3 5
0 4 4
0 2 4
1 6 6
1 1 6
1 5 9
0 1 2
1 5 -8
0 2 4
1 3 -2
0 1 10
1 7 -1
0 1 10
*/
