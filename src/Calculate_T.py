def main():
    import math
    import csv
    t = []
    x = []
    y = []
    R = 0.08
    m = 0.08
    g = 9.81
    with open('../csv/prova.csv', 'r') as file:
        reader = csv.reader(file)
        data = list(reader)
        data = data[2:]
        for row in data:
            t.append(float(row[0]))
            x.append(float(row[1]))
            y.append(float(row[2]))
        dt_average = sum([t[i+1]-t[i] for i in range(len(t)-1)]) / (len(t)-1)
        T_0 = 4*math.pi*math.sqrt(R/g)
        print(T_0)
        time_between_inversions = 0.5*T_0
        cooldown_frames = int(time_between_inversions*0.75/dt_average)
        cooldown_remaining = 0
        prominence_threshold = 0.001
        current_max_y = -float('inf')
        current_max_index = -1
        inversions = []
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
        first_inversion_index = inversions[0]
        last_index = inversions[2]
        t_first_inversion = t[first_inversion_index]
        t_last_inversion = t[last_index]
        Period = t_last_inversion - t_first_inversion
        print(f"Period: {Period} s")
    
if __name__ == "__main__":
    main()