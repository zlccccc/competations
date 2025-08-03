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
const LL maxn=1e6+7;
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


LL inv[2000002];//inverse
LL fac[2000002];//Factorial
LL C(int n,int m){
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
vector<int> factor[maxn];
int n,m;
int TaskA(){
    int i,j,k;
    scanf("%d%d",&k,&n);
    ll ans=1;
    //f_0()=2
    for (int v:factor[n]){
        int cnt=0;
        while (n%v==0) n/=v,cnt++;
        ll mul=C(k+cnt-1,k)+C(k+cnt,k); mul%=M;
        ans=(ll)ans*mul%M;
//        printf("%d: C(%d %d)*2+C(%d %d)\n",v,k+cnt-1,k,k+cnt,k);
    }
    printf("%d\n",ans);
    return 0;
}
void initialize(){
    int i,j;
    FOR(i,2,1000000) if (!factor[i].size())
        for (j=i;j<=1000000;j+=i) factor[j].push_back(i);
    fac[0]=1;
    FOR(i,1,2000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,2000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,2000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
}
void Task_one(){TaskA();}
void Task_T(){int T;scanf("%d",&T);while (T--) TaskA();}
void Task_more_n(){while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m(){while (~scanf("%d%d",&n,&m)) TaskA();}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_T();
}
/*
1 2 3 4 5
1 1 1 1 1(0)
1 2 3 4 5(1)
1 3 6 10 15(2)

0 1 2 3 4 5 6...
1 2 2 2 2 2 2...(0)
1 1 1 1 1 1 1
0 1 1 1 1 1 1
*/
