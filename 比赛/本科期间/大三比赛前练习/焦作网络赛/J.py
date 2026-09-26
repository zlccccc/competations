C = int(raw_input())
for i in range(0, C):
	n = int(raw_input())
	if n == 1 :
		print 'Arena of Valor'
		continue
	if n == 2:
		print 'Clash Royale'
		continue
	m = 2
	tmpn, len = n, 0
	while tmpn > 0:
		tmpn /= 10
		len += 1
	base, digit, cur = 300, len / m, len % m
	while (cur + m <= base) and (digit > 0):
		cur += m
		digit -= 1
	div = 10 ** (digit * m)
	tmpn = n / div
	x = int(float(tmpn) ** (1.0 / m))
	x *= (10 ** digit)
	while True:
		x0 = x
		x = x + x * (n - x ** m) / (n * m)
		if x == x0: break
	while (x + 1) ** m <= n:
		x = x + 1
	okay1 = 0
	if (x ** m == n):okay1 = 1
	#print 'x = %d , n = %d okay1=%d' %(x,n,okay1)

	n = n*(n-1)/2
	tmpn, len = n, 0
	while tmpn > 0:
		tmpn /= 10
		len += 1
	base, digit, cur = 300, len / m, len % m
	while (cur + m <= base) and (digit > 0):
		cur += m
		digit -= 1
	div = 10 ** (digit * m)
	tmpn = n / div
	x = int(float(tmpn) ** (1.0 / m))
	x *= (10 ** digit)
	while True:
		x0 = x
		x = x + x * (n - x ** m) / (n * m)
		if x == x0: break
	while (x + 1) ** m <= n:
		x = x + 1
	okay2 = 0
	if (x ** m == n): okay2 = 1
	if (okay1==1) and (okay2==1):
		print 'Arena of Valor'
		continue
	if (okay1==1):
		print 'Hearth Stone'
		continue
	if (okay2==1):
		print 'Clash Royale'
		continue
	print 'League of Legends'
	