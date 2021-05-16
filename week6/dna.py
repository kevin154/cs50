from sys import argv
import csv


def countMaxSequence(data, pattern):

    maxSeq = 0
    currSeq = 0 
    patternLength = len(pattern)

    i = 0
    # Iterate across the DNA data
    while i < len(data):
        subStr = data[i:i+patternLength]
        # Check substring matches mattern
        if subStr == pattern:
            currSeq += 1
            # If a pattern match jump forward to check next pattern
            i += patternLength
        else:
            # No match record longest sequence and move forward to next
            maxSeq = max(maxSeq, currSeq)
            currSeq = 0
            i += 1
    return maxSeq


# Check command line, ensure three inputs
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# Process names csv
with open(argv[1], mode='r') as namesFile:
    reader = csv.DictReader(namesFile)

    # List of DNA sequences we are interested in
    sequences = reader.fieldnames[1:]
    d = []
    for row in reader:
        d.append(row)
        
# Process DNA sequence file
with open(argv[2], mode='r') as seqFile:
    dnaData = seqFile.read()


# Map sequences to their respective counts 
countMap = {k: countMaxSequence(dnaData, k) for k in sequences}

# Check each sequence vs expected sequence for each person
for i in range(len(d)):
    iter = 0
    for k in countMap.keys():
        if int(d[i][k]) == countMap[k]:
            iter += 1
    # If have a perfect match then print the name
    if iter == len(countMap):
        print(d[i]['name'])  
        exit(0)

# Else if no matches then invalid
print('No match')
