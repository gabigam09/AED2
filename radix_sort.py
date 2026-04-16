def counting_sort_para_radix(A, exp):
    n = len(A)
    B = [0] * n
    C = [0] * 10  # Base decimal (0 a 9)

    # 1. Conta as ocorrências do dígito específico (A[i] // exp) % 10
    for i in range(n):
        indice = (A[i] // exp) % 10
        C[indice] += 1

    # 2. Soma de prefixo
    for i in range(1, 10):
        C[i] += C[i - 1]

    # 3. Constrói o array de saída (estabilidade é vital!)
    for i in range(n - 1, -1, -1):
        indice = (A[i] // exp) % 10
        B[C[indice] - 1] = A[i]
        C[indice] -= 1

    # 4. Copia de volta para o array original
    for i in range(n):
        A[i] = B[i]

def radix_sort(A):
    # Encontra o valor máximo para saber o número de dígitos
    max_val = max(A)
    
    # Executa o counting sort para cada dígito (unidade, dezena, centena...)
    exp = 1
    while max_val // exp > 0:
        counting_sort_para_radix(A, exp)
        exp *= 10
    return A

# Teste
arr = [329, 457, 657, 839, 436]
print(f"Radix Sort: {radix_sort(arr)}")
