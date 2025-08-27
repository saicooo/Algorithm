    #include <iostream>
    #include <vector>
    #include <string>

    //print all the steps defprefix_arr
    void print_prefix_step(const std::string& str, const std::vector<int>& prefix_arr, int i, int j) {
        std::cout << "i = " << i << ", j = " << j << ", str[i] = " << str[i]
                << ", str[j] = " << str[j] << "\n";
        std::cout << "Current prefix array: ";
        for (int k = 0; k <= i; ++k) {
            if (k == i)
                std::cout << "[" << prefix_arr[k] << "] ";
            else
                std::cout << prefix_arr[k] << " ";
        }
        std::cout << "\n-----------------------------------\n";
    }

    // Computes the prefix function used in the KMP algorithm
    std::vector<int> prefix_function(const std::string& str) {
        int n = str.length();
        if (n == 0) return std::vector<int>(0); // If the string is empty
        std::vector<int> prefix_arr(n);
        int j;
        // Build the prefix array
        for (int i = 1; i < n; ++i) {
            j = prefix_arr[i - 1];
            // Backtrack in prefix array while characters don't match
            while (j > 0 && str[i] != str[j]) j = prefix_arr[j - 1];
            // If characters match, increase j
            if (str[i] == str[j]) j++;
            // Assign the prefix value
            prefix_arr[i] = j;

            // طباعة خطوات مصفوفة prefix
            print_prefix_step(str, prefix_arr, i, j);
        }
        return prefix_arr;
    }

    // KMP (Knuth–Morris–Pratt) string matching algorithm
    std::vector<int> kmp(const std::string& patt, const std::string& temp, bool stop_at_first) {
        std::vector<int> answer;
        int patt_len = patt.size();
        int temp_len = temp.size();
        // If either string is empty, return -1
        if (patt_len == 0 || temp_len == 0) {
            answer.push_back(-1);
            return answer;
        }
        // Build prefix function for pattern
        std::vector<int> p = prefix_function(patt + "#");
        int j = 0;
        for (int i = 0; i < temp_len; ++i) {
            // While characters mismatch, backtrack using prefix function
            while (j > 0 && patt[j] != temp[i]) j = p[j - 1];
            if (patt[j] == temp[i]) j++; // If characters match, move forward

            if (j == patt_len) {
                // Found full match
                answer.push_back(i - patt_len + 1); // Store start index of match
                if (stop_at_first) break; // Stop if only one match is needed
            }
        }
        // If no matches found, return -1
        if (answer.empty()) answer.push_back(-1);
        return answer;
    }

    // Checks if one string is a cyclic shift of another
    int check_cycle(const std::string& patt, const std::string& temp) {
        int patt_len = patt.size();
        int temp_len = temp.size();
        // If lengths differ or any string is empty, return -1
        if (patt_len == 0 || temp_len == 0) return -1;
        if (patt_len != temp_len) return -1;
        // Check if temp exists in patt + patt using KMP
        std::vector<int> res = kmp(temp, patt + patt, true);
        return res[0]; // Return the match index or -1
    }

    // Reads two input strings from input stream
    bool read_strings(std::string& patt, std::string& temp, std::istream& in) {
        in >> patt;
        in >> temp;
        // Return false if any string is empty
        if (patt.empty() || temp.empty()) return false;
        return true;
    }

    // Prints the content of a vector separated by commas
    void print_vector(const std::vector<int>& vec) {
        for (int i = 0; i < vec.size(); ++i) {
            if (i == vec.size() - 1)
                std::cout << vec[i] << "\n";
            else
                std::cout << vec[i] << ",";
        }
    }

    int main(int argc, char** argv) {
        int task = 2; // Default to cycle check

        // Parse command-line arguments to set task type
        for (int i = 0; i < argc; ++i) {
            if (std::string(argv[i]) == "-kmp") {
                task = 1;
                break;
            } else if (std::string(argv[i]) == "-cycle") {
                task = 2;
                break;
            } else if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
                task = 0;
                break;
            }
        }

        // If no valid task specified
        if (task == -1) {
            std::cout << "You have to specialize the task: either choose KMP or Cycle Check.\nTo get more info use key -h or --help.\n";
            return 0;
        } else if (task == 0) {
            // Display help information
            std::cout << "Use -kmp to start Knuth–Morris–Pratt Algorithm\n";
            std::cout << "Use -cycle to check if a string is a cycle shift of another one\n";
            return 0;
        }

        std::string pattern, temp;
        // Read input strings
        if (!read_strings(pattern, temp, std::cin)) {
            std::cout << "You've entered empty string\n";
            return 0;
        }

        // Execute selected task
        if (task == 1) {
            // Perform KMP search
            std::vector<int> res = kmp(pattern, temp, false);
            print_vector(res);
            return 0;
        } else {
            // Perform cycle shift check
            std::cout << check_cycle(pattern, temp) << '\n';
            return 0;
        }
    }
