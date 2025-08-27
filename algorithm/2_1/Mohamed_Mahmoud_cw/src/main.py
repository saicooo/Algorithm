import time
import random

class HashTableDoubleHashing:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size
        self.keys = [None] * size
        self.collisions = 0

    def hash1(self, key):
        return key % self.size

    def hash2(self, key):
        return 1 + (key % (self.size - 1))

    def insert(self, key, value):
        index = self.hash1(key)
        if self.table[index] is None:
            self.table[index] = value
            self.keys[index] = key
        else:
            self.collisions += 1
            i = 0
            while self.table[index] is not None:
                i += 1
                index = (self.hash1(key) + i * self.hash2(key)) % self.size
            self.table[index] = value
            self.keys[index] = key

    def search(self, key):
        index = self.hash1(key)
        i = 0
        while self.keys[index] != key:
            i += 1
            index = (self.hash1(key) + i * self.hash2(key)) % self.size
            if i > self.size:  # Защита от бесконечного цикла
                return None
        return self.table[index]

    def delete(self, key):
        index = self.hash1(key)
        i = 0
        while self.keys[index] != key:
            i += 1
            index = (self.hash1(key) + i * self.hash2(key)) % self.size
            if i > self.size:
                return
        self.table[index] = None
        self.keys[index] = None

class HashTableChaining:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]
        self.collisions = 0

    def hash(self, key):
        return key % self.size

    def insert(self, key, value):
        index = self.hash(key)
        for pair in self.table[index]:
            if pair[0] == key:
                pair[1] = value
                return
        if self.table[index]:
            self.collisions += 1
        self.table[index].append([key, value])

    def search(self, key):
        index = self.hash(key)
        for pair in self.table[index]:
            if pair[0] == key:
                return pair[1]
        return None

    def delete(self, key):
        index = self.hash(key)
        for pair in self.table[index]:
            if pair[0] == key:
                self.table[index].remove(pair)
                return

# Пример генерации данных
def generate_random_data(size, max_value):
    return [random.randint(0, max_value) for _ in range(size)]

# Пример исследования
def run_experiment():
    size = 100
    max_value = 1000
    data = generate_random_data(70, max_value)

    # Создаем таблицы
    dh_table = HashTableDoubleHashing(size)
    chaining_table = HashTableChaining(size)

    # Измеряем время и коллизии
    start = time.time()
    for key in data:
        dh_table.insert(key, key * 2)
    dh_time = time.time() - start

    start = time.time()
    for key in data:
        chaining_table.insert(key, key * 2)
    chaining_time = time.time() - start

    print("Double Hashing Time:", dh_time, "Collisions:", dh_table.collisions)
    print("Chaining Time:", chaining_time, "Collisions:", chaining_table.collisions)

run_experiment()


