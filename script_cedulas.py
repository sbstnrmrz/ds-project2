import random

with open("cedulas.txt", "w") as file:
    for _ in range(70):
        file.write(str(random.randint(0, 32000000)) + "\n")

print("70 cedulas en cedulas.txt")
