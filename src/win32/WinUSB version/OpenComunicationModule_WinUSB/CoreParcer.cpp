#include "CoreParcer.h"

CoreParcer::CoreParcer(void)
{
}

CoreParcer::~CoreParcer(void)
{
	_TokenActionList.clear();
	_DataForProcesing.clear();
}

 void CoreParcer:: ProcessData(void)
 {
 string _TokenWithDelim;
 string _OriginalToken;
     if(_TokenActionList.size()!=0)
     {
         for(uint64_t i = 0; i< _TokenActionList.size();i++)
         {
             _OriginalToken = _TokenActionList[i]->GetKey();
             _TokenWithDelim=  _Delimetr + _OriginalToken; 
             _TokenActionList[i]->SetKey(_TokenWithDelim);
             _TokenActionList[i]->LoadData(_DataForProcesing);
             _TokenActionList[i]->ParcingData();
             _TokenActionList[i]->SetKey(_OriginalToken);
			 _TokenWithDelim.clear();
             
         }
    
     }
    
 }
 
 ParcerBaseTokenActionProvider* CoreParcer:: GetActionProvider( const char* Token)
 {
    return   GetActionProvider(string( Token));
 }
 
  ParcerBaseTokenActionProvider* CoreParcer:: GetActionProvider(string Token)
 {
  uint64_t Postion;
  if( _TokenActionList.size()!=0)
     {
         for(uint64_t i = 0; i< _TokenActionList.size();i++)
         {
             if(Token  == _TokenActionList[i]->GetKey())
             {
                Postion = i;
                break;
             }
         }
    
     }
    return  _TokenActionList[Postion];
 }
 
void   CoreParcer:: LoadData(char** Data,int CountStrings)
{
   
	for(uint64_t i = 0; i<CountStrings;i++)
    {
		ParcebleData.append (Data[i]);
    }

}


void   CoreParcer:: LoadData(char* Data)
{
}

void CoreParcer:: SetDelimetr(string Deilmetr)
{
    _Delimetr = Deilmetr;

}

void CoreParcer::  SetDelimetr(const char* Deilmetr)
{
    SetDelimetr(string(Deilmetr));
}

void CoreParcer::  AddToken(ParcerBaseTokenActionProvider* _Token)
{
  _TokenActionList.push_back(_Token);
}

 CoreParcer&  CoreParcer:: operator+=(ParcerBaseTokenActionProvider* _Token)
 {
    this->AddToken(_Token);
    return *this;
 }
 




 