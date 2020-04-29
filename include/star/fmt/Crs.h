/**
 * @author   lucb
 * @date     2020/2/14
 */

#ifndef __STAR_SDK_FMT_CRS_H
#define __STAR_SDK_FMT_CRS_H

#include <star/Star.h>
#include <star/fmt/Writer.h>

#include <vector>
#include <star/DateTime.h>

namespace ss {
namespace fmt {

class __star_export CrsBinWriter : public FileWriter{
public:
    CrsBinWriter();
    virtual ~CrsBinWriter();

    void writeHeader() override;

    size_t write(const Point& point) override;

protected:
    void doWriteHeader();
    void updateHeader(const Point& point);

protected:

#pragma pack(push, 1)
    struct Timestamp {
        uint16_t wYear;
        uint16_t wMonth;
        uint16_t wDayOfWeek;
        uint16_t wDay;
        uint16_t wHour;
        uint16_t wMinute;
        uint16_t wSecond;
        uint16_t wMilliseconds;
    };
    //CRS ������������ͷ�ṹ
    struct CsrHeader {
        uint32_t   packFlag ;    //!< ���ݰ���ʶ: 0xE7E7E7E7
        uint16_t   versions ;    //!< �汾��
        uint16_t   devNum ;      //!< �豸���
        uint32_t   serialNum ;   //!< ���к�
        uint8_t    devStaFlag ;  //!< �豸״̬��ʶ 0�����������쳣 �� 11 | 11 | 11(������״̬) | 11(ɨ����״̬)
        uint32_t   scanFrq ;     //!< ɨ��Ƶ��   ��λ RPS(ת/��)
        uint32_t   pointFrq ;    //!< ��Ƶ       ��λ Hz(��/��)
        uint32_t   angleRes ;    //!< �Ƕȷֱ��� ��λ ǧ��֮һ��
        uint64_t   pulseNum ;    //!< DMI�������
        uint32_t   pointsCount ; //!< һ�����������ܵ���
        Timestamp  svrSysTime ;     //!< ����ɼ�ʱ�䣬��λʱ�䡣
    };

//CRS �����ݽṹ
    struct CrsPoint {
        float    angle;               //!< ɨ��Ƕ�
        uint16_t range;      //!< ��� ��λmm
        uint16_t intension;  //!< ����ǿ��:
    };
#pragma pack(pop)

    struct CrsLine {
        CsrHeader             header;
        std::vector<CrsPoint> points;
    };

private:
    CrsLine     _crsLine;
    uint64_t    _sumSqrCnt;            //���������ֵ
    uint32_t    _preSqrCnt;            //��һ���������ֵ
    double      _timestamp;
    DateTime    _sysTime;
};

}
}

#endif //__STAR_SDK_FMT_CRS_H
