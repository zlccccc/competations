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
const LL maxn=1e6+7;
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

char A[maxn];
map<int,int> pre,now,all;
int main() {
    freopen("jingles.in","r",stdin);
    freopen("jingles.out","w",stdout);
    int T,i;
    while (~scanf("%d",&T)){
        while (T--){
            scanf("%s",A);
            int len=strlen(A);
            now.clear();pre.clear();all.clear();
            REP(i,len){
                pre[0]=i;
                for (auto x:pre){
                    int sta=x.first|(1<<(A[i]-'a'));
                    if (!now.count(sta)||now[sta]>x.second)
                        now[sta]=x.second;
                }for (auto x:now){
//                    printf("%d[%d] ",x.first,x.second);
                    all[x.first]=max(all[x.first],i-x.second+1);
                }
//                puts("");
                pre.swap(now);now.clear();
            }
//            for (auto x:all) printf("%d: %d\n",x.first,x.second);
            LL ans=0;
            for (auto x:all){
                int sta=x.first,len=x.second,cnt=0;
                while (sta) cnt+=(sta&1),sta>>=1;
                ans+=(LL)cnt*len;
            }
            printf("%d %I64d\n",(int)all.size(),ans);
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
/*
*/
