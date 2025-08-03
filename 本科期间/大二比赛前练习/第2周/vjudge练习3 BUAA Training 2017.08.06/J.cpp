#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
double mat[1001][1001];
int u[40001],v[40001];
int father[10001];
int id[10001];
#define eps 1e-8
int findfather(int x)
{
    if(x==father[x])
        return x;
    else return father[x]=findfather(father[x]);
}
void Gauss(int n)
{
    int i,j,k,col,maxr;
    for(k=0,col=0;k<n&&col<n;k++,col++)
    {
        maxr=k;
        for(i=k+1;i<n;i++)
            if(fabs(mat[i][col])>fabs(mat[maxr][col]))
                maxr=i;
        if(k!=maxr)
            for(j=col;j<=n;j++)
                swap(mat[k][j],mat[maxr][j]);
        for(j=col+1;j<=n;j++)
            mat[k][j]/=mat[k][col];
        mat[k][col]=1;
        for(i=0;i<n;i++)
            if(i!=k)
            {
                if(fabs(mat[i][k])<eps)
                    continue;
                for(j=col+1;j<=n;j++)
                    mat[i][j]-=mat[k][j]*mat[i][col];
                mat[i][col]=0;
            }
    }
    return;
}
int main()
{
    int kase,N,M,S,T,c,cnt;
    scanf("%d",&kase);
    while(kase--)
    {
        scanf("%d%d%d%d",&N,&M,&S,&T);
        for(int i=1;i<=N;i++)
            father[i]=i;
        for(int i=0;i<M;i++)
        {
            scanf("%d%d%d",&u[i],&v[i],&c);
            if(c==0)
            {
                father[findfather(v[i])]=findfather(u[i]);
                i--;
                M--;
            }
        }
        if(findfather(S)==findfather(T))
        {
            printf("0.000000\n");
            continue;
        }
        cnt=0;
        for(int i=1;i<=N;i++)
            if(i==findfather(i))
                id[i]=cnt++;
        for(int i=1;i<=N;i++)
            id[i]=id[findfather(i)];
        for(int i=0;i<M;i++)
            father[findfather(id[v[i]])]=findfather(id[u[i]]);
        if(findfather(id[S])!=findfather(id[T]))
        {
            printf("inf\n");
            continue;
        }
        for(int i=0;i<M;i++)
        {
            mat[id[u[i]]][id[u[i]]]++;
            mat[id[u[i]]][id[v[i]]]--;
            mat[id[v[i]]][id[u[i]]]--;
            mat[id[v[i]]][id[v[i]]]++;
        }
        mat[id[S]][cnt]=1;
        mat[id[T]][cnt]=-1;
        mat[0][id[S]]++;
        Gauss(cnt);
        printf("%lf\n",mat[id[S]][cnt]-mat[id[T]][cnt]+eps);
        for(int i=0;i<cnt;i++)
            for(int j=0;j<=cnt;j++)
                mat[i][j]=0;
    }
    return 0;
}
