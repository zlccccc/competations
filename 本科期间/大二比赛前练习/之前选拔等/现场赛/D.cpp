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

const int N=10;
struct matrix{
    int A[N][N];
    matrix(){memset(A,0,sizeof(A));}
}InI,ToT;
matrix mul(matrix A,matrix B){
    matrix C;int i,j,k;
    REP(i,N)
        REP(j,N)
            REP(k,N)
                C.A[i][j]=((LL)A.A[i][k]*B.A[k][j]+C.A[i][j])%M;
    return C;
}
matrix poww(matrix A,int b){
    matrix ret;int i;
    REP(i,10) ret.A[i][i]=1;
    for (; b; b>>=1,A=mul(A,A))
        if (b&1) ret=mul(ret,A);
    return ret;
}
int A[3][3];
inline int getid(int i,int j){
    return i*3+j;
}
int B[3][3],C[3][3];
LL F[maxn][3][3];
int main() {
    int n,i,j,k,T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        REP(i,3) REP(j,3) scanf("%d",&A[i][j]);
        InI=matrix();ToT=matrix();
        InI.A[9][9]=ToT.A[9][9]=1;
        REP(i,3) REP(j,3) if (i!=j){//1
            int k=3^i^j; B[i][j]=0;
            if (A[i][k]&&A[k][j]) B[i][j]=2;
            if (A[i][j]) B[i][j]=1;
        }
        if (n==1){
            if (B[0][2]) printf("%d\n",B[0][2]);
            else puts("-1");
            continue;
        }
        REP(i,3) REP(j,3) if (i!=j){
            int k=3^i^j; C[i][j]=0;
            if (A[i][j]&&B[i][k]&&B[k][j]){
                C[i][j]=(B[i][k]+B[k][j]+1)%M;
            }else if (A[i][k]&&A[k][j]&&B[i][j]&&B[j][i]){
                C[i][j]=(B[i][j]*2+B[j][i]+2)%M;
            }else if (B[k][i]&&B[i][k]&&A[i][j]&&B[i][j]){
                C[i][j]=(B[i][k]+B[k][i]+B[i][j]+1);
            }else if (B[k][j]&&B[j][k]&&A[i][j]&&B[i][j]){
                C[i][j]=(B[j][k]+B[k][j]+B[i][j]+1);
            }else C[i][j]=0;
        }
        if (n==2){
            if (C[0][2]) printf("%d\n",C[0][2]);
            else puts("-1");
            continue;
        }
        REP(i,3) REP(j,3)
            InI.A[9][getid(i,j)]=C[i][j];
//        REP(i,3) REP(j,3) F[1][i][j]=B[i][j];int t;
//        FOR(t,2,n) {
//            REP(i,3) REP(j,3){
//                int k=3^i^j;
//                if (A[i][j]&&F[t-1][i][k]&&F[t-1][k][j]){
//                    F[t][i][j]=(F[t-1][i][k]+F[t-1][k][j]+1)%M;
//                }else if (A[i][k]&&A[k][j]&&F[t-1][i][j]&&F[t-1][j][i]){
//                    F[t][i][j]=(F[t-1][i][j]*2+F[t-1][j][i]+2)%M;
//                }else F[t][i][j]=0;
//            }
//        }printf("dbg: %d ",F[n][0][2]);
        REP(i,3) REP(j,3) if (i!=j){
            int k=3^i^j;
            if (A[i][j]&&C[i][k]&&C[k][j]){
                ToT.A[getid(i,k)][getid(i,j)]=1;
                ToT.A[getid(k,j)][getid(i,j)]=1;
                ToT.A[9][getid(i,j)]=1;
            }else{//B:anyway
                if (A[i][k]&&A[k][j]&&C[i][j]&&C[j][i]){
                    ToT.A[getid(i,j)][getid(i,j)]=2;
                    ToT.A[getid(j,i)][getid(i,j)]=1;
                    ToT.A[9][getid(i,j)]=2;
                }
            }
        }
        InI=mul(InI,poww(ToT,n-2));
        if (InI.A[9][getid(0,2)]) printf("%d\n",InI.A[9][getid(0,2)]);
        else puts("-1");
    }
    return 0;
}
/*
50
2
1 1 1
1 1 0
0 0 1
3
1 1 1
1 1 0
0 0 1
*/
