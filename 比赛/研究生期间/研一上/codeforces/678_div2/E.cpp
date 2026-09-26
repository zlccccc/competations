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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}


map<int,int> MP;//value,pos
int R[maxn],cnt[maxn];
int A[maxn],pos[maxn];

int C[maxn];
int main() {
	int i,n; scanf("%d",&n);
    FOR(i,1,n) {
        scanf("%d",&A[i]);
        assert(1<=A[i]&&A[i]<=n);
    } FOR(i,1,n) pos[i]=n+1;
    rFOR(i,1,n) {
        R[i]=pos[A[i]]; pos[A[i]]=i;
    } int now=1,tot=0;
    FOR(i,1,n) {//f[1]
        cnt[A[i]]++;
        if (A[i]!=1) C[1]++;
        if (cnt[now]) {
            while (cnt[now]) now++;
            MP[now]=i;//pos
        }
    }
    MP[INF]=n+1;//MP[MAXVALUE]=n+1 为了简化操作
    FOR(i,1,n) { //remove this 的贡献
        int position=i;//should_add
        while (1) {//不能直接remove
            auto it=MP.lower_bound(A[i]);
            if (it==MP.end()) break;
            if (it->second>=R[i]) break;//del this; position
            int len=it->second-i+1,x=it->first;//should+
            if (position==i) position=it->second;//first_change
            // printf("%d->%d: mex=%d; len=%d\n",i,it->second,it->first,len);
            // assert(len>=it->first);
            C[it->first]++;
            auto itt=it; itt++;
            int _R=itt->second; MP.erase(it);
            if (_R>R[i]) MP[x]=R[i];//insert_more
        }//not!
        if (position!=i&&A[i]) MP[A[i]]=position;
        // printf("i=%d; position=%d\n",i,position);
        // for (auto now:MP) printf("(%d,%d) ",now.first,now.second); puts("<- MP");
        // if (position!=i&&A[i]) printf("push_%d-%d\n",A[i],position);
    } assert(tot<=3*n);//最大3n以内; 应该说2n以内
	int ans=1;
	while (C[ans]) ans++;
	printf("%d\n",ans);
}
/*
*/