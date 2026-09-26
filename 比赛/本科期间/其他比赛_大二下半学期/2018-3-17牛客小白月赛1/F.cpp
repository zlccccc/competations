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
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

bitset<1007> A[1007][4];
int T;
int n,m;
int i,j,k;
int main(){
    scanf("%d%d%d%d",&n,&m,&k,&T);
    while (T--){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        A[x][0][y]=1;
        A[z][1][y]=1;
        A[x][2][z]=1;
    }
    rFOR(i,1,m){//y
        FOR(j,1,n){//x
            if (A[j][0][i]) putchar('x');
            else putchar('.');
        }putchar(' ');
        FOR(j,1,k){//z
            if (A[j][1][i]) putchar('x');
            else putchar('.');
        }puts("");
    }puts("");
    FOR(i,1,k){
        FOR(j,1,n){
            if (A[j][2][i]) putchar('x');
            else putchar('.');
        }if (i!=k) puts("");
    }
}
/*
2 3 4 2
1 1 2
2 3 4
*/
