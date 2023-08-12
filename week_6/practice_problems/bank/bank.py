greeting = input("Greeting: ").lower().split(",")

greeting = " ".join(greeting).split()

if greeting[0] == "hello":
    print("$0")
elif greeting[0][0] == "h" and greeting[0] != "hello":
    print("$20")
else:
    print("$100")