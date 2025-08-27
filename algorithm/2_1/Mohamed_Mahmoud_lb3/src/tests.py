from main import Node, insert, delete, delete_min, delete_max

def test_insert():
    root = None
    values = [10, 20, 30, 40, 50, 25]
    for value in values:
        root = insert(value, root)

    assert root.val == 30
    assert root.left.val == 20
    assert root.right.val == 40
    assert root.left.left.val == 10
    assert root.left.right.val == 25
    assert root.right.right.val == 50

    print("Test insert passed!")

def test_delete():
    root = None
    values = [10, 20, 30, 40, 50, 25]
    for value in values:
        root = insert(value, root)

    root = delete(20, root)
    assert root.val == 30
    assert root.left.val == 25
    assert root.left.left.val == 10

    print("Test delete passed!")

def test_delete_min():
    root = None
    values = [10, 20, 30, 40, 50, 25]
    for value in values:
        root = insert(value, root)

    root = delete_min(root)
    assert root.val == 30
    assert root.left.val == 20
    assert root.left.left is None

    print("Test delete_min passed!")

def test_delete_max():
    root = None
    values = [10, 20, 30, 40, 50, 25]
    for value in values:
        root = insert(value, root)

    root = delete_max(root)
    assert root.val == 30
    assert root.right.val == 40
    assert root.right.right is None

    print("Test delete_max passed!")

test_insert()
test_delete()
test_delete_min()
test_delete_max()