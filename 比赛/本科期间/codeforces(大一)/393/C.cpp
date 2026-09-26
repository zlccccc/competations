#include <sstream>
#include <fstream>
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
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

struct node{
    int sum,rmax;
    node(){sum=rmax=0;}
}T[maxn*4];
node merge(node A,node B){
    node ret;
    ret.sum=A.sum+B.sum;
    ret.rmax=max(B.rmax,A.rmax+B.sum);
    return ret;
}
void update(int x,int pos,int val,int L,int R){
//    debug("update: %d %d %d %d\n",x,pos,L,R);
    if (L==R){
        if (val==1) T[x].sum=T[x].rmax=1;
        else T[x].sum=-1,T[x].rmax=0;
        return;
    }int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    else update(x<<1|1,pos,val,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
int A[maxn];
int query(int x,int k,int L,int R){//k:should
//    debug("query: %d %d %d %d\n",x,k,L,R);
    if (T[x].rmax+k<=0) return -1;
    if (L==R) return A[L];
    int mid=(L+R)/2;
    if (T[x<<1|1].rmax+k<=0) return query(x<<1,k+T[x<<1|1].sum,L,mid);
    else return query(x<<1|1,k,mid+1,R);
}
int TaskA(){
    int n,m,i,j;
    scanf("%d",&n);
    FOR(i,1,n){
        int x,op,k;
        scanf("%d%d",&x,&op);
        if (op==1) scanf("%d",&k);
        else op=-1; A[x]=k;
        update(1,x,op,1,n);
        printf("%d\n",query(1,0,1,n));
    }
    return 0;
}
void initialize(){}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
