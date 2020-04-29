#ifndef __STAR_SDK_CALC_MATH_CONVERT_H
#define __STAR_SDK_CALC_MATH_CONVERT_H

#include <vector>
#include <time.h>

#include <star/Star.h>
#include <star/Lidar.h>

namespace ss {
namespace calc {
namespace math {

void TranToWGS84(int CentralMeridian,double *pos);
void TranToCoorXYZ(double a,double b,double *XYZ,double *pos);

double deg2rad(double arg); //!< �Ƕ�ת��Ϊ����
double rad2deg(double arg); //!< ����ת��Ϊ�Ƕ�
void BL_GUSS(double sa,double sb,double l,double b,double *x,double *y) ;

}
}
}

#endif // __STAR_SDK_CALC_MATH_CONVERT_H
