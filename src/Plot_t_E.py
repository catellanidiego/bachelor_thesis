def main():
    import matplotlib.pyplot as plt
    import csv
    with open("../csv/CSV_E.csv", "r") as file:
        data = csv.reader(file)
        t = []
        E = []
        for row in data:
            t.append(float(row[0]))
            E.append(float(row[1]))
        plt.plot(t, E)
        plt.xlabel("Time")
        plt.ylabel("Energy")
        plt.grid(True)
        plt.show()

if __name__ == "__main__":
    main()