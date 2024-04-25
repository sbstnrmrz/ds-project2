import random

with open("telefonos.txt", "w") as file:
    prefijos = ["414", "424", "416", "426", "412", "276", "212"]
    for _ in range(70):
        pre = random.choice(prefijos)
        file.write(str(pre) + str(random.randint(1000000, 9999999)) + "\n")

print("70 telefonos en telefonos.txt")
