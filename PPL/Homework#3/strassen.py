import numpy as np


def mul_matrix(first_matrix, second_matrix):
    size = int(len(first_matrix[0]))

    if size == 1:
        return first_matrix * second_matrix

    middle = size // 2

    a_1_1 = first_matrix[:middle, :middle]
    a_1_2 = first_matrix[:middle, middle:]
    a_2_1 = first_matrix[middle:, :middle]
    a_2_2 = first_matrix[middle:, middle:]

    b_1_1 = second_matrix[:middle, :middle]
    b_1_2 = second_matrix[:middle, middle:]
    b_2_1 = second_matrix[middle:, :middle]
    b_2_2 = second_matrix[middle:, middle:]

    p_1 = mul_matrix(a_1_1 + a_2_2, b_1_1 + b_2_2)
    p_2 = mul_matrix(a_2_1 + a_2_2, b_1_1)
    p_3 = mul_matrix(a_1_1, b_1_2 - b_2_2)
    p_4 = mul_matrix(a_2_2, b_2_1 - b_1_1)
    p_5 = mul_matrix(a_1_1 + a_1_2, b_2_2)
    p_6 = mul_matrix(a_2_1 - a_1_1, b_1_1 + b_1_2)
    p_7 = mul_matrix(a_1_2 - a_2_2, b_2_1 + b_2_2)

    c_1_1 = p_1 + p_4 - p_5 + p_7
    c_1_2 = p_3 + p_5
    c_2_1 = p_2 + p_4
    c_2_2 = p_1 - p_2 + p_3 + p_6

    return_matrix = np.empty([size, size], dtype=np.int)
    return_matrix[:middle, :middle] = c_1_1
    return_matrix[:middle, middle:] = c_1_2
    return_matrix[middle:, :middle] = c_2_1
    return_matrix[middle:, middle:] = c_2_2

    return return_matrix


def input_matrix(input_size_of_matrix):
    degree = np.ceil(np.log2(input_size_of_matrix))
    size_of_matrix = 2 ** degree

    matrix = np.zeros(shape=(size_of_matrix, size_of_matrix), dtype=np.int)
    for i in range(input_size_of_matrix):
        matrix[i][:input_size_of_matrix] = input().split(' ')

    return matrix


def print_matrix(matrix, size):
    for line in matrix[:size]:
        for elem in line[:size]:
            print(elem, end=' ')
        print()


def main():
    size_of_matrix = int(input())

    first_matrix = input_matrix(size_of_matrix)
    second_matrix = input_matrix(size_of_matrix)

    res_matrix = mul_matrix(first_matrix, second_matrix)

    print_matrix(res_matrix, size_of_matrix)

if __name__ == "__main__":
    main()
