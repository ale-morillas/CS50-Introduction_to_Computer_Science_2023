import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    cumulative = {}

    for value in reader:
        state = str(value["state"])
        cases = int(value["cases"])

        if state not in cumulative:
            cumulative[state] = []

        cumulative[state].append(cases)

    for state, cases in cumulative.items():
        if state not in new_cases:
            new_cases[state] = []
            new_cases[state].append(cases[0])

        for i in range(1, len(cases)):
            diff = cases[i] - cases[i - 1]
            new_cases[state].append(diff)

    return new_cases

# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        values = new_cases[state]
        avgs = list()
        summ = 0
        start = 0
        stop = 7
        end = len(values)

        while stop <= end:
            summ = sum(values[start: stop + 1])
            avg = int(summ / 7)
            avgs.append(avg)
            start += 1
            stop += 1

        size = len(avgs)
        inc = (avgs[size - 1] - avgs[size - 2]) / avgs[size - 1]
        print(f"{state} had a 7-day average of {avg} and an increase of {inc:.2f}%.")


main()
