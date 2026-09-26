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
const LL maxn=2e5+7;
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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
 
typedef pair<int,ll> pil;
int A[maxn],B[maxn],top;
pil merge(pil A,pil B){
    // printf("merge: %d %lld; %d %lld\n",A.first,A.second,B.first,B.second);
    if (A.first<B.first) return B;
    else if (A.first>B.first) return A;
    else A.second+=B.second; return A;
}
pair<int,ll> solve(int l,int r){
    // printf("solve:%d %d\n",l,r);
    if (r-l==1) return make_pair(1,1);
    int i,j;
    pii now=make_pair(0,1),ret=now,nxt;
    rep(i,l,r){
        if (str[i]=='('){
            int cnt=1;
            for (j=i+1;cnt;j++) {
                if (str[j]=='(') cnt++;
                else if (str[j]==')') cnt--;
            } nxt=solve(i+1,j-1);
        } else j=i+1,nxt=make_pair(1,1);
        now.first+=nxt.first;
        now.second*=nxt.second;
        if (str[j]!='*') {
            ret=merge(ret,now);
            now=make_pair(0,1);
        } i=j;
    }
     // printf("%d %d\n",ret.first,ret.second);
    return ret;
}
int main() {
    scanf("%s",str);
    pil now1=solve(0,strlen(str));
    scanf("%s",str);
    pil now2=solve(0,strlen(str));
    // puts("OK2");
    if (now1.first>now2.first) return 0*puts("1/0");
    if (now1.first<now2.first) return 0*puts("0/1");
    // printf("%d %lld %d %lld\n",now1.first,now1.second,now2.first,now2.second);
    ll g=gcd(now1.second,now2.second);
    now1.second/=g; now2.second/=g;
    printf("%lld/%lld\n",now1.second,now2.second);
}
/*
*/