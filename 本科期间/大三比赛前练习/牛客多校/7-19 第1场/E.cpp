#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG1
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
inline void mul(ll &A,ll B){(A*=B)%=M;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m,_m;
char S[maxn];

int A[maxn];
int ans[maxn][17][17];//pos,del,lastval
int nxt[maxn],pos[maxn];
void solve_1(){
    int i,j,k;
    FOR(k,0,n-1) {
//        rFOR(i,0,m) FOR(j,0,_m) ans[k][i][j]=0;
        rFOR(i,0,m) FOR(j,0,_m) if (ans[k][i][j]){//del
            int p;
            if (j==A[k])
                FOR(p,k+1,min(k+m-i,nxt[k]-1)) add(ans[p][i+p-k][j],ans[k][i][j]);
//            printf("%d:%d %d => %d to min(%d,%d)\n",k,i,j,k+1,k+m-i,nxt[k]-1);
            add(ans[k+1][i][A[k+1]],ans[k][i][j]);
        }
    }
//    FOR(k,0,n) {FOR(i,0,m) {FOR(j,0,_m) printf("%d ",ans[k][i][j]); printf("  <- used: %d \n",i);}puts("");}
}
void solve_2(){
    int i,j,k;
    FOR(k,1,n){
    }
}
int TaskA(){
    int i,j,k;
    scanf("%d",&_m);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,_m) pos[i]=n+1; pos[0]=n+1;
    rFOR(i,0,n) nxt[i]=pos[A[i]],pos[A[i]]=i;
    FOR(k,0,n) FOR(i,0,m) FOR(j,0,_m) ans[k][i][j]=0;
    ans[0][0][0]=1; solve_1();
    int Ans=0;
    FOR(j,0,_m) add(Ans,ans[n][m][j]);
    printf("%d\n",Ans);
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
	Task_more_n_m();
}
/*
3 2 2
1 2 1
4 2 2
1 2 1 2
*/
