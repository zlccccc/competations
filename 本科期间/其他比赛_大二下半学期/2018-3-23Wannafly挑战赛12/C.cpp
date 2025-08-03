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
#include <cstdlib>
#include <iomanip>
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

int T;
int n,m;
int i,j,k;
char a[maxn];
int F[maxn][15];
int ans=0;
int main(){
    scanf("%d%d",&n,&m);
    scanf("%s",a+1);
    F[0][0]=0;
    FOR(i,1,13) F[0][i]=-INF;
    FOR(i,1,n){
        FOR(j,0,m){
            F[i][j]=-INF;
            int OK=((j&1)==(a[i]-'a'));
            F[i][j]=max(F[i][j],F[i-1][j]);
            if (j){
                if (F[i-1][j-1]!=0)
                    F[i][j]=max(F[i][j],F[i-1][j-1]);
            }F[i][j]+=OK;
//            printf("%d %d : %d %d\n",i,j,F[i-1][j],F[i][j]);
            ans=max(ans,F[i][j]);
        }
    }
    printf("%d\n",ans);
}
/*
3 3
bba
*/
