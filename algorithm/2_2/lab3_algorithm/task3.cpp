#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <iomanip>

// Feature flags - can be toggled true/false
#define ENABLE_SPECIAL_OPERATION false  // Enables pair deletion operation
#define ENABLE_VISUALIZATION false    // Enables step-by-step DP matrix display

using namespace std;

/**
 * Visualizes the DP matrix with current cell highlighted
 * @param dp The dynamic programming matrix storing edit distances
 * @param A The source string being transformed
 * @param B The target string
 * @param i Current row index (position in string A)
 * @param j Current column index (position in string B)
 */
void visualizeDP(const vector<vector<int>>& dp, const string& A, const string& B, int i, int j) {
    cout << "\nDP matrix state at (" << i << "," << j << "):\n";
    
    // Print column headers (characters of string B)
    cout << "     ";
    for (char c : B) cout << setw(4) << c;
    cout << endl;
    
    // Print each row with row label (character from string A)
    for (int x = 0; x < dp.size(); ++x) {
        cout << (x > 0 ? A[x-1] : ' ') << " |";
        for (int y = 0; y < dp[x].size(); ++y) {
            // Highlight current cell being processed
            if (x == i && y == j) cout << "[";
            else cout << " ";
            
            // Print cell value
            cout << setw(2) << dp[x][y];
            
            // Close highlight if needed
            if (x == i && y == j) cout << "]";
            else cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    // Initialize operation costs (can be modified or read from input)
    int cost_replace = 1;  // Cost to replace a character
    int cost_insert = 1;   // Cost to insert a character
    int cost_delete = 1;   // Cost to delete a character
    int cost_delete_two_diff = 0; // Cost for special pair deletion
    
    // Read input strings
    string A, B;
    cout << "Enter source string: ";
    cin >> A;
    cout << "Enter target string: ";
    cin >> B;
    
    int lenA = A.size();
    int lenB = B.size();

    // DP table initialization:
    // dp[i][j] represents the minimum edit distance between A[0..i-1] and B[0..j-1]
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
        cout << "\n=== INITIAL DP MATRIX ===\n";
        visualizeDP(dp, A, B, 0, 0);
    }

    // Fill the DP table
    for (int i = 1; i <= lenA; ++i) {
        for (int j = 1; j <= lenB; ++j) {
            if (A[i-1] == B[j-1]) {
                // Characters match - no operation needed
                dp[i][j] = dp[i-1][j-1];
                
                if (ENABLE_VISUALIZATION) {
                    cout << "MATCH at A[" << i-1 << "]='" << A[i-1] 
                         << "' and B[" << j-1 << "]='" << B[j-1] << "'\n";
                    cout << "Carrying value from diagonal: dp[" << i << "][" << j 
                         << "] = dp[" << i-1 << "][" << j-1 << "] = " << dp[i][j] << "\n";
                }
            } else {
                // Calculate standard operation costs
                int replace_cost = dp[i-1][j-1] + cost_replace;
                int insert_cost = dp[i][j-1] + cost_insert;
                int delete_cost = dp[i-1][j] + cost_delete;
                
                // Select minimum cost operation
                dp[i][j] = min({replace_cost, insert_cost, delete_cost});
                
                if (ENABLE_VISUALIZATION) {
                    cout << "\nCALCULATING dp[" << i << "][" << j << "]:\n";
                    cout << "Replace cost: " << replace_cost << "\n";
                    cout << "Insert cost: " << insert_cost << "\n";
                    cout << "Delete cost: " << delete_cost << "\n";
                    cout << "Selected minimum cost: " << dp[i][j] << "\n";
                }
            }
            
            // Special operation: delete two different consecutive characters
            if (ENABLE_SPECIAL_OPERATION && i >= 2 && A[i-1] != A[i-2]) {
                int special_delete_cost = dp[i-2][j] + cost_delete_two_diff;
                if (special_delete_cost < dp[i][j]) {
                    dp[i][j] = special_delete_cost;
                    
                    if (ENABLE_VISUALIZATION) {
                        cout << "SPECIAL PAIR DELETE of '" << A[i-2] << A[i-1] << "'\n";
                        cout << "New minimum cost: " << dp[i][j] << "\n";
                    }
                }
            }
            
            // Display current DP state if visualization is enabled
            if (ENABLE_VISUALIZATION) {
                visualizeDP(dp, A, B, i, j);
                cout << "----------------------------------------\n";
            }
        }
    }

    // Output final result with explanation
    cout << "\n=== FINAL RESULT ===\n";
    cout << "Minimum edit distance between \"" << A << "\" and \"" << B << "\": " 
         << dp[lenA][lenB] << "\n";
    
    // Optional: Print the entire DP matrix at the end
    if (ENABLE_VISUALIZATION) {
        cout << "\n=== COMPLETE DP MATRIX ===\n";
        visualizeDP(dp, A, B, lenA, lenB);
    }

    return 0;
}

