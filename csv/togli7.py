import pandas as pd
import numpy as np
import glob
import os

def get_first_period(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            if ',' not in f.readline() and ',' not in f.readline():
                return None
        df = pd.read_csv(file_path, skiprows=1) 
    except Exception:
        return None
        
    df.columns = df.columns.str.strip()
    if 't' not in df.columns or 'x' not in df.columns:
        return None

    t, x = df['t'].values, df['x'].values
    crossings = np.where(np.diff(np.sign(x)))[0]
    
    exact_times = []
    for i in crossings:
        t1, t2, x1, x2 = t[i], t[i+1], x[i], x[i+1]
        if x2 != x1:
            exact_times.append(t1 - x1 * (t2 - t1) / (x2 - x1))
            
    if len(exact_times) >= 3:
        return exact_times[2] - exact_times[0]
    return None

cartella_csv = "./"
prefissi = ('S_big', 'S_small', 'C_big', 'C_small')
tutti_i_file = glob.glob(os.path.join(cartella_csv, "*.csv"))

files_da_processare = [f for f in tutti_i_file if os.path.basename(f).startswith(prefissi)]
risultati = {prefisso: [] for prefisso in prefissi}

print("--- Dettaglio per singolo file ---")
for file in files_da_processare:
    nome_file = os.path.basename(file)
    T = get_first_period(file)
    
    if isinstance(T, float):
        print(f"{nome_file}: {T:.5f} s")
        for prefisso in prefissi:
            if nome_file.startswith(prefisso):
                risultati[prefisso].append(T)
                break
    else:
        print(f"{nome_file}: Errore o dati insufficienti")

medie_calcolate = {}
for prefisso, valori in risultati.items():
    if valori:
        medie_calcolate[prefisso] = np.mean(valori)

print("\n--- Periodi medi per ogni Dataset ---")
for prefisso in prefissi:
    if prefisso in medie_calcolate:
        print(f"{prefisso}: {medie_calcolate[prefisso]:.5f} s")

print("\n--- Analisi dell'Isocronismo (Scarti) ---")
if 'S_big' in medie_calcolate and 'S_small' in medie_calcolate:
    diff_S = abs(medie_calcolate['S_big'] - medie_calcolate['S_small'])
    print(f"Scarto Pendolo Semplice (Big vs Small): {diff_S:.5f} s")

if 'C_big' in medie_calcolate and 'C_small' in medie_calcolate:
    diff_C = abs(medie_calcolate['C_big'] - medie_calcolate['C_small'])
    print(f"Scarto Pendolo Cicloidale (Big vs Small): {diff_C:.5f} s")