from main import rabin_karp_search, graham_scan, find_area

def test_rabin_karp():
    """Тестирование алгоритма Рабина-Карпа"""
    assert rabin_karp_search('abacaba', 'aba') == [0, 4]
    assert rabin_karp_search('xyz', 'abcdefg') == []
    assert rabin_karp_search('', 'abcdefgh') == []
    assert rabin_karp_search('abcdefgh', 'abcdefgh') == [0]
    assert rabin_karp_search('a', 'aaaaaa') == [0, 1, 2, 3, 4, 5]  # Multiple matches

def test_graham_make_figure():
    """Тестирование алгоритма Грэхема на соединение вершин"""
    result = graham_scan([[3, 1], [6, 8], [1, 7], [9, 3], [9, 6], [9, 0]])
    assert result == [1, 0, 5, 3, 4, 2]  # Update this based on the expected indices

    # Test with collinear points
    result_collinear = graham_scan([[1, 1], [2, 2], [3, 3], [4, 4]])
    assert result_collinear == [0, 3]  # Only endpoints should be part of the hull

def test_graham_find_square():
    """Тестирование алгоритма Грэхема на нахождение площади"""
    result = graham_scan([[3, 1], [6, 8], [1, 7], [9, 3], [9, 6], [9, 0]])
    convex_hull_points = [[3, 1], [1, 7], [6, 8], [9, 6], [9, 3], [9, 0]]  # Expected points
    assert find_area(convex_hull_points) == 47.5  # Update this based on the expected area

    # Test with a simple square
    square_points = [[0, 0], [0, 1], [1, 1], [1, 0]]
    assert find_area(square_points) == 1.0  # Area of the square

if __name__ == "__main__":
    test_rabin_karp()
    test_graham_make_figure()
    test_graham_find_square()
    print("All tests passed!")