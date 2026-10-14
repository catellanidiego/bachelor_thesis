def main() :
    import math
    import csv
    R = 0.08
    m = 0.08
    g = 9.81
    with open('../csv/Data_cycloidal_pendulum.csv', 'r') as infile:
        reader = csv.reader(infile)
        data = list(reader)
        data = data[2:]
        t = []
        x = []
        y = []
        for row in data:
            t.append(float(row[0]))
            x.append(float(row[1]))
            y.append(float(row[2]))
        inversions_found = 0
        cooldown_remaining = 0
        target_index = -1
        first_inversion_index = -1
        for i in range(1, len(y) -1):
            if cooldown_remaining > 0:
                cooldown_remaining -= 1
                continue
            y_prev = y[i - 1]
            y_curr = y[i]
            y_next = y[i + 1]
            is_maximum = y_prev < y_curr and y_curr > y_next
            if is_maximum:
                inversions_found += 1
                cooldown_remaining = 30

                if inversions_found == 1:
                    first_inversion_index = i
                    s_1 = math.sqrt(8 * R * y_curr)

                if inversions_found == 20:
                    target_index = i
                    break
        if target_index != -1 and first_inversion_index != -1:
            print(f"First inversion has curvilinear abscissa = {s_1}")
            print(f"20th inversion has time = {t[target_index]}, and energy = {m*g*y[target_index]}")
if __name__ == "__main__":
    main()