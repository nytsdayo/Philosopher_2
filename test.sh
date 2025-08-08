#!/bin/bash

# ANSI Color Codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

LOG_FILE="../test_output.log" # Log file in the root directory
TEST_COUNT=0
PASS_COUNT=0

# Function to print a pass message
print_pass() {
    ((TEST_COUNT++))
    ((PASS_COUNT++))
    echo -e "${GREEN}PASS: $1${NC}"
}

# Function to print a fail message
print_fail() {
    ((TEST_COUNT++))
    echo -e "${RED}FAIL: $1${NC}"
    echo "--- LOG ---"
    # Check if log file exists and is not empty
    if [ -s $LOG_FILE ]; then
        cat $LOG_FILE
    else
        echo "Log file is empty or does not exist."
    fi
    echo "-----------"
}

# Function to generate a main.c file with specified parameters
generate_main_c() {
    # $1: philo_num, $2: time_to_die, $3: time_to_eat, $4: time_to_sleep, $5: max_eat_count
    cat > srcs/main.c << EOL
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "ph_dining.h"
#include "ph_utils.h"
#include "ph_status.h"

#define PHILO_NUM $1
#define DEAD_TIME $2
#define EAT_TIME $3
#define SLEEP_TIME $4
#define MAX_EAT_COUNT $5

int	main(int argc, char **argv)
{
	t_dining_data dining_data;
	(void)argc;
	(void)argv;
	dining_data.philo_num = PHILO_NUM;
	dining_data.time_to_die = DEAD_TIME;
	dining_data.time_to_eat = EAT_TIME;
	dining_data.time_to_sleep = SLEEP_TIME;
	dining_data.max_eat_count = MAX_EAT_COUNT;
	if (ph_dining(dining_data) != PH_SUCCESS)
	{
		fprintf(stderr, "ph_dining error\\n");
		return (1);
	}
	return (0);
}
EOL
}

# Cleanup function for a single test run
test_cleanup() {
    make fclean > /dev/null 2>&1
}

# Run a test case
# $1: Test name
# $2: philo_num, $3: time_to_die, $4: time_to_eat, $5: time_to_sleep, $6: max_eat_count
# $7: expected outcome ("death" or "full" or "no_eat")
run_test() {
    local test_name="$1"
    local philo_num=$2
    local time_to_die=$3
    local time_to_eat=$4
    local time_to_sleep=$5
    local max_eat_count=$6
    local expected_outcome="$7"

    echo -e "\n${YELLOW}--- Running Test: $test_name ---${NC}"
    echo "Params: N=$philo_num, die=$time_to_die, eat=$time_to_eat, sleep=$time_to_sleep, count=$max_eat_count"

    generate_main_c $philo_num $time_to_die $time_to_eat $time_to_sleep $max_eat_count

    # Compile
    make re > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        print_fail "$test_name (Compilation Failed)"
        return
    fi

    # Run and log
    # Use a timeout to prevent infinite loops (e.g., deadlocks)
    timeout 5s ./philo > $LOG_FILE 2>&1

    # Analyze
    if [ "$expected_outcome" == "death" ]; then
        if grep -q "died" $LOG_FILE; then
            print_pass "$test_name (Philosopher correctly died)"
        else
            print_fail "$test_name (Philosopher was supposed to die, but didn't)"
        fi
    elif [ "$expected_outcome" == "full" ]; then
        if grep -q "died" $LOG_FILE; then
            print_fail "$test_name (Philosopher died unexpectedly)"
            test_cleanup
            return
        fi

        local total_eat_count=$(grep "is eating" $LOG_FILE | wc -l)
        local expected_eats=$((philo_num * max_eat_count))

        if [ "$total_eat_count" -eq "$expected_eats" ]; then
            print_pass "$test_name (All philosophers ate $max_eat_count times)"
        else
            print_fail "$test_name (Incorrect number of meals. Expected: $expected_eats, Got: $total_eat_count)"
        fi
    elif [ "$expected_outcome" == "no_eat" ]; then
        if grep -q "is eating" $LOG_FILE; then
            print_fail "$test_name (Philosophers ate, but shouldn't have)"
        else
            print_pass "$test_name (Program exited without any meals, as expected)"
        fi
    fi
    test_cleanup
}

# --- SCRIPT START ---

# Backup main.c and set a trap to restore it on exit
echo "Backing up original main.c to main.c.bak"
cp srcs/main.c srcs/main.c.bak
trap 'echo -e "\nRestoring original main.c and cleaning up..."; mv srcs/main.c.bak srcs/main.c; rm -f $LOG_FILE;' EXIT INT TERM

# Clean slate
rm -f $LOG_FILE

# --- TEST CASES ---
run_test "Happy Path" 4 800 200 200 7 "full"
run_test "Death Condition" 4 200 400 100 -1 "death"
run_test "One Philosopher" 1 800 200 200 -1 "death"
run_test "Zero Meals" 5 800 200 200 0 "no_eat"

# --- SUMMARY ---
echo -e "\n--- Test Summary ---"
echo -e "Total Tests: $TEST_COUNT"
echo -e "${GREEN}Passed: $PASS_COUNT${NC}"
if [ $PASS_COUNT -ne $TEST_COUNT ]; then
    echo -e "${RED}Failed: $((TEST_COUNT - PASS_COUNT))${NC}"
    exit 1
else
    echo "All tests passed!"
    exit 0
fi
