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
#include <bitset>
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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int i,j,k;
int S[107]={0,1,3,6,8,10,11};
int bit[57][500000];
LL ans;
int main(){
    bit[0][0]=1;
    FOR(i,1,100) S[i]=i*i;
    FOR(k,1,100){
        rFOR(i,1,50){
            FOR(j,S[k],500000) if (bit[i-1][j-S[k]]){
                if (bit[i][j]) bit[i][j]=2;
                else bit[i][j]=bit[i-1][j-S[k]];
            }
        }
    }FOR(i,1,500000) if (bit[50][i]==1) ans+=i,printf("%d ",i);
    printf("%lld\n",ans);
}
/*
6
1 1 2 3 4 5
*/
