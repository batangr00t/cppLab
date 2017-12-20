//
// Created by cho on 17. 11. 26.
//

#ifndef CPP_POINTBUILDER_H
#define CPP_POINTBUILDER_H

#include <memory>
#include <random>

#include "ActivePoint.h"
#include "BuilderInterface.h"


class BuilderRandom : public BuilderInterface {
public:
	BuilderRandom();
	BuilderRandom(double max_x, double max_y, int type);
	virtual ~BuilderRandom();

	enum Type { CLOCKWISE, COUNTERCLOCKWISE, STOPPED, MIXED, SIZE };
	int getTypeSize() {	return Type::SIZE; };
	ActivePointPtr getNext() override;
	ActivePointPtr getNext(int type);
	ActivePointPtr getClockwise();
	ActivePointPtr getCounterClockwise();
	ActivePointPtr getStopped();

private:
    log4cplus::Logger _logger;

    // point x, y interval
	double _max_x;
	double _max_y;

    // generator type
	int _type;

    // random number generator
    std::mt19937 _gen;
    std::uniform_int_distribution<>        _dis_type;
    std::uniform_real_distribution<double> _dis_x;
    std::uniform_real_distribution<double> _dis_y;
};


#endif //CPP_POINTBUILDER_H
