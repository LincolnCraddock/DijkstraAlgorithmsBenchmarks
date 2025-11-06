#!/bin/bash

usage() {
    echo "Usage: $0 -t [-asgnd] | -h"
}

# parse args
hProvided=false
tProvided=false
a="priority-queue"
s=1
g="random"
n=250
dProvided=false
while getopts ":t:a:s:g:n:d:h" opt; do
case "$opt" in
    h)
        hProvided=true
        ;;
    t)
        tProvided=true;
        t=$OPTARG
        ;;
    a)
        a=$OPTARG
        ;;
    s)
        s=$OPTARG
        ;;
    g)
        g=$OPTARG
        ;;
    n)
        n=$OPTARG
        ;;
    d)
        dProvided=true
        d=$OPTARG
        ;;
    \?)
        echo "Invalid option: -$OPTARG" 1>&2
        usage
        exit 1
        ;;
    :)
        echo "Option -$OPTARG requires an argument." 1>&2
        usage
        exit 1
        ;;
esac
done

# -h provided
if $hProvided; then
    usage 
    echo "Runs the Driver the number of times specified by -t and prints the times in ms."
    echo ""
    echo "  -t=NUM    how many times to run the Driver"
    echo "  -a=ALG    algorithm to run: priority-queue or linear-search"
    echo "  -s=NUM    sample size"
    echo "  -g=GRAPH  kind of graph to evaluate: random or worse-case"
    echo "  -n=NUM    number of nodes in graph"
    echo "  -d=NUM    number to seed the RNG with"
    echo "  -h        display this help and exit"
    echo ""
    echo "Use either -t or -h."
    exit 0
fi

# -t must be provided if -h isn't
if ! $tProvided; then
    usage 1>&2
    echo "Try '$0 -h' for more information." 1>&2
    exit 1
fi

# first run
if [ $t -gt 0 ]; then
    if [ dProvided ]; then
        result=$(./Driver "$a" "$s" "$g" "$n")
    else
        result=$(./Driver "$a" "$s" "$g" "$n" "$d")
    fi
    if [ $? -ne 0 ]; then
        echo "$result"
        exit 1
    else
        echo "$result" | awk "END {print \$(NF-1)}"
    fi
fi

# run the other t-1 times
for ((i=1; i<t; i++)); do
    if [ dProvided ]; then
        ./Driver "$a" "$s" "$g" "$n" | awk "END {print \$(NF-1)}"
    else
        ./Driver "$a" "$s" "$g" "$n" "$d" | awk "END {print \$(NF-1)}"
    fi
done
