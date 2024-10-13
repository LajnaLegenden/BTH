#!/usr/bin/env bash

# Function to run the compiler and record the result
run_test() {
    local file=$1
    local category=$(basename "$(dirname "$file")")
    
    echo "Testing $file"
    output=$(./compiler "$file" 2>&1)
    local return_code=$?
    
    if echo "$output" | grep -qi "error"; then
        result="FAILED (error in output)"
    elif [ $return_code -eq 0 ]; then
        result="PASSED"
    else
        result="FAILED (non-zero return code)"
    fi
    
    echo "$category,$(basename "$file"),$return_code,$result" >> results.csv
    echo "Result: $result"
    echo "----------------------------------------"
}

# Create or clear the results file
echo "Category,File,Return Code,Result" > results.csv

# Recursively find and test all .java files
find test_files -name "*.java" | while read -r file; do
    run_test "$file"
done

echo "Testing complete. Results saved in results.csv"

# Print a summary of results
echo -e "\nSummary of results:"
awk -F',' 'NR>1 {print $4}' results.csv | sort | uniq -c

# Print a summary of return codes
echo -e "\nSummary of return codes:"
sort -t',' -k3 -n results.csv | awk -F',' 'NR>1 {print $3}' | uniq -c