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
const LL maxn=5e5+7;
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

const int N=12;
struct matrix{
    int A[N][N];
    matrix(){
        memset(A,0,sizeof(A));
    }
}mat,now;
matrix mul(matrix &A,matrix &B){
    matrix C;int i,j,k;
    REP(i,N)
        REP(j,N)
            REP(k,N)
                C.A[i][j]=((LL)A.A[i][k]*B.A[k][j]+C.A[i][j])%M;
    return C;
}
inline matrix poww(matrix a, int b) {
    matrix ret;int i;
    REP(i,N) ret.A[i][i]=1;
    for (; b; b>>=1ll,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}
//status:
//*cxiv*dxiv*
//*vixd*vixc*vix.
void solve_mat(){
    mat.A[0][1]=1;mat.A[0][0]=25;//*
    mat.A[1][2]=1;mat.A[1][0]=24;mat.A[1][1]=1;//v
    mat.A[2][3]=1;mat.A[2][0]=24;mat.A[2][1]=1;//i
    mat.A[3][4]=1;mat.A[3][0]=23;mat.A[3][1]=1;//x(not +c)

    mat.A[4][5]=1;mat.A[4][4]=25;//d
    mat.A[5][6]=1;mat.A[5][4]=24;mat.A[5][5]=1;//v
    mat.A[6][7]=1;mat.A[6][4]=24;mat.A[6][5]=1;//i
    mat.A[7][8]=1;mat.A[7][4]=23;mat.A[7][5]=1;//x(not +d)

    mat.A[8][9]=1;  mat.A[8][8]=25;//c
    mat.A[9][10]=1; mat.A[9][8]=24; mat.A[9][9]=1;//v
    mat.A[10][11]=1;mat.A[10][8]=24;mat.A[10][9]=1;//i
                    mat.A[11][8]=23;mat.A[11][9]=1;//x//(not +d|c)
}
int main() {
    int i,j,n,T;
    scanf("%d",&T);
    solve_mat();
    while (T--){
        scanf("%d",&n);
        now=poww(mat,n);
        LL ans=0;
        rep(i,8,N) ans+=now.A[0][i];
        ans%=M;
        static int x=0;
        printf("Case #%d: %lld\n",++x,ans);
    }
}
/*
*/
