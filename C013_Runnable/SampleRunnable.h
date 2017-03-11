/*
 * SampleRunnable.h
 *
 *  Created on: 2016. 12. 4.
 *      Author: cho
 */

#ifndef C013_RUNNABLE_SAMPLERUNNABLE_H_
#define C013_RUNNABLE_SAMPLERUNNABLE_H_

#include "Runnable.h"

class SampleRunnable: public Runnable {
public:
	SampleRunnable(const std::string& name);
	virtual ~SampleRunnable();

	bool doInitilize();
	bool doRun();
	bool doFinalize();
private:
	std::string _name;
};

#endif /* C013_RUNNABLE_SAMPLERUNNABLE_H_ */
