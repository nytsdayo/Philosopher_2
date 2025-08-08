#!/bin/bash

# ANSI Color Codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

LOG_FILE="test_output.log"
TEST_COUNT=0
PASS_COUNT=0
PHILO_EXEC="./philo/philo"

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
    if [ -f "$LOG_FILE" ]; then
        echo "--- LOG ---"
        cat "$LOG_FILE"
        echo "-----------"
    fi
}

# Function to run a test for invalid arguments
# $1: Test name
# $2: Command-line arguments
run_arg_test() {
    local test_name="$1"
    shift
    local args="$@"

    echo -e "\n${YELLOW}--- Running Arg Test: $test_name ---${NC}"
    echo "Params: $args"

    # Run the program and check for a non-zero exit code
    $PHILO_EXEC $args > $LOG_FILE 2>&1
    if [ $? -ne 1 ]; then
        print_fail "$test_name (Program should have exited with status 1, but it didn't)"
    else
        print_pass "$test_name (Program correctly exited with error status)"
    fi
}


# Run a simulation test case
# $1: Test name
# $2: philo_num, $3: time_to_die, $4: time_to_eat, $5: time_to_sleep, $6: max_eat_count
# $7: expected outcome ("death" or "full" or "no_eat")
run_sim_test() {
    local test_name="$1"
    local philo_num=$2
    local time_to_die=$3
    local time_to_eat=$4
    local time_to_sleep=$5
    local max_eat_count=$6
    local expected_outcome="$7"

    # Construct arguments, handle optional max_eat_count
    local args="$philo_num $time_to_die $time_to_eat $time_to_sleep"
    if [ "$max_eat_count" != "" ]; then
        args="$args $max_eat_count"
    fi
    local display_max_eat=${max_eat_count:--1}

    echo -e "\n${YELLOW}--- Running Sim Test: $test_name ---${NC}"
    echo "Params: $args"

    # Run and log, use timeout
    timeout 10s $PHILO_EXEC $args > $LOG_FILE 2>&1

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
            return
        fi

        local total_eat_count=$(grep "is eating" $LOG_FILE | wc -l)
        local expected_eats=$((philo_num * max_eat_count))

        if [ "$total_eat_count" -ge "$expected_eats" ]; then
            print_pass "$test_name (All philosophers ate at least $max_eat_count times)"
        else
            print_fail "$test_name (Incorrect number of meals. Expected: >=$expected_eats, Got: $total_eat_count)"
        fi
    elif [ "$expected_outcome" == "no_eat" ]; then
        if grep -q "is eating" $LOG_FILE; then
            print_fail "$test_name (Philosophers ate, but shouldn't have)"
        else
            print_pass "$test_name (Program exited without any meals, as expected)"
        fi
    fi
}

# --- SCRIPT START ---
echo "Compiling the project..."
make -C philo/ re > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation Failed!${NC}"
    exit 1
fi
echo "Compilation successful."

# Clean slate
rm -f $LOG_FILE

# --- ARGUMENT VALIDATION TESTS ---
run_arg_test "No Arguments" ""
run_arg_test "Not Enough Arguments" "1 2 3"
run_arg_test "Too Many Arguments" "1 2 3 4 5 6"
run_arg_test "Non-numeric Argument" "1 2 three 4 5"
run_arg_test "Zero Philosophers" "0 800 200 200"

# --- SIMULATION TESTS ---
run_sim_test "Happy Path" 4 800 200 200 7 "full"
run_sim_test "Death Condition" 4 200 400 100 "" "death"
run_sim_test "One Philosopher" 1 800 200 200 "" "death"
run_sim_test "Zero Meals" 5 800 200 200 0 "no_eat"
run_sim_test "Many Philosophers" 200 410 200 200 "" "death" # Should die quickly

# --- SUMMARY ---
echo -e "\n--- Test Summary ---"
echo -e "Total Tests: $TEST_COUNT"
echo -e "${GREEN}Passed: $PASS_COUNT${NC}"
if [ $PASS_COUNT -ne $TEST_COUNT ]; then
    echo -e "${RED}Failed: $((TEST_COUNT - PASS_COUNT))${NC}"
    make -C philo/ fclean > /dev/null 2>&1
    exit 1
else
    echo "All tests passed!"
    make -C philo/ fclean > /dev/null 2>&1
    exit 0
fi
