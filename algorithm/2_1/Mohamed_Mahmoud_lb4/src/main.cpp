def rabin_karp_search(pattern, text):
    if len(pattern) == 0 or len(pattern) > len(text):
        return []

    pattern_length = len(pattern)
    text_length = len(text)
    prime = 10**9 + 7
    base = 256
    
    pattern_hash = 0
    current_hash = 0
    base_power = 1
    
    for i in range(pattern_length - 1):
        base_power = (base_power * base) % prime
    
    for i in range(pattern_length):
        pattern_hash = (pattern_hash * base + ord(pattern[i])) % prime
        current_hash = (current_hash * base + ord(text[i])) % prime
    
    result_indices = []
    
    for i in range(text_length - pattern_length + 1):
        if pattern_hash == current_hash:
            if text[i:i + pattern_length] == pattern:
                result_indices.append(i)
        
        if i < text_length - pattern_length:
            current_hash = (current_hash - ord(text[i]) * base_power) % prime
            current_hash = (current_hash * base + ord(text[i + pattern_length])) % prime
            current_hash = (current_hash + prime) % prime
    
    return result_indices

def rotate(A, B, C):
    return (B[0] - A[0]) * (C[1] - B[1]) - (B[1] - A[1]) * (C[0] - B[0])

def find_area(points):
    n = len(points)
    area = 0.0
    for i in range(n):
        j = (i + 1) % n
        area += points[i][0] * points[j][1]
        area -= points[j][0] * points[i][1]
    area = abs(area) / 2.0
    return area

def graham_scan(points):
    n = len(points)
    if n < 3:
        return points

    P = list(range(n))
    
    for i in range(1, n):
        if points[P[i]][0] < points[P[0]][0]:
            P[i], P[0] = P[0], P[i]
    
    for i in range(2, n):
        j = i
        while j > 1 and rotate(points[P[0]], points[P[j - 1]], points[P[j]]) < 0:
            P[j], P[j - 1] = P[j - 1], P[j]
            j -= 1
    
    S = [P[0], P[1]]
    for i in range(2, n):
        while len(S) > 1 and rotate(points[S[-2]], points[S[-1]], points[P[i]]) < 0:
            S.pop()
        S.append(P[i])

    return S

if __name__ == "__main__":
    pattern = input("Enter the pattern: ").strip()
    text = input("Enter the text: ").strip()

    occurrences = rabin_karp_search(pattern, text)
    print("Pattern found at indices:", " ".join(map(str, occurrences)))

    n = int(input("Enter the number of points: "))
    A = []
    for i in range(n):
        t = list(map(int, input("Enter point (x, y): ").split(', ')))
        A.append(t)

    convex_hull_indices = graham_scan(A)
    convex_hull_points = [A[i] for i in convex_hull_indices]
    area = find_area(convex_hull_points)

    print("Convex Hull Points:", convex_hull_points)
    print("Area of Convex Hull:", area)

