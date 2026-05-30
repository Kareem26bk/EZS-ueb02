#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#include <errlog.h>
#include <stdlib.h>

static long sysmonInit(aSubRecord *prec) {
    return 0;
}

static long sysmonProcess(aSubRecord *prec) {
    double loadavg[3] = {0.0, 0.0, 0.0};
    getloadavg(loadavg, 3);
    *(double *)prec->vala = loadavg[0];
    *(double *)prec->valb = loadavg[1];
    *(double *)prec->valc = loadavg[2];

    long ncpu = sysconf(_SC_NPROCESSORS_ONLN);
    *(epicsInt32 *)prec->vald = (epicsInt32)ncpu;

    uint64_t memsize = 0;
    size_t len = sizeof(memsize);
    if (sysctlbyname("hw.memsize", &memsize, &len, NULL, 0) != 0) {
        epicsPrintf("Error: sysctlbyname failed for hw.memsize\n");
    } else {
        *(double *)prec->vale = (double)memsize / (1024.0 * 1024.0 * 1024.0);
    }

    struct timeval boottime = {0, 0};
    len = sizeof(boottime);
    if (sysctlbyname("kern.boottime", &boottime, &len, NULL, 0) != 0) {
        epicsPrintf("Error: sysctlbyname failed for kern.boottime\n");
    } else {
        struct timeval now;
        gettimeofday(&now, NULL);
        *(double *)prec->valf = (double)(now.tv_sec - boottime.tv_sec);
    }

    return 0;
}

epicsRegisterFunction(sysmonInit);
epicsRegisterFunction(sysmonProcess);
