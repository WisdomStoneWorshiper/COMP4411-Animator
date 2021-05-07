#include "c2interpolatingcurveevaluator.h"
#include "vec.h"
#include "mat.h"

#include <assert.h>

#define seg_num 150

// reference: google U washington c2 interpolating curve

void C2InterpolatingCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
												std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength, const bool& bWrap) const {
	ptvEvaluatedCurvePts.clear();
	vector<Point> temp_pt_arr(ptvCtrlPts);
	temp_pt_arr.push_back(Point(ptvCtrlPts[0].x + fAniLength, ptvCtrlPts[0].y));
	int m = ptvCtrlPts.size();
	
	if (!bWrap)
		--m;
	vector<float> gamma(temp_pt_arr.size());
	vector<float> delta(temp_pt_arr.size());
	vector<float> D(temp_pt_arr.size());

	gamma[0] = 0.5f;
	for (int i = 1; i < m; ++i) {
		gamma[i] = 1.0f / (4 - gamma[i - 1]);
	}
	gamma[m] = 1.0f / (2 - gamma[m - 1]);
	delta[0] = 3.0f * (temp_pt_arr[1].y - temp_pt_arr[0].y) * gamma[0];
	for (int i = 1; i < m; ++i) {
		delta[i] = (3.0f * (temp_pt_arr[i + 1].y - temp_pt_arr[i-1].y)-delta[i-1])*gamma[i];
	}
	delta[m] = (3.0f * (temp_pt_arr[m].y - temp_pt_arr[m - 1].y)-delta[m-1])*gamma[m];

	D[m] = delta[m];
	for (int i = m - 1; i >= 0; --i) {
		D[i] = delta[i] - gamma[i] * D[i + 1];
	}

	const Mat4f Mh(2, -2, 1, 1, -3, 3, -2, -1, 0, 0, 1, 0, 1, 0, 0, 0);
	for (int i = 0; i < m; ++i) {
		Vec4f Gh(temp_pt_arr[i].y, temp_pt_arr[i + 1].y, D[i], D[i + 1]);
		Vec4f temp = Mh * Gh;
		for (int j = 0; j < seg_num; ++j) {
			double t = j / (double)seg_num;
			Vec4f T(t * t * t, t * t, t, 1);
			float dx = temp_pt_arr[i + 1].x - temp_pt_arr[i].x;
			float temp_y = T * temp;
			float temp_x = temp_pt_arr[i].x + t * dx;
			temp_x = fmod(temp_x, fAniLength);
			ptvEvaluatedCurvePts.push_back(Point(temp_x, temp_y));
		}
	}
	if (!bWrap) {
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvEvaluatedCurvePts[ptvEvaluatedCurvePts.size() - 1].y));
		ptvEvaluatedCurvePts.push_back(Point(0, ptvEvaluatedCurvePts[0].y));
		
	}
}