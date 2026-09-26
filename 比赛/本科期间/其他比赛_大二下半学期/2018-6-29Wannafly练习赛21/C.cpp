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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int p[maxn],cntp;
map<int,int> MAX,SUM;
int TaskA(){
    int n,i,j;
    scanf("%d",&n);
    MAX.clear();SUM.clear();
    while(n--){
        int A;
        scanf("%d",&A);
        for(i=1;i<=cntp&&p[i]*p[i]<=A;i++) if (A%p[i]==0){
            int mask=0;
            while (A%p[i]==0) A/=p[i],mask++;
            MAX[p[i]]=max(MAX[p[i]],mask),SUM[p[i]]+=mask;
        }MAX[A]=max(MAX[A],1);SUM[A]++;
    }
    LL ans=1;
    for (auto now:MAX) {
        int T=now.first;
        ans=ans*powMM(T,max(MAX[T]*2-SUM[T],SUM[T]%2))%M;
    }
    printf("%lld\n",ans);
    return 0;
}
bool mark[maxn];
void initialize(){
    int i,j;
    FOR(i,2,100000){
        if (!p[i]) p[++cntp]=i;
        for (j=i+i;j<=100000;j+=i) p[j]=1;
    }
//    FOR(i,1,cntp) printf("%d ",p[i]);puts("");
//    debug("%d",cntp);
}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
