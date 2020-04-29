/**
 * @author   lucb
 * @date     2020/2/14
 */

#ifndef __STAR_SDK_LIDAR_H
#define __STAR_SDK_LIDAR_H

#include <cstdint>

namespace ss {
namespace lidar {
    enum DeviceModel {
        APilot = 0 ,
        RAngle,
        UArm,
        TPilot,
        AK,
        RFans,
        SL,
        CFans,
        UT = 8 ,
        IRA,
    };

    enum EchoType {     //!<�ز�����
        EchoAll = 0,
        EchoOne = 1,    //!< 1�ز�
        EchoTwo = 2,    //!< 2�ز�
        EchoTri = 4,    //!< 3�ز�
        EchoFor = 8,    //!< 4�ز�
    };

    enum ScanType {     //!<ɨ��ɼ�����
        ScanNear = 0,   //!< ������ģʽ
        ScanMiddle = 1, //!< ����ģʽ
        ScanMiddleFar = 2, //!< ��Զ����ģʽ
        ScanFar = 3,    //!< Զ����ģʽ
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    // *                       ������������
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    // ��෽ʽ
    enum RangeMode {
        AMCW = 0xAB,
        TOF  = 0xCB
    } ;

    // ������
    enum TZeorMode {
        Fall = 1 ,         //!< �ɼ��½���
        Rise = 0 ,         //!< �ɼ�������
    } ;

    // MPIA_ģʽ
    enum MpiaMode {
        OnlyA = 0,         //!< ��MPIA_A
        OnlyB = 2,         //!< ��MPIA_B
        T0Same = 4,        //!< MPIA_A&B����ʹ��ͬһT0
        T0Diff = 8,         //!< MPIA_A&B�����һ��T0
        MFmode = 9
    };

    enum ProgramMode {
        ProgrmModeNon = 0 ,
        ProgrmModeMP = 1 ,
    };
    enum GpsType {        //GPS����
        GpsApplanix = 0,
        GpsTrimble =1 ,
        GpsNoval = 2 ,
        GpsJavat =3  ,
        GpsNmea = 4,
        GpsGsof = 5,
        GPSInpps = 6,
    };

    enum MirrorNumber {
        oneMirror       = 0,
        twoMirror       = 1,
        threeMirror     = 2,
        fourMirror      = 3,
        zeroAngSignal   = 4,
        updataFrame     = 5,
    };

    enum ScanMode {
        ScanPlusPosA,            //!< ����λ��ģʽ, ������ת
        ScanPlusPosR,            //!< ���λ��ģʽ, ������ת
        ScanMinusPosA,           //!< ����λ��ģʽ, ������ת
        ScanMinusPosR,           //!< ���λ��ģʽ, ������ת
        ScanPlusSpeed,           //!< �ٶ�ģʽ, ������ת
        ScanMinuSpeed            //!< �ٶ�ģʽ, ������ת
    };

    // ɨ����ת��״̬
    enum ScanState {
        StandReady  = 0x0 ,  //׼��״̬
        ScanStand   = 0x1 ,  //ת��״̬
        ScanError   = 0x2,
    };

    enum TurretMode {             //!< ת̨����ģʽ
        TurretReset     = 0x00, //!< ����
        TurretContinue  = 0x01, //!< ����ģʽ
        TurretArea      = 0x02, //!< ����ģʽ
        TurretPosition  = 0x04, //!< λ��ģʽ
        TurretNextTrige = 0x08, //!< ��һ���ع��
        TurretStop      = 0x10, //!< ֹͣ
        TurretSearch    = 0x20, //!< ��ѯ
    } ;

    enum ProjectionType {
        UTM     =0,
        GUSS    =1,
    };

    enum EllipsoidType{
        WGS84      =0,
        BeiJing54  =1,
        XiAn80     =2,
        GJ2000     =3,
    } ;

    constexpr static int FREQ_FAR_MIN = 50;
    constexpr static int FREQ_FAR_MAX = 100;
    constexpr static int FREQ_MEDIUM_FAR_MIN = 110;
    constexpr static int FREQ_MEDIUM_FAR_MAX = 200;
    constexpr static int FREQ_MEDIUM_MIN = 210;
    constexpr static int FREQ_MEDIUM_MAX = 450;
    constexpr static int FREQ_NERAR_MIN = 460;
    constexpr static int FREQ_NERAR_MAX = 600;

    constexpr static int DATA_POINT_COUNT =  0x10000 ; //��������Ϊ64K

#ifndef T0_STEP
    const static int32_t T0_STEP = 0x80000000; // 2^31, 2147483648
    const static int32_t T0_Clock_Freq = 5000000;	// 5M  //1���ӵ�T0 Countֵ
    const static double T0_Clock_Prcs = 40.0e-6;		// 40PPM
    const static int T0_Clock_Check = (150);  //by zhangwei ��pps�ļ���ж�ֵ���ӵ�5000150
#endif

    constexpr static int CPT_DELETE_LINE_COUNT = 2 ;  //��ʼʱɾ��ɨ���ߵĸ���
    constexpr static int CPT_DELTETE_INDEX = 2;
    constexpr static float CPT_DELTETE_RANGEMIN = 2;
    constexpr static float CPT_DELTETE_RANGEMAX = 3;
    constexpr static int CPT_DELETE_POINT_COUNT = 500 ; //һ��ɨ�������ٵ�ĸ���
}
}

#endif //__STAR_SDK_LIDAR_H
