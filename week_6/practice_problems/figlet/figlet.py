from sys import argv, exit
from pyfiglet import Figlet
import random

figlet = Figlet()
fonts = figlet.getFonts()
s = input("Input: ")

try:
    if len(argv) == 1:
        f = random.choice(fonts)
        figlet.setFont(font=f)
        print(figlet.renderText(s))

    elif argv[1] in ['-f', '--font']:
        figlet.setFont(font=argv[2])
        print(figlet.renderText(s))
    else:
        exit("Invalid usage")
except:
    exit("Invalid usage")





