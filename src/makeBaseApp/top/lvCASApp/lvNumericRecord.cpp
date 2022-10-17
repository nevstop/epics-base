/*
 * lvNumericRecord.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: Kai Yang
 */
#include "lvCASDef.h"
#include "stdlib.h"
namespace lvCASInterface
{

	lvRecord* lvNumericRecord::createNumericRecord(DBENTRY *pdbentry,lvCAS& casIn,aitEnum typeIn)
	{
		initRecord ini;
		const char* pRecName = dbGetRecordName(pdbentry);
		const char* value;
		long status = dbFindField(pdbentry,"EGU");
		if(!status)
			value = dbGetString(pdbentry);
		ini.egu = value;

		status = dbFindField(pdbentry,"PREC");
		if(!status)
			value = dbGetString(pdbentry);
		ini.prec = atoi(value);

		status = dbFindField(pdbentry,"HOPR");
		if(!status)
			value = dbGetString(pdbentry);
		ini.hopr = atof(value);

		status = dbFindField(pdbentry,"LOPR");
		if(!status)
			value = dbGetString(pdbentry);
		ini.lopr = atof(value);

		status = dbFindField(pdbentry,"HIHI");
		if(!status)
			value = dbGetString(pdbentry);
		ini.hihi = atof(value);

		status = dbFindField(pdbentry,"LOLO");
		if(!status)
			value = dbGetString(pdbentry);
		ini.lolo = atof(value);

		status = dbFindField(pdbentry,"HIGH");
		if(!status)
			value = dbGetString(pdbentry);
		ini.high = atof(value);

		status = dbFindField(pdbentry,"LOW");
		if(!status)
			value = dbGetString(pdbentry);
		ini.low = atof(value);

		status = dbFindField(pdbentry,"HYST");
		if(!status)
			value = dbGetString(pdbentry);
		ini.hyst = atof(value);

		status = dbFindField(pdbentry,"MDEL");
		if(!status)
			value = dbGetString(pdbentry);
		ini.mdel = atof(value);

		status = dbFindField(pdbentry,"ADEL");
		if(!status)
			value = dbGetString(pdbentry);
		ini.adel = atof(value);

		status = dbFindField(pdbentry,"HHSV");
		if(!status)
			ini.hhsv = dbGetMenuIndex(pdbentry);

		status = dbFindField(pdbentry,"LLSV");
		if(!status)
			ini.llsv = dbGetMenuIndex(pdbentry);

		status = dbFindField(pdbentry,"HSV");
		if(!status)
			ini.hsv = dbGetMenuIndex(pdbentry);

		status = dbFindField(pdbentry,"LSV");
		if(!status)
			ini.lsv = dbGetMenuIndex(pdbentry);

		return new(std::nothrow) lvNumericRecord(pRecName,casIn,typeIn,ini);
	}

	lvNumericRecord::lvNumericRecord(const char *nameIn,  lvCAS & casIn, aitEnum typeIn,initRecord& ini)
	:lvRecord(nameIn,casIn)
	{
		this->pOld = new gddScalar(gddAppType_value, typeIn);
        if(pOld.valid())
        {
        	int gddStatus = pOld->unreference ();
        	assert ( ! gddStatus );
        }

		lvPV *pPV = new(std::nothrow) lvScalarPV(casIn,*this,"VAL",typeIn,ReadWrite);
		installPV("VAL",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"EGU",aitEnumString,ReadWrite);
		pPV->pValue->putConvert(ini.egu);
		installPV("EGU",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"PREC",aitEnumUint16,ReadWrite);
		pPV->pValue->putConvert(ini.prec);
		installPV("PREC",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"HOPR",typeIn,ReadWrite);
		pPV->pValue->putConvert(ini.hopr);
		installPV("HOPR",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"LOPR",typeIn,ReadWrite);
		pPV->pValue->putConvert(ini.lopr);
		installPV("LOPR",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"HIHI",typeIn,ReadWrite);
		pPV->pValue->putConvert(ini.hihi);
		installPV("HIHI",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"LOLO",typeIn,ReadWrite);
		pPV->pValue->putConvert(ini.lolo);
		installPV("LOLO",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"HIGH",typeIn,ReadWrite);
		pPV->pValue->putConvert(ini.high);
		installPV("HIGH",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"LOW",typeIn,ReadWrite);
		pPV->pValue->putConvert(ini.low);
		installPV("LOW",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"HHSV",aitEnumEnum16,ReadWrite);
		pPV->pValue->putConvert(ini.hhsv);
		installPV("HHSV",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"LLSV",aitEnumEnum16,ReadWrite);
		pPV->pValue->putConvert(ini.llsv);
		installPV("LLSV",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"HSV",aitEnumEnum16,ReadWrite);
		pPV->pValue->putConvert(ini.hsv);
		installPV("HSV",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"LSV",aitEnumEnum16,ReadWrite);
		pPV->pValue->putConvert(ini.lsv);
		installPV("LSV",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"HYST",typeIn,ReadWrite);
		pPV->pValue->putConvert(ini.hyst);
		installPV("HYST",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"ADEL",typeIn,ReadWrite);
		pPV->pValue->putConvert(ini.adel);
		installPV("ADEL",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"MDEL",typeIn,ReadWrite);
		pPV->pValue->putConvert(ini.mdel);
		installPV("MDEL",pPV);
	}



	gddAppFuncTableStatus lvNumericRecord::getPrecision(gdd &value)
	{
		lvPV* pPV = findPV("PREC");
		return pPV->getValue(value);
	}

	gddAppFuncTableStatus lvNumericRecord::getHighLimit(gdd & value)
	{
		lvPV* pPV = findPV("HIGH");
		return pPV->getValue(value);
	}



	gddAppFuncTableStatus lvNumericRecord::getLowLimit(gdd & value)
	{
		lvPV* pPV = findPV("LOW");
		return pPV->getValue(value);
	}



	gddAppFuncTableStatus lvNumericRecord::getUnits(gdd & value)
	{
		lvPV* pPV = findPV("EGU");
		return pPV->getValue(value);
	}



	gddAppFuncTableStatus lvNumericRecord::getHihiLimit(gdd & value)
	{
		lvPV* pPV = findPV("HIHI");
		return pPV->getValue(value);
	}



	gddAppFuncTableStatus lvNumericRecord::getLoloLimit(gdd & value)
	{
		lvPV* pPV = findPV("LOLO");
		return pPV->getValue(value);
	}



	gddAppFuncTableStatus lvNumericRecord::getHoprLimit(gdd & value)
	{
		lvPV* pPV = findPV("HOPR");
		return pPV->getValue(value);
	}



	gddAppFuncTableStatus lvNumericRecord::getLoprLimit(gdd & value)
	{
		lvPV* pPV = findPV("LOPR");
		return pPV->getValue(value);
	}

	caStatus lvNumericRecord::preUpdate(lvPV* pPV,const gdd& valueIn)
	{
		caStatus status = lvRecord::preUpdate(pPV,valueIn);
		if(status)
			return status;

		string s(pPV->getName());
		if(s == "HHSV" || s == "LLSV" || s == "HSV" || s == "LSV")
		{
			aitUint16 e = 0;
			valueIn.getConvert(e);
			if(e >= ALARM_NSEV)
				return S_casApp_outOfBounds;
		}
		return S_casApp_success;
	}

	casEventMask lvNumericRecord::postUpdate(lvPV *pPV)
	{
		string pvName(pPV->getName());
		casEventMask select;
		if(pvName == "VAL")
		{
			select |= checkAlarms(pPV);
			select |= checkValue(pPV);
			this->pOld->put(&(*pPV->pValue));
		}
		else{
			if(pvName == "SEVR" || pvName == "STAT")
				select = cas.alarmEventMask() | cas.valueEventMask();
			else
				select = cas.valueEventMask() | cas.logEventMask();
		}
		return select;
	}

	gddAppFuncTableStatus lvNumericRecord::getEnums(lvPV* pPV,gdd & enumsIn)
	{
		string s(pPV->getName());
		int nStr = 0;
		gddAppFuncTableStatus stat;
		stat = lvRecord::getEnums(pPV,enumsIn);
		if(stat != S_casApp_noSupport)
			return stat;
		if(s == "HHSV" || s == "LLSV" || s == "HSV" || s == "LSV")
		{
			nStr = ALARM_NSEV;
			return getEnumStrs(nStr,epicsAlarmSeverityStrings,enumsIn);
		}
		return S_casApp_noSupport;
	}

	casEventMask lvNumericRecord::checkAlarms(lvPV *pPV)
	{
		lvPV *pvLimit,*pvLimitSevr;
		double val,hyst,alev;
		aitInt16 asev,oldStat,oldSevr;
		aitInt16 newStat,newSevr;
		lvPV* pvStat = findPV("STAT");
		lvPV* pvSevr = findPV("SEVR");



		pvStat->pValue->getConvert(oldStat);
		pvSevr->pValue->getConvert(oldSevr);
		pPV->pValue->getConvert(val);
		findPV("HYST")->pValue->getConvert(hyst);
		newSevr = 0;
		newStat = 0;

		//HIHI alarm
		pvLimit = findPV("HIHI");
		pvLimit->pValue->getConvert(alev);
		pvLimitSevr = findPV("HHSV");
		pvLimitSevr->pValue->getConvert(asev);
		if (asev && (val >= alev || ((oldStat == HIHI_ALARM) && (val >= alev - hyst)))) {
			newStat = HIHI_ALARM;
			newSevr = asev;
			goto CHECK;
		}

		//LOLO alarm
		pvLimit = findPV("LOLO");
		pvLimit->pValue->getConvert(alev);
		pvLimitSevr = findPV("LLSV");
		pvLimitSevr->pValue->getConvert(asev);
		if (asev && (val <= alev || ((oldStat == LOLO_ALARM) && (val <= alev + hyst)))) {
			newStat = LOLO_ALARM;
			newSevr = asev;
			goto CHECK;
		}

		//HIGH alarm
		pvLimit = findPV("HIGH");
		pvLimit->pValue->getConvert(alev);
		pvLimitSevr = findPV("HSV");
		pvLimitSevr->pValue->getConvert(asev);
		if (asev && (val >= alev || ((oldStat == HIGH_ALARM) && (val >= alev - hyst)))) {
			newStat = HIGH_ALARM;
			newSevr = asev;
			goto CHECK;
		}

		//LOW alarm
		pvLimit = findPV("LOW");
		pvLimit->pValue->getConvert(alev);
		pvLimitSevr = findPV("LSV");
		pvLimitSevr->pValue->getConvert(asev);
		if (asev && (val <= alev || ((oldStat == LOW_ALARM) && (val <= alev + hyst)))) {
			newStat = LOW_ALARM;
			newSevr = asev;
			goto CHECK;
		}

	CHECK:

		casEventMask eventSelect;

		if(newSevr != oldSevr)
		{
			gdd* pg = new gddScalar(gddAppType_value,aitEnumEnum16);
			pg->putConvert(newSevr);
			pvSevr->setValue(*pg);
			pg->unreference();
			eventSelect |= cas.alarmEventMask();
		}
		if(newStat != oldStat)
		{
			gdd* pg = new gddScalar(gddAppType_value,aitEnumEnum16);
			pg->putConvert(newStat);
			pvStat->setValue(*pg);
			pg->unreference();
			eventSelect |= cas.alarmEventMask();
		}
		pPV->setStatSevr(newStat,newSevr);
		return eventSelect;
	}

	casEventMask lvNumericRecord::checkValue(lvPV *pPV)
	{
		double adel,mdel,oldVal,val,delta;
		findPV("ADEL")->pValue->getConvert(adel);
		findPV("MDEL")->pValue->getConvert(mdel);
		pPV->pValue->getConvert(val);
		pOld->getConvert(oldVal);

		casEventMask eventSelect;
		/* check for value and archive change */
		delta = val - oldVal;
		if(delta < 0.0)
			delta = -delta;
		if(delta > mdel)
			eventSelect |= cas.valueEventMask();
		if(delta > adel)
			eventSelect |= cas.logEventMask();

		return eventSelect;
	}

}
