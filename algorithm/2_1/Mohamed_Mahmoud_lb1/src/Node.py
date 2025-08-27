class Node:
    def __init__(self, n=None):
        self.data = []
        self.next = n

    def __len__(self):
        return len(self.data)

    def __str__(self):
        return ' '.join(map(str, self.data))

    def add(self, data):
        self.data.append(data)