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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m;
char S[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}

const LL MOD=998244353;
const LL g=3;
LL mul(LL x,LL y) {
    return x*y%MOD;
}
LL poww(LL a,LL b) {
    LL ret=1;
    for (; b; b>>=1ll,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}
void ntt(LL *A,int len,int inv) { //抄的板子
    int i,j,k;
    for (i=1,j=len/2; i<len-1; i++) {
        if (i<j) swap(A[i],A[j]);
        k=len/2;
        while (j>=k) {
            j-=k;
            k/=2;
        }
        if (j<k) j+=k;
    }
    for (i=2; i<=len; i<<=1) {
        LL wn=poww(g,(MOD-1)/i);
        if (inv==-1) wn=poww(wn,MOD-2);
        for (j=0; j<len; j+=i) {
            LL w=1;
            for (k=j; k<(j+i/2); k++) {
                LL a=A[k],b=mul(w,A[k+i/2]);
                A[k]=(a+b)%MOD;
                A[k+i/2]=(a-b+MOD)%MOD;
                w=mul(w,wn);
            }
        }
    }
    if (inv==-1) {
        LL vn=poww(len,MOD-2);
        REP(i,len) A[i]=mul(A[i],vn);
    }
}
ll X[1<<20|7],Y[1<<20|7];
void multi(vector<int> &A,vector<int> &B){
    int len=1,n=A.size(),m=B.size(),i;
    while (len<n+m) len<<=1;
    REP(i,n) X[i]=A[i];
    rep(i,n,len) X[i]=0;
    REP(i,m) Y[i]=B[i];
    rep(i,m,len) Y[i]=0;
    ntt(X,len,1);ntt(Y,len,1);
    REP(i,len) X[i]=mul(X[i],Y[i]);
    ntt(X,len,-1);
    A.resize(n+m-1);
    vector<int>().swap(B);
    REP(i,n+m-1) A[i]=X[i];
}
struct node{
    int pos,length;
    node(int _p,int _l):pos(_p),length(_l){}
    bool operator < (const node &A)const{
        if (length!=A.length) return length>A.length;
        return pos<A.pos;
    }
};
vector<int> V[maxn];
priority_queue<node> Q;
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m){
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
int TaskA() {
	int i,j,K;
	scanf("%d",&K);
	FOR(i,1,m){
		int k;
		scanf("%d",&k);
		V[i].resize(k+1);
		FOR(j,1,k) V[i][j]=C(k,j);
		Q.push(node(i,k));
	}
    while (Q.size()>1){
        node A=Q.top();Q.pop();
        node B=Q.top();Q.pop();
//        for (auto now:value[A.pos]) printf("%-3d",now);puts("");
//        for (auto now:value[B.pos]) printf("%-3d",now);puts("");
        multi(V[A.pos],V[B.pos]);
//        for (auto now:value[A.pos]) printf("%-3d",now);puts(" <- ans");
        Q.push(node(A.pos,V[A.pos].size()));
    } node A=Q.top();Q.pop();
    printf("%d\n",V[A.pos][K]);
	return 0;
}
void initialize() {
    int i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_more_n_m();
}
/*

*/
