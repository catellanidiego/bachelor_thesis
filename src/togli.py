import pandas as pd
import numpy as np
from scipy.signal import find_peaks
import matplotlib.pyplot as plt

def valida_dati_tracker(file_csv, R_teorico=0.08):
    print(f"=== ANALISI VALIDAZIONE TRACKER: {file_csv} ===\n")
    
    # 1. Lettura dati (assumendo colonne 't', 'x', 'y' standard di Tracker)
    try:
        # Adatta il separatore o le righe da saltare in base al tuo output di Tracker
        df = pd.read_csv(file_csv, sep=',', decimal='.', skiprows=2, names=['t', 'x', 'y'])
    except Exception as e:
        print(f"Errore nella lettura del CSV: {e}")
        return

    t = df['t'].values
    x = df['x'].values
    y = df['y'].values
    
    # 2. Controllo Duplicati (Frame doppi di Tracker)
    duplicati = np.sum((np.diff(x) == 0) & (np.diff(y) == 0))
    if duplicati > 0:
        print(f"⚠️ TROVATI {duplicati} FRAME DUPLICATI.")
        print("   Tracker ha esportato frame identici consecutivi. Questo rompe le disuguaglianze strette (>) nella ricerca dei massimi.")
    else:
        print("✅ Nessun frame duplicato rilevato.")

    # 3. Controllo Offset Origine (Quota y misurata dal fondo)
    y_min = np.min(y)
    if abs(y_min) > 0.001: # Tolleranza di 1 mm
        print(f"⚠️ OFFSET ORIGINE ERRATO: Il punto più basso si trova a y = {y_min*1000:.2f} mm.")
        print("   L'origine degli assi in Tracker non è allineata con il fondo esatto della cicloide.")
    else:
        print(f"✅ Offset origine accettabile (y_min = {y_min*1000:.2f} mm).")

    # 4. Ricerca Massimi Robusta (Evita i falsi positivi da rumore)
    # Calcoliamo la distanza temporale media per frame
    dt_medio = np.median(np.diff(t))
    # Un periodo è circa T0 = 2*pi*sqrt(4R/g) (per la cicloide) ~ 0.56 s
    # Una mezza oscillazione dura circa 0.28 s. Impostiamo una distanza minima di 0.2 s (cooldown)
    distanza_minima_frame = int(0.2 / dt_medio)
    
    # Troviamo i picchi (inversioni) basandoci sulla coordinata x
    picchi_dx, _ = find_peaks(x, distance=distanza_minima_frame, prominence=0.01)
    picchi_sx, _ = find_peaks(-x, distance=distanza_minima_frame, prominence=0.01)
    
    print(f"\n✅ Trovati {len(picchi_dx)} massimi a destra e {len(picchi_sx)} massimi a sinistra.")
    print(f"   (Cooldown impostato correttamente a {distanza_minima_frame} frame per evitare falsi positivi).")

    # 5. Controllo Inclinazione (Asimmetria Sinistra-Destra)
    # Confrontiamo le quote y dei picchi a destra e a sinistra per vedere se c'è un tilt
    y_dx_media = np.mean(y[picchi_dx[:5]]) if len(picchi_dx) >= 5 else np.mean(y[picchi_dx])
    y_sx_media = np.mean(y[picchi_sx[:5]]) if len(picchi_sx) >= 5 else np.mean(y[picchi_sx])
    differenza_y = abs(y_sx_media - y_dx_media)
    
    if differenza_y > 0.001: # Se la differenza supera 1 mm
        print(f"⚠️ POSSIBILE INCLINAZIONE ASSE Y: Differenza di quota tra picchi sx e dx = {differenza_y*1000:.2f} mm.")
        print("   In un sistema reale, la sfera non può salire più in alto del lato precedente. L'asse di Tracker è storto o la telecamera non era in bolla.")
    else:
        print(f"✅ Allineamento orizzontale accettabile (Differenza quote sx-dx: {differenza_y*1000:.2f} mm).")

    # 6. Controllo Calibrazione Scala (Stima del raggio R)
    # Vicino al fondo, la cicloide è approssimabile a una parabola y = x^2 / (8R)
    # Prendiamo i punti vicino al fondo (es. y < 2 cm)
    punti_fondo = df[df['y'] < 0.02].copy()
    if len(punti_fondo) > 10:
        # Fit parabolico: y = a * x^2 + b*x + c
        fit = np.polyfit(punti_fondo['x'], punti_fondo['y'], 2)
        a = fit[0]
        R_stimato = 1 / (8 * a)
        errore_scala = abs(R_stimato - R_teorico) / R_teorico * 100
        
        if errore_scala > 3.0: # Errore superiore al 3%
            print(f"⚠️ ERRORE DI SCALA (BASTONE DI CALIBRAZIONE): R stimato dalla traiettoria = {R_stimato:.4f} m (Atteso: {R_teorico} m).")
            print(f"   Errore del {errore_scala:.1f}%. Controlla la lunghezza del segmento di calibrazione su Tracker.")
        else:
            print(f"✅ Calibrazione scala coerente (R stimato = {R_stimato:.4f} m, errore {errore_scala:.1f}%).")

    # Plot diagnostico
    plt.figure(figsize=(10, 5))
    plt.plot(t, x, label='Posizione x(t)', alpha=0.7)
    plt.plot(t[picchi_dx], x[picchi_dx], "o", color='red', label='Picchi Destri Rilevati')
    plt.plot(t[picchi_sx], x[picchi_sx], "x", color='green', label='Picchi Sinistri Rilevati')
    plt.title("Validazione Rilevamento Periodi (Tracker)")
    plt.xlabel("Tempo (s)")
    plt.ylabel("Posizione X (m)")
    plt.legend()
    plt.grid(True)
    plt.show()


valida_dati_tracker("../csv/Data_cycloidal_pendulum.csv", R_teorico=0.08)