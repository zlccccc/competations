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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=19260817;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

namespace fastIO {
#define BUF_SIZE 100000
#define OUT_SIZE 1000000
    bool IOerror = 0;

    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if (p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if (pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }

    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }

    inline int read(char *s) {
        char ch = nc();
        for (; blank(ch); ch = nc());
        if (IOerror)
            return 0;
        for (; !blank(ch) && !IOerror; ch = nc())
            *s++ = ch;
        *s = 0;
        return 1;
    }

    inline int RI(int &a) {
        char ch = nc();

        a = 0;
        for (; blank(ch); ch = nc());
        if (IOerror)
            return 0;
        int flag;
        if (ch == '-') {
            flag = -1;
            ch = nc();
        } else { flag = 1; }
        for (; !blank(ch) && !IOerror; ch = nc())
            a = a * 10 + ch - '0';
        a = a * flag;
        return 1;
    }

    struct Ostream_fwrite {
        char *buf, *p1, *pend;

        Ostream_fwrite() {
            buf = new char[BUF_SIZE];
            p1 = buf;
            pend = buf + BUF_SIZE;
        }

        void out(char ch) {
            if (p1 == pend) {
                fwrite(buf, 1, BUF_SIZE, stdout);
                p1 = buf;
            }
            *p1++ = ch;
        }

        void flush() {
            if (p1 != buf) {
                fwrite(buf, 1, p1 - buf, stdout);
                p1 = buf;
            }
        }

        ~Ostream_fwrite() { flush(); }
    } Ostream;

    inline void print(char x) { Ostream.out(x); }

    inline void println() { Ostream.out('\n'); }

    inline void flush() { Ostream.flush(); }

    char Out[OUT_SIZE], *o = Out;

    inline void print1(char c) { *o++ = c; }

    inline void println1() { *o++ = '\n'; }

    inline void flush1() {
        if (o != Out) {
            if (*(o - 1) == '\n')
                *--o = 0;
            puts(Out);
        }
    }

    struct puts_write {
        ~puts_write() { flush1(); }
    } _puts;
};
int n,m;
int i,j,k,t;
vector<int> edge[maxn];
vector<int> Q;
int fa[maxn];//BFSÐò
LL val[maxn],subval[maxn],cnt[maxn],sub[maxn];
int tot=0;
int ans;LL now;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,2,n) scanf("%d",&fa[i]),sub[fa[i]]++;
	FOR(i,1,m){
		int x;
		fastIO::RI(x);
		subval[fa[fa[x]]]++;//sub of sub
		val[fa[x]]++;//sub
		cnt[x]++;
		now=subval[x]+val[x]*2+cnt[x]*(sub[x]+1);//this.sub
//		printf("  %d\n",now);
		if (fa[x]) now+=cnt[fa[x]]*2+val[fa[x]];//this.pre
		if (fa[fa[x]]) now+=cnt[fa[fa[x]]];
//		printf("%d\n",now);
		ans+=now%M*i%M;
		while (ans>M) ans-=M;
	}printf("%d\n",ans);
}
/*
6 3
1 1 2 3 3
1 2 3
*/
