/*
 * lvVectorRecord.cpp
 *
 *  Created on: Jul 17, 2013
 *      Author: Kai Yang
 */
#include "lvCASDef.h"
namespace lvCASInterface
{
	static const aitEnum ftype[]={
			aitEnumFixedString,
			aitEnumInt8,
			aitEnumUint8,
			aitEnumInt16,
			aitEnumUint16,
			aitEnumInt32,
			aitEnumUint32,
			aitEnumFloat32,
			aitEnumFloat64,
			aitEnumEnum16
	};

	lvRecord* lvVectorRecord::createVectorRecord(DBENTRY *pdbentry,lvCAS& casIn)
	{
		initRecord ini;
		const char* pRecName = dbGetRecordName(pdbentry);
		const char* value;
		int cnt = 0;
		int vindex = 0;
		aitEnum type;
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

		status = dbFindField(pdbentry,"NELM");
		if(!status)
			value = dbGetString(pdbentry);
		cnt = atoi(value);

		status = dbFindField(pdbentry,"FTVL");
		if(!status)
			vindex = dbGetMenuIndex(pdbentry);
		type = ftype[vindex];

		return new(std::nothrow) lvVectorRecord(pRecName,casIn,type,cnt,ini);
	}

	lvVectorRecord::lvVectorRecord(const char *name,  lvCAS & casIn, aitEnum typeIn, aitUint32 countIn, initRecord & ini)
	:lvRecord(name,casIn)
	{
		lvPV *pPV = new(std::nothrow) lvVectorPV(casIn,*this,"VAL",typeIn,ReadWrite,countIn);
		installPV("VAL",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"EGU",aitEnumString,ReadWrite);
		pPV->pValue->putConvert(ini.egu);
		installPV("EGU",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"PREC",aitEnumUint16,ReadWrite);
		pPV->pValue->putConvert(ini.prec);
		installPV("PREC",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"HOPR",aitEnumFloat32,ReadWrite);
		pPV->pValue->putConvert(ini.hopr);
		installPV("HOPR",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"LOPR",aitEnumFloat32,ReadWrite);
		pPV->pValue->putConvert(ini.lopr);
		installPV("LOPR",pPV);

		pPV = new(std::nothrow) lvScalarPV(casIn,*this,"NELM",aitEnumUint32,ReadOnly);
		pPV->pValue->putConvert(countIn);
		installPV("NELM",pPV);
	}



	gddAppFuncTableStatus lvVectorRecord::getPrecision(gdd & value)
	{
		lvPV* pPV = findPV("PREC");
		return pPV->getValue(value);
	}



	gddAppFuncTableStatus lvVectorRecord::getUnits(gdd & value)
	{
		lvPV* pPV = findPV("EGU");
		return pPV->getValue(value);
	}



	gddAppFuncTableStatus lvVectorRecord::getHoprLimit(gdd & value)
	{
		lvPV* pPV = findPV("HOPR");
		return pPV->getValue(value);
	}

	gddAppFuncTableStatus lvVectorRecord::getLoprLimit(gdd & value)
	{
		lvPV* pPV = findPV("LOPR");
		return pPV->getValue(value);
	}

	gddAppFuncTableStatus lvVectorRecord::getHighLimit(gdd &value)
	{
		return getHoprLimit(value);
	}

	gddAppFuncTableStatus lvVectorRecord::getLowLimit(gdd &value)
	{
		return getLoprLimit(value);
	}

	gddAppFuncTableStatus lvVectorRecord::getHihiLimit(gdd &value)
	{
		return getHoprLimit(value);
	}

	gddAppFuncTableStatus lvVectorRecord::getLoloLimit(gdd &value)
	{
		return getLoprLimit(value);
	}


	casEventMask lvVectorRecord::postUpdate(lvPV *pPV)
	{
		return casEventMask(cas.valueEventMask() | cas.logEventMask());
	}
}
