from LinkedList import UnrolledLinkedList
import math
class Node:
    def init(self, size):
        self.elements = []
        self.next = None
        self.size = size



def calculate_optimal_node_size(num_elements):
    # Размер int в байтах
    size_of_int = 4
    
    # Общий объем памяти в байтах
    total_memory = num_elements * size_of_int
    
    # Минимальный размер строки кэша в байтах
    cache_line_size = 64
    
    # Количество строк кэша с округлением вверх
    cache_lines_needed = math.ceil(total_memory / cache_line_size)
    
    # Оптимальное количество строк с добавлением одной строки кэша
    optimal_cache_lines = cache_lines_needed + 1
    
    return optimal_cache_lines




# Пример использования
elements = input().split(" ")
num_elements = len(elements)

ull = UnrolledLinkedList(num_elements)

for elem in elements:
    ull.append(elem)

ull.display()



def check(arr_1, arr_2, n_array=16):
    ull = UnrolledLinkedList(num_elements =n_array)
    
    # Insert elements from arr_1
    for value in arr_1:
        ull.append(value)
        ull.display()
    
    # Delete elements from arr_2
    for value in arr_2:
        ull.delete(value)
        ull.display()
       


# # Test the unrolled linked list
# arr_1 = [i for i in range(1, 21)]  # Elements to insert
# arr_2 = [5, 10, 15]  # Elements to delete
# check(arr_1, arr_2)