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
const LL maxn=5e5+7;
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

int nxt[maxn][27],pre[maxn],tot;
LL cnt[maxn],all[maxn];
vector<int> ids[maxn];
void Ins(char A[],int len,int k){
    int i,now=0;
    REP(i,len){
        int c=A[i]-'a';
        if (!nxt[now][c]) {
            nxt[now][c]=++tot;
            pre[tot]=now;
//            printf("pre-%d=%d\n",tot,now);
        }now=nxt[now][c];
        all[now]+=k;
    }cnt[now]+=k;
}
int getid(char A[],int len){
    int i,now=0;
    REP(i,len){
        int c=A[i]-'a';
        now=nxt[now][c];
        if (!now||!all[now]) return 0;
    }return now;
}
int n;
char op[20];
char A[maxn];
int main() {
    int i,j,T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        REP(i,n){
            scanf("%s",op);
            if (op[0]=='i'){
                int k;
                scanf("%s%d",A,&k);
                int len=strlen(A);
                reverse(A,A+len);
                Ins(A,len,k);
            }if (op[0]=='d'){
                scanf("%s",A);
                int len=strlen(A);
                reverse(A,A+len);
                int pos=getid(A,len);
                if (pos==0||!cnt[pos]) puts("Empty");
                else {
                    for (int now=pos;now;now=pre[now]){
                        all[now]-=cnt[pos];
//                        printf("pre[%d]=%d ",now,pre[now]);
//                        printf("%d\n",now);
                    }cnt[pos]=0;
                }
            }if (op[0]=='q'){
                scanf("%s",A);
                int len=strlen(A);
                reverse(A,A+len);
                int pos=getid(A,len);
                if (pos==0) puts("0");
                else printf("%lld\n",all[pos]);
            }
        }FOR(i,0,tot){
            cnt[i]=all[i]=0;pre[i]=0;
            REP(j,26) nxt[i][j]=0;
        }
    }
}
/*
8
100
insert barty 8
query ty
insert barty 8
query ty
insert party 9
query ty
delete barty
query ty
q barty
q y
1
q y
*/
