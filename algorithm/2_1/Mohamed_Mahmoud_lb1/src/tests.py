from LinkedList import UnrolledLinkedList

def test_append():
    ull = UnrolledLinkedList(10)
    ull.append(1)
    ull.append(2)
    ull.append(3)
    assert len(ull) == 3

def test_display():
    ull = UnrolledLinkedList(10)
    ull.append(1)
    ull.append(2)
    ull.append(3)
    # This test is more for visual confirmation, so we'll just call the display method
    ull.display()

def test_search():
    ull = UnrolledLinkedList(10)
    ull.append(1)
    ull.append(2)
    ull.append(3)
    assert ull.search(2) == (0, 1)
    assert ull.search(4) is None

def test_delete():
    ull = UnrolledLinkedList(10)
    ull.append(1)
    ull.append(2)
    ull.append(3)
    assert ull.delete(2) is True
    assert len(ull) == 2
    assert ull.delete(4) is False

def test_clear():
    ull = UnrolledLinkedList(10)
    ull.append(1)
    ull.append(2)
    ull.append(3)
    ull.clear()
    assert len(ull) == 0

if __name__ == "__main__":
    test_append()
    test_display()
    test_search()
    test_delete()
    test_clear()
    print("All tests passed!")