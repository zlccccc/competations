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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
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

int tot;
int nxt[maxn][26],pre[maxn];
LL sum[maxn],val[maxn],cnt[maxn],nowcnt[maxn],lazy[maxn];
inline void update(int pos,int d){
    lazy[pos]+=d;
    val[pos]+=d*nowcnt[pos];
    sum[pos]+=d*cnt[pos];
}
int getpos(char A[],bool add){
    int len=strlen(A),now=0,i;
    REP(i,len){
        int c=A[i]-'a';
        if (!nxt[now][c]){
            if (add) nxt[now][c]=++tot,pre[tot]=now;
            else return 0;
        }now=nxt[now][c];
        if (lazy[now]){
            int j;
            REP(j,26) if (nxt[now][j])
                update(nxt[now][j],lazy[now]);
            lazy[now]=0;
        }
    }return now;
}
int n;
char A[maxn];
int main() {
    int i,j;
    int T;
    scanf("%d",&n);
    FOR(i,1,n){
        int op,pos;
        scanf("%d%s",&op,A);
        if (op==1) pos=getpos(A,1);
        else pos=getpos(A,0);
//        printf("pos=%d\n",pos);
        if (op==1){
            int a;
            scanf("%d",&a);
            val[pos]+=a;nowcnt[pos]++;
            for (int p=pos;p;p=pre[p])
                cnt[p]++,sum[p]+=a;
        }if (op==2){
            int d;
            scanf("%d",&d);
            if (pos) update(pos,d);
            for (int p=pre[pos];p;p=pre[p])
                sum[p]+=cnt[pos]*d;
        }if (op==3) printf("%lld\n",val[pos]);
        if (op==4) printf("%lld\n",sum[pos]);
//        printf("  op=%d;  \n",op);
//        printf("pos:%d : %lld(sum);%lld(val);%lld(cnt);%lld(thiscnt);%lld(lazy)\n",pos,sum[pos],val[pos],cnt[pos],nowcnt[pos],lazy[pos]);
    }
    return 0;
}
/*
20
1 a -10
1 abcba -9
1 abcbacd 5
4 a
2 a 9
3 aadaa
3 abcbacd
4 a
3 a
2 a 10
3 a
2 a -2
2 d -8
1 ab -2
2 ab -7
1 aadaa -3
4 a
3 abcba
4 a
4 c
*/
