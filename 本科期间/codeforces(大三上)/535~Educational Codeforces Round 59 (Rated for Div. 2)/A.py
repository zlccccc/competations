T = int(input())
for _ in range(T):
    n = int(input())
    A = str(input())
    if (len(A) == 2 and A[0] >= A[1]):
        print('NO')
    else :
        print('YES')
        print(2)
        print(A[0],A[1:])
