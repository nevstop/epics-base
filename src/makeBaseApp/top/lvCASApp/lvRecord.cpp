/*
 * lvRecord.cpp
 *
 *  Created on: Jul 12, 2013
 *      Author: Kai Yang
 */
#include "lvCASDef.h"
#include "alarmString.h"

namespace lvCASInterface
{
	lvPV *lvRecord::findPV(const char *field)
	{
		string s(field);
		if(this->fields.count(s))
			return this->fields[s];
		return NULL;
	}


	lvRecord::lvRecord(const char *nameIn, lvCAS & casIn):name(nameIn),cas(casIn)
	{
		//install SEVR and STAT
		lvPV *pPV = new(std::nothrow) lvScalarPV(casIn,*this,"STAT",aitEnumEnum16,ReadOnly);
		installPV("STAT",pPV);
		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"SEVR",aitEnumEnum16,ReadOnly);
		installPV("SEVR",pPV);
	}

	lvRecord::~lvRecord()
	{
		pvMap::iterator i = this->fields.begin();
		while(i != fields.end())
		{
			delete i->second;
			++i;
		}
		fields.clear();
	}



	gddAppFuncTableStatus lvRecord::getPrecision(gdd & value)
	{
		return S_casApp_noSupport;
	}



	gddAppFuncTableStatus lvRecord::getHighLimit(gdd & value)
	{
		return S_casApp_noSupport;
	}



	gddAppFuncTableStatus lvRecord::getLowLimit(gdd & value)
	{
		return S_casApp_noSupport;
	}



	gddAppFuncTableStatus lvRecord::getUnits(gdd & value)
	{
		return S_casApp_noSupport;
	}


	gddAppFuncTableStatus lvRecord::getEnumStrs(int nStr,const char* strSrc[],gdd & enumsIn)
	{
		aitFixedString *str;
		lvFixedStringDestructor *pDes;

		str = new aitFixedString[nStr];
		if (!str) {
			return S_casApp_noMemory;
		}

		pDes = new lvFixedStringDestructor;
		if (!pDes) {
			delete [] str;
			return S_casApp_noMemory;
		}

		for(int i = 0; i < nStr; ++i)
			strncpy (str[i].fixed_string, strSrc[i],sizeof(aitFixedString));

		enumsIn.setDimension(1);
		enumsIn.setBound (0,0,nStr);
		enumsIn.putRef (str, pDes);
		return S_cas_success;
	}

	gddAppFuncTableStatus lvRecord::getEnums(lvPV* pPV,gdd & enumsIn)
	{
		//fprintf(stderr,"lvRecord::getEnums\n");
		string s(pPV->getName());
		int nStr = 0;
		if(s == "SEVR")
		{
			nStr = ALARM_NSEV;
			return getEnumStrs(nStr,epicsAlarmSeverityStrings,enumsIn);
		}
		if(s == "STAT")
		{
			nStr = ALARM_NSTATUS;
			return getEnumStrs(nStr,epicsAlarmConditionStrings,enumsIn);
		}
		return S_casApp_noSupport;
	}



	gddAppFuncTableStatus lvRecord::getHihiLimit(gdd & value)
	{
		return S_casApp_noSupport;
	}



	gddAppFuncTableStatus lvRecord::getLoloLimit(gdd & value)
	{
		return S_casApp_noSupport;
	}



	gddAppFuncTableStatus lvRecord::getHoprLimit(gdd & value)
	{
		return S_casApp_noSupport;
	}



	gddAppFuncTableStatus lvRecord::getLoprLimit(gdd & value)
	{
		return S_casApp_noSupport;
	}

	void lvFixedStringDestructor::run ( void * pUntyped )
	{
	    aitFixedString *ps = (aitFixedString *) pUntyped;
	    delete [] ps;
	}

	caStatus lvRecord::preUpdate(lvPV* pPV,const gdd& valueIn)
	{
		string s(pPV->getName());
		aitUint16 e = 0;
		if(s == "STAT")
		{
			valueIn.getConvert(e);
			if(e >= ALARM_NSTATUS)
				return S_casApp_outOfBounds;
		}
		if(s == "SEVR")
		{
			valueIn.getConvert(e);
			if(e >= ALARM_NSEV)
				return S_casApp_outOfBounds;
		}
		return S_casApp_success;
	}
}
