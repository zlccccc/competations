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
const LL maxn=4e4+107;
// const double pi=acos(-1.0);
// const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

const int L=54;
//copied from blog;
const char op[7]="FLRUDB";
const int d[6][5][4]={
    {{1,3,9,7},{2,6,8,4},{43,19,48,18},{44,22,47,15},{45,25,46,12}},//F
    {{10,12,18,16},{11,15,17,13},{37,1,46,36},{40,4,49,33},{43,7,52,30}},//L
    {{19,21,27,25},{20,24,26,22},{54,9,45,28},{51,6,42,31},{48,3,39,34}},//R
    {{37,39,45,43},{38,42,44,40},{28,19,1,10},{29,20,2,11},{30,21,3,12}},//U
    {{16,7,25,34},{17,8,26,35},{46,48,54,52},{47,51,53,49},{18,9,27,36}},//D
    {{28,30,36,34},{29,33,35,31},{27,39,10,52},{24,38,13,53},{21,37,16,54}}//B
};
int id[L+1];
void Move(char c) {
    int i,k,o;
    REP(i,7) if (op[i]==c) {
        REP(k,5) {
            int tmp=id[d[i][k][3]];
            rrep(o,1,4) id[d[i][k][o]]=id[d[i][k][o-1]];
            id[d[i][k][0]]=tmp;
        }
    }
}
char str[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i;
        ll ans=1;
        scanf("%s",str);
        int n=strlen(str);
        FOR(i,1,54) id[i]=i;
        REP(i,n) {
            if (str[i]=='\'') Move(str[i-1]),Move(str[i-1]);
            else if (str[i]=='2') Move(str[i-1]);
            else Move(str[i]);
        }
        FOR(i,1,54) {
            int c=1;
            for (int k=id[i];k!=i;k=id[k]) c++;
            ans=ans/gcd(ans,c)*c;
        }
        // FOR(i,1,54) printf("%d ",id[i]); puts("<- id");
        printf("Case #%d:\n",_);
        printf("%lld\n",ans);
    }
}
/*
*/