class CustomStack:
    def __init__(self):
        self._elements = []
        self.gallops_count = 0
        self.merge_count = 0

    def __len__(self):
        return len(self._elements)

    def top(self):
        return self._elements[-1] if self._elements else None

    def push(self, item):
        self._elements.append(item)
        if len(self._elements) >= 2:
            self._merge()

    def pop(self):
        if self._elements:
            self._elements.pop()

    def _merge(self):
        valid = True

        while valid:
            if len(self._elements) < 2:
                break

            y = self._elements[-2]
            x = self._elements[-1]

            if len(self._elements) > 2:
                z = self._elements[-3]
                if not (len(z) > len(x) + len(y) and len(y) > len(x)):
                    if len(z) < len(x):
                        self._elements[-1] = self._merge_arrays(self._elements[-1], y, 3)
                        self._log_merge()
                        self._elements.pop(-2)
                    else:
                        self._elements[-1] = self._merge_arrays(self._elements[-1], y, 3)
                        self._log_merge()
                        self._elements.pop(-2)
                else:
                    valid = False
            else:
                if not (len(y) > len(x)):
                    self._elements[-1] = self._merge_arrays(self._elements[-1], y, 3)
                    self._log_merge()
                    self._elements.pop(-2)
                else:
                    valid = False

    def _merge_arrays(self, arr1, arr2, gallop_start):
        result = []
        first_count, second_count = 0, 0
        first_index, second_index = 0, 0

        while len(result) < len(arr1) + len(arr2):
            if first_count == gallop_start:
                found_index = (
                    self._binary_search(arr1[first_index:], arr2[second_index]) + first_index
                )
                result.extend(arr1[first_index:found_index])
                first_index = found_index
                first_count = 0
                self.gallops_count += 1

            if second_count == gallop_start:
                found_index = (
                    self._binary_search(arr2[second_index:], arr1[first_index]) + second_index
                )
                result.extend(arr2[second_index:found_index])
                second_index = found_index
                second_count = 0
                self.gallops_count += 1

            if first_index == len(arr1):
                result.extend(arr2[second_index:])
                break
            if second_index == len(arr2):
                result.extend(arr1[first_index:])
                break

            if abs(arr1[first_index]) > abs(arr2[second_index]):
                result.append(arr1[first_index])
                first_index += 1
                first_count += 1
                second_count = 0
            else:
                result.append(arr2[second_index])
                second_index += 1
                second_count += 1
                first_count = 0

        return result

    def _binary_search(self, original_array, target):
        left, right = 0, len(original_array) - 1
        result_index = len(original_array)

        while left <= right:
            mid = (left + right) // 2
            mid_value = original_array[mid]

            if abs(mid_value) < abs(target):
                result_index = mid
                right = mid - 1
            else:
                left = mid + 1

        return result_index

    def _log_merge(self):
        print(f"Gallops {self.merge_count}:", self.gallops_count)
        self.gallops_count = 0
        print(f"Merge {self.merge_count}:", *self._elements[-1])
        self.merge_count += 1

    def final_merge(self):
        while len(self._elements) >= 2:
            y = self._elements[-2]
            x = self._elements[-1]

            if len(self._elements) > 2:
                z = self._elements[-3]
                if len(z) < len(x):
                    self._elements[-3] = self._merge_arrays(self._elements[-3], y, 3)
                    self._log_merge()
                    self._elements.pop(-2)
                else:
                    self._elements[-1] = self._merge_arrays(self._elements[-1], y, 3)
                    self._log_merge()
                    self._elements.pop(-2)
            else:
                self._elements[-1] = self._merge_arrays(self._elements[-1], y, 3)
                self._log_merge()
                self._elements.pop(-2)

def calculate_min_run(n):
    r = 0
    while n >= 16:
        r |= n & 1
        n >>= 1
    return n + r

def insertion_sort(original_array):
    for i in range(1, len(original_array)):
        key = original_array[i]
        j = i - 1

        while j >= 0 and abs(original_array[j]) < abs(key):
            original_array[j + 1] = original_array[j]
            j -= 1

        original_array[j + 1] = key

    return original_array

def separate_array(array, min_run):
    runs = [[]]

    for i in range(len(array)):
        if len(runs[-1]) < min_run:
            runs[-1].append(array[i])
            if i == len(array) - 1:
                insertion_sort(runs[-1])
        else:
            ascending, descending = _is_sorted_abs(runs[-1])

            if ascending and not descending:
                if abs(array[i]) > abs(runs[-1][-1]):
                    runs[-1].append(array[i])
                else:
                    insertion_sort(runs[-1])
                    runs.append([array[i]])
                continue

            if not ascending and descending:
                if abs(array[i]) < abs(runs[-1][-1]):
                    runs[-1].append(array[i])
                else:
                    insertion_sort(runs[-1])
                    runs.append([array[i]])
                continue

            if not ascending and not descending:
                insertion_sort(runs[-1])
                runs.append([array[i]])
                continue

            if ascending and descending:
                if abs(array[i]) == abs(runs[-1][-1]):
                    runs[-1].append(array[i])
                    continue
                insertion_sort(runs[-1])
                runs.append([array[i]])

    return runs

def _is_sorted_abs(arr):
    ascending = all(abs(arr[i]) <= abs(arr[i + 1]) for i in range(len(arr) - 1))
    descending = all(abs(arr[i]) >= abs(arr[i + 1]) for i in range(len(arr) - 1))
    return ascending, descending

def tim_sort(original_array):
    min_run = calculate_min_run(len(original_array))
    runs = separate_array(original_array, min_run)

    for i, run in enumerate(runs):
        print(f"Part {i}:", *run)

    stack = CustomStack()

    for run in runs:
        stack.push(run)

    stack.final_merge()

    return stack.top()

n = int(input())
input_data = [int(x) for x in input().split()]

print("Answer:", *tim_sort(input_data))
