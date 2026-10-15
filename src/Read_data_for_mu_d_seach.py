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
        dt_average = sum([t[i+1]-t[i] for i in range(len(t)-1)]) / (len(t)-1)
        T_0 = 4 *math.pi*math.sqrt(R/g)
        time_between_inversions = 0.5 * T_0
        cooldown_frames = int(time_between_inversions*0.75/dt_average)
        inversions = []
        cooldown_remaining = 0
        prominence_threshold = 0.01
        current_max_y = -float('inf')
        current_max_index = -1
        for i in range(len(y)):
            if cooldown_remaining > 0:
                cooldown_remaining -= 1
                current_max_y = y[i]
                current_max_index = i
                continue
            if y[i] > current_max_y:
                current_max_y = y[i]
                current_max_index = i 

            elif current_max_y - y[i] > prominence_threshold:
                inversions.append(current_max_index)
                cooldown_remaining = cooldown_frames

        if len(inversions) > 0:
            first_inversion_index = inversions[0]
            last_index = inversions[-1]
            y_first_inversion = y[first_inversion_index]
            s_1 = math.sqrt(8*R*y_first_inversion)
            initial_energy = m*g*y_first_inversion
            t_last_inversion = t[last_index]
            energy_last_inversion = m*g*y[last_index]
            number_of_periods = (len(inversions)-1)/2
            print(f"Number of periods: {number_of_periods}")
            print(f"Initial curvilinear abscissa: {s_1}")
            print(f"Initial energy: {initial_energy} J")
            print(f"Final energy: {energy_last_inversion} J")
if __name__ == "__main__":
    main()