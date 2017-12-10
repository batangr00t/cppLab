//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_POINTBUILDERINTERFACE_H
#define CPP_POINTBUILDERINTERFACE_H

#include <memory>
#include "Point.h"

using PointPtr = std::shared_ptr<Point>;

class PointBuilderInterface {
public:
	virtual ~PointBuilderInterface() {};
	virtual PointPtr getNext() = 0;
};


#endif //CPP_POINTBUILDERINTERFACE_H
