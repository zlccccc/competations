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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
    int l,r,val,mark;
}T[maxn*15];
int root,cnt;
void pushdown(int x){
}void pushup(int x){
    T[x].val=0;
    if (T[T[x].l].mark) T[x].val+=max(0,T[T[x].l].val);
    if (T[T[x].r].mark) T[x].val+=max(0,T[T[x].r].val);//pushdown_OK
//    printf("pushup(%d): %d %d %d\n",x,T[T[x].l].val,T[T[x].r].val,T[x].val);
}
void update(int x,int l,int r,int mark,int L,int R){
    //if (!x) x=++cnt;
//    printf("x=%d l,r=%d %d; mark=%d ;L,R=%d %d;   %d\n",x,l,r,mark,L,R,R-L+1);
    if (l<=L&&R<=r){T[x].mark=mark;T[x].val=R-L+1;return;}
    int mid=(L+R)/2;
    if (T[x].mark!=-1){
        if (!T[x].l) T[x].l=++cnt;
        T[T[x].l].val=mid-L+1;
        if (!T[x].r) T[x].r=++cnt;
        T[T[x].r].val=R-mid;
        T[T[x].l].mark=T[x].mark;
        T[T[x].r].mark=T[x].mark;
        T[x].mark=-1;
    }
    if (l<=mid) update(T[x].l,l,r,mark,L,mid);
    if (mid<r) update(T[x].r,l,r,mark,mid+1,R);
    pushup(x);
//        printf("  %d:l,r=%d %d ;val mark=  %d %d\n",x,T[x].l,T[x].r,T[x].val,T[x].mark);
}
int n,m,q;
int i,j,k;
int main(){
    scanf("%d%d",&n,&q);
    root=++cnt;T[root].mark=1;T[root].val=n;
    while (q--){
        int op,l,r;
        scanf("%d%d%d",&l,&r,&op);
        if (op==1) update(root,l,r,0,1,n);
        else update(root,l,r,1,1,n);
//        for (int x=1;x<=cnt;x++) printf("%d:l,r=%d %d ;val mark=  %d %d\n",x,T[x].l,T[x].r,T[x].val,T[x].mark);
//        printf("ANS=     %d\n",T[root].val);
        if (T[root].mark) printf("%d\n",T[root].val);
        else puts("0");
    }
}
/*
*/
