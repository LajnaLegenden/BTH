#include <iostream>
#include <cassert>
#include "fs.cpp"

int main() {
    // Test case 1: Relative path with no symbolic links
    std::string pwd = "/home/user";
    std::string path = "Documents/file.txt";
    std::string expected = "/home/user/Documents/file.txt";
    std::string actual = absolutePath(pwd, path);
    assert(actual == expected);
    std::cout << "Test case 1 passed\n";

    // Test case 2: Relative path with symbolic links
    pwd = "/home/user";
    path = "Documents/link_to_file.txt";
    expected = "/home/user/Documents/file.txt";
    actual = absolutePath(pwd, path);
    assert(actual == expected);
    std::cout << "Test case 2 passed\n";

    // Test case 3: Absolute path
    pwd = "/home/user";
    path = "/home/user/Documents/file.txt";
    expected = "/home/user/Documents/file.txt";
    actual = absolutePath(pwd, path);
    assert(actual == expected);
    std::cout << "Test case 3 passed\n";

    // Test case 4: Path with ".." directory
    pwd = "/home/user/Documents";
    path = "../file.txt";
    expected = "/home/user/file.txt";
    actual = absolutePath(pwd, path);
    assert(actual == expected);
    std::cout << "Test case 4 passed\n";

    // Test case 5: Path with "." directory
    pwd = "/home/user/Documents";
    path = "./file.txt";
    expected = "/home/user/Documents/file.txt";
    actual = absolutePath(pwd, path);
    assert(actual == expected);
    std::cout << "Test case 5 passed\n";

    std::cout << "All test cases passed\n";
    return 0;
}