#include "HiRessTimeMeasure.h"
static unsigned long long TimerHandlers = 0;
/******************************************************************************/
HiRessTimeMeasure::HiRessTimeMeasure(void):
	 _Sec(0),
	 _Milisec(0)
{
    QueryPerformanceFrequency(&_Freq);
	CalibrateTSC();
    TickInterval = 1/(double)_Freq.QuadPart;
	TimerHandlers++;
}
/******************************************************************************/

HiRessTimeMeasure::~HiRessTimeMeasure(void)
{
	if(TimerHandlers != 0)
	{
	TimerHandlers--;
	}
}
/******************************************************************************/
inline void HiRessTimeMeasure::  StartCPUCycles(void)
 {
  
 rdtscBegin = __rdtsc();
   


 }
/******************************************************************************/

inline void HiRessTimeMeasure:: Start(void)
{   
	QueryPerformanceCounter(&_Begin);

}
/******************************************************************************/
inline void HiRessTimeMeasure::End(void)
{
	QueryPerformanceCounter(&_End);
	_Total.QuadPart = _End.QuadPart -  _Begin.QuadPart;
}
/******************************************************************************/
inline void   HiRessTimeMeasure:: EndCPUCycles(void)
{
  rdtscEnd = __rdtsc();
   
}
/******************************************************************************/
double HiRessTimeMeasure::GetEllapsedSeconds(void)
{
	_Sec =(DOUBLE) _Total.QuadPart/_Freq.QuadPart;
	return _Sec;
}
/******************************************************************************/
	double HiRessTimeMeasure::GetEllapsedMiliseconds(void)
{
	_Milisec = (DOUBLE)(_Total.QuadPart*1000)/_Freq.QuadPart;
	return _Milisec;
}
/******************************************************************************/
inline DWORD64 HiRessTimeMeasure:: GetEllapsedCPUCycles(void)
 {
   rdtsTotal = (rdtscEnd - rdtscBegin) ;
   return  rdtsTotal;

 }
 /******************************************************************************/
double HiRessTimeMeasure::GetEllapsedMicroseconds(void)
{
	_Microsec =(DOUBLE) (_Total.QuadPart*1000000)/_Freq.QuadPart;
	return _Microsec;
}
/******************************************************************************/
unsigned long long HiRessTimeMeasure::GetTotalCountHandles(void)
{
	return TimerHandlers;
}
/******************************************************************************/
 DWORD HiRessTimeMeasure:: GetCPUFrequncyOnFly(void)
 {

 return 0;
 }
/******************************************************************************/
 void  HiRessTimeMeasure::CalibrateTSC(void)
{

HANDLE Process = GetCurrentProcess();
DWORD AffinityMask = 0x1;
SetProcessAffinityMask(Process,AffinityMask);
DWORD64 CyCB = __rdtsc();
StartCPUCycles();
rdtscCallOverheadCycles = __rdtsc() - CyCB;
StartCPUCycles();
Sleep(1000);
EndCPUCycles();
double Cyc= GetEllapsedCPUCycles();
rdtscimeNsPerCycle = 1000000000/Cyc;
rdtscFrequencyMhz = Cyc/1000000;
SetProcessAffinityMask(Process,0xff);
}
 /******************************************************************************/
 double  HiRessTimeMeasure::GetEllapsedNanoseconds(void)
 {
	 return (double)GetEllapsedCPUCycles() * rdtscimeNsPerCycle;
 }
 /******************************************************************************/