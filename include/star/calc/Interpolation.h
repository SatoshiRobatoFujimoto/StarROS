#ifndef __STAR_SDK_CALC_INTERPOLATION_H
#define __STAR_SDK_CALC_INTERPOLATION_H

#include <star/Star.h>
#include <star/Lidar.h>
#include <star/Shot.h>

#include <string>

namespace ss {
namespace calc {

namespace math {
class CTrackFile;
}

class __star_export Interpolation {
public:
#if 0
    Interpolation(IMP_DCORING_S* ring);
#endif
    Interpolation();
    ~Interpolation();

    void updatePpsSign(const PosPPS_S& ppsSign, bool isSlowData);

    int setGuiControl(float utc2gps) { cfg_gps_utc = utc2gps; return 0; };

    int setSbetfile(const char* file);

    double utc2GPS(double utc, double utc_gps);                       ///����õ�ÿ��UTCʱ���Ӧ��GPSʱ��
//	flag 1: fast pps; 0:slw pps
    int tzero2UTC(unsigned int tzeroStamp, double& utc, int flag = 1);       ///����õ���ʱ�����Ӧ��UTCʱ��
//  int tzero2Stage(unsigned int tzeroStamp, TurnMsg_S &stag);   ///����õ�ÿ��������ת̨��Ϣ
//	int tzero2Inclt(unsigned int tzeroStamp, IncltMsg_S& inclt);
    int gps2POS_m(double gps, PosMsg_S& posMsg);                     ///����õ�ÿ��GPSʱ���Ӧ��POS��̬��Ϣ
//	int pushSbetBuffer(SBET_Rec* _mt_sbetbuf, unsigned int mt_bufCount);

protected:
    void CheckHeading(double& heading_0, double heading_1);

private:
    PosPPS_S	        _ppsSign;    //ppsSign
    PosPPS_S	        _slwPpsSign; //ppsSign
    std::string	        _sbetpath;

    float		        cfg_gps_utc;		///UTC��GPSʱ���
    float		        cfg_maxUtcGap; ///zks: should be less then shot's t0 cycle (12.8 mSec for 16 bits, 3.2sec for 24 bits)
    int			        s_idxsbet;
    math::CTrackFile*   m_trackFile;
};

}
}


#endif //__STAR_SDK_CALC_INTERPOLATION_H
