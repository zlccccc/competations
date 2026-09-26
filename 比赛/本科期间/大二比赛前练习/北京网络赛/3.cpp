#include <cstdio>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef unsigned long long LL;
const int INF=2100000000;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

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

int aa;
char ch;

int F() {
    while (ch = getchar(), ch < '0' || ch > '9');
    aa = ch - '0';
    while (ch = getchar(), ch >= '0' && ch <= '9')aa = aa * 10 + ch - '0';
    return aa;
}


int a[307][307];
int SUM[307][307],MIN[307][307][307];
int n,m,P;
int i,j;
int SUM1[307],SUM2[307];
int ans;
int now,noww;bool mark;
int main(){
	while (fastIO::RI(n)){
		fastIO::RI(m);fastIO::RI(P);
		FOR(i,1,n)
			FOR(j,1,m) fastIO::RI(a[i][j]);//.....
		int x1,x2,y;
		FOR(x1,1,n)
			FOR(y,1,m) SUM[y][x1]=SUM[y][x1-1]+a[x1][y];
		FOR(y,1,m){
			FOR(x1,1,n){
				MIN[y][x1][x1]=a[x1][y];
				FOR(x2,x1+1,n){
					if (MIN[y][x1][x2-1]<a[x2][y]) MIN[y][x1][x2]=MIN[y][x1][x2-1];
					else MIN[y][x1][x2]=a[x2][y];
				}
			}
		}
//	FOR(y,1,m)
//		FOR(x1,1,n)
//			FOR(x2,x1,n) printf("%d, %d->%d MIN=%d\n",y,x1,x2,MIN[y][x1][x2]);
		ans=-INF;
		FOR(x1,1,n){
			FOR(x2,x1,n){
				now=0;mark=0;
				SUM2[m+1]=0;
				rFOR(y,1,m) {SUM2[y]=SUM2[y+1]+SUM[y][x2]-SUM[y][x1-1];if (SUM2[y]<0) SUM2[y]=0;}
				FOR(y,1,m){
					if (x1==1&&x2==n&&!mark&&y==m){
						if (m!=1){
							now-=SUM[1][x2]-SUM[1][x1-1];
							noww=now+SUM[y][x2]-SUM[y][x1-1];
							if (ans<noww) ans=noww;
						}
					}else{
						noww=now+SUM[y][x2]-SUM[y][x1-1];
						if (ans<noww) ans=noww;
//						printf("%d %d %d  :sum: noww=%d;now=%d,ADD=%d\n",x1,x2,y,noww,now,SUM[y][x2]-SUM[y][x1-1]);
						if (noww<0) now=0,mark=1;
						else now=noww;
					}
					SUM1[y]=SUM1[y-1]+SUM[y][x2]-SUM[y][x1-1];if (SUM1[y]<0) SUM1[y]=0;
					noww=SUM1[y-1]+SUM2[y+1]+SUM[y][x2]-SUM[y][x1-1]-MIN[y][x1][x2]+P;
//					printf("%d %d %d ::sum1::noww=%d\n",x1,x2,y,noww);
					if (ans<noww) ans=noww;
				}
			}
		}
		printf("%d\n",ans);
	}
}
/*
*/
