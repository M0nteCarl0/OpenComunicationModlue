#include "ParcerBaseTokenActionProvider.h"

/**********************************************************************/
ParcerBaseTokenActionProvider::ParcerBaseTokenActionProvider(void)
{
 _Key  = " ";
 _Parced = false;
 _IsChild = false;
 _AgsCheckList.reset();	
}
/**********************************************************************/
ParcerBaseTokenActionProvider::~ParcerBaseTokenActionProvider(void)
{
}
/**********************************************************************/
 void ParcerBaseTokenActionProvider:: SetKey(string Key)
 {
     _Key = Key;
     _IsChild = true;
	 _IsTokenDestroyed = false;
 }
 /**********************************************************************/
void ParcerBaseTokenActionProvider:: SetKey(const char* Key)
{
    SetKey( string(Key));
}
/**********************************************************************/
bool  ParcerBaseTokenActionProvider:: IsParced(void)
{
    return  _Parced;
}
/**********************************************************************/
void ParcerBaseTokenActionProvider:: SetParced(void)
{
    _Parced = true;
}
/**********************************************************************/
void ParcerBaseTokenActionProvider:: ReserParced(void)
{
    _Parced = false;
}
/**********************************************************************/
 void  ParcerBaseTokenActionProvider::LoadData(vector<string> _ParcebleStrings)
 {
        _ParcebleData =  _ParcebleStrings;
 }

 /**********************************************************************/
void ParcerBaseTokenActionProvider :: LoadData(char** _ParcebleStrings,int Argc,bool StringCapsule)
{
    if(_ParcebleStrings!=NULL)
    {
		if(!StringCapsule)
		{
			 _ParcebleData.clear();
			 _ParcebleData = vector<string>(Argc);       
			 for(uint64_t i = 0;i<Argc;i++)
			 {
			     _ParcebleData[i] = _ParcebleStrings[i];
			 }
		}
		else
		{

			 for(uint64_t i = 0;i<Argc;i++)
			 {
				 _ParcebleDataS.append(_ParcebleStrings[i]);
			 }

		}
    }

}

  /**********************************************************************/
   void ParcerBaseTokenActionProvider:: ParcingData(void)
   {
        ReserParced();
        ResetPositionInParsedSequnce();

        if(FindKey())
        {
            Default();
            Parce();
            Trace();
			SetParced();
           
        }
   }
 /**********************************************************************/
 bool  ParcerBaseTokenActionProvider:: FindKey(void)
 {
    bool Res = false;
    _AgsCheckList.reset();
	if(!_ParcebleData.empty())
	{
   for(uint64_t i = 0;i< _ParcebleData.size();i++)
         {
            if( _ParcebleData[i] ==  _Key)
                {
                   _PositionKey = i;
                   Res = true;
                   break;
                }
   }
	}
	else
	{
		_ParcebleDataS.find(_Key);

	}

        return  Res;
 }
 /**********************************************************************/
 uint64_t  ParcerBaseTokenActionProvider:: GetPositionKey(void)
 {
    return  _PositionKey;
 }
 /**********************************************************************/
 string ParcerBaseTokenActionProvider:: GetKey(void)
 {
 return _Key;
 }
  /**********************************************************************/
 vector<string> ParcerBaseTokenActionProvider:: GetParcebleData(void)
 {
 return _ParcebleData;
 };
 /**********************************************************************/
  const  char*   ParcerBaseTokenActionProvider::GetFirsrtArgz(void)
 {
        _PositionInParsedSequnce = GetPositionKey()+1;
          
          if( _ParcebleData[_PositionInParsedSequnce][0] !=  _ParcebleData[1][0])
          {
          _AgsCheckList.set(0,true);
          return    _ParcebleData[_PositionInParsedSequnce].c_str();
          }
          else

        {
        _AgsCheckList.set(0,false);
        return NULL;
        }
 }
 /**********************************************************************/
 const char*  ParcerBaseTokenActionProvider:: GetNexttArgz(void)
 {

 _PositionInParsedSequnce++;
 uint16_t Position = _PositionInParsedSequnce;
 static bool ControlSymbolFound = false;
 const char* Data = NULL;
    if(  _PositionInParsedSequnce <= _ParcebleData.size() - 1 )
    {
    
    if( _ParcebleData[_PositionInParsedSequnce][0]!=NULL)
        {

            if(_ParcebleData[_PositionInParsedSequnce][0] !=  _ParcebleData[1][0] && !ControlSymbolFound )
            {

                _AgsCheckList.set(_PositionInParsedSequnce,true);
                Data =   _ParcebleData[_PositionInParsedSequnce].c_str();
            }
            else
            {
                _AgsCheckList.set(_PositionInParsedSequnce,false);
                _PositionInParsedSequnce = Position;
                ControlSymbolFound  = true;

            }

        }
    }
    else
    {      
         return Data;
    }
 }
 /**********************************************************************/
  uint64_t ParcerBaseTokenActionProvider:: GetPositionInParsedSequnce(void)
  {

  return  _PositionInParsedSequnce;

  }

/**********************************************************************/
 void   ParcerBaseTokenActionProvider:: ResetPositionInParsedSequnce(void)
 {
      _PositionInParsedSequnce = 0;
 }
   
/**********************************************************************/
  bool    ParcerBaseTokenActionProvider:: IsChildren(void)
 {
 return _IsChild;
 }
/**********************************************************************/
 bool  ParcerBaseTokenActionProvider::  IsTokenDestroyed(void)
{

		return _IsTokenDestroyed;
}
/**********************************************************************/
 bool   ParcerBaseTokenActionProvider:: CheckArgIsParced(int Postion)
 {
 bool  Res =  false;;

    if(_AgsCheckList.test(Postion))
    {
    
    Res =  true;
    }


     return Res;

 }
 /**********************************************************************/

 

