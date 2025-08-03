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
 
#define DEBUG1
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
const LL maxn=3e5+7;
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
 
set<int> have[2];
int A[maxn],C[32][2];
int nxt[maxn*30][2],tot;
void ins(int x) {
    // printf("ins: %d\n",x);
    int now=0,i;
    rREP(i,31) {
        int k=(x>>i)&1;
        if (!nxt[now][k]) nxt[now][k]=++tot;
        now=nxt[now][k];
    }
}
map<int,int> MP; int itot;
int MAX=INF;
void cal(int x) {
    int now=0,nowMAX=0,i;
    rREP(i,31) {
        int k=(x>>i)&1;
        if (nxt[now][k]) {
            now=nxt[now][k];
        } else {
            nowMAX|=1<<i;
            now=nxt[now][k^1];
        }
    } min_(MAX,nowMAX);
}
int CNT;
vector<int> last,ans;
deque<int> Q[maxn*2];
int main() {
    int i,j;
    startTimer();
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) REP(j,31) if ((A[i]>>j)&1) C[j][1]++; else C[j][0]++;
    rREP(j,31) {
        if (C[j][1]!=n&&C[j][0]!=n) break;
    } int k=j;
    if (k==-1||n<=2) {
        FOR(i,1,n) printf("%d%c",i," \n"[i==n]);
        return 0;
    }
    FOR(i,1,n) if (((A[i]>>k)&1)) ins(A[i]);
    FOR(i,1,n) if (!((A[i]>>k)&1)) cal(A[i]);
    printTimer(); startTimer();
    FOR(i,1,n) {
        if (!MP.count(A[i])) MP[A[i]]=++itot;
        if (!MP.count(MAX^A[i])) MP[MAX^A[i]]=++itot;
        Q[MP[A[i]]].push_back(i);
        have[(A[i]>>k)&1].insert(i);
    }
    // FOR(i,1,n) FOR(j,1,n) if ((A[i]>>k)%2!=(A[j]>>k)%2) min_(MAX,A[i]^A[j]);
    // printf("OK ! k=%d %d\n",k,MAX);
    for (auto now:MP) {
        if (Q[now.second].size()&&Q[MP[MAX^now.first]].size()) {
            CNT++;
            // printf("SUM: %d\n",now.first);
        }
    } CNT/=2;
    int Pre=-1;;
    FOR(i,1,n+n) {
        if (ans.size()==n) break;
        debug("\n%d (pre=%d): ",i,Pre);
        bool ToLast=0;
        int pos=INF;//only this
        if (Pre==-1) min_(pos,i);
        else {
            int Pre_MAX=MP[Pre^MAX];
            if (have[(Pre>>k)&1].size()) min_(pos,*(have[(Pre>>k)&1].begin()));
            if (Q[Pre_MAX].size()) min_(pos,Q[Pre_MAX].front());
            if (last.size()) {
                int P=INF,p_p=-1;
                if (last.size()==1) { // 这里竟然还有问题
                    // if (!Q[MP[MAX^A[last[0]]]].size()) return 0*puts("NO WAY");
                    p_p=Q[MP[MAX^A[last[0]]]].front();
                    debug("p_p=%d last=%d pos=%d\n",p_p,last[0],pos);
                    last.push_back(p_p); have[(A[p_p]>>k)&1].erase(p_p);
                }
                int t; REP(t,2) {
                    if ((A[last[t]]^Pre)<=MAX&&!have[(A[last[t]]>>k)&1].size())
                        min_(P,last[t]);
                }
                debug("P=%d pos=%d, p_p=%d\n",P,pos,p_p);
                if (P<=pos) {
                    if (p_p!=-1) Q[MP[A[p_p]]].pop_front();
                    else i--;
                    int all=last[0]^last[1];
                    ans.push_back(P);
                    ans.push_back(all^P);
                    Pre=A[all^P];
                    last.clear(); CNT=-1;
                    debug("1 : %d %d %d\n",P,all^P,p_p);
                    continue;
                } else if (p_p!=-1) {
                    last.pop_back();
                    have[(A[p_p]>>k)&1].insert(p_p);
                }
            }
        }
        //changes
        int x=A[pos];
        int MPx=MP[x],MAX_x=MP[MAX^x];
        if (Q[MPx].size()==1) {
            if (Q[MAX_x].size()) CNT--;
            if ((CNT==0&&Q[MAX_x].size())||
                    (last.size()&&(x^MAX)==A[last[0]])) {
                last.push_back(pos); ToLast=1;
            }
        } Q[MPx].pop_front();//only this
        if (!ToLast) {
            ans.push_back(pos); Pre=A[pos];
        }
        debug("2(pre=%d): %d %d\n",Pre,pos,ToLast);
        have[(A[pos]>>k)&1].erase(pos);
    }
    printTimer();
    REP(i,(int)ans.size()) printf("%d%c",ans[i]," \n"[i==(int)ans.size()-1]);
}
/*
8 1 9 2 6 0 8 1 7
3 1 3 5
4 1 3 7 15
4 1 2 4 8
*/