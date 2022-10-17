/*
 * lvCAS.cpp
 *
 *  Created on: Jul 17, 2013
 *      Author: Kai Yang
 */
#include "lvCASDef.h"
#include "fdManager.h"

namespace lvCASInterface
{
	lvCAS::lvCAS(const char *name,const char* dbdFile):pdbbase(NULL), casName(name),isRunning(false),isDone(false),subThreadExit(false),callbackFun(NULL)
	{
		lvPV::initFT();
		long status = dbReadDatabase(&pdbbase,dbdFile,NULL,NULL);
		assert(!status);
		threadId = epicsThreadCreate("backGroundThread",epicsThreadPriorityLow,epicsThreadGetStackSize(epicsThreadStackSmall),lvCAS::threadFunc,this);
		//epicsThreadSleep(0.2);
	}

	caStatus lvCAS::loadDbFile(const char* dbfile)
	{
		if(!pdbbase)
			return S_casApp_undefined;

		DBENTRY *pdbentry;
		long status;
		lvRecord* prec;
		status = dbReadDatabase(&pdbbase,dbfile,NULL,NULL);
		assert(!status);

		pdbentry = dbAllocEntry(pdbbase);
		status = dbFindRecordType(pdbentry, "ai");
		if (status) {
			printf("No aiRecord descriptions\n");
		}
		else
		{
			status = dbFirstRecord(pdbentry);
			if (status)
				printf(" No aiRecords\n");
			while (!status) {
				prec = lvNumericRecord::createNumericRecord(pdbentry,*this,aitEnumFloat64);
				if(!prec)
				{
					dbFreeEntry(pdbentry);
					return S_casApp_noMemory;
				}
				this->installRecord(dbGetRecordName(pdbentry),prec);
				status = dbNextRecord(pdbentry);
			}
		}

		status = dbFindRecordType(pdbentry, "ao");
		if (status) {
			printf("No aoRecord descriptions\n");
		}
		else
		{
			status = dbFirstRecord(pdbentry);
			if (status)
				printf(" No aoRecords\n");
			while (!status) {
				prec = lvNumericRecord::createNumericRecord(pdbentry,*this,aitEnumFloat64);
				if(!prec)
				{
					dbFreeEntry(pdbentry);
					return S_casApp_noMemory;
				}
				this->installRecord(dbGetRecordName(pdbentry),prec);
				status = dbNextRecord(pdbentry);
			}
		}

		status = dbFindRecordType(pdbentry, "bi");
		if (status) {
			printf("No biRecord descriptions\n");
		}
		else
		{
			status = dbFirstRecord(pdbentry);
			if (status)
				printf(" No biRecords\n");
			while (!status) {
				prec = lvLogicRecord::createLogicRecord(pdbentry,*this,aitEnumEnum16);
				if(!prec)
				{
					dbFreeEntry(pdbentry);
					return S_casApp_noMemory;
				}
				this->installRecord(dbGetRecordName(pdbentry),prec);
				status = dbNextRecord(pdbentry);
			}
		}

		status = dbFindRecordType(pdbentry, "bo");
		if (status) {
			printf("No boRecord descriptions\n");
		}
		else
		{
			status = dbFirstRecord(pdbentry);
			if (status)
				printf(" No boRecords\n");
			while (!status) {
				prec = lvLogicRecord::createLogicRecord(pdbentry,*this,aitEnumEnum16);
				if(!prec)
				{
					dbFreeEntry(pdbentry);
					return S_casApp_noMemory;
				}
				this->installRecord(dbGetRecordName(pdbentry),prec);
				status = dbNextRecord(pdbentry);
			}
		}

		status = dbFindRecordType(pdbentry, "waveform");
		if (status) {
			printf("No waveformRecord descriptions\n");
		}
		else
		{
			status = dbFirstRecord(pdbentry);
			if (status)
				printf(" No waveformRecords\n");
			while (!status) {
				prec = lvVectorRecord::createVectorRecord(pdbentry,*this);
				if(!prec)
				{
					dbFreeEntry(pdbentry);
					return S_casApp_noMemory;
				}
				this->installRecord(dbGetRecordName(pdbentry),prec);
				status = dbNextRecord(pdbentry);
			}
		}
		dbFreeEntry(pdbentry);
		return S_casApp_success;
	}

	lvCAS::~lvCAS()
	{
		isDone = true;
		while(!subThreadExit)//wait for sub thread exit
			epicsThreadSleep(0.02);
		recordMap::iterator it = records.begin();
		for(;it != records.end(); ++it)
		{
			delete it->second;
		}
		//records.clear();
		dbFreeBase(pdbbase);
	}



	pvExistReturn lvCAS::pvExistTest(const casCtx & ctx, const caNetAddr & addr, const char *pPVName)
	{
		return pvExistTest(ctx,pPVName);
	}



	pvAttachReturn lvCAS::pvAttach(const casCtx & casCtx, const char *pPVName)
	{
		lvPV* pPV = findPV(pPVName);
		if(pPV)
			return *pPV;
		return S_casApp_pvNotFound;
	}

	lvPV *lvCAS::findPV(const char *pvName)
	{
		string recName,fieldName;
		resolveName(pvName,recName,fieldName);
		lvRecord* prec = findRecord(recName);
		lvPV* pPV = NULL;
		if(prec)
			pPV = prec->findPV(fieldName.c_str());
		return pPV;
	}



	void lvCAS::startCAS()
	{
		isRunning = true;
		//epicsThreadResume(threadId);
	}



	void lvCAS::stopCAS()
	{
		isRunning = false;
	}


	lvRecord* lvCAS::findRecord(const string& recName)
	{
		if(records.count(recName))
			return records[recName];
		return NULL;
	}

	int lvCAS::resolveName(const char *pvName, string & recName, string & fieldName)
	{
		string tmp(pvName);
		//aitInt32 len = tmp.length();
		aitInt32 pos = reverseFindFirstValidDot(tmp);
		if(pos > 0)
		{
			recName = tmp.substr(0,pos);
			fieldName = tmp.substr(pos+1);
		}
		else
		{
			recName = tmp;
			fieldName = "VAL";
		}
		return 0;
	}

	aitInt32 lvCAS::reverseFindFirstValidDot(const string& str)
	{
		aitInt32 len=str.length();
		for(aitInt32 i=minFieldLength; i<=maxFieldLength; i++)
		{
			if(len<=i+1)
				return -1;
			if(str[len-i-1]=='.')
				return (len-i-1);
		}
		return -1;
	}

	pvExistReturn lvCAS::pvExistTest(const casCtx & casCtx, const char *pPVName)
	{
		lvPV* pPV = findPV(pPVName);
		return pPV ? pverExistsHere : pverDoesNotExistHere;
	}

	void lvCAS::threadFunc(void* parm)
	{
		lvCAS* pCAS = (lvCAS*)parm;
		while(!pCAS->isDone)
		{
			if(pCAS->isRunning)
				::fileDescriptorManager.process(0.02);
			else
				epicsThreadSleep(0.02);
		}
		pCAS->subThreadExit = true;
		//for debug
		fprintf(stderr,"working thread exit\n");
		//end
	}
}
