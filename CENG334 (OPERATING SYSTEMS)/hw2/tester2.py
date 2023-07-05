import subprocess

expected_output = "108 110 122 \n223 242 245 \n363 366 387 \n477 502 531 \n"
num_passed = 0

number_of_iteration = 10000

with open("input_example.txt", "r") as f:
    input_data = f.read()

for i in range(number_of_iteration):
    print("\rCounter: {}".format(i+1), end="")
    process = subprocess.run("./hw2", input=input_data, capture_output=True, text=True)
    if process.stdout == expected_output:
        num_passed += 1
    else:
        print(f"FAILED AT {i+1}. iteration.")
        print("Expected:")
        print(expected_output)
        print("Got:")
        print(process.stdout)

print()
print(f"{num_passed} out of {number_of_iteration} tests passed.")
