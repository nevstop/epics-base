/*
 * lvCASDef.h
 *
 *  Created on: Jul 4, 2013
 *      Author: Kai Yang
 */

#ifndef LVCASDEF_H_
#define LVCASDEF_H_

#include "gddAppFuncTable.h"
#include "smartGDDPointer.h"
#include "epicsTimer.h"
#include "casdef.h"
#include "epicsAssert.h"
//#include "resourceLib.h"
#include "gddApps.h"
#include "gddAppTable.h"
#include "epicsThread.h"
#include "dbStaticLib.h"
#include <map>
#include <string>

namespace lvCASInterface{
using namespace std;


	enum accessType{
		NoAcess,
		ReadOnly,
		WriteOnly,
		ReadWrite
	};

	class lvFixedStringDestructor: public gddDestructor {
		virtual void run (void *);
	};


	class lvRecord;
	class lvCAS;
	class lvChannel;
	class lvPV: public casPV{
		friend class lvNumericRecord;
		friend class lvLogicRecord;
		friend class lvVectorRecord;
		friend class lvChannel;
	public:
		lvPV (lvCAS& casIn, lvRecord & recIn, const  char * pNameIn,aitEnum typeIn,accessType accTypeIn);

		//void show ( unsigned level ) const;

		//caServer
		// Called by the server libary each time that it wishes to
		// subscribe for PV the server tool via postEvent() below.
		//
		caStatus interestRegister ();

		//
		// called by the server library each time that it wishes to
		// remove its subscription for PV value change events
		// from the server tool via caServerPostEvents()
		//
		void interestDelete ();

		aitEnum bestExternalType () const;

		//
		// chCreate() is called each time that a PV is attached to
		// by a client. The server tool must create a casChannel object
		// (or a derived class) each time that this routine is called
		//
		// If the operation must complete asynchronously then return
		// the status code S_casApp_asyncCompletion and then
		// create the casChannel object at some time in the future
		//
		casChannel *createChannel (const casCtx &ctx,
		        const char * const /* pUserName */,
		        const char * const /* pHostName */ );

		//
		// This gets called when the pv gets a new value
		//
		caStatus setValue ( const gdd & );//also used in VI interface
		caStatus getValue(gdd &value);//also used in VI interface

		//access control here
		caStatus read ( const casCtx &, gdd & protoIn );
		caStatus write ( const casCtx &, const gdd & value );


		//caStatus readNoCtx ( smartGDDPointer pProtoIn );

		void destroy ();

		void setStatSevr(aitInt16 stat, aitInt16 sevr);
		void getStatSevr(aitInt16& stat, aitInt16& sevr);

		const char * getName() const;

		//void lvPostEvent(const casEventMask & select, const gdd & event );

		static void initFT();

		/*casChannel * createChannel ( const casCtx &ctx,
			const char * const pUserName,
			const char * const pHostName );*/

	protected:
		lvCAS & cas;
		smartGDDPointer pValue;
		lvRecord & rec;
		bool interest;
		aitEnum type;
		accessType accType;
		aitString name;
		//static epicsTime currentTime;



	private:

		//
		// Std PV Attribute fetch support
		//delegate to Record
		//
		 gddAppFuncTableStatus getPrecision(gdd &value);
		 gddAppFuncTableStatus getUnits(gdd &value);
		 gddAppFuncTableStatus getEnums(gdd &value);
		 gddAppFuncTableStatus getHighLimit(gdd &value);
		 gddAppFuncTableStatus getLowLimit(gdd &value);
		 gddAppFuncTableStatus getHihiLimit(gdd &value);
		 gddAppFuncTableStatus getLoloLimit(gdd &value);
		 gddAppFuncTableStatus getHoprLimit(gdd &value);
		 gddAppFuncTableStatus getLoprLimit(gdd &value);

		lvPV & operator = ( const lvPV & );
		lvPV ( const lvPV & );

		virtual caStatus updateValue ( const gdd & ) = 0;
		//
		// static
		//
		static gddAppFuncTable<lvPV> ft;
		static bool hasBeenInitialized;
	};

	class lvChannel : public casChannel{
	public:
		lvChannel ( const casCtx & ctxIn );
	    bool readAccess () const;
	    bool writeAccess () const;
	private:
	    lvChannel & operator = ( const lvChannel & );
	    lvChannel ( const lvChannel & );
	};

	class lvScalarPV:public lvPV
	{
	public:
		lvScalarPV(lvCAS& casIn,lvRecord & rec, const  char * pNameIn,aitEnum typeIn,accessType accType);

	private:
		virtual caStatus updateValue ( const gdd & );

		lvScalarPV & operator = ( const lvScalarPV & );
		lvScalarPV ( const lvScalarPV & );
	};

	class lvVectorPV:public lvPV
	{
	public:
		lvVectorPV(lvCAS& casIn,lvRecord & rec, const  char * pNameIn,aitEnum typeIn,accessType accType,aitUint32 countIn);
		virtual unsigned maxDimension () const; // return zero if scalar
		virtual aitIndex maxBound ( unsigned dimension ) const;

	private:
		virtual caStatus updateValue ( const gdd & );
		lvVectorPV & operator = ( const lvVectorPV & );
		lvVectorPV ( const lvVectorPV & );
	private:
		const aitIndex elementCount;
	};

	class lvRecord{
		friend class lvPV;
		typedef map<string,lvPV*> pvMap;
	public:
		 //filed is characters after dot. if VAL is used, field can be "VAL" or ""
		 lvPV*  findPV(const char* field);
		 int installPV(const char* filed,lvPV* pPV);
		 virtual ~lvRecord();
		 const char* getName() const;
	protected:
		 lvRecord(const char* name, lvCAS& casIn);
		 gddAppFuncTableStatus getEnumStrs(int nStr,const char* strSrc[],gdd & enmusIn);
		 //called by lvPV counterpart
		 virtual gddAppFuncTableStatus getPrecision(gdd &value);
		 virtual gddAppFuncTableStatus getHighLimit(gdd &value);
		 virtual gddAppFuncTableStatus getLowLimit(gdd &value);
		 virtual gddAppFuncTableStatus getUnits(gdd &value);
		 virtual gddAppFuncTableStatus getEnums(lvPV* pPV,gdd &value);
		 virtual gddAppFuncTableStatus getHihiLimit(gdd &value);
		 virtual gddAppFuncTableStatus getLoloLimit(gdd &value);
		 virtual gddAppFuncTableStatus getHoprLimit(gdd &value);
		 virtual gddAppFuncTableStatus getLoprLimit(gdd &value);

		 //called by lvPV::update before and after lvPV::updateValue to check alarm & set event mask
		 virtual caStatus preUpdate(lvPV* pPV,const gdd& valueIn);
		 virtual casEventMask postUpdate(lvPV *pPV) = 0;

		 aitString name;
		 lvCAS& cas;
		 pvMap fields;
	private:
		 lvRecord & operator = ( const lvRecord & );
		 lvRecord ( const lvRecord & );

	};

	struct initRecord
	{
		aitFloat64 hihi;
		aitFloat64 lolo;
		aitFloat64 high;
		aitFloat64 low;
		aitFloat64 hyst;
		aitFloat64 adel;
		aitFloat64 mdel;
		aitFloat64 hopr;
		aitFloat64 lopr;
		aitString egu;
		aitInt16 prec;
		aitEnum16 hhsv;
		aitEnum16 llsv;
		aitEnum16 hsv;
		aitEnum16 lsv;
		aitEnum16 zsv;
		aitEnum16 osv;
		aitEnum16 cosv;
	};

	class lvNumericRecord:public lvRecord
	{
	public:
		lvNumericRecord(const char* name, lvCAS& casIn,aitEnum typeIn,initRecord& ini);
		//pdbentry points to a ai/ao record instance
		static lvRecord* createNumericRecord(DBENTRY *pdbentry,lvCAS&,aitEnum);

	protected:
		virtual gddAppFuncTableStatus getPrecision(gdd &value);
		virtual gddAppFuncTableStatus getHighLimit(gdd &value);
		virtual gddAppFuncTableStatus getLowLimit(gdd &value);
		virtual gddAppFuncTableStatus getUnits(gdd &value);
		virtual gddAppFuncTableStatus getHihiLimit(gdd &value);
		virtual gddAppFuncTableStatus getLoloLimit(gdd &value);
		virtual gddAppFuncTableStatus getHoprLimit(gdd &value);
		virtual gddAppFuncTableStatus getLoprLimit(gdd &value);
		virtual gddAppFuncTableStatus getEnums(lvPV* pPV,gdd &value);
		virtual casEventMask postUpdate(lvPV *pPV);
		virtual caStatus preUpdate(lvPV* pPV,const gdd& valueIn);
		smartGDDPointer pOld;
	private:
		casEventMask checkAlarms(lvPV *pPV);
		casEventMask checkValue(lvPV *pPV);
		lvNumericRecord & operator = ( const lvNumericRecord & );
		lvNumericRecord ( const lvNumericRecord & );
	};

	class lvLogicRecord:public lvRecord
	{
	public:
		lvLogicRecord(const char* name, lvCAS& casIn,aitEnum typeIn,initRecord& ini);
		static lvRecord* createLogicRecord(DBENTRY *pdbentry,lvCAS& casIn,aitEnum typeIn);
	protected:
		virtual gddAppFuncTableStatus getEnums(lvPV*,gdd &value);
		virtual gddAppFuncTableStatus getPrecision(gdd &value);
		virtual casEventMask postUpdate(lvPV *pPV);
		virtual caStatus preUpdate(lvPV* pPV,const gdd& valueIn);
		smartGDDPointer pOld;
	private:
		lvLogicRecord & operator = ( const lvLogicRecord & );
		lvLogicRecord ( const lvLogicRecord & );
	};

	class lvAiRecord:public lvNumericRecord
	{
	public:
		lvAiRecord(const char* name, lvCAS& casIn,initRecord& ini):lvNumericRecord(name,casIn,aitEnumFloat64,ini){}
		//~lvAiRecord();
		static lvRecord* createAiRecord(DBENTRY *pdbentry,lvCAS& casIn);
	private:
		lvAiRecord & operator = ( const lvAiRecord & );
		lvAiRecord ( const lvAiRecord & );
	};

	class lvAoRecord:public lvNumericRecord
	{
	public:
		lvAoRecord(const char* name, lvCAS& casIn,initRecord& ini):lvNumericRecord(name,casIn,aitEnumFloat64,ini){}
		//~lvAoRecord();
		static lvRecord* createAoRecord(DBENTRY *pdbentry,lvCAS& casIn);
	private:
		lvAoRecord & operator = ( const lvAoRecord & );
		lvAoRecord ( const lvAoRecord & );
	};

	class lvBiRecord:public lvLogicRecord
	{
	public:
		lvBiRecord(const char* name, lvCAS& casIn,initRecord& ini):lvLogicRecord(name,casIn,aitEnumEnum16,ini){}
		//~lvBiRecord();
	private:
		lvBiRecord & operator = ( const lvBiRecord & );
		lvBiRecord ( const lvBiRecord & );
	};

	class lvBoRecord:public lvLogicRecord
	{
	public:
		lvBoRecord(const char* name, lvCAS& casIn,initRecord& ini):lvLogicRecord(name,casIn,aitEnumEnum16,ini){}
		~lvBoRecord();
	private:
		lvBoRecord & operator = ( const lvBoRecord & );
		lvBoRecord ( const lvBoRecord & );
	};

	class lvVectorRecord:public lvRecord
	{
	public:
		lvVectorRecord(const char* name, lvCAS& casIn,aitEnum typeIn,aitUint32 countIn,initRecord& ini);
		static lvRecord* createVectorRecord(DBENTRY *pdbentry,lvCAS& casIn);
	protected:
		virtual gddAppFuncTableStatus getPrecision(gdd &value);
		virtual gddAppFuncTableStatus getUnits(gdd &value);
		virtual gddAppFuncTableStatus getHoprLimit(gdd &value);
		virtual gddAppFuncTableStatus getLoprLimit(gdd &value);
		virtual gddAppFuncTableStatus getHighLimit(gdd &value);
		virtual gddAppFuncTableStatus getLowLimit(gdd &value);
		virtual gddAppFuncTableStatus getHihiLimit(gdd &value);
		virtual gddAppFuncTableStatus getLoloLimit(gdd &value);
		virtual casEventMask postUpdate(lvPV *pPV);
	private:
		lvVectorRecord & operator = ( const lvVectorRecord & );
		lvVectorRecord ( const lvVectorRecord & );
	};


	typedef lvVectorRecord lvWaveformRecord;
	
	typedef void (*caCallback)(const char* pvname,const void *value,int len);
	class lvCAS:public caServer
	{
		typedef map<string,lvRecord*> recordMap;
	public:
		lvCAS(const char* name,const char* path);
		~lvCAS();
		pvExistReturn pvExistTest ( const casCtx & ctx,const caNetAddr &, const char * pPVName );
		pvAttachReturn pvAttach ( const casCtx &,const char * pPVName );
		int installRecord(const char* name,lvRecord* pRecord);
		lvPV* findPV(const char* pvName);
		void startCAS();
		void stopCAS();
		bool Running();
		caStatus loadDbFile(const char* dbfile);
		void installCallback(caCallback cb){
			callbackFun = cb;
		}
		caCallback getCallback(){
			return callbackFun;
		}
	private:
		int resolveName(const char* pvName,string& recName,string& fieldName);
		pvExistReturn pvExistTest ( const casCtx &,const char * pPVName );
		aitInt32 reverseFindFirstValidDot(const string& str);
		lvRecord* findRecord(const string& recName);
		static void threadFunc(void* parm);
	private:
		DBBASE *pdbbase;
		bool isRunning;
		bool isDone;
		bool subThreadExit;
		recordMap records;
		aitString casName;
		epicsThreadId threadId;
		caCallback callbackFun;
		static const aitInt32 minFieldLength=3; ///< The minimum length of field name
		static const aitInt32 maxFieldLength=4;///< The maximum length of field name
	};

	inline lvPV::lvPV (lvCAS& casIn, lvRecord & recIn, const  char * pNameIn,aitEnum typeIn,accessType accTypeIn)
		:cas(casIn),rec(recIn),name(pNameIn),type(typeIn),accType(accTypeIn),interest(false)
	{		
	}

    inline void lvPV::getStatSevr(aitInt16 & stat, aitInt16 & sevr)
    {
        this->pValue->getStatSevr(stat, sevr);
    }

    inline gddAppFuncTableStatus lvPV::getPrecision(gdd & value)
    {
    	return rec.getPrecision(value);
    }

    inline gddAppFuncTableStatus lvPV::getHoprLimit(gdd & value)
    {
    	return rec.getHoprLimit(value);
    }

    inline gddAppFuncTableStatus lvPV::getLoloLimit(gdd & value)
    {
    	return rec.getLoloLimit(value);
    }

    inline gddAppFuncTableStatus lvPV::getUnits(gdd & value)
    {
    	return rec.getUnits(value);
    }

    inline gddAppFuncTableStatus lvPV::getEnums(gdd & value)
    {
    	return rec.getEnums(this,value);
    }

    inline gddAppFuncTableStatus lvPV::getHighLimit(gdd & value)
    {
    	return rec.getHighLimit(value);
    }

    inline gddAppFuncTableStatus lvPV::getLowLimit(gdd & value)
    {
    	return rec.getLowLimit(value);
    }

    inline gddAppFuncTableStatus lvPV::getHihiLimit(gdd & value)
    {
    	return rec.getHihiLimit(value);
    }

    inline gddAppFuncTableStatus lvPV::getLoprLimit(gdd & value)
    {
    	return rec.getLoprLimit(value);
    }

    inline void lvPV::setStatSevr(aitInt16 stat, aitInt16 sevr)
    {
    	this->pValue->setStatSevr(stat,sevr);
    }

    inline const char* lvRecord::getName() const
    {
    	return name.string();
    }

    inline int lvRecord::installPV(const char *filed, lvPV *pPV)
    {
    	this->fields[filed] = pPV;
    	return 0;
    }

    inline int lvCAS::installRecord(const char *name, lvRecord *pRecord)
    {
    	this->records[name] = pRecord;
    	return 0;
    }

    inline bool lvCAS::Running()
    {
    	return this->isRunning;
    }

    inline lvChannel::lvChannel(const casCtx & ctxIn):casChannel(ctxIn)
    {
    }

    inline lvRecord* lvAiRecord::createAiRecord(DBENTRY *pdbentry,lvCAS& casIn)
    {
    	return lvNumericRecord::createNumericRecord(pdbentry,casIn,aitEnumFloat64);
    }

    inline lvRecord* lvAoRecord::createAoRecord(DBENTRY *pdbentry,lvCAS& casIn)
	{
		return lvNumericRecord::createNumericRecord(pdbentry,casIn,aitEnumFloat64);
	}

}


#endif /* LVCASDEF_H_ */
