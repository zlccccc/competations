isprime = [1 for i in range(501)]
for i in range(2, 501):
    if not isprime[i]:
        continue
    # print(i)
    for j in range(2, 500//i+1):
        isprime[j * i] = 0
T = int(input())
for _ in range(T):
    n, k = list(map(int, input().split()))
    # print(n, k)
    ans = k
    for i in range(2, n//k+1):
        if not isprime[i]:
            continue
        ans *= i
    print(ans)


'''
3
10 1
10 4
10 7
'''