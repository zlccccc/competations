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
int gcd(int a,int b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,q;
int f[maxn<<2];
void update(int x,int pos,int val,int L,int R){
    if (L==R) {f[x]=val;return;}
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    else update(x<<1|1,pos,val,mid+1,R);
    f[x]=gcd(f[x<<1],f[x<<1|1]);
}int cnt;
void query(int x,int l,int r,int val,int L,int R){
    int mid=(L+R)/2;
    if (cnt>1) return;
    if (l<=L&&R<=r){
        if (f[x]%val==0) return;
        if (L==R) cnt++;
        else {
            query(x<<1,l,r,val,L,mid);
            query(x<<1|1,l,r,val,mid+1,R);
        }return;
    }
    if (l<=mid) query(x<<1,l,r,val,L,mid);
    if (mid<r) query(x<<1|1,l,r,val,mid+1,R);
}
int a[maxn];
int main(){
    int i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i]);n++;
    FOR(i,1,n-1) update(1,i,a[i],1,n);
    scanf("%d",&q);
    FOR(i,1,q){
        int op;
        scanf("%d",&op);
        if (op==1){
            int l,r,x;cnt=0;
            scanf("%d%d%d",&l,&r,&x);
            query(1,l,r,x,1,n);
            if (cnt<=1) puts("YES");
            else puts("NO");
//            printf("cnt=%d  x=%d\n",cnt,x);
        }else if (op==2){
            int i,y;
            scanf("%d%d",&i,&y);
            update(1,i,y,1,n);
        }
    }
}
/*
*/
