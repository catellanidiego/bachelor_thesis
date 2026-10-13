def main():
    import matplotlib.pyplot as plt
    import csv
    with open("../csv/CSV_theta_omega.csv", "r") as file:
        data = csv.reader(file)
        theta = []
        omega = []
        for row in data:
            theta.append(float(row[0]))
            omega.append(float(row[1]))
        plt.plot(theta, omega)
        plt.xlabel("Theta")
        plt.ylabel("Omega")
        plt.grid(True)
        plt.show()

main()