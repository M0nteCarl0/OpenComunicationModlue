#pragma once
#include <string>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <bitset>
using namespace std;
class ParcerBaseTokenActionProvider
{
public:
	ParcerBaseTokenActionProvider(void);
	~ParcerBaseTokenActionProvider(void);
	virtual void Parce(void) = 0;
	virtual void Default(void) = 0;
    virtual void Trace(void) = 0;

    void ParcingData(void);
    void LoadData(char** _ParcebleStrings,int Argc,bool StringCapsule = false);
    void LoadData(vector<string> _ParcebleStrings);
	void LoadData(string _ParcebleStrings);
    void SetKey(string Key);
    void SetKey(const char* Key);
    string GetKey(void);
    bool FindKey(void);
    bool CheckArgIsParced(int Postion);
    uint64_t GetPositionKey(void);
    vector<string> GetParcebleData(void);
    bool  IsParced(void);
    void SetParced(void);
    void ReserParced(void);
    const char* GetFirsrtArgz(void);
    const char* GetNexttArgz(void);
    bool IsChildren(void);
	bool IsTokenDestroyed(void);
    uint64_t GetPositionInParsedSequnce(void);
private:
    void  ResetPositionInParsedSequnce(void);
    string   _Key;
    vector<string> _ParcebleData;
	string _ParcebleDataS;
    bool     _Parced;
    bool    _IsChild;
	bool    _IsTokenDestroyed;
    uint64_t _NumberWordForParce;
    uint64_t _PositionKey;
    uint64_t _PositionInParsedSequnce;
    uint64_t _PositionLastWord;
	uint64_t _ArgumentID;    
    bitset<128> _AgsCheckList;
};

