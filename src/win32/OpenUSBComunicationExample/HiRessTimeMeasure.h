#include <Windows.h>
#ifndef _HRTM_
#define _HRTM_
class HiRessTimeMeasure
{
public:
	HiRessTimeMeasure(void);
	~HiRessTimeMeasure(void);
	void CalibrateTSC(void);
	void Start(void);
    void StartCPUCycles(void);
	void End(void);
    void EndCPUCycles(void);
	double GetEllapsedSeconds(void);
	double GetEllapsedMiliseconds(void);
	double GetEllapsedMicroseconds(void);
	double GetEllapsedNanoseconds(void);
    DWORD64 GetEllapsedCPUCycles(void);
	unsigned long long GetTotalCountHandles(void);
    DWORD GetCPUFrequncyOnFly(void);
private:
	double rdtscimeNsPerCycle; 
	double rdtscFrequencyMhz;
	LARGE_INTEGER _Begin;
	LARGE_INTEGER _End;
	LARGE_INTEGER _Total;
	LARGE_INTEGER _Freq;
    DWORD64 rdtscBegin;
	DWORD64 rdtscCallOverheadCycles;
    DWORD64 rdtscEnd;
    DWORD64 rdtsTotal;
	DOUBLE _Sec;
	DOUBLE _Milisec;
	DOUBLE _Microsec;
    double TickInterval;
	unsigned long long TimerID;
};
#endif
