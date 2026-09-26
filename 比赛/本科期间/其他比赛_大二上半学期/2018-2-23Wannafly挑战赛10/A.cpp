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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k;
int T;
int a[10],ans;
void dfs(int x,int used){
    int i;
//    printf("%d %d\n",x,used);
    if (used==7) ans=min(ans,x);
    REP(i,3) if (!((used>>i)&1)) dfs((int)((LL)x*a[i]/100),used|(1<<i));
}
int main(){
    scanf("%d%d%d%d",&n,&a[0],&a[1],&a[2]);
    REP(i,3) a[i]=100-a[i];
//    REP(i,3) printf("a=%d ",a[i]);
    ans=INF;dfs(n,0);
    printf("%d\n",n-ans);
}
/*
*/
