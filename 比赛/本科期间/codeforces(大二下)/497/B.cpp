#include <bits/stdc++.h>
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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B){A+=B;(A>=M)&&(A-=M);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m;
char S[maxn];

struct node{
    int A,B,C;
    node(int _A,int _B,int _C):A(_A),B(_B),C(_C){};
};
ll C(int n,int m){
    ll ans=1;int i;
    FOR(i,n-m+1,n) ans*=i;
    FOR(i,1,m) ans/=i;
    return ans;
}
int cnt[maxn];
int f[8],g[8],h[8];
vector<node> have;
int TaskA(){
    int A,B,C,i,j,k;
    scanf("%d%d%d",&A,&B,&C);
    have.clear();
    have.push_back(node(A,B,C));
    have.push_back(node(A,C,B));
    have.push_back(node(B,A,C));
    have.push_back(node(B,C,A));
    have.push_back(node(C,A,B));
    have.push_back(node(C,B,A));
    g[7]=gcd(gcd(A,B),C);   f[7]=cnt[g[7]];
    g[6]=gcd(B,C);          f[6]=cnt[g[6]]-f[7];
    g[5]=gcd(A,C);          f[5]=cnt[g[5]]-f[7];
    g[3]=gcd(A,B);          f[3]=cnt[g[3]]-f[7];
    g[4]=C;                 f[4]=cnt[g[4]]-f[5]-f[6]-f[7];
    g[2]=B;                 f[2]=cnt[g[2]]-f[3]-f[6]-f[7];
    g[1]=A;                 f[1]=cnt[g[1]]-f[3]-f[5]-f[7];
//    rep(i,1,8) debug("%-2d : %-3d %-3d\n",i,g[i],f[i]);
    ll ans=0;
    REP(i,8) if (f[i]){
        rep(j,i,8) if (f[j]){
            rep(k,j,8) if (f[k]){
                bool okay=0;
                for (auto now:have){
                    if (now.A%g[i]==0&&now.B%g[j]==0&&now.C%g[k]==0) okay=1;
                    if (okay) break;
                }if (!okay) continue;
                h[i]++; h[j]++; h[k]++;
//                printf(" okay: %d %d %d (%d %d %d)\n",i,j,k,g[i],g[j],g[k]);
                ll now=1; int t;
                REP(t,8) if (h[i]) now*=::C(f[t]+h[t]-1,h[t]);
                ans+=now;
                h[i]--; h[j]--; h[k]--;
            }
        }
    }printf("%I64d\n",ans);
    return 0;
}
void initialize(){
    int i,j;
    FOR(i,1,100000){
        for (j=1;j*j<=i;j++) if (i%j==0){
            cnt[i]++;
            if (j!=i/j) cnt[i]++;
        }
    }
}
void Task_one(){TaskA();}
void Task_T(){int T;scanf("%d",&T);while (T--) TaskA();}
void Task_more_n(){while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m(){while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string(){while (~scanf("%s",S)) TaskA();}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_T();
}
/*

*/
