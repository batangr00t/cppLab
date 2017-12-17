//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_POINTBUILDERINTERFACE_H
#define CPP_POINTBUILDERINTERFACE_H

#include <memory>
#include "ActivePoint.h"

using ActivePointPtr = std::shared_ptr<ActivePoint>;

class BuilderInterface {
public:
	virtual ~BuilderInterface() {};
	virtual int getTypeSize() = 0;
	virtual ActivePointPtr getNext(int type) = 0;
};


#endif //CPP_POINTBUILDERINTERFACE_H
