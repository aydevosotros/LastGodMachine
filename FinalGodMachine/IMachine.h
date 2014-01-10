
#ifndef IMACHINE_H_
#define IMACHINE_H_

#include "Sample.h"

class IMachine {
public:
	virtual void addTrainingSet(std::vector<Sample> trainingSet)=0;
	virtual void clearTrainingSet()=0;
	virtual void setParameters()=0;

	//Y estos?
//	virtual bool isTrainingReady()=0;
//	virtual void classifySample(Sample sample)=0;
};

#endif

//	virtual bool isReadyToCross()=0;
//	virtual bool isDoorOnFire(double input[])=0;
