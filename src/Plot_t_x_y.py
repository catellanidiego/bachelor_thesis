def main():
    import matplotlib.pyplot as plt
    import csv
    with open("../csv/CSV_t_x_y.csv", "r") as file:
        data = csv.reader(file)
        t = []
        x = []
        y = []
        for row in data:
            t.append(float(row[0]))
            x.append(float(row[1]))
            y.append(float(row[2]))
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.plot(t, x, y)
        ax.set_xlabel("Time")
        ax.set_ylabel("X")
        ax.set_zlabel("Y")
        plt.grid(True)
        plt.show()
if __name__ == "__main__":
    main()