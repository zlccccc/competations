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

int A[1007][1007];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,j,x,y,_x,_y,ans=INF;
        int n,m; scanf("%d%d%d",&n,&x,&y);
        m=n;
        FOR(i,1,n) FOR(j,1,m) scanf("%d",&A[i][j]);
        FOR(_x,1,n) {
            FOR(_y,1,m) {
                int nowans=(abs(x-_x)+abs(y-_y)+1)/2;
                // if (_x==7&&_y==2)printf("nowans: %d\n",nowans);
                vector<int> v;
                FOR(i,max(1,_x-3),min(n,_x+3)) {
                    int r=3-abs(_x-i);
                    FOR(j,max(1,_y-r),min(m,_y+r)) {
                        // printf("")
                        if (i==_x&&j==_y) continue;
                        // assert(abs(y-j)+abs(x-i)<=3);
                        v.push_back(A[i][j]);
                    }
                } 
                REP(i,10) v.push_back(0);
                sort(v.begin(), v.end());
                v.push_back(A[_x][_y]);
                reverse(v.begin(), v.end());
                rep(i,1,(int)v.size()) v[i]+=v[i-1];
                int count=0,food=0;
                // if (_x==1&&_y==1) 
                // printf("%d ",v.size());
                while(count<8) {
                    int more=(8*(count+1)*(count+1)-food+v[count]-1)/v[count];
                    more=max(more,1);
                    food+=v[count]*more;
                    nowans+=more;
                    while (food>=8*(count+1)*(count+1)) count++;
                    // if (_x==7&&_y==2) printf("%d: food=%d\n",nowans,food);
                } min_(ans,nowans);
                // if (nowans==39) {
                //     printf("sizes=%d ",(int)v.size());
                //     for (int V:v) printf("%d ",V); puts("");
                //     printf("%d,%d : %d %d\n",_x,_y,nowans,food);
                // }
            }
        } printf("%d\n",ans);
    }
}
/*
*/