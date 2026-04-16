def counting_sort(A, k):
    """
    Implementação do Counting Sort seguindo o CLRS.
    A: Array de entrada
    k: Valor máximo esperado no array
    """
    n = len(A)
    # 1. Cria o array de saída B e o array de contagem C
    B = [0] * n
    C = [0] * (k + 1)

    # 2. Contagem das frequências
    for x in A:
        C[x] += 1
    
    # 3. Soma de Prefixo (Acumulado)
    # C[i] agora contém a quantidade de elementos menores ou iguais a i
    for i in range(1, k + 1):
        C[i] = C[i] + C[i-1]
    
    # 4. Construção do array de saída B
    # Percorremos de trás para frente para garantir ESTABILIDADE
    for j in range(n - 1, -1, -1):
        valor = A[j]
        posicao = C[valor] - 1  # -1 porque Python usa índices de 0 a n-1
        B[posicao] = valor
        C[valor] -= 1
        
    return B

# Exemplo de uso:
array_original = [4, 1, 3, 1, 2]
valor_maximo = 4

array_ordenado = counting_sort(array_original, valor_maximo)

print(f"Original: {array_original}")
print(f"Ordenado: {array_ordenado}")
