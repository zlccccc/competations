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
int now=0;
const int SIZE=500;
int block[maxn];
int a[maxn];
int b[800];
void change(int x){
    int i;b[x]=a[x*SIZE];
    for (i=x*SIZE;i<=min((x+1)*SIZE-1,n);i++)
        b[x]=gcd(b[x],a[i]);
}
int main(){
    int i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i]);
    FOR(i,1,500000) block[i]=i/SIZE;
    FOR(i,0,n/SIZE) change(i);
    scanf("%d",&q);
    FOR(i,1,q){
        int op;
        scanf("%d",&op);
        if (op==1){
            int l,r,x,i,j;
            scanf("%d%d%d",&l,&r,&x);int cnt=0;
            for (i=l;i<=r&&block[i]==block[l];i++) if (gcd(x,a[i])!=x) cnt++;
            if (i<=r){
                for (i/=SIZE;i<block[r];i++) if (cnt<=1&&gcd(x,a[i])!=x){
                    rep(j,i*SIZE,(i+1)*SIZE) if (gcd(x,a[j])!=x) cnt++;
                }for (i*=SIZE;i<=r;i++) if (gcd(x,a[i])!=x) cnt++;
            }
            if (cnt<=1) puts("YES");
            else puts("NO");
//            printf("cnt=%d  x=%d\n",cnt,x);
        }else if (op==2){
            int i,y;
            scanf("%d%d",&i,&y);
            a[i]=y;change(block[i]);
        }
    }
}
/*
*/
