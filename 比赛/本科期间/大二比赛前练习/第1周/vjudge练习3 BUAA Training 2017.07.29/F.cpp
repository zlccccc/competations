#include <cstdio>
int A[101][101];
int main()
{
    int N,M,now;
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        now=1;
        for(int i=0;i<M;i++)
        {
            A[i][1]=now;
            if(i%(N-1)==(N-2))
                now=now%N+1;
        }
        now=1;
        for(int i=0;i<M;i++)
        {
            while(now==A[i][1])
                now=now%N+1;
            A[i][0]=now;
            now=now%N+1;
            if(i%(N-1)==(N-2))
                now=1;
        }
        for(int i=0;i<M;i++)
        {
            now=1;
            for(int j=2;j<N;j++)
            {
                while(now==A[i][0]||now==A[i][1])
                    now=now%N+1;
                A[i][j]=now;
                now=now%N+1;
            }
        }
        for(int i=0;i<M;i++)
        {
            for(int j=0;j<N-1;j++)
                printf("%d ",A[i][j]);
            printf("%d\n",A[i][N-1]);
        }
    }
    return 0;
}
