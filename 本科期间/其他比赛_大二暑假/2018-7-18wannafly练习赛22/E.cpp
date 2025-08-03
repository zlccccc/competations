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
const LL maxn=5e5+7;
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

// 火车上这垃圾网速...开热点交题都交不上去
inline int lowbit(int x){return x&-x;}
ll A[maxn],sum[maxn],B[maxn];
inline void update(int x,ll val){
    for (;x<=n;x+=lowbit(x)) sum[x]+=val;
}inline ll query(int x){
    ll ret=0;
    for (;x;x-=lowbit(x)) ret+=sum[x];
    return ret;
}
//n^x(mod m)=m^(phi(m)+x%phi(m))%m (x>m)
inline ll mod(LL a,int b){
    if (a<b) return a;
    return a%b+b;
}
inline int poww(ll a,int b,int M){
    ll ret=1; a=mod(a,M);
    for (;b;b>>=1ll,a=mod(1ll*a*a,M))
        if (b&1) ret=mod(1ll*ret*a,M);
    return ret;
}
const int MAX=2e7+1;
int phi[MAX+7];
int P[maxn];
int tot;
ll solve(int l,int r,int pos){
    if (l==r||pos==tot) return mod(A[l],P[pos]);
    A[l+1]=A[l]+B[l+1];
    return poww(A[l],solve(l+1,r,pos+1),P[pos]);
}
int TaskA(){
    int i,j,k,q;
    FOR(i,1,n) scanf("%lld",&A[i]),B[i]=A[i]-A[i-1];
    FOR(i,1,n) update(i,B[i]);
    FOR(i,1,m){
        int op,l,r,val;
        scanf("%d%d%d%d",&op,&l,&r,&val);
        if (op==1){
            B[l]+=val; B[r+1]-=val;
            update(l,val);
            update(r+1,-val);
        }else{
            P[1]=val;
            for (tot=1;P[tot]!=1;tot++) P[tot+1]=phi[P[tot]];
            A[l]=query(l);
            printf("%lld\n",solve(l,r,1)%val);
        }
    }
    return 0;
}
int p[MAX+7],ctot;
void initialize(){
    tot=0;int i,j;phi[1]=1;
    FOR(i,2,MAX){
        if (!p[i]) p[ctot++]=i,phi[i]=i-1;
        REP(j,ctot){
            //感觉上不会爆,因为是从小往筛的
            if (i*p[j]>MAX) break;
            p[i*p[j]]=1;
            if (i%p[j]==0) {phi[i*p[j]]=phi[i]*p[j];break;}
            else phi[i*p[j]]=phi[i]*(p[j]-1);
        }
    }
}
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

*/
