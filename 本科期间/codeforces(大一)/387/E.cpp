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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=4e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a; }
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

void read(int &x,char *buf){
    for(x=0;(*buf<'0'||*buf>'9')&&*buf!='-';++buf);
    int flag=0;if (*buf=='-') flag=1,buf++;
    while('0'<=*buf&&*buf<='9')x=x*10+*buf-48,++buf;
    if (flag) x=-x;
}
char A[maxn];
vector<char> ans[maxn];
int cnt[maxn],nowdep,maxdep;
int main() {
    int n,m,i,j;
    scanf("%s",A);
    int len=strlen(A);
    cnt[0]=INF;nowdep=maxdep=1;i=0;
    while(i<len){
        while (A[i]!=','&&A[i]!='\0')
            ans[nowdep].push_back(A[i++]);
        ans[nowdep].push_back(' ');
        if (A[i]=='\0') break;
        cnt[nowdep-1]--;
        while (!('0'<=A[i]&&A[i]<='9')) i++;
        read(cnt[nowdep],A+i);nowdep++;
        while (!cnt[nowdep-1]) nowdep--;
        maxdep=max(maxdep,nowdep);
        while (A[i]!=','&&A[i]!='\0') i++;i++;
        if (A[i]=='\0') break;
//        printf("(%-2d) %s\n",nowdep,A+i);
    }printf("%d\n",maxdep);
    FOR(i,1,maxdep){
        for (char c:ans[i]) putchar(c);
        puts("");
    }
    return 0;
}
/*
8 8
1 3 5 7 9 11 13 15
*/
