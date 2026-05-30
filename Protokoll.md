# Messprotokoll: EPICS aSub-Record & SCAN
**Modul:** Echtzeitsysteme (HA2)  
**Student:** [Abdulkareem Al-Kubati / 109694]  
**Hochschule:** BHT   

---

## 1. Ziel und Implementierung
Ziel der Übung war die Implementierung eines EPICS-IOC unter macOS, der Systemgrößen (CPU-Last, RAM, Uptime) ausliest und als Channel-Access-PVs bereitstellt. Dafür wurden native C-Funktionen (`getloadavg`, `sysctlbyname`) in einer `aSub`-Record-Subroutine verknüpft. Die periodische Aktualisierung erfolgt alle 2 Sekunden über das `SCAN`-Feld.

## 2. Auswertung des SCAN-Verhaltens und Jitter (P4)
Die aufgezeichneten Messdaten belegen eine periodische Aktualisierung der PVs (`SYS:UPTIME`, `SYS:LOAD1`). Die mittlere Periode beträgt exakt 2 Sekunden, entsprechend der Konfiguration `field(SCAN, "2 second")`.

Dabei treten minimale Abweichungen (Jitter) im Millisekundenbereich auf. Die Ursachen hierfür sind:
* **Scheduler-Jitter:** macOS ist kein hartes Echtzeitsystem (Hard Real-Time OS). Der Betriebssystem-Scheduler weist dem internen EPICS-Timer keine absolute Priorität zu.
* **CA-Overhead (Netzwerklatenz):** Die Datenübertragung vom IOC zum Client über das Channel Access (CA) Protokoll erzeugt zusätzliche Netzwerklatenzen.

> **Anmerkung:** Die während der Messung aufgetretene Warnung *"Identical process variable names on multiple servers"* demonstriert erfolgreich die Broadcast-Natur von EPICS, da andere IOCs im Labornetzwerk zeitgleich dieselben PV-Namen publizierten.

## 3. SCAN Passive vs. Periodic (Bonus B1)
* **Periodic (2 second):** Der interne Timer triggert den `aSub`-Record automatisch alle 2 Sekunden (ideal für kontinuierliches Monitoring).
* **Passive:** Der Record aktualisiert die Werte nur bei einem externen Event. Dies wurde erfolgreich mit dem Befehl `caput SYS:STATS.PROC 1` im Terminal getestet. Diese Methode eignet sich für On-Demand-Abfragen, um Systemressourcen zu schonen.

## 4. Analyse der Messdaten

```bash
SYS:LOAD1                      2026-05-22 11:54:28.347007 0.810059
SYS:UPTIME                     2026-05-22 11:54:28.347020 75057
SYS:LOAD1                      2026-05-22 11:54:30.345291 0.825195
SYS:UPTIME                     2026-05-22 11:54:30.345328 75059
SYS:UPTIME                     2026-05-22 11:54:32.346865 75061
SYS:LOAD1                      2026-05-22 11:54:34.346811 0.838867
SYS:UPTIME                     2026-05-22 11:54:34.346849 75063
SYS:UPTIME                     2026-05-22 11:54:36.346713 75065
SYS:UPTIME                     2026-05-22 11:54:38.346643 75067
SYS:LOAD1                      2026-05-22 11:54:40.340864 0.771484
SYS:UPTIME                     2026-05-22 11:54:40.340906 75069
SYS:UPTIME                     2026-05-22 11:54:42.346515 75071
SYS:LOAD1                      2026-05-22 11:54:44.340096 0.789551
SYS:UPTIME                     2026-05-22 11:54:44.340137 75073
