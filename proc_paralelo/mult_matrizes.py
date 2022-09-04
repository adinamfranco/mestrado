def multmatrizes(matA, matB):
    LsizeA = len(matA)
    CsizeA = len(matA[0])
    CsizeB = len(matB[0])
    resMat = []
    for i in range(LsizeA):
        resMat.append([])
        for j in range(CsizeB):
            val = 0
            for k in range(CsizeA):
                val =+ matA[i][k]*matB[k][j]
            resMat[i].append(val)
    print(resMat)
    

a = [[2, 3], [4, 6]]
b = [[1, 3, 0], [2, 1, 1]]

multmatrizes(a, b)