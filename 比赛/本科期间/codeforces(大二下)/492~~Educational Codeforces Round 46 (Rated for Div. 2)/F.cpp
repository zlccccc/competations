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
const LL maxn=5e5+7;
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
pii T[maxn<<2];
void update(int x,int last,int val,int l,int r,int L,int R){
    if (l<=L&&R<=r) {
        T[x]=max(T[x],make_pair(last,val));
        return;
    }int mid=(L+R)/2;
    if (l<=mid) update(x<<1,last,val,l,r,L,mid);
    if (mid<r) update(x<<1|1,last,val,l,r,mid+1,R);
}
pii query(int x,int pos,int L,int R){
    if (L==R) return T[x];
    int mid=(L+R)/2;pii ret=T[x];
    if (pos<=mid) ret=max(ret,query(x<<1,pos,L,mid));
    else ret=max(ret,query(x<<1|1,pos,mid+1,R));
    return ret;
}
int A[maxn];
vector<pii> queries[maxn];
int pos[maxn],pre[maxn],nxt[maxn];
int ans[maxn];
int TaskA(){
    int n,q,i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) pos[A[i]]=0;
    FOR(i,1,n) pre[i]=pos[A[i]],pos[A[i]]=i;
    FOR(i,1,n) pos[A[i]]=n+1;
    rFOR(i,1,n) nxt[i]=pos[A[i]],pos[A[i]]=i;
    scanf("%d",&q);
    FOR(i,1,q){
        int l,r;
        scanf("%d%d",&l,&r);
        queries[r].push_back(make_pair(l,i));
    }FOR(i,1,n){
        update(1,nxt[i]-1,A[i],pre[i]+1,i,1,n);
        for (auto now:queries[i]){
            int l=now.first;
            auto q=query(1,l,1,n);
            if (q.first>=i) ans[now.second]=q.second;
            else ans[now.second]=0;
        }
    }FOR(i,1,q) printf("%d\n",ans[i]);
}
int main() {
	int startTime=clock();
	//initialize
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
