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
#include <bitset>
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

int n,m;
int i,j,k;
char a[maxn];
bitset<400> F[100][2],now[2];
int ans;
int main(){
    scanf("%s",a);
    int len=strlen(a);
    scanf("%d",&n);
    F[0][0][150]=1;
    REP(i,len){
        rREP(j,n+1){
            now[0]=now[1]=0;
            if (a[i]=='F'){
                rep(k,1,300) if(F[j][0][k-1]) now[0][k]=1;
                rep(k,1,300) if(F[j][1][k+1]) now[1][k]=1;
                if (j) {
                    rep(k,1,300) if (F[j-1][0][k]) now[1][k]=1;
                    rep(k,1,300) if (F[j-1][0][k]) now[0][k]=1;
                }
            }else{
                rep(k,1,300) if (F[j][0][k]) now[1][k]=1;
                rep(k,1,300) if (F[j][1][k]) now[0][k]=1;
                if (j) {
                    rep(k,1,300) if(F[j-1][0][k-1]) now[0][k]=1;
                    rep(k,1,300) if(F[j-1][1][k+1]) now[1][k]=1;
                }
            }F[j][0]=now[0];
            F[j][1]=now[1];
        }
//        printf("%d:(len=%d)\n",i,len);
//        REP(j,n+1)
//            REP(k,300) if (F[j][0][k]) printf("->:%d %d\n",j,k);
//        REP(j,n+1)
//            REP(k,300) if (F[j][1][k]) printf("<-:%d %d\n",j,k);
    }
    REP(k,300) if (F[n][0][k]||F[n][1][k]) ans=max(ans,abs(150-k));
    printf("%d\n",ans);
}
/*
FT
0
*/
