/*
 * lvPV.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: Kai Yang
 */
#include "lvCASDef.h"

namespace lvCASInterface{

	bool lvPV::hasBeenInitialized = false;
	gddAppFuncTable<lvPV> lvPV::ft;

    caStatus lvPV::interestRegister()
	{
		 if ( ! this->getCAS() )
		{
			 //fprintf(stderr,"no cas at lvPV::interestRegister\n");
			 return S_casApp_success;
		}
		this->interest = true;
		return S_casApp_success;
	}



    void lvPV::interestDelete()
    {
    	this->interest = false;
    }

    caStatus lvPV::getValue(gdd & value)
    {
    	caStatus status;

    	    if ( this->pValue.valid () ) {
    	        gddStatus gdds;

    	        /*gdds = gddApplicationTypeTable::
    	            app_table.smartCopy( &value, this->pValue );*/
    	        gdds = value.put(&(*this->pValue));
    	        if (gdds) {
    	            status = S_cas_noConvert;
    	        }
    	        else {
    	            status = S_cas_success;
    	        }
    	    }
    	    else {
    	        status = S_casApp_undefined;
    	    }
    	    return status;
    }


    const char * lvPV::getName() const
    {
    	return this->name.string();
    }

    void lvPV::initFT()
    {
    	 if ( lvPV::hasBeenInitialized ) {
    	            return;
    	    }

		//
		// time stamp, status, and severity are extracted from the
		// GDD associated with the "value" application type.
		//
		lvPV::ft.installReadFunc ("value", &lvPV::getValue);
		lvPV::ft.installReadFunc ("precision", &lvPV::getPrecision);
		lvPV::ft.installReadFunc ("graphicHigh", &lvPV::getHoprLimit);
		lvPV::ft.installReadFunc ("graphicLow", &lvPV::getLoprLimit);
		lvPV::ft.installReadFunc ("controlHigh", &lvPV::getHoprLimit);
		lvPV::ft.installReadFunc ("controlLow", &lvPV::getLoprLimit);
		lvPV::ft.installReadFunc ("alarmHigh", &lvPV::getHihiLimit);
		lvPV::ft.installReadFunc ("alarmLow", &lvPV::getLoloLimit);
		lvPV::ft.installReadFunc ("alarmHighWarning", &lvPV::getHighLimit);
		lvPV::ft.installReadFunc ("alarmLowWarning", &lvPV::getLowLimit);
		lvPV::ft.installReadFunc ("units", &lvPV::getUnits);
		lvPV::ft.installReadFunc ("enums", &lvPV::getEnums);

		lvPV::hasBeenInitialized = true;
    }

    caStatus lvPV::setValue(const gdd & valueIn)
    {
    	caStatus status = this->rec.preUpdate(this,valueIn);
    	if(status)
    		return status;		
		
        status = this->updateValue(valueIn);
        if(status || (!this->pValue.valid())){
            return status;
        }
        //for debug
        //printf("updateValue succeed on %s.%s\n",rec.getName(), getName());
        //pValue->dump();
        //for debug end

        casEventMask select = this->rec.postUpdate(this);
        //
        // post a value change event
        //
        caServer *pCAS = this->getCAS();
        if ( this->interest == true && pCAS != NULL ) {
			this->postEvent ( select, *this->pValue );
		}
        return S_casApp_success;
    }

    casChannel *lvPV::createChannel (const casCtx &ctx,
            const char * const /* pUserName */,
            const char * const /* pHostName */ )
    {
    	return new(std::nothrow) lvChannel(ctx);
    }

    void lvPV::destroy()
    {
        //do nothing
    }

    aitEnum lvPV::bestExternalType() const
    {
        return this->type;
    }

    caStatus lvPV::read(const casCtx & casCtx, gdd & protoIn)
    {
       /* caStatus s;
        switch(this->accType)
    	{
    	case ReadOnly:
    	case ReadWrite:
    		s = lvPV::ft.read(*this,protoIn);
    		break;
    	default:
			s = S_casApp_noSupport;
    	}
        return s;*/
    	return lvPV::ft.read(*this,protoIn);
    }

    caStatus lvPV::write(const casCtx & casCtx, const gdd & value)
    {
    	/*caStatus s;
        switch(this->accType)
		{
		case WriteOnly:
		case ReadWrite:
			s = this->setValue(value);
			break;
		default:
			s = S_casApp_noSupport;
		}
        return s;*/
		
    	caStatus s = this->setValue(value);
		
		//notify client callback
		caCallback cb = cas.getCallback();
		if(cb)
		{
			const void *data = value.dataVoid();
			int len = value.isScalar() ? 1 : value.getDataSizeElements();
			if(value.primitiveType() == aitEnumString)
			{
				//value.dump();
				len = ((aitString*)data)->length();
				data = ((aitString*)data)->string();				
			}
			char fullname[50] = {0};
			sprintf(fullname,"%s.%s",rec.getName(),getName());
			cb(fullname,data,len);
		}
		return s;
    }

}
