#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <iomanip>  

// Feature flags - can be toggled true/false
#define ENABLE_SPECIAL_OPERATION true  // Enables pair deletion operation
#define ENABLE_VISUALIZATION true      // Enables step-by-step DP matrix display

using namespace std;

/**
 * Visualizes the DP matrix with current cell highlighted
 * @param dp The dynamic programming matrix
 * @param A First input string
 * @param B Second input string
 * @param i Current row index being processed
 * @param j Current column index being processed
 */
void visualizeDP(const vector<vector<int>>& dp, const string& A, const string& B, int i, int j) {
    cout << "\nDP matrix state at (" << i << "," << j << "):\n";
    
    // Print column headers (characters of string B)
    cout << "    ";
    for (char c : B) cout << setw(4) << c;
    cout << endl;
    
    // Print each row of the DP matrix
    for (int x = 0; x < dp.size(); ++x) {
        // Print row label (character from string A)
        cout << (x > 0 ? A[x-1] : ' ') << " ";
        
        for (int y = 0; y < dp[x].size(); ++y) {
            if (x == i && y == j) {
                // Highlight the current cell being processed
                cout << "[" << setw(2) << dp[x][y] << "]";
            } else {
                // Regular cell display
                cout << setw(4) << dp[x][y];
            }
        }
        cout << endl;
    }
    cout << endl;
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
    
    // Initialize DP table with (lenA+1) rows and (lenB+1) columns
    // dp[i][j] represents the edit distance between A[0..i-1] and B[0..j-1]
    vector<vector<int>> dp(lenA + 1, vector<int>(lenB + 1, 0));
    
    // Base case 1: Converting A to empty string (delete all characters)
    for (int i = 0; i <= lenA; ++i) {
        dp[i][0] = i * cost_delete;
    }
    
    // Base case 2: Building B from empty string (insert all characters)
    for (int j = 0; j <= lenB; ++j) {
        dp[0][j] = j * cost_insert;
    }
    
    // Show initial DP state if visualization is enabled
    if (ENABLE_VISUALIZATION) {
        cout << "Initial DP matrix:" << endl;
        visualizeDP(dp, A, B, 0, 0);
    }
    
    // Fill the DP table
    for (int i = 1; i <= lenA; ++i) {
        for (int j = 1; j <= lenB; ++j) {
            if (A[i-1] == B[j-1]) {
                // Characters match - no operation needed
                // Carry forward the value from diagonal (previous subproblem)
                dp[i][j] = dp[i-1][j-1];
                
                if (ENABLE_VISUALIZATION) {
                    cout << "Characters match: A[" << i-1 << "] = B[" << j-1 
                         << "] = " << A[i-1] << endl;
                    cout << "dp[" << i << "][" << j << "] = dp[" << i-1 
                         << "][" << j-1 << "] = " << dp[i][j] << endl;
                }
            } else {
                // Calculate costs for standard operations:
                // 1. Replace: cost to convert A[0..i-2] to B[0..j-2] + replace cost
                int replace_cost = dp[i-1][j-1] + cost_replace;
                
                // 2. Insert: cost to convert A[0..i-1] to B[0..j-2] + insert cost
                int insert_cost = dp[i][j-1] + cost_insert;
                
                // 3. Delete: cost to convert A[0..i-2] to B[0..j-1] + delete cost
                int delete_cost = dp[i-1][j] + cost_delete;
                
                // Choose the minimum cost operation
                dp[i][j] = min({replace_cost, insert_cost, delete_cost});
                
                if (ENABLE_VISUALIZATION) {
                    cout << "Calculating dp[" << i << "][" << j << "]:" << endl;
                    cout << "  Replace cost: " << replace_cost << endl;
                    cout << "  Insert cost: " << insert_cost << endl;
                    cout << "  Delete cost: " << delete_cost << endl;
                    cout << "  Selected minimum: " << dp[i][j] << endl;
                }
            }
            
            // Special operation: delete two different consecutive characters
            if (ENABLE_SPECIAL_OPERATION && i >= 2 && A[i-1] != A[i-2]) {
                int special_delete_cost = dp[i-2][j] + cost_delete_two_diff;
                dp[i][j] = min(dp[i][j], special_delete_cost);
                
                if (ENABLE_VISUALIZATION) {
                    cout << "  Special delete pair cost: " << special_delete_cost << endl;
                    cout << "  Updated minimum: " << dp[i][j] << endl;
                }
            }
            
            // Display current DP state if visualization is enabled
            if (ENABLE_VISUALIZATION) {
                visualizeDP(dp, A, B, i, j);
                cout << "----------------------------------------" << endl;
            }
        }
    }
    
    // Output final result (edit distance between complete strings)
    if (ENABLE_VISUALIZATION) {
        cout << "Final edit distance: ";
    }
    cout << dp[lenA][lenB] << endl;
    
    return 0;
}