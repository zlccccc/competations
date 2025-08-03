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
const LL maxn=3e5+7;
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

vector<int> edge[maxn];
//broken : p<=sum{w}
int X[maxn],Y[maxn];
ll w[maxn],p[maxn];
ll sum[maxn],more[maxn];
bool okay;
void dfs_1(int x){
    for (int v:edge[x]) {
        dfs_1(v);
        sum[x]+=sum[v]+w[v];
    } if (p[x]<sum[x]) okay=0;
    more[x]=min(w[x]-1,p[x]-sum[x]);
    p[x]-=more[x]; w[x]-=more[x];
}ll dfs_2(int x,ll limit){
    more[x]=min(limit,(ll)more[x]); limit-=more[x];
    limit=min(limit,(ll)more[x]+p[x]-sum[x]);
    int ret=more[x];
//    printf("w=%d p=%d sum=%d more=%d limit=%d\n",w[x],p[x],sum[x],more[x],limit);
    for (int v:edge[x]){
        ll t=dfs_2(v,limit);
        limit-=t; ret+=t;
    }return ret;
}
int TaskA(){
    int i,j,k;
    more[1]=p[1]=INFF;
    FOR(i,1,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        scanf("%I64d%I64d",&w[y],&p[y]);
        edge[x].push_back(y);
        X[i]=x; Y[i]=y;
    } okay=1; dfs_1(1);
//    puts("");FOR(i,1,n-1) printf("%d %d %d %d more=%d\n",X[i],Y[i],w[Y[i]],p[Y[i]],more[Y[i]]);puts("");
//    FOR(i,1,n-1) printf("%d %d %d %d\n",X[i],Y[i],w[Y[i]]+more[Y[i]],p[Y[i]]+more[Y[i]]);puts("");
    if (!okay) return 0*puts("-1");
    dfs_2(1,INFF);
    printf("%d\n",n);
    FOR(i,1,n-1) printf("%d %d %I64d %I64d\n",X[i],Y[i],w[Y[i]]+more[Y[i]],p[Y[i]]+more[Y[i]]);
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
