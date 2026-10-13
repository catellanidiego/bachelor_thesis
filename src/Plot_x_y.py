def main():
    import matplotlib.pyplot as plt
    import csv
    with open("../csv/CSV_x_y.csv", "r") as file:
        data = csv.reader(file)
        t = []
        x = []
        y = []
        for row in data:
            x.append(float(row[0]))
            y.append(float(row[1]))
        plt.plot(x, y)
        plt.xlabel("X")
        plt.ylabel("Y")
        plt.grid(True)
        plt.show()

main()