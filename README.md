# EPICS aSub & SCAN - Übungsaufgabe 2

Dieses Repository enthält die Lösung für die zweite EPICS-Übungsaufgabe im Modul Echtzeitsysteme.

## Projektinhalt:
* **sysmonApp/src/sysmonSub.c**: C-Subroutine zum Auslesen der macOS-Systemdaten (RAM, CPUs, Load, Uptime).
* **sysmonApp/Db/sysmon.db**: EPICS Datenbank mit `aSub`-Record und `Periodic SCAN` Konfiguration.
* **camonitor.log**: Logdatei der Channel-Access-Überwachung (Nachweis für P4).
* **Protokoll.md**: Die vollständige Auswertung und Diskussion der Jitter- und SCAN-Verhalten direkt hier im Repository.
