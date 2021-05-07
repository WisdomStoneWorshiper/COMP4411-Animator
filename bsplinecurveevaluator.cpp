#include "bsplinecurveevaluator.h"
#include "mat.h"
#include "vec.h"

#include <assert.h>

#define seg_num 30


void BsplineCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
											 std::vector<Point>& ptvEvaluatedCurvePts, const float& fAniLength,
											 const bool& bWrap) const {
	ptvEvaluatedCurvePts.clear();
	vector<Point> temp_pt_arr;
	int ctrlPointsSize = ptvCtrlPts.size();
	const Mat4d M(-1, 3, -3, 1, 3, -6, 3, 0, -3, 0, 3, 0, 1, 4, 1, 0);
	if (!bWrap) {
		temp_pt_arr.push_back(ptvCtrlPts[0]);
		temp_pt_arr.insert(temp_pt_arr.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		temp_pt_arr.push_back(ptvCtrlPts[ctrlPointsSize - 1]);
	} else {
		temp_pt_arr.push_back(Point(ptvCtrlPts[ctrlPointsSize - 2].x - fAniLength, ptvCtrlPts[ctrlPointsSize - 2].y));
		temp_pt_arr.push_back(Point(ptvCtrlPts[ctrlPointsSize - 1].x - fAniLength, ptvCtrlPts[ctrlPointsSize - 1].y));
		temp_pt_arr.insert(temp_pt_arr.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		temp_pt_arr.push_back(Point(ptvCtrlPts[0].x + fAniLength, ptvCtrlPts[0].y));
		temp_pt_arr.push_back(Point(ptvCtrlPts[1].x + fAniLength, ptvCtrlPts[1].y));
	}

	int i = 0;


	for (; i + 3 < temp_pt_arr.size(); i++) {
		Vec4d px(temp_pt_arr[i].x, temp_pt_arr[i + 1].x, temp_pt_arr[i + 2].x, temp_pt_arr[i + 3].x);
		Vec4d py(temp_pt_arr[i].y, temp_pt_arr[i + 1].y, temp_pt_arr[i + 2].y, temp_pt_arr[i + 3].y);
		for (int j = 0; j < seg_num; ++j) {
			double t = j / (double)seg_num;
			Vec4d T(t * t * t, t * t, t, 1);
			Vec4d TM = (M.transpose() * T) / 6;
			Point temp_pt(TM * px, TM * py);
			ptvEvaluatedCurvePts.push_back(temp_pt);
		}
	}

	if (!bWrap) {
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvEvaluatedCurvePts[ptvEvaluatedCurvePts.size() - 1].y));
		ptvEvaluatedCurvePts.push_back(Point(0, ptvEvaluatedCurvePts[0].y));
	}
}
