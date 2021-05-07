#pragma once

#pragma warning(disable : 4786)

#include "CurveEvaluator.h"

// using namespace std;

class CatmullRomCurveEvaluator : public CurveEvaluator {
public:
	void evaluateCurve(const std::vector<Point>& ptvCtrlPts, std::vector<Point>& ptvEvaluatedCurvePts,
					   const float& fAniLength, const bool& bWrap) const;
};
