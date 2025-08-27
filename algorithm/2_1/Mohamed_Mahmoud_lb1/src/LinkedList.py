from Node import Node
from calculate_optimal_node_size import calculate_optimal_node_size

class UnrolledLinkedList:
    def __init__(self, num_elements):
        self.node_size = calculate_optimal_node_size(num_elements)
        self.head = None
        self.tail = None

    #при заполенении ноды разбивать ее на две, заполненные на половину
    def append(self, element):
        if self.head is None:
            self.head = Node()
            self.tail = self.head

        if len(self.tail.data) >= self.node_size:
            new_node = Node()
            self.tail.next = new_node
            self.tail = new_node

        self.tail.add(element)

    def display(self):
        current = self.head
        node_index = 0
        while current:
            print(f"Node {node_index}: {current}")
            current = current.next
            node_index += 1

    def __len__(self):
        length = 0
        current = self.head
        while current:
            length += len(current.data)
            current = current.next
        return length

    def search(self, element):
        current = self.head
        node_index = 0
        element_index = 0
        while current:
            for data in current.data:
                if data == element:
                    return (node_index, element_index)
                element_index += 1
            current = current.next
            node_index += 1
        return None

    def delete(self, element):
        current = self.head
        previous = None
        while current:
            if element in current.data:
                current.data.remove(element)
                if len(current.data) == 0:
                    if previous:
                        previous.next = current.next
                    else:
                        self.head = current.next
                return True
            previous = current
            current = current.next
        return False

    def clear(self):
        self.head = None
        self.tail = None
        
 
    def balance_nodes(self):

        current_node = self.head
        while current_node is not None:
            if len(current_node.data) > self.node_size:
                new_node = Node()
                self.last_node = new_node
                current_node.next = new_node
            if current_node.next is not None:
                while len(current_node.data) > self.node_size / 2:
                    current_node.next.data.insert(0,current_node.data.pop())
                while len(current_node.data) < self.node_size / 2:
                    current_node.data.insert(-1,current_node.next.data.pop(0))
                if len(self.last_node.data) <= self.node_size / 2 and self.last_node != self.head:
                    prev_node = self.head
                    while prev_node.next!=self.last_node:
                        prev_node=prev_node.next
                    prev_node.data[int(self.node_size/2):] = self.last_node.data
                    prev_node.next = None
                    self.last_node = prev_node
            current_node = current_node.next
            
            #возможно last_node будет не инициализирована