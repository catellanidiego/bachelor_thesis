def main():
    import matplotlib.pyplot as plt
    import csv
    with open("../csv/Data_for_comparison.csv","r") as infile:
        reader = csv.reader(infile)
        next(reader)
        next(reader)
        data = list(reader)
        t = []
        h = []
        for row in data:
            t.append(float(row[0]))
            h.append(float(row[1]))

    plt.plot(t, h)
    plt.xlabel("Time")
    plt.ylabel("Height")
    plt.show()

if __name__ == "__main__":
    main()