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
const LL maxn=1007+107;
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

const int BLOCK=10;
char str[107];
void ask_10_times(vector<int> &v) {
    int i;
    char now[2];
    FOR(i,1,v.size()) {
        if (v[i]) printf("%d\n",v[i]);
        else puts("1");
        fflush(stdout);
        scanf("%s",now);
        str[i]=now[0];
    }
}
vector<int> v1,v2;
vector<pii> back;//x->y
bool mask[107];//same_mask; not_same_mask
char real_str[17][27];
int main() {
    int T,B,_; T=1;
    scanf("%d%d",&T,&B);
    FOR(_,1,T){
        int i,t;
        back.clear(); v1.clear(); v2.clear();
        vector<int> v;
        REP(t,B/BLOCK) {//group
            v.clear();
            FOR(i,1,BLOCK/2) v.push_back(t*BLOCK/2+i);
            FOR(i,1,BLOCK/2) v.push_back((B/BLOCK*2-t)*BLOCK/2-i+1);
            ask_10_times(v);
            FOR(i,1,BLOCK/2) {//to right half
                back.push_back(make_pair(t*BLOCK/2+i,(B/BLOCK*2-t)*BLOCK/2-i+1));
                mask[(B/BLOCK*2-t)*BLOCK/2-i+1]=str[i]^str[i+BLOCK/2];
            }
            FOR(i,1,BLOCK) real_str[t][i]=str[i];

            FOR(i,1,BLOCK/2) if (str[i]!=str[i+BLOCK/2]) break;
            if (i==BLOCK/2+1) v1.push_back(0);
            else {
                v1.push_back(t*BLOCK/2+i);
                
            }
            if (i==BLOCK/2) i=1;
            v.push_back(t*BLOCK/2+i);//sync
            // puts(str);
        } //sync_first
        v.clear();
        REP(t,B/BLOCK) {
        } while (v.size()<BLOCK) v.push_back(1);
        ask_10_times(v);
        REP(t,B/BLOCK) mask[t]=
        //self_sync
    }
}
/*
*/