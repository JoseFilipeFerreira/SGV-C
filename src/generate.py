with open("db/ClientesAll.txt", "w") as f:
    buf = ""
    for l in range(0,27):
        for n in range(1, 10000):
            buf += (chr(65 + l) + str(n) + "\n")
    f.write(buf)

with open("db/ProdutosAll.txt", "w") as f:
    buf = ""
    for l1 in range(0,27):
        for l2 in range(0,27):
            for n in range(1, 10000):
                buf += (chr(65 + l1) + chr(65 + l2) + str(n) + "\n")
    f.write(buf)

#VERY DANGEROUS
#generates a file with 67 MILION PETABYTES

#with open("db/VendasAll.txt", "w") as f:
#    for l1 in range(0,27):
#        for l2 in range(0,27):
#            for n in range(1000, 5001):
#                cli = chr(65 + l1) + chr(65 + l2) + str(n)
#                for l in range(0,27):
#                    for n in range(1000, 10000):
#                        prod = chr(65 + l) + str(n)
#                        for val in range(0, 99999):
#                            for number in range(0, 200):
#                                for r in ["N", "P"]:
#                                    for mes in range(1, 13):
#                                        for fil in range(1,4):
#                                            f.write(prod + " " + str(val/10) + " " + str(number) + " " + r + " " + cli + " " + str(mes) + " " + str(fil) + "\n")
