import math
import matplotlib . pyplot as plt
import numpy as np

filep = open("manufacturing_defects.txt", "r")

file_txt = filep.read()

filep.close()

file_lines = file_txt.split('\n')


'''
(a) Give a table how many cases occur for all companies between 2000 and 2019 for each number of defects (#
of Defects).
Hint: When you check the file you will see: # of Defects = {0, 1, 2, 3, 4}.

'''
cases = {}
for curr_line in file_lines:
    line_items = curr_line.split('\t')

    for element in line_items[2:]:
        x = int(element)

        if x in cases:
            cases[x] += 1
        else:
            cases[x] = 1

print("\# of Defects\t|\# of cases in all company between the years")
print(64 * "-")
for case in cases:
    print(case, end='')
    print("\t\t|", end='')
    print(cases[case])


'''
(b) Estimate λ from the given data.
λ = total number of event / total number of cases
λ = total number of defects / total number of cases

'''
total_number_of_defects = 0
total_number_of_cases = 0
for case in cases:
    total_number_of_defects += case * cases[case]
    total_number_of_cases += cases[case]

the_lambda = total_number_of_defects / total_number_of_cases

print(f"Total number of defects is {total_number_of_defects}")
print(f"Total number of cases {total_number_of_cases}")
print(f"Lambda is {the_lambda}")


'''
(c) Update Table 1 in Table 2 with Poisson predicted cases with the estimated λ.

'''
predicted_cases = {}
for case in cases:
    predicted_cases[case] = (((math.e ** (-1 * the_lambda)) * (the_lambda ** case)) / math.factorial(case)) * total_number_of_cases

print("\# of Defects\t|\# of cases in all company between the years\t|Predicted \# of cases in all companies between the years")
print(122 * "-")
for case in cases:
    print(case, end='')
    print("\t\t|", end='')
    print(cases[case], end='')
    print("\t\t\t\t\t\t|", end='')
    print(predicted_cases[case])


'''
(d) Draw a barplot for the actual cases (Table 2 in column 2) and the predicted cases (Table 2 column 3) with
respect to # of defecrs. You should put the figure.

'''
a_range = np.arange(len(cases))

actual_plt = plt.bar(a_range - 0.1, list(cases.values()), 0.2, label='actual', color = '#000000')
predicted_plt = plt.bar(a_range + 0.1, list(predicted_cases.values()), 0.2, label='predicted', color = '#808080')

plt.xlabel("Number of defects")
plt.ylabel("Number of cases")
plt.title("Actual cases and The predicted cases")
plt.xticks(a_range)
plt.legend()
plt.tight_layout()
plt.show()

