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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=2e6+7;
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

int n;
int A[maxn][2];
int R[maxn][2],F[maxn][2];//R:->max_length; F:->actual
void taskA(){
    static int x=0;
    int i,k;
    scanf("%d",&n);
    FOR(i,1,n){
        int D;
        scanf("%d%d%d",&D,&A[i][0],&A[i][1]);
        A[i][0]=D+A[i][0];
        A[i][1]=D-A[i][1];
    }
    rFOR(i,1,n){
        REP(k,2){
            if (i!=n&&A[i][k]==A[i+1][k]) R[i][k]=R[i+1][k];
            else R[i][k]=i;
        }
    }
    rFOR(i,1,n){
        REP(k,2){
            F[i][k]=R[i][k];
            int b1=R[i][k]+1;
            if (b1<=n){
                F[i][k]=max(F[i][k],R[b1][k^1]);
                int a2=R[b1][k^1]+1;
                if (a2<=n&&A[a2][k]==A[i][k]){
                    F[i][k]=max(F[i][k],R[a2][k]);
                    int b2=R[a2][k]+1;
                    if (b2<=n&&A[b2][k^1]==A[b1][k^1]){
                        F[i][k]=max(F[i][k],F[a2][k]);
                    }
                }
            }
        }
    }
    int ans=0,cnt=0;
    FOR(i,1,n){
        int len=max(F[i][0],F[i][1])-i+1;
        if (ans<len) ans=len,cnt=0;
        if (ans==len) cnt++;
    }
    printf("Case #%d: %d %d\n",++x,ans,cnt);
}
int main() {
    int T;
    scanf("%d",&T);
    while (T--) taskA();
    return 0;
}
/*
*/
