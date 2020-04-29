/**
 * @author   lucb
 * @date     2020/3/2
 */

#ifndef __STAR_SDK_MSG_SHOT_H
#define __STAR_SDK_MSG_SHOT_H

#include <star/Lidar.h>

namespace ss {

struct Point2d {
    double x = 0;
    double y = 0;
};

struct Point3d {
    double x = 0;
    double y = 0;
    double z = 0;
};

struct LasPulse_S {
    bool flag = false;             //zks: ??? for what ???
    uint16_t m_uInt = 0; ///< intensity
    uint16_t m_uInt_wide = 0;
    float m_fRange = 0;          ///<��������
    float m_fRange_T0 = 0;          ///<��������
    float m_cPulseWidth = 0;  ///<���ο��
    // unsigned int32_t m_cPulseWidth ;  ///<���ο��
    uint32_t riseEdge = 0;  //��λ�ź��������
};

struct LasShot_S {
    bool flag = false; //��־�Ƿ��лز�����
    bool flagSL = false;
    uint16_t dataID = 0;
    uint16_t lidarID = 0;     //������ID   add by scofield zhang 2019 10 17
    uint16_t planeNum = 0;
    lidar::MirrorNumber mirrorNumb = lidar::zeroAngSignal;   //zeroAngSignal ��4�ز� riseEdge ��ʾ ������� countֵ
    int32_t angleArea = 0;
    uint32_t m_tzero = 0; ///<
    int32_t data_grade = 0;
    int32_t mpia_sel = 0;
    double m_dAngleX = 0;     ///<���ɨ���X
    double turnAngle = 0;   //ת̨�Ƕ�
    double afa = 0;
    double bta = 0;
    double utcTime = 0;    ///<utcʱ��(��λ:����)  add by scofield zhang 2019 10 17
    LasPulse_S m_pulse[4]; ///<�ز�����
};

#define PPS_STAMP_DEFAULT (0x80000000) //max T0,2^31, 2147483648
#define PPS_DIFF_DEFAULT  (5000000)
#define UTC_STAMP_DEFAULT (0.0)

struct PosPPS_S {
    uint32_t ppsStamp = PPS_STAMP_DEFAULT;
    int32_t diffPpsStamp = PPS_DIFF_DEFAULT; //zks: alway positive, if negative, something wrong!
    double utcStamp = UTC_STAMP_DEFAULT;
};

/**
* \struct  SLasResolvedPulse
* @n
* �����ز����ݡ�ͨ�����㣬���ɴ�������Ļز����ݼ�����ظ�������
*/
struct LasResolvedPulse {
    int stripNb = 0;		///< ������
    double X = 0;		///< X����
    double Y = 0;		///< Y����
    double Z = 0;		///< Z����
};

/**
* \struct  SLasResolvedShot
* @n
* һ��ɨ�輤������ȡ���ݽ������������ݽṹ
*/
typedef struct LasResolvedShot {
    LasShot_S lasShot;
    double stageangle = 0;   ////ת̨�Ƕ���Ϣ��ͨ���ڲ��ȡ
    double bubble_x = 0;
    double bubble_y = 0;
    double m_dGPSTime = 0;	///<GPSʱ��(��λ:����)
    double pos[6] = {0};	///<GPS����(��)������λֵ��¼��γ��(����)���ڲ�
    double rph[3]  = {0};	///<IMU��̬roll,pitch,heading(����)���ڲ�
    LasResolvedPulse m_pulse[4]; ///<�����Ļز�����
} SHOTS_CALCOUT_S ; // SHOTS_CALCOUT_S ;


struct PosMsg_S {
    double gpstime = 0;
    double heading = 0;
    double pitch = 0;
    double roll = 0;
    double latitude = 0;
    double lontitude = 0;
    double height = 0;
    Point3d velocity;
};

//ָ����
struct Narrow_S {
    double narrowAngle = 0;
    double turnAngle = 0;
};

}

#endif //__STAR_SDK_MSG_SHOT_H
