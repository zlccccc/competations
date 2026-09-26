#include<bits/stdc++.h>
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
using namespace std;
const int maxn=4e6+7;

typedef long long ll;
//2^16
void print4(int x){
    for (int i=0;i<4;i++) printf("%d",(x>>i)&1); puts("");
    for (int i=4;i<8;i++) printf("%d",(x>>i)&1); puts("");
    for (int i=8;i<12;i++) printf("%d",(x>>i)&1); puts("");
    for (int i=12;i<16;i++) printf("%d",(x>>i)&1); putchar(' ');
}
map<int,int> Blocks;
void initBlocks(){
    vector<int> One;
    One.push_back((1<<0)|(1<<4)|(1<<8)|(1<<12));//1
    One.push_back((1<<0)|(1<<1)|(1<<2)|(1<<3));

    One.push_back((1<<0)|(1<<1)|(1<<2)|(1<<6));//2
    One.push_back((1<<1)|(1<<5)|(1<<8)|(1<<9));
    One.push_back((1<<0)|(1<<4)|(1<<5)|(1<<6));
    One.push_back((1<<0)|(1<<1)|(1<<4)|(1<<8));

    One.push_back((1<<0)|(1<<1)|(1<<2)|(1<<4));//3
    One.push_back((1<<0)|(1<<1)|(1<<5)|(1<<9));
    One.push_back((1<<2)|(1<<4)|(1<<5)|(1<<6));
    One.push_back((1<<0)|(1<<4)|(1<<8)|(1<<9));

    One.push_back((1<<0)|(1<<1)|(1<<4)|(1<<5));//4

    One.push_back((1<<1)|(1<<2)|(1<<4)|(1<<5));//7
    One.push_back((1<<0)|(1<<4)|(1<<5)|(1<<9));

    One.push_back((1<<1)|(1<<4)|(1<<5)|(1<<9));//6
    One.push_back((1<<1)|(1<<4)|(1<<5)|(1<<6));
    One.push_back((1<<0)|(1<<4)|(1<<5)|(1<<8));
    One.push_back((1<<0)|(1<<1)|(1<<2)|(1<<5));

    One.push_back((1<<1)|(1<<4)|(1<<5)|(1<<8));//5
    One.push_back((1<<0)|(1<<1)|(1<<5)|(1<<6));

    int bottom=(1<<3)|(1<<7)|(1<<11)|(1<<15);
    for (int i=0;i<(int)One.size();i++) {
        int now=One[i];
        if (!(bottom&now)) One.push_back(now<<1);
    }Blocks[0]++;
    for (int i=0;i<(int)One.size();i++) {
        int now=One[i];
        map<int,int> tmp;
        for (auto p:Blocks) {
            tmp[p.first]+=p.second;
            if (!(p.first&now))
                tmp[p.first|now]+=p.second;
        } tmp.swap(Blocks);
    }
//    for (auto p:One) {
//        int x=p; print4(x);
//        printf(" \n\n");
//    }
//    for (auto p:Blocks) {
//        int x=p.first; print4(x);
//        printf(" : %d\n\n",p.second);
//    }
//    printf("%d\n",Blocks.size());
}

struct matrix{
    int A[107][107];
    matrix(){memset(A,0,sizeof(A));}
}ini;

int e[4096][4096];
bool canIn[4096],canOut[4096];
int okay[4096],tot;
vector<int> could;
void initTrans() {
    int status,top=(1<<0)|(1<<1)|(1<<2)|(1<<3);
    REP(status,(1<<12)) {
        for (auto now:Blocks) if (!(now.first&status)){
            int nxtsta=now.first|status;
            if ((nxtsta&top)==top){
                e[status][nxtsta>>4]+=now.second;
//                printf("%x - %x\n",status,nxtsta>>4);
            }
        }
    } queue<int> Q;
    Q.push(0); canIn[0]=1;
    int i;
    while (Q.size()) {
        int x=Q.front(); Q.pop();
        REP(i,4096) if (!canIn[i]&&e[x][i]) {
            canIn[i]=1; Q.push(i);
        }
    }
    Q.push(0); canOut[0]=1;
    while (Q.size()) {
        int x=Q.front(); Q.pop();
        REP(i,4096) if (!canOut[i]&&e[i][x]) {
            canOut[i]=1; Q.push(i);
        }
    }
    REP(i,4096) if (canIn[i]&&canOut[i]) {
        okay[i]=tot++; could.push_back(i);
//        print4(i); puts(""); puts("");
    }
//    printf("tot=%d",tot);
    for (int u:could){
        for (int v:could){
            ini.A[okay[u]][okay[v]]=e[u][v];
        }
    }
}

matrix mul(matrix A,matrix B,int p) {
    matrix ret; int i,j,k;
    REP(k,tot) REP(i,tot) REP(j,tot)
        ret.A[i][j]=(ret.A[i][j]+(ll)A.A[i][k]*B.A[k][j])%p;
    return ret;
}
matrix powMM(matrix a,int b,int p){
    matrix ret; int i;
    REP(i,tot) ret.A[i][i]=1;
    for (;b;a=mul(a,a,p),b>>=1)
        if (b&1) ret=mul(ret,a,p);
    return ret;
}

int main() {
    int i;
    initBlocks();
    initTrans();
    int n,p;
    scanf("%d%d",&n,&p);
    matrix ans=powMM(ini,n,p);
    printf("%d\n",ans.A[0][0]);
    return 0;
}
/*
*/