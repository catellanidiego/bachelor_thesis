import pandas as pd
import numpy as np
from scipy.signal import find_peaks

def valida_dati_tracker(file_csv, R_teorico=0.08):
    print(f"=== ANALISI VALIDAZIONE TRACKER: {file_csv} ===\n")
    
    # 1. Lettura dati
    try:
        df = pd.read_csv(file_csv, sep=',', decimal='.', skiprows=2, names=['t', 'x', 'y'])
    except Exception as e:
        print(f"Errore nella lettura del CSV: {e}")
        return

    t = df['t'].values
    x = df['x'].values
    y = df['y'].values
    
    # 2. Controllo Duplicati
    duplicati = np.sum((np.diff(x) == 0) & (np.diff(y) == 0))
    if duplicati > 0:
        print(f"⚠️ TROVATI {duplicati} FRAME DUPLICATI.")
        print("   Tracker ha esportato frame identici consecutivi. Questo rompe le disuguaglianze strette (>) nella ricerca dei massimi.")
    else:
        print("✅ Nessun frame duplicato rilevato.")

    # 3. Controllo Offset Origine
    y_min = np.min(y)
    if abs(y_min) > 0.001: 
        # Il format {:+.2f} forza sempre la stampa di + o -
        print(f"⚠️ OFFSET ORIGINE ERRATO: Il punto più basso si trova a y = {y_min*1000:+.2f} mm.")
        if y_min > 0:
            print("   -> L'origine degli assi su Tracker è troppo in BASSO. (Sposta l'origine verso l'alto)")
        else:
            print("   -> L'origine degli assi su Tracker è troppo in ALTO. (Sposta l'origine verso il basso)")
    else:
        print(f"✅ Offset origine accettabile (y_min = {y_min*1000:+.2f} mm).")

    # 4. Ricerca Massimi Robusta
    dt_medio = np.median(np.diff(t))
    distanza_minima_frame = int(0.2 / dt_medio)
    
    picchi_dx, _ = find_peaks(x, distance=distanza_minima_frame, prominence=0.01)
    picchi_sx, _ = find_peaks(-x, distance=distanza_minima_frame, prominence=0.01)
    
    print(f"\n✅ Trovati {len(picchi_dx)} massimi a destra e {len(picchi_sx)} massimi a sinistra.")
    print(f"   (Cooldown impostato correttamente a {distanza_minima_frame} frame per evitare falsi positivi).")

    # 5. Controllo Inclinazione (Asimmetria Sinistra-Destra)
    y_dx_media = np.mean(y[picchi_dx[:5]]) if len(picchi_dx) >= 5 else np.mean(y[picchi_dx])
    y_sx_media = np.mean(y[picchi_sx[:5]]) if len(picchi_sx) >= 5 else np.mean(y[picchi_sx])
    differenza_y = abs(y_sx_media - y_dx_media)
    
    if differenza_y > 0.001: 
        print(f"⚠️ POSSIBILE INCLINAZIONE ASSE Y: Differenza di quota tra picchi sx e dx = {differenza_y*1000:.2f} mm.")
        if y_dx_media > y_sx_media:
            print("   -> Il lato DESTRO è più in alto di quello sinistro. (Ruota l'asse su Tracker)")
        else:
            print("   -> Il lato SINISTRO è più in alto di quello destro. (Ruota l'asse su Tracker)")
    else:
        print(f"✅ Allineamento orizzontale accettabile (Differenza quote sx-dx: {differenza_y*1000:.2f} mm).")

    # 6. Controllo Calibrazione Scala 
    punti_fondo = df[df['y'] < 0.02].copy()
    if len(punti_fondo) > 10:
        fit = np.polyfit(punti_fondo['x'], punti_fondo['y'], 2)
        a = fit[0]
        R_stimato = 1 / (8 * a)
        errore_scala = abs(R_stimato - R_teorico) / R_teorico * 100
        
        if errore_scala > 3.0: 
            print(f"⚠️ ERRORE DI SCALA (BASTONE DI CALIBRAZIONE): R stimato dalla traiettoria = {R_stimato:.4f} m (Atteso: {R_teorico} m).")
            print(f"   Errore del {errore_scala:.1f}%. Controlla la lunghezza del segmento di calibrazione su Tracker.")
        else:
            print(f"✅ Calibrazione scala coerente (R stimato = {R_stimato:.4f} m, errore {errore_scala:.1f}%).")

valida_dati_tracker("../csv/prova_C_small.csv", R_teorico=0.08)