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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
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

typedef vector<int> bigNumber;
void printBigNumber(bigNumber A){
    int i;rREP(i,A.size()) debug("%03d",A[i]);deputs("");
}
struct Complex{
    double a,b;
    Complex(double _a=.0,double _b=.0):a(_a),b(_b){}
    Complex operator+(const Complex x)const{return Complex(a+x.a,b+x.b);}
    Complex operator-(const Complex x)const{return Complex(a-x.a,b-x.b);}
    Complex operator*(const Complex x)const{return Complex(a*x.a-b*x.b,a*x.b+b*x.a);}
};
Complex w[maxn];
void init_wn(int len,int inv){
    int i;
    REP(i,len/2) w[i]=Complex(cos(-inv*2*pi*i/len),sin(-inv*2*pi*i/len));
}
void fft(Complex *A,int len,int inv){
    int i,j,k;
    for (i=1,j=len/2;i<len-1;i++){
        if (i<j) swap(A[i],A[j]);
        k=len/2;
        while (j>=k) j-=k,k/=2;
        if (j<k) j+=k;
    }for (i=2;i<=len;i<<=1){
        for (j=0;j<len;j+=i){
            for (k=j;k<(j+i/2);k++){
                Complex a=A[k],b=w[len/i*(k-j)]*A[k+i/2];
                A[k]=a+b; A[k+i/2]=a-b;
            }
        }
    }if (inv==-1) REP(i,len) A[i].a/=len;
}
Complex x1[maxn],x2[maxn];
LL ans[maxn];
void MUL(bigNumber &A,bigNumber &B){
    int len=1,i;
    while (len<=(int)(A.size()+B.size())) len<<=1;
    REP(i,(int)A.size()) x1[i]=Complex(A[i]);
    rep(i,(int)A.size(),len) x1[i]=Complex();
    REP(i,(int)B.size()) x2[i]=Complex(B[i]);
    rep(i,(int)B.size(),len) x2[i]=Complex();
    init_wn(len,1); fft(x1,len,1);fft(x2,len,1);
    REP(i,len) x1[i]=x1[i]*x2[i];
    init_wn(len,-1);fft(x1,len,-1);
    REP(i,len) ans[i]=x1[i].a+0.5;
    REP(i,len) ans[i+1]+=ans[i]/1000,ans[i]%=1000;
    while (ans[len-1]<=0&&len-1>0) len--;
    A.resize(len);
    REP(i,len) A[i]=ans[i];
}
void MUL(bigNumber &A,int B){
    int i;
    for (auto &now:A) now*=B;
    REP(i,(int)A.size()){
        if (A[i]>=1000){
            if (i==(int)A.size()-1) A.push_back(0);
            A[i+1]+=A[i]/1000; A[i]%=1000;
        }
    }
}
bool lessthan(bigNumber &A,bigNumber &B){
    int i;
    if (A.size()!=B.size()) return A.size()<B.size();
    rREP(i,A.size()) if (A[i]!=B[i]) return A[i]<B[i];
    return 0;
}
bigNumber pow3,top;
char A[maxn];
int TaskA() {
	int i;
	scanf("%s",A);
    int len=strlen(A);
    if (len==1&&A[0]=='1') return 0*puts("1");
    top.resize((len-1)/3+1); reverse(A,A+len);
    for (auto &now:top) now=0;
    rREP(i,len) top[i/3]=top[i/3]*10+A[i]-'0';
    int num=(len-1)*(log(10)/log(3))-2;
    num=max(num,0); pow3.resize(1);pow3[0]=1;
    rREP(i,30) {
        MUL(pow3,pow3);
        if ((num>>i)&1) MUL(pow3,3);
    }int ans=INF;
    deputs("top:");printBigNumber(top);
    deputs("pow3:");printBigNumber(pow3);
    printBigNumber(pow3);
    while (lessthan(pow3,top)){
        int now=num*3;bigNumber nowNum=pow3;
        for (;lessthan(nowNum,top);MUL(nowNum,2),now+=2);
        ans=min(ans,now); MUL(pow3,3); num++;
        debug("%d : %d\n",num,now);
        printBigNumber(nowNum);
    }ans=min(ans,num*3);
    return 0*printf("%d\n",ans);
}
int main() {
	int startTime=clock();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*

*/
