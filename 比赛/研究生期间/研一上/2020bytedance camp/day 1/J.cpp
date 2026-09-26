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
const LL maxn=1e5+107;
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


int value[maxn][2];
int A[maxn][2];
vector<pii> P[maxn];
int S[maxn],top;
char ans[maxn];

int Base[32],Use[32],Pos[32];
void insert(int val,int pos) {
    int i; int use=0;
    rREP(i,32) if ((val>>i)&1) {
        if (!Base[i]) Base[i]=val,Use[i]=use^(1<<i),Pos[i]=pos; 
        val^=Base[i]; use^=Use[i];
    }
}
int query(int val) {
    int i; int use=0;
    rREP(i,32) if ((val>>i)&1) {
        if (!Base[i]) return -1;
        val^=Base[i]; use^=Use[i];
    } return use;
}
int main() {
    int n,k,i;
    scanf("%d%d",&n,&k);
    FOR(i,1,n) {
        scanf("%d%d",&A[i][0],&A[i][1]);
        P[A[i][0]].push_back(make_pair(i,0));
        P[A[i][1]].push_back(make_pair(i,1));
    }
    FOR(i,1,100000) {
        sort(P[i].begin(),P[i].end(),[&](pii x,pii y) {
            return A[x.first][x.second^1]>A[y.first][y.second^1];
        });
        for (auto now:P[i]) {
            int p,o; p=now.first; o=now.second;
            int pos=lower_bound(S,S+top+1,A[p][o^1])-S;
            value[p][o]=pos;//mex
            if (!o) {S[pos]=A[p][1]; top=max(top,pos);}
        }
    }
    // FOR(i,1,n) {
    //     printf("%d %d\n",value[i][0],value[i][1]);
    // }
    int now=0;
    FOR(i,1,k) {
        int t; scanf("%d",&t);
        int more=(value[t][0]-1)^(value[t][1]-1);
        insert(more,i); now^=value[t][0]-1;
        // printf("mex%d(%d) ",value[t][0]-1,value[t][1]-1);
        ans[i]='0';
    } int t=query(now);
    if (t==-1) return 0*puts("impossible");
    REP(i,32) if ((t>>i)&1) ans[Pos[i]]^=1;
    puts(ans+1);
}
/*
5 3
1 1
4 5
3 4
5 3
6 6
1 2 4

5 3
1 1
3 4
5 3
4 5
7 7
5 1 2
*/