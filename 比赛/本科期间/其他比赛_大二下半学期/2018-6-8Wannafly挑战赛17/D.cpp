#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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

#define DEBUG
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
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

int A[maxn],root;
struct matrix{
    LL A[5][5];int l,r;
    matrix(){memset(A,0,sizeof(A));}
}T[maxn*2],F0,F1;
matrix mul(matrix &A,matrix &B){
    matrix C;int i,j,k;
    REP(i,5) REP(k,5) if (A.A[i][k]) REP(j,5)
        C.A[i][j]+=A.A[i][k]*B.A[k][j];
    return C;
}
int tot;
void build(int &x,int L,int R){
    if (!x) x=++tot;
    if (L==R){
        T[x]=A[L]?F1:F0;
        return;
    }int mid=(L+R)/2;
    build(T[x].l,L,mid);
    build(T[x].r,mid+1,R);
    memcpy(T[x].A,mul(T[T[x].l],T[T[x].r]).A,sizeof(T[1].A));
}
void update(int &x,int pos,int k,int L,int R){
    if (!x) x=++tot;
    if (L==R){
        T[x]=k?F1:F0;
        return;
    }int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,k,L,mid);
    else update(T[x].r,pos,k,mid+1,R);
    memcpy(T[x].A,mul(T[T[x].l],T[T[x].r]).A,sizeof(T[1].A));
}
matrix ans;
void query(int x,int l,int r,int L,int R){
    if (l<=L&&R<=r){
        ans=mul(ans,T[x]);
        return;
    }int mid=(L+R)/2;
    if (l<=mid) query(T[x].l,l,r,L,mid);
    if (mid<r) query(T[x].r,l,r,mid+1,R);
}
int main() {
    int i,j,n,m;
    F0.A[0][4]=1;F0.A[0][0]=1;//0
    F0.A[1][2]=1;F0.A[2][1]=1;//1 2
    F0.A[3][0]=1;F0.A[3][3]=1;
    F0.A[4][4]=1;F0.A[3][4]=1;

    F1.A[1][4]=1;F1.A[1][0]=1;//1
    F1.A[2][2]=1;F1.A[0][1]=1;//2 0
    F1.A[3][1]=1;F1.A[3][3]=1;
    F1.A[4][4]=1;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&A[i]);
    build(root,1,n);
    FOR(i,1,m){
        int op;
        scanf("%d",&op);
        if (op==1){
            int x;
            scanf("%d",&x);
            A[x]^=1;
            update(root,x,A[x],1,n);
        }else{
            int l,r;
            scanf("%d%d",&l,&r);
            ans=matrix();
            REP(j,5) ans.A[j][j]=1;
            query(root,l,r,1,n);
            printf("%lld\n",ans.A[3][4]);
        }
    }
    return 0;
}
/*
*/
