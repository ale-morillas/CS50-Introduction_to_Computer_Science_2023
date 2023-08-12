from cs50 import get_int

# Prompt from the user
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break
# Build pyramid
for i in range(1, height + 1):
    for j in range(1, height + 1):
        if i + j <= height:
            print(" ", end="")
        else:
            print("#", end="")
    print()