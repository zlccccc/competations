#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B){A+=B;(A>=M)&&(A-=M);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m;
char S[maxn];

const int MAX=1e9+7;
struct node{
    int l,r,val;
}T[maxn*40];int tot;
struct station{
    int x,r,f;
}A[maxn];
void update(int &x,int pos,int L,int R){
//    printf("%d %d %d %d\n",x,pos,L,R);
    if (!x) x=++tot; T[x].val++;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,L,mid);
    else update(T[x].r,pos,mid+1,R);
}
int query(int x,int l,int r,int L,int R){
    if (!x) return 0;
    if (l<=L&&R<=r) return T[x].val;
    int ret=0,mid=(L+R)/2;
    if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
    if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
    return ret;
}
int root[maxn];
int TaskA(){
    int i,j,k,q;
    scanf("%d",&k);
    FOR(i,1,n) scanf("%d%d%d",&A[i].x,&A[i].r,&A[i].f);
    sort(A+1,A+1+n,[](station A,station B){
        return A.r>B.r;
    });ll ans=0;
    FOR(i,1,n) {
        FOR(j,-k,k) if (j+A[i].f>0)
            ans+=query(root[j+A[i].f],A[i].x-A[i].r,A[i].x+A[i].r,1,MAX);
        update(root[A[i].f],A[i].x,1,MAX);
    }printf("%I64d\n",ans);
    return 0;
}
void initialize(){}
void Task_one(){TaskA();}
void Task_T(){int T;scanf("%d",&T);while (T--) TaskA();}
void Task_more_n(){while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m(){while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string(){while (~scanf("%s",S)) TaskA();}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_more_n();
}
/*

*/
