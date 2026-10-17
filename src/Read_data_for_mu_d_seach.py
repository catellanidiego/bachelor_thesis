def main() :
    import math
    import csv
    R = 0.08
    m = 0.08
    g = 9.81
    t = []
    x = []
    y = []
    with open('../csv/Data_cycloidal_pendulum.csv', 'r') as infile:
        reader = csv.reader(infile)
        data = list(reader)
        data = data[2:]
        for row in data:
            t.append(float(row[0]))
            x.append(float(row[1]))
            y.append(float(row[2]))

        y_avg = sum(y)/len(y)
        inversions = []
        prominence_threshold = 0.001
        current_max_y = -float('inf')
        peak_found = False
        current_max_index = -1
        for i in range(len(y)):
            if peak_found == False:
                if y[i] > y_avg:
                    if y[i] > current_max_y:
                        current_max_y = y[i]
                        current_max_index = i
                    elif y[i] < current_max_y - prominence_threshold:
                        inversions.append(current_max_index)
                        peak_found = True
            else:
                if y[i] < y_avg:
                    peak_found = False
                    current_max_y = -float('inf')
        if len(inversions) > 0 and len(inversions) % 2 == 0:
           inversions.pop()
        
        if len(inversions) > 0:
            first_inversion_index = inversions[0]
            last_index = inversions[-1]
            y_first_inversion = y[first_inversion_index]
            y_last_inversion = y[last_index]

            s_1 = math.sqrt(8*R*y_first_inversion)
            initial_energy = m*g*y_first_inversion
            energy_last_inversion = m*g*y[last_index]
            number_of_periods = (len(inversions)-1)//2
            print(f"Number of periods: {(number_of_periods)}")
            print(f"Initial curvilinear abscissa: {s_1}")
            print(f"Initial energy: {initial_energy} J")
            print(f"Final energy: {energy_last_inversion} J")
if __name__ == "__main__":
    main()