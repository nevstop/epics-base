/*
 * lvVectorPV.cpp
 *
 *  Created on: Jul 11, 2013
 *      Author: Kai Yang
 */
#include "lvCASDef.h"
namespace lvCASInterface
{

	lvVectorPV::lvVectorPV(lvCAS& casIn,lvRecord & rec, const  char * pNameIn,aitEnum typeIn,accessType accType,aitUint32 countIn)
	:lvPV(casIn,rec,pNameIn,typeIn,accType),elementCount(countIn)
	{
		pValue = new gddAtomic (gddAppType_value, typeIn,1u, countIn);
		if(pValue.valid())
		{
			int gddStatus = pValue->unreference();
			assert ( ! gddStatus );
			size_t sz = countIn * aitSize[typeIn];
			aitInt8 * arr = new aitInt8[sz];
			assert (arr);
			gddDestructor* des = new gddDestructor();
			assert(des);
			memset(arr,0,sz);
			pValue->putRef(arr,des);
		}
	}

    aitIndex lvVectorPV::maxBound(unsigned  dimension) const
    {
    	if (dimension==0u) {
    	    return this->elementCount;
		}
    	else {
    	    return 0u;
    	}
    }

    unsigned lvVectorPV::maxDimension() const
    {
    	return 1u;
    }

    caStatus lvVectorPV::updateValue(const gdd & value)
	{

	   /*
		//
	    // Check bounds of incoming request
	    // (and see if we are replacing all elements -
	    // replaceOk==true)
	    //
	    // Perhaps much of this is unnecessary since the
	    // server lib checks the bounds of all requests
	    //
	    if ( value.isAtomic()) {
	        if ( value.dimension() != 1u ) {
	            return S_casApp_badDimension;
	        }
	        const gddBounds* pb = value.getBounds ();
	        if ( pb[0u].first() != 0u ) {
	            return S_casApp_outOfBounds;
	        }
	        else if ( pb[0u].size() > this->info.getElementCount() ) {
	            return S_casApp_outOfBounds;
	        }
	    }
	    else if ( ! value.isScalar() ) {
	        //
	        // no containers
	        //
	        return S_casApp_outOfBounds;
	    }*/

	    //
	    // Create a new array data descriptor
	    // (so that old values that may be referenced on the
	    // event queue are not replaced)
	    //
	    smartGDDPointer pNewValue ( new gddAtomic(gddAppType_value, this->type,1u, this->elementCount));
	    if ( ! pNewValue.valid() ) {
	        return S_casApp_noMemory;
	    }

	    //
	    // smart pointer class takes care of the reference count
	    // from here down
	    //
	    gddStatus gdds = pNewValue->unreference( );
	    assert ( ! gdds );


	    //
	    // copy in the values that they are writing
	    //
	    gdds = pNewValue->put( & value );
	    if ( gdds ) {
	        return S_cas_noConvert;
	    }

	    //not sure if i should unreference.i don't need 'cause assign copy will do it
	    //gdds = this->pValue->unreference();
	    //assert ( ! gdds );

	    this->pValue = pNewValue;
		aitTimeStamp gddts (epicsTime::getCurrent () );
		pValue->setTimeStamp(&gddts);

	    return S_casApp_success;
	}
}
