#include <iostream>
#include <vector>

// Class representing a table that can be divided into blocks
class Table
{
    int N; // Size of the table (N x N)
    int minCounter; // Minimum number of blocks needed to cover the table
    std::vector<std::pair<int, std::pair<int, int>>> resArr; // Stores the result blocks (size, (x, y))
    std::vector<std::vector<bool>> mainArr; // 2D array representing the table (true = occupied, false = empty)

public:
    // Constructor to initialize the table
    Table(int N) : N(N), minCounter(N * N), mainArr(N)
    {
        // Resize each row of the table to N columns
        for (int i = 0; i < N; i++)
            mainArr[i].resize(N);
    }

    // Function to insert a block of size m x m at position (x, y)
    void insertBlock(int, int, int);

    // Function to remove a block of size m x m at position (x, y)
    void removeBlock(int, int, int);

    // Function to find the first empty cell in the table
    std::pair<int, int> findEmpty();

    // Function to find the maximum possible size of a block that can be placed at (x, y)
    std::pair<int, bool> findMaxSize(int, int);

    // Recursive function to choose blocks and try to cover the table
    void chooseBlock(std::vector<std::pair<int, std::pair<int, int>>>&, int, int, int);

    // Function to handle the case when N is a prime number
    void primeNumber();

    // Function to print the result (minimum number of blocks and their positions)
    void printAnswer(int scale = 1);

    // Function to handle the case when N is divisible by 2
    void division2();

    // Function to handle the case when N is divisible by 3
    void division3();

    // Function to handle the case when N is divisible by 5
    void division5();
};

// Function to print the result (minimum number of blocks and their positions)
void Table::printAnswer(int scale)
{
    std::cout << minCounter << '\n'; // Print the minimum number of blocks
    for (int i = 0; i < minCounter; i++)
    {
        // Print the position and size of each block, scaled by the given scale
        std::cout << resArr[i].second.first * scale + 1 << ' ' << resArr[i].second.second * scale + 1 << ' ' << resArr[i].first * scale << '\n';
    }
}

// Function to insert a block of size m x m at position (x, y)
void Table::insertBlock(int m, int x, int y)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mainArr[x + i][y + j] = true; // Mark the cells as occupied
        }
    }
}

// Function to remove a block of size m x m at position (x, y)
void Table::removeBlock(int m, int x, int y)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mainArr[x + i][y + j] = false; // Mark the cells as empty
        }
    }
}

// Function to find the first empty cell in the table
std::pair<int, int> Table::findEmpty()
{
    // Start searching from the middle of the table to the end
    for (int i = N / 2; i < N; i++)
    {
        for (int j = N / 2; j < N; j++)
        {
            if (!mainArr[i][j]) // If the cell is empty
                return std::make_pair(i, j); // Return its coordinates
        }
    }
    return std::make_pair(-1, -1); // Return (-1, -1) if no empty cell is found
}

// Function to find the maximum possible size of a block that can be placed at (x, y)
std::pair<int, bool> Table::findMaxSize(int x, int y)
{
    // Check the maximum possible size in the row
    for (int i = y + 1; i < N; i++)
    {
        if (mainArr[x][i]) // If an occupied cell is found
        {
            if (N - x == i - y) // If the block can be a square
                return std::make_pair(N - x, true); // Return the size and true (square)
            return std::make_pair((N - x > i - y) ? i - y : N - x, false); // Return the size and false (not square)
        }
    }
    // If no occupied cell is found in the row
    if (N - x == N - y) // If the block can be a square
        return std::make_pair(N - x, true); // Return the size and true (square)
    return std::make_pair((N - x > N - y) ? N - y : N - x, false); // Return the size and false (not square)
}

// Recursive function to choose blocks and try to cover the table
void Table::chooseBlock(std::vector<std::pair<int, std::pair<int, int>>>& tmpArr, int counter, int x, int y)
{
    std::pair<int, int> coord = findEmpty(); // Find the first empty cell
    if (coord.first == -1) // If no empty cell is found (table is fully covered)
    {
        if (tmpArr.size() < minCounter) // If the current solution is better than the previous best
        {
            resArr = tmpArr; // Update the result
            minCounter = tmpArr.size(); // Update the minimum counter
        }
        return;
    }
    if (counter + 1 >= minCounter) // If the current solution is already worse than the best, stop
    {
        return;
    }
    int tmpBestCounter = minCounter; // Store the current best counter

    std::pair<int, bool> maxSize = findMaxSize(coord.first, coord.second); // Find the maximum possible block size at the empty cell
    if (maxSize.second) // If the block can be a square
    {
        tmpArr.push_back(std::make_pair(maxSize.first, coord)); // Add the block to the temporary solution
        insertBlock(maxSize.first, coord.first, coord.second); // Insert the block into the table
        chooseBlock(tmpArr, counter + 1, x, y); // Recursively try to cover the rest of the table
        removeBlock(maxSize.first, coord.first, coord.second); // Remove the block (backtracking)
        tmpArr.pop_back(); // Remove the block from the temporary solution
    }
    else // If the block cannot be a square
    {
        for (int i = maxSize.first; i >= 1; i--) // Try all possible block sizes from max to 1
        {
            if (tmpBestCounter > minCounter && i == 1) // If the current solution is already worse, skip
                continue;
            tmpArr.push_back(std::make_pair(i, coord)); // Add the block to the temporary solution
            insertBlock(i, coord.first, coord.second); // Insert the block into the table
            chooseBlock(tmpArr, counter + 1, x, y); // Recursively try to cover the rest of the table
            removeBlock(i, coord.first, coord.second); // Remove the block (backtracking)
            tmpArr.pop_back(); // Remove the block from the temporary solution
        }
    }
}

// Function to handle the case when N is a prime number
void Table::primeNumber()
{
    // Insert three initial blocks to cover the table
    insertBlock(N / 2 + 1, 0, 0);
    insertBlock(N / 2, N / 2 + 1, 0);
    insertBlock(N / 2, 0, N / 2 + 1);
    int counter = 3; // Counter for the number of blocks used
    int minCounter = N * N; // Initialize the minimum counter
    std::vector<std::pair<int, std::pair<int, int>>> tmpArr; // Temporary array to store the blocks
    tmpArr.push_back(std::make_pair(N / 2 + 1, std::make_pair(0, 0))); // Add the first block
    tmpArr.push_back(std::make_pair(N / 2, std::make_pair(N / 2 + 1, 0))); // Add the second block
    tmpArr.push_back(std::make_pair(N / 2, std::make_pair(0, N / 2 + 1))); // Add the third block
    chooseBlock(tmpArr, counter, N / 2, N / 2); // Start the recursive process to cover the rest of the table
}

// Function to handle the case when N is divisible by 2
void Table::division2()
{
    if (N % 2 == 0) // Check if N is divisible by 2
    {
        int N_div = N / 2; // Calculate the size of each sub-block
        std::cout << 4 << '\n'; // Print the number of blocks (always 4 for N divisible by 2)
        // Print the positions and sizes of the 4 blocks
        std::cout << 1 << ' ' << 1 << ' ' << N_div << '\n';
        std::cout << N_div + 1 << ' ' << 1 << ' ' << N_div << '\n';
        std::cout << 1 << ' ' << N_div + 1 << ' ' << N_div << '\n';
        std::cout << N_div + 1 << ' ' << N_div + 1 << ' ' << N_div << '\n';
    }
}

// Function to handle the case when N is divisible by 3
void Table::division3()
{
    int realN = N; // Store the original size of the table
    int scale = N / 3; // Calculate the scaling factor
    N = 3; // Set N to 3 (since the table is divided into 3x3 sub-blocks)
    primeNumber(); // Solve the problem for the 3x3 table
    printAnswer(scale); // Print the result, scaled by the scaling factor
}

// Function to handle the case when N is divisible by 5
void Table::division5()
{
    int realN = N; // Store the original size of the table
    int scale = N / 5; // Calculate the scaling factor
    N = 5; // Set N to 5 (since the table is divided into 5x5 sub-blocks)
    primeNumber(); // Solve the problem for the 5x5 table
    printAnswer(scale); // Print the result, scaled by the scaling factor
}

int main()
{
    int N;
    std::cin >> N; // Input the size of the table
    Table table(N); // Create a Table object

    if (N % 2 == 0) // If N is divisible by 2
    {
        table.division2(); // Handle the case
        return 0;
    }

    if (N % 3 == 0) // If N is divisible by 3
    {
        table.division3(); // Handle the case
    }
    else if (N % 5 == 0) // If N is divisible by 5
    {
        table.division5(); // Handle the case
    }
    else // If N is a prime number
    {
        table.primeNumber(); // Handle the case
        table.printAnswer(); // Print the result
    }

    return 0;
}