key = input("> ")

length = len(key)

assert length & 1 == 0


for i in range(length >> 1):
    print(f"0x{key[2*i: 2*i+2]}, ", end="")

print()
print()