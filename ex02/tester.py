import subprocess
import random

def is_sorted(numbers):
	return all(numbers[i] <= numbers[i + 1] for i in range(len(numbers) - 1))

def main():
	num_elements = int(input("How many elements do you want to sort? "))

	numbers = random.sample(range(1, 10001), num_elements)
	print(f"Unsorted list: {numbers}")
	command = ["./PmergeMe"]  + list(map(str, numbers))
	result = subprocess.run(command, capture_output=True, text=True)
	output = result.stdout
	print ("Output from PmergeMe: ", result.stdout)

	for line in output.splitlines():
		if line.startswith("Vector After:"):
			vector_after = list(map(int, line.split(":")[1].strip().split()))
			if is_sorted(vector_after):
				print("Vector After is sorted.")
			else:
				print("Vector After is not sorted.")
		elif line.startswith("Deque After:"):
			deque_after = list(map(int, line.split(":")[1].strip().split()))
			if is_sorted(deque_after):
				print("Deque After is sorted.")
			else:
				print("Deque After is not sorted.")

if __name__ == "__main__":
	main()
