import subprocess
import matrices
import time
#generate n test cases
def run(n):
    test_passed = 0
    for j in range(n):
        print(f"TEST {j+1}:", end="")
        with open(f"outputs/output{j+1}.txt", "r") as f:
            expected_output = f.read()
        with open(f"inputs/input{j+1}.txt", "r") as f:
            input_data = f.read()

        num_passed = 0
        number_of_iteration = 100
        for i in range(number_of_iteration):
            process = subprocess.run("./hw2", input=input_data, capture_output=True, text=True)
            if process.stdout == expected_output:
                num_passed += 1
            # else:
            #     print(f"FAILED AT {i+1}. iteration.")
            #     print("Expected:")
            #     print(expected_output)
            #     print("Got:")
            #     print(process.stdout)
        if(num_passed != number_of_iteration):
            print("Expected:")
            print(expected_output)
            print("Got:")
            print(process.stdout)
            print(f"{num_passed} out of {number_of_iteration} trials passed for test {j+1}.")
        else:
            print("OK.")
            test_passed += 1

    if(test_passed == n):
        print("PASS ALL THE TESTS!")
    else:
        print(f"{test_passed}/{n} PASS")
    

if __name__ == '__main__' :
    n = 25
    matrices.generate_test_cases(n)
    run(n)


