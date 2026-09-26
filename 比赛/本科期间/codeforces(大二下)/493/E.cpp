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
const LL M=998244353;
const LL maxn=1.2e5+7;
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
    int lazy,minimum,times,cnt;
    ll ans;
    node(){lazy=minimum=cnt=times=0;ans=0;}
}T[maxn<<2];
inline void update_value(int x,int k){
    T[x].minimum+=k; T[x].lazy+=k;
}inline void update_times(int x,int k){
    //不能在这里判断,因为可能整体变化~
    T[x].times+=k; T[x].ans+=(ll)k*T[x].cnt;
}
inline void pushdown(int x){
    if (T[x].lazy){
        update_value(x<<1,T[x].lazy);
        update_value(x<<1|1,T[x].lazy);
        T[x].lazy=0;
    }if (T[x].times){
        if (T[x].minimum==T[x<<1].minimum) update_times(x<<1,T[x].times);
        if (T[x].minimum==T[x<<1|1].minimum) update_times(x<<1|1,T[x].times);
        T[x].times=0;
    }
}
node merge(node A,node B){
    node ret;
    ret.minimum=min(A.minimum,B.minimum);
    if (ret.minimum==A.minimum) ret.cnt+=A.cnt;
    if (ret.minimum==B.minimum) ret.cnt+=B.cnt;
    ret.ans=A.ans+B.ans;
    return ret;
}
void update(int x,int l,int r,int val,int L,int R){
    if (l<=L&&R<=r){
        update_value(x,val);
        return;
    }int mid=(L+R)/2;
    pushdown(x);
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
void update(int x,int pos,int val,int L,int R){
    if (L==R){
        T[x].cnt+=val;
        return;
    }int mid=(L+R)/2;
    pushdown(x);
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    if (mid<pos) update(x<<1|1,pos,val,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
ll query(int x,int l,int r,int L,int R){
    if (l<=L&&R<=r) return T[x].ans;
    ll ret=0; int mid=(L+R)/2;
    pushdown(x);
    if (l<=mid) ret+=query(x<<1,l,r,L,mid);
    if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
    return ret;
}
typedef pair<int,int> pii;
int A[maxn];
ll ans[maxn];
int stack_max[maxn],top_max;
int stack_min[maxn],top_min;
vector<pii> queries[maxn];
int TaskA(){
    int i,j,k;
    int n,q;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    scanf("%d",&q);
    FOR(i,1,q){
        int l,r;
        scanf("%d%d",&l,&r);
        queries[r].push_back(make_pair(l,i));
    }
    FOR(k,1,n){
        while (top_max&&A[stack_max[top_max]]<=A[k]) {
            int pos=stack_max[top_max--];//max
            update(1,stack_max[top_max]+1,pos,A[k]-A[pos],1,n);
        }stack_max[++top_max]=k;
        while (top_min&&-A[stack_min[top_min]]<=-A[k]) {
            int pos=stack_min[top_min--];//max
            update(1,stack_min[top_min]+1,pos,-A[k]+A[pos],1,n);
        }stack_min[++top_min]=k;
        update(1,k,1,1,n);//this
        update_times(1,1);
        for (auto now:queries[k]) {
            int l=now.first,id=now.second,r=k;
            ans[id]=query(1,l,r,1,n);
        }update(1,1,k,-1,1,n);
    }
    FOR(i,1,q) printf("%I64d\n",ans[i]);
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
