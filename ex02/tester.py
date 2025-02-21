import subprocess
import random

def main():
	num_elements = int(input("How many elements do you want to sort? "))

	numbers = [random.randint(1, 100000) for _ in range(num_elements)]
	print(f"Unsorted list: {numbers}")

	command = ["./PmergeMe"]  + list(map(str, numbers))
	result = subprocess.run(command, capture_output=True, text=True)
	print ("Output from PmergeMe: ", result.stdout)

if __name__ == "__main__":
	main()
