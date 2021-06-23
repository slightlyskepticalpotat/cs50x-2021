n = -1
while not 1 <= n <= 8:
    try:
        n = int(input("Height: "))
    except:
        pass

# Draw the blocks
for i in range(1, n + 1):
    print(" " * (n - i) + "#" * i + "  " + "#" * i)