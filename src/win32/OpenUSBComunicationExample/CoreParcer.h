#pragma once
#include "ParcerBaseTokenActionProvider.h"
#include <string>
class CoreParcer
{
public:
	CoreParcer(void);
	~CoreParcer(void);
    void SetDelimetr(string Deilmetr);
    void SetDelimetr(const char* Deilmetr);

    void  LoadData(char** Data,int CountStrings);
    void  LoadData(char* Data);
    void AddToken(ParcerBaseTokenActionProvider* _Token);
    CoreParcer& operator+=(ParcerBaseTokenActionProvider* _Token);
    void ProcessData(void);
    ParcerBaseTokenActionProvider* GetActionProvider(const char* Token);
    ParcerBaseTokenActionProvider* GetActionProvider(string Token);
      
   private:
   string _Delimetr;
   vector<ParcerBaseTokenActionProvider*> _TokenActionList;
   uint64_t _NumberarcedKey;
   vector<string> _DataForProcesing;
   string ParcebleData;
   int      _Argc;
};

