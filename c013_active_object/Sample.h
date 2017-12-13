/*
 * SampleRunnable.h
 *
 *  Created on: 2016. 12. 4.
 *      Author: cho
 */

#ifndef C013_RUNNABLE_SAMPLERUNNABLE_H_
#define C013_RUNNABLE_SAMPLERUNNABLE_H_

#include "ActiveObject.h"

class Sample: public ActiveObject {
public:
	Sample(const std::string& name);
	virtual ~Sample();

	bool doInitilize();
	bool doRun();
	bool doFinalize();
};

#endif /* C013_RUNNABLE_SAMPLERUNNABLE_H_ */
