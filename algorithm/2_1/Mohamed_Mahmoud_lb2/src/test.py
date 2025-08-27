from main import tim_sort


def test_empty_list():
    input_list = []
    sorted_result = tim_sort(input_list)
    assert sorted_result == [], f"Expected [], got {sorted_result}"


def test_single_item_list():
    input_list = [96]
    sorted_result = tim_sort(input_list)
    assert sorted_result == [96], f"Expected [96], got {sorted_result}"


def test_sorted_list():
    input_list = [5, 4, 3, 2, 1]
    sorted_result = tim_sort(input_list)
    assert sorted_result == [5, 4, 3, 2, 1], f"Expected [5, 4, 3, 2, 1], got {sorted_result}"


def test_reverse_sorted_list():
    input_list = [1, 2, 3, 4, 5]
    sorted_result = tim_sort(input_list)
    assert sorted_result == [5, 4, 3, 2, 1], f"Expected [5, 4, 3, 2, 1], got {sorted_result}"


def test_random_list():
    input_list = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
    sorted_result = tim_sort(input_list)
    assert sorted_result == [9, 6, 5, 5, 5, 4, 3, 3, 2, 1, 1], f"Expected [9, 6, 5, 5, 5, 4, 3, 3, 2, 1, 1], got {sorted_result}"


def test_duplicates_in_list():
    input_list = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
    sorted_result = tim_sort(input_list)
    assert sorted_result == [9, 6, 5, 5, 5, 4, 3, 3, 2, 1, 1], f"Expected [9, 6, 5, 5, 5, 4, 3, 3, 2, 1, 1], got {sorted_result}"


def test_negative_numbers_in_list():
    input_list = [-3, 1, -4, 1, 5, -9, 2, 6, -5, 3, 5]
    sorted_result = tim_sort(input_list)
    assert sorted_result == [-9, 6, 5, -5, 5, -4, -3, 3, 2, 1, 1], f"Expected [-9, 6, 5, -5, 5, -4, -3, 3, 2, 1, 1], got {sorted_result}"


def test_identical_elements_in_list():
    input_list = [7, 7, 7, 7, 7]
    sorted_result = tim_sort(input_list)
    assert sorted_result == [7, 7, 7, 7, 7], f"Expected [7, 7, 7, 7, 7], got {sorted_result}"


def test_large_numbers_in_list():
    input_list = [1, 10, 100, 1000, 10000, 1000000]
    sorted_result = tim_sort(input_list)
    assert sorted_result == [1000000, 10000, 1000, 100, 10, 1], f"Expected [1000000, 10000, 1000, 100, 10, 1], got {sorted_result}"


if __name__ == '__main__':
    test_empty_list()
    test_single_item_list()
    test_sorted_list()
    test_reverse_sorted_list()
    test_random_list()
    test_duplicates_in_list()
    test_negative_numbers_in_list()
    test_identical_elements_in_list()
    test_large_numbers_in_list()

    print("All tests passed successfully!")
