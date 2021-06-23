import csv
import sys


# Check the arguments
if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")

# Load the profiles
profiles = []
with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)
    for line in reader:
        for key in line:
            if key != "name":
                line[key] = int(line[key])
        profiles.append(line)

# Load the STRs
with open(sys.argv[1], "r") as file:
    strs = {seq: 0 for seq in file.readline().strip().split(",")[1:]}
strs["name"] = "John Doe"

# Load the DNA sequence
with open(sys.argv[2], "r") as file:
    sequence = file.read().strip()

# Calculate the longest STRs
for key in strs:
    if key != "name":
        while key * (strs[key] + 1) in sequence:
            strs[key] += 1

# Check against each person
for possible_match in profiles:
    strs["name"] = possible_match["name"]
    if strs == possible_match:
        print(strs["name"])
        sys.exit()
print("No match")