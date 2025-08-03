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
const LL maxn=1e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

char a[maxn];
int f[maxn][107],g[maxn][107];//0:max,1:mid
bool mark;
int k,K;
int solve(int l,int r){
    int x=l;
    if (l==r) {f[x][0]=g[x][0]=a[l]-'0';return 0;}
    int tot=1,mid=l;
    while (tot){
        mid++;
        if (tot==1&&a[mid]=='?') break;
        if (a[mid]=='(') tot++;
        if (a[mid]==')') tot--;
    }l++;r--;//delete ()
    assert(tot);
    int L=solve(l,mid-1),R=solve(mid+1,r);//number of +
    int i,j;
    FOR(i,0,min(k,L+R+1)) f[x][i]=-INF,g[x][i]=INF;
    FOR(i,0,L) FOR(j,0,R) if (i+j<=k){
        if (!mark){
            f[x][i+j]=max(f[x][i+j],f[l][i]-g[mid+1][j]);
            f[x][i+j+1]=max(f[x][i+j+1],f[l][i]+f[mid+1][j]);
            g[x][i+j]=min(g[x][i+j],g[l][i]-f[mid+1][j]);
            g[x][i+j+1]=min(g[x][i+j+1],g[l][i]+g[mid+1][j]);
        }else{
            f[x][i+j]=max(f[x][i+j],f[l][i]+f[mid+1][j]);
            f[x][i+j+1]=max(f[x][i+j+1],f[l][i]-g[mid+1][j]);
            g[x][i+j]=min(g[x][i+j],g[l][i]+g[mid+1][j]);
            g[x][i+j+1]=min(g[x][i+j+1],g[l][i]-f[mid+1][j]);
        }
    }
//    printf("x=%d,l,mid,r=  %d %d %d\n",x,l,mid,r);
//    FOR(i,0,L+R+1) printf("%d ",f[x][i]);puts("  f");
//    FOR(i,0,L+R+1) printf("%d ",g[x][i]);puts("  g");
    return min(L+R+1,k);
}
int n,m;
int i,j;
int main(){
    scanf("%s%d%d",a,&k,&K);
    if (k>K) {swap(k,K);mark=1;}
    n=strlen(a);
    solve(0,n-1);
    printf("%d\n",f[0][k]);
//    printf("%d\n",g[1][k]);
}
/*
((1?(5?7))?((6?2)?7))
3 2
*/
