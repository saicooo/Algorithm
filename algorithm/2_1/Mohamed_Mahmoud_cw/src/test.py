import unittest
from main import HashTableDoubleHashing, HashTableChaining

class TestHashTableDoubleHashing(unittest.TestCase):
    def setUp(self):
        self.table = HashTableDoubleHashing(10)

    def test_insert_and_search(self):
        self.table.insert(5, "value5")
        self.table.insert(15, "value15")
        self.assertEqual(self.table.search(5), "value5")
        self.assertEqual(self.table.search(15), "value15")

    def test_collision_handling(self):
        self.table.insert(5, "value5")
        self.table.insert(15, "value15")
        self.assertEqual(self.table.collisions, 1)

    def test_delete(self):
        self.table.insert(5, "value5")
        self.table.delete(5)
        self.assertIsNone(self.table.search(5))

    def test_search_nonexistent(self):
        self.assertIsNone(self.table.search(100))

class TestHashTableChaining(unittest.TestCase):
    def setUp(self):
        self.table = HashTableChaining(10)

    def test_insert_and_search(self):
        self.table.insert(5, "value5")
        self.table.insert(15, "value15")
        self.assertEqual(self.table.search(5), "value5")
        self.assertEqual(self.table.search(15), "value15")

    def test_collision_handling(self):
        self.table.insert(5, "value5")
        self.table.insert(15, "value15")
        self.assertEqual(self.table.collisions, 1)

    def test_delete(self):
        self.table.insert(5, "value5")
        self.table.delete(5)
        self.assertIsNone(self.table.search(5))

    def test_search_nonexistent(self):
        self.assertIsNone(self.table.search(100))

if __name__ == '__main__':
    unittest.main()