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

const int MAX=1<<20;
ll number[77][77];
int n,m;
char A[maxn];
int F[77][MAX+7];
int TaskA(){
    int i,j,k;
    scanf("%d%s",&n,A+1);
    FOR(i,1,n) FOR(j,i,n)
        number[i][j]=min(250ll,number[i][j-1]*2+A[j]-'0');
//    FOR(i,1,n) FOR(j,i,n) printf("%d-%d : %lld\n",i,j,number[i][j]);
    int ans=0;
    FOR(i,1,n){
        FOR(j,1,i) if (number[j][i]>0&&number[j][i]<20){
//            printf("%d ",number[j][i]);
            number[j][i]--;
            FOR(k,1,MAX) add(F[i][k|(1<<number[j][i])],F[j-1][k]);
            F[i][(1<<number[j][i])]++;
        }int now=0;
        REP(j,20) now|=1<<j,add(ans,F[i][now]);
//        printf("%d\n",ans);
    }
    printf("%d\n",ans);
    return 0;
}
void initialize(){}
void Task_one(){TaskA();}
void Task_T(){int T;scanf("%d",&T);while (T--) TaskA();}
void Task_more_n(){while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m(){while (~scanf("%d%d",&n,&m)) TaskA();}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
*/
