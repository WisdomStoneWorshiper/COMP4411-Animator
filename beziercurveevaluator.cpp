#include "BezierCurveEvaluator.h"
#include "vec.h"
#include "mat.h"

#include <assert.h>

#define seg_num 30



void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts, std::vector<Point>& ptvEvaluatedCurvePts,
										 const float& fAniLength, const bool& bWrap) const {
	ptvEvaluatedCurvePts.clear();
	vector<Point> temp_pt_arr(ptvCtrlPts);
	const Mat4d M(-1, 3, -3, 1, 3, -6, 3, 0, -3, 3, 0, 0, 1, 0, 0, 0);
	if (bWrap) {
		temp_pt_arr.push_back(Point(ptvCtrlPts[0].x + fAniLength, ptvCtrlPts[0].y));
	}

	bool wrapped = false;

	int i = 0;
	

	for (; i+3 < temp_pt_arr.size(); i += 3) {
		//ptvEvaluatedCurvePts.push_back(temp_pt_arr[i]);
		//ptvEvaluatedCurvePts.push_back(temp_pt_arr[i + 3]);
		//ptvEvaluatedCurvePts.push_back(temp_pt_arr[i + 3]);
		Vec4d px(temp_pt_arr[i].x, temp_pt_arr[i + 1].x, temp_pt_arr[i + 2].x, temp_pt_arr[i + 3].x);
		Vec4d py(temp_pt_arr[i].y, temp_pt_arr[i + 1].y, temp_pt_arr[i + 2].y, temp_pt_arr[i + 3].y);
		for (int j = 0; j < seg_num; ++j) {
			double t = j / (double)seg_num;
			Vec4d T(t * t * t, t * t, t, 1);
			Vec4d TM = M.transpose()*T;
			Point temp_pt(TM * px, TM * py);
			if (bWrap && temp_pt.x > fAniLength) {
				float x_adj = temp_pt.x - fAniLength;
				if (!wrapped) {
					Point last = ptvEvaluatedCurvePts[ptvEvaluatedCurvePts.size()-1];
					ptvEvaluatedCurvePts.push_back(
						Point(fAniLength, last.y + (temp_pt.y - last.y) * (fAniLength - last.x) / (temp_pt.x-last.x)
					));
					ptvEvaluatedCurvePts.push_back(Point(
						0, last.y + (temp_pt.y - last.y) * (fAniLength - last.x) / (temp_pt.x - last.x)));
					wrapped = true;
				}
				temp_pt.x = x_adj;
			}
			ptvEvaluatedCurvePts.push_back(temp_pt);
		}
		if (temp_pt_arr[i + 3].x > fAniLength) {
			ptvEvaluatedCurvePts.push_back(Point(temp_pt_arr[i + 3].x-fAniLength,temp_pt_arr[i + 3].y));
		} else {
			ptvEvaluatedCurvePts.push_back(temp_pt_arr[i + 3]);
		}
		/*if (bWrap && temp_pt_arr[i + 3].x > fAniLength) {
			ptvEvaluatedCurvePts.push_back(Point(temp_pt_arr[i + 3].x-fAniLength,temp_pt_arr[i + 3].y));
		} else {
			ptvEvaluatedCurvePts.push_back(temp_pt_arr[i + 3]);
		}*/
	}
	
	for (; i < ptvCtrlPts.size(); ++i) {
		ptvEvaluatedCurvePts.push_back(ptvCtrlPts[i]);
	}
	
	if (!bWrap) {
		ptvEvaluatedCurvePts.push_back(Point(0,ptvEvaluatedCurvePts[0].y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength,
											 ptvEvaluatedCurvePts[ptvEvaluatedCurvePts.size() - 1].y));
	} else if (!wrapped) {
		float ratio =
			(fAniLength - ptvCtrlPts[ptvCtrlPts.size() - 1].x)
					  / (ptvCtrlPts[0].x + fAniLength - ptvCtrlPts[ptvCtrlPts.size() - 1].x);
		float y = ptvCtrlPts[ptvCtrlPts.size() - 1].y + (ptvCtrlPts[0].y - ptvCtrlPts[ptvCtrlPts.size() - 1].y) * ratio;
		printf("ratio:%f y:%f", ratio,
			   y);
		
		ptvEvaluatedCurvePts.push_back(Point(fAniLength,y));
		ptvEvaluatedCurvePts.push_back(Point(0,y));	
	}
}
