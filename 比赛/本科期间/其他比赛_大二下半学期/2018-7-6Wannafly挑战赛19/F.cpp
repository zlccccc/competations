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

typedef pair<int,int> pii;
int len;
int cnt[27];
pii H[maxn];
map<pii,int> MP;
char A[maxn];
struct node{
    int l,r,id;
}Q[maxn];
int block[maxn],SIZE;
bool cmp(node A,node B){
    if (block[A.l]!=block[B.l]) return block[A.l]<block[B.l];
    return A.r<B.r;
}ll Ans[maxn];
int TaskA(){
    int n,q;
    int i,j,k;
    scanf("%d",&k);
    scanf("%s",A+1);
    n=strlen(A+1);
    FOR(i,1,n){
        cnt[A[i]-'a']++;
        cnt[A[i]-'a']%=k;
        ll h_h;
        h_h=0; REP(j,26) h_h=(h_h*131+cnt[j])%(ll)(1e9+7); H[i].first=h_h;
        h_h=0; REP(j,26) h_h=(h_h*133+cnt[j])%(ll)(1e9+9); H[i].second=h_h;
    }scanf("%d",&q);
    SIZE=sqrt(n);if (!SIZE) SIZE++;
    FOR(i,1,n) block[i]=i/SIZE;
    FOR(i,1,q){
        scanf("%d%d",&Q[i].l,&Q[i].r);
        Q[i].id=i; Q[i].l--;
    }sort(Q+1,Q+1+n,cmp);
    int L=1,R=0;
    ll ans=0;
    FOR(i,1,q){
        while (R<Q[i].r){R++;ans+=MP[H[R]];MP[H[R]]++;}
        while (L>Q[i].l){L--;ans+=MP[H[L]];MP[H[L]]++;}
        while (R>Q[i].r){MP[H[R]]--;ans-=MP[H[R]];R--;}
        while (L<Q[i].l){MP[H[L]]--;ans-=MP[H[L]];L++;}
        Ans[Q[i].id]=ans;
    }FOR(i,1,q) printf("%lld\n",Ans[i]);
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
