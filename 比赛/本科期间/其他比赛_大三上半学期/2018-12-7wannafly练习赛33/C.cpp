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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
char str[maxn];
 
int A[maxn],C[255],D[255];
string ans,now;
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int i,j,k,t;
        scanf("%s",str);
        int len=strlen(str); ans="";
        REP(i,len) C[(int)str[i]-'0']++;
        REP(i,10) REP(j,10) REP(k,10){
            C[i]--; C[j]--; C[k]--;
            if (C[i]>=0&&C[j]>=0&&C[k]>=0&&(i*100+j*10+k)%8==0){
                now="";
                REP(t,10) D[t]=C[t];
                rREP(t,10) while (D[t]--) now+=t+'0';
                now+=i+'0'; now+=j+'0'; now+=k+'0';
                ans=max(ans,now);
                // cout<<now<<"\n";
            } C[i]++; C[j]++; C[k]++;
        } if (len==2){
            REP(j,10) REP(k,10){
                C[j]--; C[k]--;
                if (C[j]>=0&&C[k]>=0&&(j*10+k)%8==0){
                    now=""; now+=j+'0'; now+=k+'0';
                    ans=max(ans,now);
                    // cout<<now<<"\n";
                } C[j]++; C[k]++;
            }
        } if (len==1&&(str[0]-'0')%8==0) ans+=str[0];
        if (ans=="") puts("-1");
        else cout<<ans<<"\n";
        REP(i,len) C[(int)str[i]-'0']--;
    }
}
/*
*/