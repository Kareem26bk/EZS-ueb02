# EPICS aSub & SCAN - Übungsaufgabe 2

Dieses Repository enthält die Lösung für die zweite EPICS-Übungsaufgabe im Modul Echtzeitsysteme.

## Projektinhalt:
* **sysmonSub.c**: C-Subroutine zum Auslesen der macOS-Systemdaten (RAM, CPUs, Load, Uptime).
* **sysmon.db**: EPICS Datenbank mit `aSub`-Record und `Periodic SCAN` Konfiguration.
* **camonitor.log**: Logdatei der Channel-Access-Überwachung (Nachweis für P4).

Die vollständige Auswertung und Diskussion der Jitter- und SCAN-Verhalten befindet sich im `Protokoll.pdf`, welches separat im Moodle eingereicht wurde.
