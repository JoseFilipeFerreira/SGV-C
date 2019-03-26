with open("db/ClientesAll.txt", "w") as f:
    for l in range(1,26):
        for n in range(1000, 5001):
            f.write(chr(65 + l) + str(n) + "\n")

with open("db/ProdutosAll.txt", "w") as f:
    for l1 in range(1,26):
        for l2 in range(1,26):
            for n in range(1000, 10000):
                f.write(chr(65 + l1) + chr(65 + l2) + str(n) + "\n")