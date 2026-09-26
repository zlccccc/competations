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

char str[maxn];
char ans[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,n;
        scanf("%s",str+1);
        n=strlen(str+1); ans[n+1]=0;
        int cnt=0,all=0;
        FOR(i,1,n) {
            ans[i]=str[i];
            if (str[i]=='(') cnt++;
            if (str[i]==')') cnt--;
            if (str[i]=='?') all++;
        }
        FOR(i,1,n) if (cnt<0&&ans[i]=='?') all--,cnt++,ans[i]='(';
        rFOR(i,1,n) if (cnt>0&&ans[i]=='?') all--,cnt--,ans[i]=')';
        cnt=-all/2;
        FOR(i,1,n) if (cnt<0&&ans[i]=='?') all--,cnt++,ans[i]='(';
        rFOR(i,1,n) if (ans[i]=='?') ans[i]=')';
        cnt=0;
        FOR(i,1,n) {
            if (ans[i]=='(') cnt++;
            if (ans[i]==')') cnt--;
            if (cnt<0) break;
        }
        // if (cnt!=0) {puts("NO"); continue;}
        // puts(ans+1);
        bool mark=0;
        cnt=0;
        FOR(i,1,n) {
            int j;
            if (ans[i]=='(') cnt++;
            if (ans[i]==')') cnt--;
            if (str[i]=='?') {
                int nowcnt=cnt;
                if (ans[i]=='(') nowcnt-=2; // other col
                if (ans[i]==')') nowcnt+=2; // other col
                if (nowcnt<0) continue;
                // printf("nowcnt=%d\n",nowcnt);
                FOR(j,i+1,n) {
                    if (str[j]=='(') nowcnt++;
                    if (str[j]==')') nowcnt--;
                    if (str[j]=='?') break;
                    if (nowcnt<0||j==n+1) break;
                }
                // printf("nowcnt=%d  %c %c\n",nowcnt,str[i],str[j]);
                // swap(ans[i],ans[j]); puts(ans+1); swap(ans[i],ans[j]);
                if (j==n+1) break;
                if (nowcnt<0) continue;
                if (ans[j]=='(') nowcnt--;
                if (ans[j]==')') nowcnt++;
                if (nowcnt<0) continue;
                // printf("nowcnt=%d\n",nowcnt);
                if (str[i]=='?'&&str[j]=='?'&&ans[i]!=ans[j]) {
                    // swap(ans[i],ans[j]); puts(ans+1); swap(ans[i],ans[j]);
                    mark=1;
                }
            }
        }
        if (!mark) puts("YES");// all )
        else puts("NO");
    }
}
/*
50000
?)?(??
(?))
??????
()
??
?(?)()?)
*/