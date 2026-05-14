from fractions import Fraction

n, x = map(int, input().split())
b = list(map(int, input().split()))
b.sort(reverse = True)

total = 0
for i in range(n): 
    total += b[i] // (i + 1)
    b[i] %= (i + 1)

if total >= x: 
    print("YES")
    exit(0)

x -= total
totald = Fraction(0, 1)

for i in range(n): 
    totald += Fraction(int(b[i]), int(i + 1))

if totald >= Fraction(x, 1): 
    print("YES") 
else: 
    print("NO")

