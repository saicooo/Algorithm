from typing import Union
from anytree import Node as AnyTreeNode, RenderTree

class Node:
    def __init__(self, val, left: Union[Node, None] = None, right: Union[Node, None] = None):
        self.val = val
        self.left = left
        self.right = right
        self.height = 1

def get_height(node: Union[Node, None]) -> int:
    if not node:
        return 0
    return node.height

def update_height(node: Node):
    node.height = 1 + max(get_height(node.left), get_height(node.right))

def get_balance(node: Union[Node, None]) -> int:
    if not node:
        return 0
    return get_height(node.left) - get_height(node.right)

def rotate_right(y: Node) -> Node:
    x = y.left
    T2 = x.right
    x.right = y
    y.left = T2
    update_height(y)
    update_height(x)
    return x

def rotate_left(x: Node) -> Node:
    y = x.right
    T2 = y.left
    y.left = x
    x.right = T2
    update_height(x)
    update_height(y)
    return y

def insert(val, node: Union[Node, None]) -> Node:
    if not node:
        return Node(val)
    
    if val < node.val:
        node.left = insert(val, node.left)
    elif val > node.val:
        node.right = insert(val, node.right)
    else:
        # Ignore duplicate values
        return node
    
    update_height(node)
    
    balance = get_balance(node)
    
    if balance > 1 and val < node.left.val:
        return rotate_right(node)
    
    if balance < -1 and val > node.right.val:
        return rotate_left(node)
    
    if balance > 1 and val > node.left.val:
        node.left = rotate_left(node.left)
        return rotate_right(node)
    
    if balance < -1 and val < node.right.val:
        node.right = rotate_right(node.right)
        return rotate_left(node)
    
    return node

def get_min_value_node(node: Node) -> Node:
    current = node
    while current.left is not None:
        current = current.left
    return current

def delete(val, node: Union[Node, None]) -> Union[Node, None]:
    if not node:
        return node
    
    if val < node.val:
        node.left = delete(val, node.left)
    elif val > node.val:
        node.right = delete(val, node.right)
    else:
        if not node.left:
            return node.right
        elif not node.right:
            return node.left
        
        temp = get_min_value_node(node.right)
        node.val = temp.val
        node.right = delete(temp.val, node.right)
    
    update_height(node)
    
    balance = get_balance(node)
    
    if balance > 1 and get_balance(node.left) >= 0:
        return rotate_right(node)
    
    if balance > 1 and get_balance(node.left) < 0:
        node.left = rotate_left(node.left)
        return rotate_right(node)
    
    if balance < -1 and get_balance(node.right) <= 0:
        return rotate_left(node)
    
    if balance < -1 and get_balance(node.right) > 0:
        node.right = rotate_right(node.right)
        return rotate_left(node)
    
    return node

def delete_min(node: Union[Node, None]) -> Union[Node, None]:
    if node is None:
        return node
    
    if node.left is None:
        return node.right
    
    node.left = delete_min(node.left)
    
    update_height(node)
    
    balance = get_balance(node)
    
    if balance > 1 and get_balance(node.left) >= 0:
        return rotate_right(node)
    
    if balance > 1 and get_balance(node.left) < 0:
        node.left = rotate_left(node.left)
        return rotate_right(node)
    
    if balance < -1 and get_balance(node.right) <= 0:
        return rotate_left(node)
    
    if balance < -1 and get_balance(node.right) > 0:
        node.right = rotate_right(node.right)
        return rotate_left(node)
    
    return node

def delete_max(node: Union[Node, None]) -> Union[Node, None]:
    if node is None:
        return node
    
    if node.right is None:
        return node.left
    
    node.right = delete_max(node.right)
    
    update_height(node)
    
    balance = get_balance(node)
    
    if balance > 1 and get_balance(node.left) >= 0:
        return rotate_right(node)
    
    if balance > 1 and get_balance(node.left) < 0:
        node.left = rotate_left(node.left)
        return rotate_right(node)
    
    if balance < -1 and get_balance(node.right) <= 0:
        return rotate_left(node)
    
    if balance < -1 and get_balance(node.right) > 0:
        node.right = rotate_right(node.right)
        return rotate_left(node)
    
    return node

def diff(root: Node) -> int:
    min_diff = float('inf')
    
    def dfs(node):
        nonlocal min_diff
        if not node:
            return
        
        if node.left:
            min_diff = min(min_diff, abs(node.val - node.left.val))
            dfs(node.left)
        
        if node.right:
            min_diff = min(min_diff, abs(node.val - node.right.val))
            dfs(node.right)
    
    dfs(root)
    return min_diff

def convert_to_anytree(node: Union[Node, None]) -> Union[AnyTreeNode, None]:
    if node is None:
        return None

    anytree_node = AnyTreeNode(str(node.val))

    if node.left:
        anytree_node.children += (convert_to_anytree(node.left),)
    if node.right:
        anytree_node.children += (convert_to_anytree(node.right),)

    return anytree_node

def print_tree(root):
    anytree_root = convert_to_anytree(root)
    for pre, fill, node in RenderTree(anytree_root):
        print(f"{pre}{node.name}")

root = None
values = [10, 20, 30, 40, 50, 25, 30, 40, 100, 23, 11]

for value in values:
    root = insert(value, root)

print("Original tree:")
print_tree(root)

root = delete(20, root)
print("\nTree after deleting node with value 20:")
print_tree(root)

root = delete_min(root)
print("\nTree after deleting minimum node:")
print_tree(root)

root = delete_max(root)
print("\nTree after deleting maximum node:")
print_tree(root)

print(f"\nMinimum difference between node values: {diff(root)}")