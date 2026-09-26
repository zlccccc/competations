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

int val[157][20];
int valuefirst[maxn];
int C[maxn];
string strval[157][20];
string min_val(string A,string B){
    if (A.length()<B.length()) return A;
    if (A.length()>B.length()) return B;
    return A<B?A:B;
}
string base = "?????????????????????????????????????????";
void init(){
    int i,j,k;
    memset(val,0x3f,sizeof(val));
    FOR(i,0,150) FOR(j,0,9) strval[i][j]=base;
    FOR(i,0,1000000) {
        C[i]=C[i/10]+i%10;
        val[C[i]][0]=min(val[C[i]][0],i);
    }
    FOR(k,1,9) {
        FOR(i,0,1000000-k) {
            int t=0,now=0;
            FOR(t,i,i+k) now+=C[t];
            if (now<=150) val[now][k]=min(val[now][k],i);
        }
    }
    FOR(k,0,9) {
        FOR(i,1,150) if (val[i][k]!=INF) strval[i][k]=to_string(val[i][k]);
        // FOR(i,1,150) if (strval[i][k]!=base) cout<<strval[i][k]<<' '; puts("");
    }
    FOR(k,0,9) {
        FOR(i,0,150) if (strval[i][k]!=base) {
            if (strval[i][k].length()<=2) continue;
            int t;
            FOR(t,1,9) {//head
                int nxt=i+(k+1)*t;
                // if (k==2&&nxt==27){
                //     cout<<strval[i][k]; printf(" %d->%d\n",i,nxt);
                // }
                if (nxt<=150) strval[nxt][k]=min_val(strval[nxt][k],to_string(t)+strval[i][k]);
            }
        }
        // if (k==8) {
        //     FOR(i,1,150) if (strval[i][k]!=base) cout<<strval[i][k]<<' '; puts("");
        // }
    }
    // FOR(i,1,100000) {
    //     C[i]=C[i/10]+i%10;
    //     strval[C[i]][0]=min_val(strval[C[i]][0],to_string(i));
    // } FOR(i,1,150) cout<<strval[i][0]<<" ";
}
int main() {
    init();
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,k; scanf("%d%d",&n,&k);
        if (strval[n][k]!=base) cout<<strval[n][k]<<"\n";
        else puts("-1");
    }
}
/*
7
1 0
1 1
42 7
13 7
99 1
99 0
99 2

*/