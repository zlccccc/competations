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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

LL f[57][57][57][2];//position, useful_0, useful_1, now_status
int A[57];
LL pow2[57];
inline int get(int x){
    if (!x) return 1;
    return pow2[x-1];
}
int main() {
    int n,p;
    int i,j,k,t,status;
    pow2[0]=1;
    FOR(i,1,50) pow2[i]=pow2[i-1]*2%M;
    scanf("%d%d",&n,&p);
    FOR(i,1,n) scanf("%d",&A[i]);
    f[0][0][0][0]=1;
    FOR(k,1,n){
        REP(status,2){
            REP(i,k){
                REP(j,k){
                    if (f[k-1][i][j][status]){
                        if (A[k]!=1){
                            (f[k][i+1][j][status^1]+=f[k-1][i][j][status]*pow2[k-j-1]%M*get(j))%=M;
                            (f[k][i][j][status]+=f[k-1][i][j][status]*pow2[k-j-1]%M*(pow2[j]-get(j)))%=M;
                        }if (A[k]!=0){//black
                            (f[k][i][j+1][status^1]+=f[k-1][i][j][status]*pow2[k-i-1]%M*get(i))%=M;
                            (f[k][i][j][status]+=f[k-1][i][j][status]*pow2[k-i-1]%M*(pow2[i]-get(i)))%=M;
                        }
                    }
                }
            }
        }
    }
    LL ans=0;
    FOR(i,0,n)
        FOR(j,0,n)
            ans+=f[n][i][j][p];
    ans%=M;ans+=M;ans%=M;
    printf("%I64d\n",ans);
}
/*
*/
