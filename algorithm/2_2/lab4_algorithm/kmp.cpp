#include <iostream>
#include <vector>
#include <string>

// دالة لطباعة خطوات بناء مصفوفة prefix_arr
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

// Computes the prefix function (also known as "failure function") used in KMP
std::vector<int> prefix_function(const std::string& str) {
    int n = str.length();
    if(n == 0) return std::vector<int> (0);
    std::vector<int> prefix_arr(n);
    int j;
    for (int i = 1; i < n; ++i) {
        j = prefix_arr[i - 1];
        while (j > 0 && str[i] != str[j]) j = prefix_arr[j - 1];
        if (str[i] == str[j]) j++;
        prefix_arr[i] = j;

        // طباعة خطوات المصفوفة
        print_prefix_step(str, prefix_arr, i, j);
    }
    return prefix_arr;
}

// Implements the Knuth–Morris–Pratt (KMP) algorithm for pattern matching
std::vector<int> kmp(const std::string& patt, const std::string& temp, bool stop_at_first) {
    std::vector<int> answer;
    int patt_len = patt.size();
    int temp_len = temp.size();
    if(patt_len == 0 || temp_len == 0) {
        answer.push_back(-1);
        return answer;
    }
    std::vector<int> p = prefix_function(patt + "#");
    int j = 0;
    for(int i = 0; i < temp_len; ++i) {
        while(j > 0 && patt[j] != temp[i]) j = p[j-1];
        if(patt[j] == temp[i]) j++;
        if(j == patt_len) {
            answer.push_back(i - patt_len + 1);
            if(stop_at_first) break;
        }
    }
    if(answer.empty()) answer.push_back(-1);
    return answer;
}

// Checks whether "temp" is a cyclic shift of "patt"
int check_cycle(const std::string& patt, const std::string& temp) {
    int patt_len = patt.size();
    int temp_len = temp.size();
    if(patt_len == 0 || temp_len == 0) return -1;
    if(patt_len != temp_len) return -1;
    std::vector<int> res = kmp(temp, patt + patt, true);
    return res[0];
}

// Reads two strings from the input
bool read_strings(std::string& patt, std::string& temp, std::istream& in) {
    in >> patt;
    in >> temp;
    if(patt.size() == 0 || temp.size() == 0) return false;
    return true;
}

// Prints a vector of integers separated by commas
void print_vector(const std::vector<int>& vec) {
    for(int i = 0; i < vec.size(); ++i) {
        if(i == vec.size() - 1) {
            std::cout << vec[i] << "\n";
        }
        else {
            std::cout << vec[i] << ",";
        }
    }
}

// Main program entry point
int main(int argc, char** argv) {
    int task = 1;
    for(int i = 0; i < argc; ++i) {
        if(std::string(argv[i]) == "-kmp") {
            task = 1;
            break;
        }
        else if(std::string(argv[i]) == "-cycle") {
            task = 2;
            break;
        }
        else if(std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
            task = 0;
            break;
        }
    }
    if(task == -1) {
        std::cout << "You have to specialize the task: either choose KMP or Cycle Check.\nTo get more info use key -h or --help.\n";
        return 0;
    }
    else if(task == 0) {
        std::cout << "Use -kmp to start Knuth–Morris–Pratt Algorithm\n";
        std::cout << "Use -cycle to check if a string is a cycle shift of another one\n";
        return 0;
    }

    std::string pattern, temp;
    if(!read_strings(pattern, temp, std::cin)) {
        std::cout << "You've entered empty string\n";
        return 0;
    }

    if(task == 1) {
        std::vector<int> res = kmp(pattern, temp, false);
        print_vector(res);
        return 0;
    }
    else {
        std::cout << check_cycle(pattern, temp) << '\n';
        return 0;
    }
}
