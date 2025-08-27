#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>  

// Feature flags - can be toggled true/false
#define ENABLE_SPECIAL_OPERATION false  // Enables pair deletion operation
#define ENABLE_VISUALIZATION false     // Enables step-by-step DP matrix display

using namespace std;

/**
 * Prints the DP matrix with operation tracking and current cell highlighting
 * @param dp The dynamic programming cost matrix
 * @param ops The operation tracking matrix
 * @param A First input string
 * @param B Second input string
 * @param i Current row index being processed
 * @param j Current column index being processed
 */
void printMatrix(const vector<vector<int>>& dp, const vector<vector<char>>& ops,
                const string& A, const string& B, int i, int j) {
    // Print column headers (characters of string B)
    cout << "     ";
    for (char c : B) cout << setw(4) << c;
    cout << "\n +" << string(5*(B.size()+1), '-') << "+\n";
    
    // Print each row with row label (character from string A)
    for (int x = 0; x <= A.size(); ++x) {
        cout << (x > 0 ? A[x-1] : ' ') << " |";
        for (int y = 0; y <= B.size(); ++y) {
            // Highlight current cell being processed
            if (x == i && y == j) cout << "[";
            else cout << " ";
            
            // Print cell value and operation symbol
            cout << setw(2) << dp[x][y] << ops[x][y];
            
            // Close highlight if needed
            if (x == i && y == j) cout << "]";
            else cout << " ";
        }
        cout << "|\n";
    }
    cout << " +" << string(5*(B.size()+1), '-') << "+\n\n";
}

int main() {
    // Read operation costs from input
    int cost_replace, cost_insert, cost_delete;
    cin >> cost_replace >> cost_insert >> cost_delete;
    
    int cost_delete_two_diff = 0;
    
    // Read special operation cost if enabled
    if (ENABLE_SPECIAL_OPERATION) {
        cin >> cost_delete_two_diff;
    }
    
    // Read input strings
    string A, B;
    cin >> A >> B;
    
    int lenA = A.size();
    int lenB = B.size();
    
    // DP table initialization:
    // dp[i][j] stores the minimum edit distance between A[0..i-1] and B[0..j-1]
    vector<vector<int>> dp(lenA + 1, vector<int>(lenB + 1, 0));
    
    // Operation tracking table:
    // ops[i][j] stores the operation performed to reach this state
    // M: Match, R: Replace, I: Insert, D: Delete, P: Pair delete
    vector<vector<char>> operations(lenA + 1, vector<char>(lenB + 1, ' '));
    
    // Base case 1: Converting A to empty string (delete all characters)
    for (int i = 0; i <= lenA; ++i) {
        dp[i][0] = i * cost_delete;
        operations[i][0] = 'D';  // Track delete operations
    }
    
    // Base case 2: Building B from empty string (insert all characters)
    for (int j = 0; j <= lenB; ++j) {
        dp[0][j] = j * cost_insert;
        operations[0][j] = 'I';  // Track insert operations
    }
    
    // Show initial DP state if visualization is enabled
    if (ENABLE_VISUALIZATION) {
        cout << "=== INITIAL MATRIX ===\n";
        printMatrix(dp, operations, A, B, 0, 0);
    }
    
    // Fill the DP tables
    for (int i = 1; i <= lenA; ++i) {
        for (int j = 1; j <= lenB; ++j) {
            if (A[i-1] == B[j-1]) {
                // Characters match - no operation needed
                dp[i][j] = dp[i-1][j-1];
                operations[i][j] = 'M';  // Track match operation
                
                if (ENABLE_VISUALIZATION) {
                    cout << "MATCH at (" << i << "," << j << "): "
                         << A[i-1] << " == " << B[j-1] << "\n";
                }
            } else {
                // Calculate standard operation costs:
                // 1. Replace: cost to convert A[0..i-2] to B[0..j-2] + replace cost
                int replace_cost = dp[i-1][j-1] + cost_replace;
                
                // 2. Insert: cost to convert A[0..i-1] to B[0..j-2] + insert cost
                int insert_cost = dp[i][j-1] + cost_insert;
                
                // 3. Delete: cost to convert A[0..i-2] to B[0..j-1] + delete cost
                int delete_cost = dp[i-1][j] + cost_delete;
                
                // Find minimum cost operation
                if (replace_cost <= insert_cost && replace_cost <= delete_cost) {
                    dp[i][j] = replace_cost;
                    operations[i][j] = 'R';  // Track replace operation
                } else if (insert_cost <= replace_cost && insert_cost <= delete_cost) {
                    dp[i][j] = insert_cost;
                    operations[i][j] = 'I';  // Track insert operation
                } else {
                    dp[i][j] = delete_cost;
                    operations[i][j] = 'D';  // Track delete operation
                }
                
                if (ENABLE_VISUALIZATION) {
                    cout << "OPERATIONS at (" << i << "," << j << "):\n"
                         << "  Replace: " << replace_cost << "\n"
                         << "  Insert: " << insert_cost << "\n"
                         << "  Delete: " << delete_cost << "\n"
                         << "  Selected: " << operations[i][j] 
                         << " (cost=" << dp[i][j] << ")\n";
                }
                
                // Check for special pair deletion operation if enabled
                if (ENABLE_SPECIAL_OPERATION && i >= 2 && A[i-1] != A[i-2]) {
                    int pair_delete_cost = dp[i-2][j] + cost_delete_two_diff;
                    if (pair_delete_cost < dp[i][j]) {
                        dp[i][j] = pair_delete_cost;
                        operations[i][j] = 'P';  // Track pair delete operation
                        
                        if (ENABLE_VISUALIZATION) {
                            cout << "  SPECIAL PAIR DELETE: " << pair_delete_cost
                                 << " (delete " << A[i-2] << A[i-1] << ")\n";
                        }
                    }
                }
            }
            
            // Display current DP state if visualization is enabled
            if (ENABLE_VISUALIZATION) {
                printMatrix(dp, operations, A, B, i, j);
                cout << "-----------------------------------------\n";
            }
        }
    }
    
    // Reconstruct the operation sequence by backtracking through the operations table
    string sequence;
    int i = lenA, j = lenB;
    while (i > 0 || j > 0) {
        char op = operations[i][j];
        sequence += op;
        
        // Move pointers based on the operation
        if (op == 'M' || op == 'R') {
            // Match or Replace: move diagonally
            i--; j--;
        } else if (op == 'I') {
            // Insert: move left
            j--;
        } else if (op == 'D') {
            // Delete: move up
            i--;
        } else if (op == 'P') {
            // Pair delete: move up two rows
            i -= 2;
        }
    }
    reverse(sequence.begin(), sequence.end());
    
    // Output results based on visualization mode
    if (ENABLE_VISUALIZATION) {
        cout << "\n=== FINAL RESULTS ===\n";
        cout << "Edit distance: " << dp[lenA][lenB] << "\n";
        cout << "Operation sequence: " << sequence << "\n";
        cout << "Legend: M=Match, R=Replace, I=Insert, D=Delete, P=PairDelete\n";
        cout << "Original string: " << A << "\n";
        cout << "Target string: " << B << "\n";
    } else {
        // Compact output format when visualization is disabled
        cout << sequence << "\n" << A << "\n" << B << "\n";
    }
    
    return 0;
}