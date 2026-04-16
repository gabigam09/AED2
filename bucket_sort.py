def bucket_sort(A):
    n = len(A)
    # 1. Cria n baldes vazios
    baldes = [[] for _ in range(n)]

    # 2. Coloca os elementos nos baldes
    # Mapeamento: valor * número_de_baldes
    for valor in A:
        indice_balde = int(n * valor)
        baldes[indice_balde].append(valor)

    # 3. Ordena cada balde individualmente
    for i in range(n):
        baldes[i].sort()

    # 4. Concatena os baldes no array de saída
    B = []
    for balde in baldes:
        B.extend(balde)
    
    return B

# Teste
arr_float = [0.78, 0.17, 0.39, 0.26, 0.72]
print(f"Bucket Sort: {bucket_sort(arr_float)}")
