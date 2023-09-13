#!/bin/bash
while getopts 'L:c2rFt' opt; do
  case $opt in
    L) limit=$OPTARG ;;
    c) mode='c' ;;
    2) mode='2' ;;
    r) mode='r' ;;
    F) mode='F' ;;
    t) mode='t' ;;
    *) echo 'Invalid option'; exit 1 ;;
  esac
done

# Shift arguments
shift $((OPTIND-1))

# Get log file
logfile=$1

function process_log_file() {
  case $mode in
    c) # xxx.xxx.xxx.xxx yyy where yyy is the number of connection attempts
    declare -A allips
    IFS=' '
    while read line; do
        read -a strarr <<< "$line"
        ip=${strarr[0]}
        #increment the value of the key if it exists, otherwise set it to 1
        allips[$ip]=$(( ${allips[$ip]} + 1 ))
    done <$logfile
    #sort ips in reverse, numeric sort with key 2, replace : with 4 spaces, print first limit lines
    for k in "${!allips[@]}" ; do
        echo $k ${allips[$k]}
    done | sort -rnk2 | sed 's/[: ]/    /g' | head -n "$limit"
    ;;

    2) # xxx.xxx.xxx.xxx yyy where yyy is the number of successful attempts
    declare -A allips
    IFS=' '
    while read line; do
        read -a strarr <<< "$line"
        ip=${strarr[0]}
        #statuscode is extrated from line using a grep pattern and cut to get the 4th field
        status=$(echo "$line" | grep -o '".*" [0-9]\+ ' | cut -d ' ' -f 4   )
        #any connection with a status code less than 299 is considered successful
        if [ "$status" -lt 299 ]; then
            allips["$ip"]=$(( ${allips["$ip"]} + 1 ))
        fi
    done <$logfile
    #sort ips in reverse, numeric sort with key 2, replace : with 4 spaces, print first limit lines
    for k in "${!allips[@]}" ; do
        echo $k ${allips[$k]}
    done | sort -rnk2 | sed 's/[: ]/    /g' | head -n "$limit"
    ;;


    r) # yyy xxx.xxx.xxx.xxx where yyy is the result code, one ip per lin
    #declare 2 maps, one for all ips and one for status codes
    declare -A allips
    declare -A statuscode

    IFS=' '
    while read line; do
    #read each line and split it into an array
        read -a strarr <<< "$line"
        ip=${strarr[0]}
        #statuscode is extrated from line using a grep pattern and cut to get the 4th field
        status=$(echo "$line" | grep -o '".*" [0-9]\+ ' | cut -d ' ' -f 4   )
        #increment number of status codes and what ip they came from
        allips["$status","$ip"]=$(( ${allips["$status","$ip"]} + 1 ))
        statuscode[$status]=$(( ${statuscode[$status]} + 1 ))

    done <$logfile
    #sort the status codes in reverse, numeric sort with key 2, replace : with 4 spaces, and savce to output
    output=$(for k in "${!statuscode[@]}"; do
        echo "$k" "${statuscode[$k]}"
    done | sort -rnk2 | sed 's/[: ]/    /g')

    status_codes=()

    # Loop through each line of the output and extract the status code, that are now in order from most used to least used
    while read -r line; do
        status_code=$(echo "$line" | awk '{print $1}')
        status_codes+=("$status_code")
    done <<< "$output"
   
    #for each code, find the ip that has the most requests and print it
    for code in "${!status_codes[@]}"; do
        #find the highest number of requests for this status code and print the ip
        for k in "${!allips[@]}" ; do
            if [[ "$k" == "${status_codes[$code]}"* ]]; then
                 IFS=',' read -r -a array <<< "$k"
                    echo "${array[0]}" "${array[1]}"
            fi
        done | sort -rnk2 | sed 's/[: ]/    /g'| head -n $limit
        printf '\n'

    done

    ;;
    
    
    F) #yyy xxx.xxx.xxx.xxx where yyy is the result code indicating failure, one ip per line
      
    declare -A allips
    declare -A statuscode

    IFS=' '
    while read line; do
        read -a strarr <<< "$line"
        ip=${strarr[0]}
        #increment the value of the key if it exists, otherwise set it to 1
        status=$(echo "$line" | grep -o '".*" [0-9]\+ ' | cut -d ' ' -f 4   )
        
        #if allips has key status
        allips["$status","$ip"]=$(( ${allips["$status","$ip"]} + 1 ))
        statuscode[$status]=$(( ${statuscode[$status]} + 1 ))

    done <$logfile

    output=$(for k in "${!statuscode[@]}"; do
        echo "$k" "${statuscode[$k]}"
    done | sort -rnk2 | sed 's/[: ]/    /g')

    status_codes=()

    # Loop through each line of the output and extract the status code, that are now in order from most used to least used
    while read -r line; do
        status_code=$(echo "$line" | awk '{print $1}')
        #if status code is greater than 399, add it to the array
        if [ "$status_code" -gt 399 ]; then
        status_codes+=("$status_code")
        fi

    done <<< "$output"
   

    for code in "${!status_codes[@]}"; do
        #find the highest number of requests for this status code and print the ip
        for k in "${!allips[@]}" ; do
            if [[ "$k" == "${status_codes[$code]}"* ]]; then
                 IFS=',' read -r -a array <<< "$k"
                    echo "${array[0]}" "${array[1]}"
            fi
        done | sort -rnk2 | sed 's/[: ]/    /g'

    done | head -n $limit

    ;;
    
    
    t) # xxx.xxx.xxx.xxx yyy where yyy is the number of bytes sent from the server
    declare -A allips
    IFS=' '
    while read line; do
        read -a strarr <<< "$line"
        ip=${strarr[0]}
        #bytes are extracted from the contentn length field of the log
        bytes=$(echo "$line" | grep -o '".*" [0-9]\+ [0-9]\+' | cut -d ' ' -f 5   )
        if [[ -n "$bytes" ]]; then
            allips[$ip]=$(( ${allips[$ip]} + $bytes ))
        fi 
        allips[$ip]=$(( ${allips[$ip]} + 0 ))
    done <$logfile 

    for k in ${!allips[@]} ; do
        echo $k ${allips[$k]}
    done | sort -rnk2 | sed 's/[: ]/    /g' | head -n "$limit"
    ;;
  esac
}

#TEST CODE DELETE LATER

process_log_file