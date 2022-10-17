/*
 * lvLogicRecord.cpp
 *
 *  Created on: Jul 16, 2013
 *      Author: Kai Yang
 */

#include "lvCASDef.h"
namespace lvCASInterface
{
//
// special gddDestructor guarantees same form of new and delete
//


	lvLogicRecord::lvLogicRecord(const char* name, lvCAS& casIn,aitEnum typeIn,initRecord& ini)
	:lvRecord(name,casIn)
	{
		this->pOld = new gddScalar(gddAppType_value, typeIn);
		if(pOld.valid())
		{
			int gddStatus = pOld->unreference ();
			assert ( ! gddStatus );
		}

		lvPV *pPV = new(std::nothrow) lvScalarPV(casIn,*this,"VAL",typeIn,ReadWrite);
		installPV("VAL",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"ZSV",aitEnumEnum16,ReadWrite);
		pPV->pValue->putConvert(ini.zsv);
		installPV("ZSV",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"OSV",aitEnumEnum16,ReadWrite);
		pPV->pValue->putConvert(ini.osv);
		installPV("OSV",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"COSV",aitEnumEnum16,ReadWrite);
		pPV->pValue->putConvert(ini.cosv);
		installPV("COSV",pPV);
	}

	gddAppFuncTableStatus lvLogicRecord::getEnums(lvPV* pPV,gdd & enumsIn)
	{

		string s(pPV->getName());
		int nStr = 0;
		gddAppFuncTableStatus stat;
		if(s == "VAL")
		{
			const char* str[2] = {"off","on"};
			return getEnumStrs(2,str,enumsIn);
		}

		stat = lvRecord::getEnums(pPV,enumsIn);
		if(stat != S_casApp_noSupport)
			return stat;

		if(s == "ZSV" || s == "OSV" || s == "COSV")
		{
			nStr = ALARM_NSEV;
			return getEnumStrs(nStr,epicsAlarmSeverityStrings,enumsIn);
		}
		return S_casApp_noSupport;
	}



	gddAppFuncTableStatus lvLogicRecord::getPrecision(gdd & prec)
	{
		prec.putConvert(0u);
		return S_cas_success;
	}

	caStatus lvLogicRecord::preUpdate(lvPV* pPV,const gdd& valueIn)
	{
		caStatus status = lvRecord::preUpdate(pPV,valueIn);
		if(status)
			return status;

		string s(pPV->getName());
		aitUint16 e = 0;
		valueIn.getConvert(e);
		if(s == "VAL")
		{
			if(e > 1)
				return S_casApp_outOfBounds;
		}

		if(s == "ZSV" || s == "OSV" || s == "COSV")
		{
			if(e >= ALARM_NSEV)
				return S_casApp_outOfBounds;
		}
		return S_casApp_success;
	}


	casEventMask lvLogicRecord::postUpdate(lvPV *pPV)
	{
		string pvName(pPV->getName());
		casEventMask eventSelect;
		if(pvName == "VAL")
		{
			aitUint32 val,oldVal;
			aitEnum16 zsv,osv,cosv,newStat = 0,newSevr = 0;


			pPV->pValue->getConvert(val);
			pOld->getConvert(oldVal);

			if(val != oldVal)
			{
				eventSelect |= (cas.valueEventMask() | cas.logEventMask());

				findPV("COSV")->pValue->getConvert(cosv);
				if(cosv > 0)
				{
					newStat = COS_ALARM;
					newSevr = cosv;
				}
			}
			else
			{
				if(val == 0)
				{
					findPV("ZSV")->pValue->getConvert(zsv);
					if(zsv > 0)
					{
						newSevr = zsv;
						newStat = STATE_ALARM;
					}
				}
				else
				{
					findPV("OSV")->pValue->getConvert(osv);
					if(osv > 0)
					{
						newSevr = osv;
						newStat = STATE_ALARM;
					}
				}
			}

			aitEnum16 oldStat,oldSevr;
			lvPV* pstat = findPV("STAT");
			pstat->pValue->getConvert(oldStat);
			lvPV* psevr = findPV("SEVR");
			psevr->pValue->getConvert(oldSevr);

			if(newSevr != oldSevr)
			{
				gdd* pg = new gddScalar(gddAppType_value,aitEnumInt16);
				pg->putConvert(newSevr);
				psevr->setValue(*pg);
				pg->unreference();
				eventSelect |= cas.alarmEventMask();
			}
			if(newStat != oldStat)
			{
				gdd* pg = new gddScalar(gddAppType_value,aitEnumInt16);
				pg->putConvert(newStat);
				pstat->setValue(*pg);
				pg->unreference();
				eventSelect |= cas.alarmEventMask();
			}
			pPV->setStatSevr(newStat,newSevr);
			pOld->put(&(*pPV->pValue));
		}
		else
		{
			if(pvName == "SEVR" || pvName == "STAT")
				eventSelect = cas.alarmEventMask() | cas.valueEventMask();
			else
				eventSelect = cas.valueEventMask() | cas.logEventMask();
		}

		return eventSelect;
	}

	lvRecord* lvLogicRecord::createLogicRecord(DBENTRY *pdbentry,lvCAS& casIn,aitEnum typeIn)
	{
		initRecord ini;
		const char* pRecName = dbGetRecordName(pdbentry);
		long status;

		status = dbFindField(pdbentry,"ZSV");
		if(!status)
			ini.zsv = dbGetMenuIndex(pdbentry);

		status = dbFindField(pdbentry,"OSV");
		if(!status)
			ini.osv = dbGetMenuIndex(pdbentry);

		status = dbFindField(pdbentry,"COSV");
		if(!status)
			ini.cosv = dbGetMenuIndex(pdbentry);


		return new(std::nothrow) lvLogicRecord(pRecName,casIn,typeIn,ini);
	}
}
