#!../../bin/darwin-aarch64/sysmon
< envPaths
dbLoadDatabase "../../dbd/sysmon.dbd"
sysmon_registerRecordDeviceDriver pdbbase
dbLoadRecords "../../sysmonApp/Db/sysmon.db"
iocInit
