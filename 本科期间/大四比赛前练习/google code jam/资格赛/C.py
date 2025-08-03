def gcd(A, B):
    if B == 0:
        return A
    return gcd(B, A % B)


T = int(input())
for _ in range(T):
    n, L = map(int, input().split(' '))
    A = [int(x) for x in input().split()]
    B = [0] * L
    # print(B)
    print('Case #%d: ' % (_ + 1), end='')
    for i in range(L - 1):
        if A[i] != A[i + 1]:
            B[i] = gcd(A[i], A[i + 1])
            for i in range(i - 1, -1, -1):
                B[i] = A[i] // B[i + 1]
            for i in range(i + 1, L, 1):
                B[i] = A[i] // B[i - 1]
            break

    S = set()
    B = [A[0] // B[0]] + B
    # print(B)
    for i in B:
        S.add(i)
    S = sorted(list(S))
    # print('S=',S)
    for i in range(len(B)):
        B[i] = S.index(B[i])
    for i in range(len(B)):
        print(chr(B[i] + ord('A')), end='')
    print()
