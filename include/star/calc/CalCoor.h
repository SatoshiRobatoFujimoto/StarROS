#ifndef __STAR_SDK_CALC_CAL_COOR_H
#define __STAR_SDK_CALC_CAL_COOR_H

#include <star/Star.h>
#include <star/Lidar.h>

#include <star/calc/PreFilter.h>
#include <star/calc/MultiLevelRegister.h>
#include <star/calc/CalMultiLidarCoor.h>
#include <star/calc/CalibRange.h>
#include <star/calc/CalibZerosAngle.h>
#include <star/calc/CalOneAxisLidarCoor.h>
#include <star/calc/CalTwoAxisLidarCoor.h>
#include <star/calc/CalGeodeticCoord.h>
#include <star/calc/PostFilter.h>


namespace ss {
namespace calc {

class Interpolation;

class __star_export CCalCoor
{
public:
    CCalCoor();
    ~CCalCoor();

    void setup(const ss::Configure& configure, Interpolation* interpolation);
    void setDeviceType(int deviceType);

    int calcXYZ(SHOTS_CALCOUT_S *currshot) ;           //������ά����

    MultiLevelRegister& multiLevelRegister();
    CalMultiLidarCoor& calMultiLidarCoor();

private:
    //�����豸����
    CalMultiLidarCoor m_calMultiLidarCoor;
    MultiLevelRegister m_levelRegister;
    //����豸����
    CCalibRange m_calibRange;
    CCalibZerosAngle  m_calibZerosAngle;
    CalOneAxisLidarCoor m_calOneAxisLidarCoor ;
    CalTwoAxisLidarCoor m_calTwoAxisLidarCoor ;
    //�������
    CCalGeodeticCoord m_calGeoeticCoor;
    //����
    CPreFilter m_preFilter;
    CPostFilter m_postFilter;

    //Ӳ������
    int m_deviceType;
};


}
}



#endif //__STAR_SDK_CALC_CAL_COOR_H
