import random

# Define a list of first names
print("PUPUPUPU")

first_names = [
    "Emma", "Liam", "Olivia", "Noah", "Ava", "William", "Sophia", "James", 
    "Isabella", "Mason", "Mia", "Ethan", "Charlotte", "Oliver", "Emily", 
    "Alexander", "Avery", "Henry", "Harper", "Jackson",
    "Aaliyah", "Lucas", "Evelyn", "Jack", "Grace", "Logan", "Chloe", 
    "Theodore", "Violet", "Elijah",
    "Lily", "Benjamin", "Addison", "Wyatt", "Eleanor", "Leo", "Sophia", 
    "Sebastian", "Anna", "Carter",
    "Isla", "Xavier", "Penelope", "Jayden", "Stella", "Asher", "Layla", "Ezra", 
    "Lucy", "Connor",
    "Riley", "Roman", "Nova", "Owen", "Claire", "Graham", "Zoe", "Jasper", 
    "Audrey", "Brooks",
    "Avery", "Malcolm", "Eleanor", "Jameson", "Sadie", "Mateo", "Wyatt", 
    "Charlie", "Everly", "Jude",
    "Aaliyah", "Josiah", "Scarlett", "Declan", "Hailey", "Levi", "Layla", 
    "Waylon", "Nora", "Oliver",
    "Eliana", "Gabriel", "Violet", "Atticus", "Mia", "Julian", "Quinn", "Evie", 
    "Jaxon", "Camden",
    "Adeline", "Jack", "Hazel", "Wesley", "Nyla", "Henry", "Paisley", "Caleb", 
    "Ryan", "Brooks",
]

# Define a list of last names
last_names = [
    "Smith", "Johnson", "Williams", "Brown", "Jones", "Miller", "Davis", 
    "Garcia", "Martinez", "Anderson",
    "Taylor", "Thomas", "Moore", "Jackson", "Turner", "Campbell", "Parker", 
    "Evans", "Edwards", "Collins",
    "Walker", "Perry", "Freeman", "Lewis", "Mitchell", "Rogers", "Flores", 
    "Cooper", "Carter", "Russell",
    "Howard", "Morgan", "Stewart", "Scott", "Peterson", "Hansen", "Murphy", 
    "Lopez", "Bailey", "Mitchell",
    "Perez", "Martin", "Anthony", "Griffin", "Alexander", "Cook", "Barnes", 
    "Morris", "Webb", "Richards",
    "Kelly", "Bryant", "Fisher", "Gray", "Lewis", "Ramirez", "Cruz", 
    "Washington", "Walker", "Sanders",
    "Lawrence", "Nelson", "Edwards", "Curtis", "Mitchell", "Hudson", "Clark", 
    "Kennedy", "Harrison",
    "Reed", "Montgomery", "Bailey", "Jefferson", "Evans", "Parker", "Campbell", 
    "Miller", "Dixon", "Carter",
    "Hawkins", "Harrison", "Bell", "Walker", "Howard", "Russell", "Morgan", 
    "Perry", "Cooper", "Myers",
]

# Generate 70 random names and write them to a text file
with open("names.txt", "w") as file:
    for _ in range(70):
        first_name = random.choice(first_names)
        last_name = random.choice(last_names)
        full_name = f"{first_name} {last_name}"
        file.write(full_name + "\n")

print("70 random names have been written to names.txt")
