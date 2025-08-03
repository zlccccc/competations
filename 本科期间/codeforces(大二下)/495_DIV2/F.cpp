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
const LL maxn=1e6+7;
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

typedef pair<int,int> pii;
int X;
int A[maxn];
struct node{
    vector<pii> L,R;ll ans;
}T[maxn<<2];
node merge(const node &A,const node &B){
    node ret; ll orL=0,orR=0;
    for (auto now:A.L) orL|=now.first,ret.L.push_back(now);
    for (auto now:B.R) orR|=now.first,ret.R.push_back(now);
    for (auto now:B.L) {
        int nxt=now.first|orL;
        if (ret.L[ret.L.size()-1].first==nxt) ret.L[ret.L.size()-1].second+=now.second;
        else ret.L.push_back(make_pair(nxt,now.second));
    }for (auto now:A.R) {
        int nxt=now.first|orR;
        if (ret.R[ret.R.size()-1].first==nxt) ret.R[ret.R.size()-1].second+=now.second;
        else ret.R.push_back(make_pair(nxt,now.second));
    }ret.ans=A.ans+B.ans;
    ll cnt=0;int i=B.L.size()-1;
    for (auto now:A.R){
        while (i>=0&&(B.L[i].first|now.first)>=X) cnt+=B.L[i].second,i--;
        ret.ans+=(ll)now.second*cnt;
    }
    return ret;
}
void build(int x,int L,int R){
    if (L==R){
        T[x].L.push_back(make_pair(A[L],1));
        T[x].R.push_back(make_pair(A[R],1));
        T[x].ans=(A[L]>=X); return;
    }int mid=(L+R)/2;
    build(x<<1,L,mid);
    build(x<<1|1,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
void update(int x,int pos,int L,int R){
    if (L==R){
        T[x].L.clear(); T[x].R.clear();
        T[x].L.push_back(make_pair(A[L],1));
        T[x].R.push_back(make_pair(A[R],1));
        T[x].ans=(A[L]>=X); return;
    }int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    if (mid<pos) update(x<<1|1,pos,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
node query(int x,int l,int r,int L,int R){
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2;
    if (r<=mid) return query(x<<1,l,r,L,mid);
    if (mid<l) return query(x<<1|1,l,r,mid+1,R);
    return merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
}
int TaskA(){
    int n,m,i;
    scanf("%d%d%d",&n,&m,&X);
    FOR(i,1,n) scanf("%d",&A[i]);
    build(1,1,n);
    FOR(i,1,m) {
        int op,l,r;
        scanf("%d%d%d",&op,&l,&r);
        if (op==1){
            A[l]=r;
            update(1,l,1,n);
        }else{
            printf("%I64d\n",query(1,l,r,1,n).ans);
        }
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
