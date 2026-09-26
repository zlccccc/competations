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
const LL M=1e9+7;
const LL maxn=2e6+107;
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

bool mark[maxn]; int val;
int tmark[maxn],n;
int ask(char c,int x) {
    int ret=0;
    printf("%c %d\n",c,x);
    fflush(stdout);
    for (int k=x;k<=n;k+=x) {
        ret+=tmark[k]; if (c=='B'&&k!=val) tmark[k]=0;
    }
    // printf("  should %d\n",ret);
    scanf("%d",&ret);
    return ret;
}
vector<int> todo;
int main() {
    int i;
    scanf("%d",&n);
    //checkit
    // scanf("%d",&val);
    FOR(i,1,n) mark[i]=1,tmark[i]=1;
    int cnt=0;
    vector<int> vec;
    int o=0,all=n;
    int ans=1;
    FOR(i,2,n) if (mark[i]) {
        cnt++; vec.push_back(i);
        int should=0;
        for (int k=i;k<=n;k+=i) should+=mark[k],mark[k]=0;
        all-=ask('B',i);
        todo.push_back(i);
        if ((++o)%100==0) {
            int now=ask('A',1);
            if (now!=all) {
                for (int v:todo) {
                    for (ll k=v;k<=n;k*=v) if (ask('A',k)) ans*=v;
                } all=now;
            } todo.clear();
        }
    }
    int now=ask('A',1);
    if (now!=all) {
        for (int v:todo) {
            for (ll k=v;k<=n;k*=v) if (ask('A',k)) ans*=v;
        }
    } todo.clear();
    printf("C %d\n",ans);
}
/*
4
2 -1 7 3
2
2 4 -3
3 4 2

*/