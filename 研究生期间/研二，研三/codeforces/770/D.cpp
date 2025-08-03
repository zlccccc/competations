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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=2e5+107;
 
// int A[]={0,1,2,3,4,5,0,8,6};
int A[]={0,1,2,0,3,5,0,8,6};
inline int ask(int x,int y,int z) {
    int ret;
    printf("? %d %d %d\n",x,y,z);
    fflush(stdout);
    // printf("%d\n",max(max(A[x],A[y]),A[z])-min(min(A[x],A[y]),A[z]));
    // return max(max(A[x],A[y]),A[z])-min(min(A[x],A[y]),A[z]);
    scanf("%d",&ret);
    return ret;
}
vector<int> Pos;
int sum[maxn];//2-more-minimum-value
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        /*to solve the problem*/
        int n,m,i,j,MAX,MIN2,MAX2=0,MIN=INF,pos=3,pos2=2;
        fflush(stdout);
        scanf("%d",&n);
        MAX=0; MIN=INF;
        FOR(i,3,n) {
            int val=ask(1,2,i);
            MIN=min(MIN,val);
            MAX=max(MAX,val);
            if (val==MAX) pos=i;
        } MAX2=MAX; MIN2=MIN;
        MAX=0; MIN=INF;
        FOR(i,2,n) if (i!=pos) {
            int val=ask(pos,1,i);
            MIN=min(MIN,val);
            MAX=max(MAX,val);
            if (val==MAX) pos2=i;
        }
        if (MAX<=MAX2&&MIN2==MAX2) printf("! %d %d\n",1,2);
        else if (MIN==MAX) printf("! %d %d\n",1,pos);
        else printf("! %d %d\n",pos,pos2);
    }
}
/*
*/