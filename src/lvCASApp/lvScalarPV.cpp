/*
 * lvScalarPV.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: Kai Yang
 */
#include "lvCASDef.h"
namespace lvCASInterface
{

	lvScalarPV::lvScalarPV(lvCAS& casIn,lvRecord & rec, const  char * pNameIn,aitEnum typeIn,accessType accType)
	:lvPV(casIn,rec,pNameIn,typeIn,accType)
	{
		pValue = new gddScalar(gddAppType_value, typeIn);
		if(pValue.valid())
		{
			int gddStatus = pValue->unreference();
			assert ( ! gddStatus );
		}
	}

	caStatus lvScalarPV::updateValue(const gdd & valueIn)
	{
		if (!valueIn.isScalar()) {
			return S_casApp_outOfBounds;
		}

		if (!pValue.valid()) {
			pValue = new gddScalar(gddAppType_value, type);
			if (!pValue.valid()) {
				return S_casApp_noMemory;
			}
			pValue->unreference();
		}

		if(pValue->put(&valueIn))
			return S_cas_noConvert;

		aitTimeStamp gddts (epicsTime::getCurrent () );
		pValue->setTimeStamp(&gddts);

		return S_casApp_success;
	}
}
