class StackNode:
    def __init__(self, value):
        self.value = value
        self.next = None

class Stack:
    def __init__(self):
        self.top_node = None

    def push(self, value):
        new_node = StackNode(value)
        new_node.next = self.top_node
        self.top_node = new_node

    def pop(self):
        if self.top_node is not None:
            value = self.top_node.value
            self.top_node = self.top_node.next
            return value
        return None

    def top(self):
        return self.top_node.value if self.top_node is not None else None

    def is_empty(self):
        return self.top_node is None

    def __len__(self):
        length = 0
        current = self.top_node
        while current:
            length += 1
            current = current.next
        return length


undo_command = input().strip()   
num_to_delete = int(input().strip())  
input_string = input().strip()   


stack = Stack()


for char in input_string:
    if char == undo_command:
        
        for _ in range(num_to_delete):
            if not stack.is_empty():
                stack.pop()
    else:
        
        stack.push(char)


result = []
while not stack.is_empty():
    result.append(stack.pop())


print("".join(result[::-1]))
