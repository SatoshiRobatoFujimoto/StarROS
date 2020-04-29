/**
 * @author   lucb
 * @date     2019/12/12
 */

#ifndef __STAR_SDK_IMP_HEADER_H
#define __STAR_SDK_IMP_HEADER_H

#include <star/msg/Message.h>
#include <star/msg/detail/basic_message.h>

namespace ss {
namespace msg {
namespace scd {
namespace v1 {

constexpr static std::size_t IMP_SYNCWORD_COUNT = 8;

#ifndef PROJ_STR_SIZE
constexpr static std::size_t PROJ_STR_SIZE = 31;
constexpr static std::size_t SCADA_VER_LEN = 32;
constexpr static std::size_t CMR_NUMBER = 6;
constexpr static std::size_t ROI_NUMBER = 2;
#endif

constexpr static std::size_t INTENSE_MAX = 2048;
constexpr static std::size_t SCDSCAN_TYPE_COUNT = 3;
constexpr static std::size_t USBCMR_MAX_NUMBER = 2;

#pragma pack(push, 1)
//��������ϵͳʱ�䣬�����ڿ�ʼʱִ��ϵͳʱ��ͬ����
typedef struct {
    uint16_t wYear;
    uint16_t wMonth;
    uint16_t wDayOfWeek;
    uint16_t wDay;
    uint16_t wHour;
    uint16_t wMinute;
    uint16_t wSecond;
    uint16_t wMilliseconds;
} CSYSTEMTIME;

typedef struct {
    int8_t syncword[IMP_SYNCWORD_COUNT]; //0xA7A7A7A7
    uint32_t formatVer;
    uint32_t timeStamp;           //���ݲɼ�ͬ��ʱ���
    uint16_t stationNbr;
    char deviceID[32];
    char scadaAddr[32];          // scada IP address
    int32_t deviceType;
    uint32_t deviceRev;     //!< �豸���
    uint32_t productDate;   //!< ������Ϣ  - from SCDCFG_VERSION_S
    // LiDAR_PRIORITY_S
    char projectID[PROJ_STR_SIZE + 1];
    char customID[PROJ_STR_SIZE + 1];
    char license[PROJ_STR_SIZE + 1];
    uint16_t workTime;       // ������ʱ��
    uint16_t laserTime;      // ������������ʱ��
    uint32_t fpgaVer;          //FPGA �汾��Ϣ
    char scadaVer[SCADA_VER_LEN];  //SCADA �汾��Ϣ
    CSYSTEMTIME sysTime;
    uint32_t systemState;      //ϵͳ״̬
    uint32_t impVer;              //IMP �汾��Ϣ
// added by zhubing 2020.2.15
    uint32_t m_cycle;              //��������
    int8_t reserver[766 - 4];             //total 1020Byte
} SCADA_META_S; //-- IMP_LidarHeader_S ;

//! ����������
typedef struct {
    int32_t lsrType;       //!< ����������
    int32_t freqMin;                //!< ��������СƵ�� ��λ:KHz
    int32_t freqMax;                //!< ���������Ƶ�� ��λ:KHz
    int32_t elecMin;                //!< ��������С���� ��λ:mw
    int32_t elecMax;                //!< ������������ ��λ:mw
    int32_t powMin;                //!< �û����ü�����С����
    int32_t powMax;                //!< �û����ü��������
    int32_t rangeMin;              //!< ��������С����
    int32_t rangeMax;              //!< ������������
    int32_t workPowMin;            //!< ���⹤����С����
    int32_t workPowMax;            //!< ���⹤�������
    int32_t reserved[5];            //!< ����  //total 64
} SCDCFG_LASER_S;

//! ����߼�����
typedef struct {
    int32_t motType;                //!< �������
    float spdMin;                 //!< �����Сת��
    float spdMax;                 //!< ������ת��
    int32_t coder;                  //!< ���������
    float zeroAng;              //!< �����λ�� or ת̨�ֱ���
    // �ӳ���ʼ�Ƕ� - �ӳ���ֹ��
    uint32_t angstr[4];
    uint32_t angstp[4];
    uint16_t scnSpdCheck;
    uint16_t stgType;    //0: bcd ; 1: acj
    uint32_t periodOrPichHigh;    //  or PITCH_all
    int8_t reserved[4];  //total 64
} SCDCFG_MOTOR_S, SCDCFG_STAGE_S;

//! ����߼�����
typedef struct {
    int32_t cmrType;                //!< ����ع�����
    int32_t cmrMode;                //!< �����¼ģʽ
    int32_t plsWidth;               //!< �����ƽ����
    int32_t cmrCount;               //!< �������
    float circum;               //!< �����ܳ�
    int32_t dmiEncoder;            //!< DMI ����������
    uint32_t shutOffset[CMR_NUMBER];   //CMR_NUMBER������ع���ʱ�Ĵ���
    int32_t cmrFlashSign;          //1��USB����ⴥ�� 0��USB����ڴ���
    int32_t reserved[3];            //!< ����  //total 64
} SCDCFG_CAMERA_S;

typedef struct {
    int32_t nearPowMin_;   //!<
    int32_t nearPowMax_;   //!<
    int32_t farPowMin_;   //!<
    int32_t farPowMax_;   //!<
    int32_t nearRangeMin_;   //!<
    int32_t nearRangeMax_;   //!<
    int32_t farRangeMin_;   //!<
    int32_t farRangeMax_;   //!<
    int32_t reserved[8];    //!<   64 Byte
} SCDCFG_RANGE_S;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                       ������������
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
typedef struct {
    int32_t rangeMode;          //!< ���ģʽ
    int32_t mpiaMode;           //!< ����ģʽ
    int32_t tzeroMode;          //!< �����ź���
    float pulseWdthA_;         //!< GPXA ������ liyp  ��ʱ
    float pulseWdthB_;         //!< GPXB ������ liyp  ��ʱ
    int32_t peakSync;           //!< �߱���ֵͬ��
    int32_t peakSyncL;           //!< �ͱ���ֵͬ��L
    int32_t simuRatio;          //!< �������ݷ���
    int32_t tdcaFact;           //!< TDC_A����ϵ��
    int32_t tdcbFact;           //!< TDC_B����ϵ��
    int32_t mSet;                //!< ���ز�����ϵ��
    float af;                   //!< ָ�����ƫ��  liyp /*����ˮ�ݾ���ϵ��*/
    uint32_t packEnable;         //!< ���ݴ��ʹ��
    uint16_t selecPeak;
    uint16_t scdVersion;
    uint16_t timeDelay;           //!< ʱ�䴰����ʱ
    uint16_t pulseCtrl;
    uint16_t pulseDelay;
    uint16_t selecPeakL;
    // int16_t reserved[1];       //total 64 Byte
} SCDCFG_RULER_S;

typedef struct {
    int32_t tempType;           //!< �¶ȴ���������
    int32_t tempMin;            //!< ����Ĭ��ֵ
    int32_t tempMax;            //!< ����Ĭ��ֵ
    int32_t gpsType;     //!< GPS����Ĭ��ֵ��eGpsTrimble
    uint16_t imuTypeSelect; //0��uIMU-IC;  1:LCI-100  2:HG4930CA51
    int16_t reserved[23];       //total 64 Byte
} SCDCFG_ENVIR_S;

typedef struct {
    float areaStrAngMin, areaStrAngMax;
    float areaStpAngMin, areaStpAngMax;
    float areaItvAngMin, areaItvAngMax;
    float angTrgStrMin, angTrgStrMax;
    float angTrgStpMin, angTrgStpMax;
    float angTrgItvMin, angTrgItvMax;
    float gridHmin, gridHmax;
    float gridVmin, gridVmax;
    int32_t gridrefRangeMin, gridrefRangeMax;
    float radianHmin, radianHmax;
    float radianVmin, radianVmax;
    float roiHstrAngMin, roiHstrAngMax;
    float roiHstpAngMin, roiHstpAngMax;
    float roiVstrAngMin, roiVstrAngMax;
    float roiVstpAngMin, roiVstpAngMax;
    int32_t cmrTimeItvMin, cmrTimeItvMax;
    int32_t cmrRangeItvMin, cmrRangeItvMax;
    //int8_t reserved[120] ; //total 256
    int32_t reserved[30];
} SCDCFG_CHECK_S;

constexpr uint16_t LSR_SEL_NUM = 16;
typedef struct {
    uint16_t laserSel[LSR_SEL_NUM];
} SCDCFG_LSRSEL_S;

constexpr uint16_t FREQ_NUM = 7;
typedef struct {
    uint16_t freq[FREQ_NUM];
    uint16_t nflight;//n�����
} SCDCFG_FREQS_S;

constexpr uint16_t ANGEL_NUM = 16;
typedef struct {
    uint16_t angle[ANGEL_NUM];
} SCDCFG_ANGELS_S;

typedef struct {
    uint32_t lsrRevSel_0_7;
    uint32_t lsrRevSel_8_15;
    uint32_t lsrRevTiem_0_3;
    uint32_t lsrRevTiem_4_7;
    uint32_t lsrRevTiem_8_11;
    uint32_t lsrRevTiem_12_15;
    int32_t reserved[10];//total 64 Byte
} SCDCFG_RLSR_CNL_S;

typedef struct {
    float range[16];
} SCDCFG_RLSR_RANGE_S;

//! ϵͳ���ò���

typedef struct {
    //zks    SCDCFG_VERSION_S version;           //!< �汾��Ϣ
    int32_t escadaType;
    SCDCFG_LASER_S lsrConf;      //!< �������߼�����
    SCDCFG_MOTOR_S scnConf;      //!< ����߼�����
    SCDCFG_STAGE_S stgConf;      //!< ת̨����  -- zks
    SCDCFG_CAMERA_S cmrConf;      //!< ����߼�����
    SCDCFG_RULER_S rlrConf;      //!< ������������
    SCDCFG_ENVIR_S envConf;      //!< ������������
    SCDCFG_RANGE_S lrsRangCfg_;  //!< ��Զ����߽�����
    SCDCFG_CHECK_S bdChkConf_;   //!< �豸����
    SCDCFG_LSRSEL_S lsrSelConf;  //!<��ͬɨ�����伤��Ƶ������
    SCDCFG_FREQS_S freqsConf;     //!<��ѡ����Ƶ������
    SCDCFG_ANGELS_S anglesConf;   //!ɨ�����ӳ��ǻ򼤹��Ƶ����
    SCDCFG_RLSR_CNL_S rfansLsr;
    SCDCFG_RLSR_RANGE_S rRangeConf;
    int8_t reserved[1132];           //!< total 2KB
} SCADA_CONFIG_S;

//Can only read from config file, not from the cmd line or GUI
typedef struct {
    float p1_A_far;      //50k-100k��Ӧ��У����
    float p2_A_far;
    float p1_B_far;
    float p2_B_far;

    float riArrayA[INTENSE_MAX];  // gpxA�Ҷȷ�Χ[0-2047]     //50k
    float riArrayB[INTENSE_MAX]; // gpxB�Ҷȷ�Χ[0-2047]
    float riArrayC[INTENSE_MAX];  // gpxA�Ҷȷ�Χ[0-2047]     //300k
    float riArrayD[INTENSE_MAX]; // gpxB�Ҷȷ�Χ[0-2047]
    float riArrayE[INTENSE_MAX];  // gpxA�Ҷȷ�Χ[0-2047]     //500k
    float riArray9[INTENSE_MAX]; // gpxB�Ҷȷ�Χ[0-2047]

    float p1_A_medium_far;  //110k-200k��Ӧ��У����
    float p2_A_medium_far;
    float p1_B_medium_far;
    float p2_B_medium_far;

    float p1_A_medium;    //210k-450k��Ӧ��У����
    float p2_A_medium;
    float p1_B_medium;
    float p2_B_medium;
    float p1_A_near;      //460-600k��Ӧ��У����
    float p2_A_near;
    float p1_B_near;
    float p2_B_near;
    //int8_t reservedB[16320] ;

    float temperatureStart;
    float temperatureEnd;
    float temperatureCoff2;
    float temperatureCoff1;
    float temperatureCoff0;
    int8_t reservedB[16300];

////����С��10�ľ����У����
    //float p1_A_far_10;      //50k��Ӧ��У����
    //float p2_A_far_10;
    //float p1_B_far_10;
    //float p2_B_far_10;
    //float p1_A_medium_10;    //300k��Ӧ��У����
    //float p2_A_medium_10;
    //float p1_B_medium_10;
    //float p2_B_medium_10;

//  float p1_A_near_10;      //500k��Ӧ��У����
//  float p2_A_near_10;
//  float p1_B_near_10;
//  float p2_B_near_10;
//  int8_t reservedB[16288] ;
//  int8_t reservedB[132080] ;         //!< 193KB
} RANGE_CALIB_S;

typedef struct {//zks:Ϊʲô���ַ�����
    char srCalibs[256]; //���������������Ϊ256
    char calibs[256];
    char urInclt[256];
    char RIfilt[256];
    char reserved[1024];  //total 2KB
} SCDCAL_ARRAY_S;

//module parameters
typedef struct {
    //int8_t para[17][128];   //!< ÿ��section���㷨ģ�����17.
    //int8_t reserved[1920] ; //!< total 4KB
    char para[25][128];   //!< ÿ��section���㷨ģ�����17.
    char reserved[896]; //!< total 4KB
} ALGSC_ARRAY_S;

//! scanner
typedef struct {
    int32_t cmdstat;
    int32_t mode;
    float angSpeed;           //!< depends on SCDSCN_MODE_E
    uint16_t roistr[4];
    uint16_t roistp[4];
    uint32_t speedCount;   //ɨ����count
    int32_t speedState;  //ɨ����ת��״̬
    int32_t grade;
    int16_t reserved[10];  //total 60 Byte
} SCDCMD_SCANER_S;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                            ת  ̨
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//! turret
typedef struct {
    int32_t cmdstat;
    int32_t mode;
    float angSpeed;
    float strAngle;
	float stpAngle;          //!< ������ʼ�Ƕ�
    float currAng;                     //!< ��ǰ�Ƕ�
    uint16_t roistr[4];
    uint16_t roistp[4];
    int32_t currMiStat;
    int32_t currMaStat;
    int32_t reserved[3];  //total 60 Byte
} SCDCMD_TURRET_S;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                            �������
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
typedef struct {
    int32_t cmdstat;
    int32_t mode;//��ת����
    float angle;//ת���Ƕ�
    float currAng;//��ǰ�Ƕ� ����λ�ñ�������ǰ�Ƕ�
    int32_t reserved[11]; //total 60 Byte
} SCDCMD_STEPMOTOR_S;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                            ��   ��
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//! �豸��������
typedef struct {
    int32_t gpsType;      //!< GPS����Ĭ��ֵ��eGpsTrimble
    uint32_t utcTime;    //!< ������ʱ
    uint32_t utcSec;     //!< UTC����
    int8_t pps;               //!< PPS�ź� 0 :���ź�   ���㣺���ź�
    uint8_t satelliteCount;    //!< gps ���Ǹ���
    uint8_t imuAmSign;         //!< IMU �����쳣�����ź� 0: �ޱ����ź�  ���㣺�б���
    uint8_t imuDataState;     //!< IMU ���ݴ���״̬ 0: ����ֹͣ����  ���㣺���ݴ���
    float fGPSx;             //!< γ��
    float fGPSy;             //!< ����
    float fGPSz;             //!< ����
    float temp[2];            //!< �¶�
    float hemi[2];            //!< ʪ��
    int16_t altitude;          //!< �߶�
    uint16_t airspeed; //!< ����
    float incX;              //!< inclinometer X
    float incY;              //!< inclinometer Y
    float compassAng;         //!< ָ����Ƕ�
} SCDCMD_ENVIR_S;

typedef struct {
    int32_t cmdStat;        //!< �������
    int32_t triggerMode;  //!< �ع�ģʽ
    int32_t interval;               //!< ʱ��/�Ƕ� ���
    int32_t angOffset;              //!< �Ƕ�ƫ��
    uint32_t msgCount;       //!< ������
    uint32_t flashCount[CMR_NUMBER];
    uint32_t trigCount;

    float strAngle;
	float stpAngle;   //!< ������ʼ�Ƕ�
    int32_t reserved[1];            // total 60 Byte
} SCDCMD_CAMERA_S;

typedef struct {
    int32_t index;
    int32_t brightness;
    int32_t contrast;
    int32_t hue;
    int32_t saturation;
    int32_t sharpness;
    int32_t gamma;
    int32_t wbalance;
    int8_t trigger;
} USBCMR_CTRL_S;

typedef struct {
    int32_t cmdStat;         //!< USB�������
    int32_t triggerMode;   //!< �ع�ģʽ
    float currAngle;            //!< ��ǰת̨trigger�Ƕ�
    float itvAngle;              //!< �ع����Ƕ�
    float strAngle;
	float stpAngle;    //!< ������ʼ�Ƕ�
    int8_t trigger[USBCMR_MAX_NUMBER];
    float expValues[USBCMR_MAX_NUMBER]; //�ع�ʱ��
    uint16_t grayValue[USBCMR_MAX_NUMBER]; //�Ҷ�ֵ
    int16_t reserved[11];    //total 60 Byte
} USBCMR_TRIG_S;

typedef struct {
    int8_t pps;           //!< PPS�ź�
    int8_t utc;           //!< UTC�ź�
    int8_t gps;           //!< GPS�ź�
    int8_t reservedA[1]; //total 60 Byte
    uint32_t tZero;
    CSYSTEMTIME syncTime;
    int8_t reserved[36]; //total 60 Byte
} SCDCMD_TIMSYN_S;

//palm ���ݴ������
typedef struct {
    int32_t cmdStat;         //���ݴ���ʹ��
    int32_t imuState;        //imu���ݴ��
    int32_t gpsState;        //gps���ݴ��
    uint32_t dmiMileage;    //dmi ����� ��λm
    int32_t gpsType;       //GPS����
    uint32_t utcTime;    //UTCʱ����
    uint32_t utcYMDH;   //UTC������ʱ
    uint16_t stateCount;  //������
    uint16_t ppsSign;   //!< PPS�ź�  0 :���ź�   1�����ź�
    uint16_t imuUtcSync;    //imu UTCʱ��ͬ�� 0 :δͬ��   1��ͬ��
    uint16_t imuDataState;  //imu ���ݴ���״̬ 0: ����ֹͣ����  ���㣺���ݴ���
    uint16_t gpsDataSate;  //gps ���ݴ���״̬ 0: ����ֹͣ����  ���㣺���ݴ���
    uint16_t switchStat;    //����״̬
    uint32_t issDataSize;
    int8_t reserved[16]; //total 60 Byte
} SCDCMD_PALM_S;

//palm ת̨
typedef struct {
    int32_t cmdStat;        //ת̨ʹ��
    int32_t mode;     //ת̨����ģʽ
    float speed;                //�Ƕ�(��)/�ٶ�(dps)
    float angle;                //ת���Ƕ�
    int32_t dire;     //����
    float pulseAng;             //ÿ�������Ӧ�ĽǶ�
    int32_t cmrStat;        //���ʹ��
    float crtAngle;               //��ǰת���Ƕ�
    int8_t reserved[28];          //!<total 60 Byte
} SCDCMD_PALMSTG_S;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                           ���ݲɼ�
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

typedef struct {             //ͬʱ�������ݲɼ�ģʽ0
    int32_t cmdstat;
    int32_t m_eEcho;      //!< �ز�ģʽ
    int32_t rangemin;
	int32_t rangeMax;   //!< meters
    int32_t mpMode;
    uint16_t isNetFlow; //storageSetup()->setup 1�����豸��PC��PAD���洢��2: �豸�洢��8: U�̴洢
    int16_t roiSstr[ROI_NUMBER];
    int16_t roiSstp[ROI_NUMBER];
    int16_t roiTstr[ROI_NUMBER];
    int16_t roiTstp[ROI_NUMBER];
    uint16_t itvWorkTime;   //�豸�������ʱ�� ��λ��
    int8_t reserved[6];             //!<total 60 Byte
    int32_t fileState;
    int32_t dataType;       //storageSetup()->setup
    int32_t scanMode;    //����Զģʽ
    uint16_t resetSign;    //����RW �������
} SCDCMD_PROGRM_S;

//! �Ĵ�������
typedef struct {
    uint32_t regAddr;          //!< �Ĵ�����ַ
    uint32_t regValue;         //!< �Ĵ�������
    int32_t reserved[13];             //!<total 60 Byte
} SCDCMD_REGIST_S;

typedef struct {
    int32_t state;
    uint16_t vol;
    uint16_t amp;       //!< ������ѹ������
    uint16_t humidA;         //!< ʪ��A
    uint16_t tempA;           //!< �¶�A
    uint16_t humidB;          //!< ʪ��B
    uint16_t tempB;           //!< �¶�B
    uint16_t altitude;       //!< �����߶�
    uint32_t tdcaFact;        //!< ����ϵ��A  FPGA �Ĵ�������  liyp
    uint32_t tdcbFact;        //!< ����ϵ��B  FPGA �Ĵ�������  liyp
    uint16_t mSet;           //!< ���ز�����ϵ��  FPGA �Ĵ������� liyp
    int8_t reserved[32];             //!<total 60 Byte
} SCADA_STATE_S;

//!< FPGA ״̬���
typedef struct {
    uint8_t hardState;    //!< T0����
    uint8_t packState;  //!< ���ݴ��
    uint8_t tranState;  //!< ���ݴ���
    uint8_t simuState;  //!< �������ģʽ
    int32_t reserve[14];  //total 60 Byte
} SCADA_FPGA_STATE;

typedef struct {
    int32_t cmdstat;
    int32_t storePlace; //���ݴ洢λ��
    int32_t storeType;          //���ݴ洢����
    int32_t reserve[12];  //totao 60 Byte
} SCADA_DATAFUN_S;

typedef struct {
    int32_t cmdstat;
    int32_t dmiEncoder;             //!< DMI ����������
    float dmiCircum;            //!< DMI �ܳ� m
    int32_t dmiSelect;
    int32_t reserve[11];  //totao 60 Byte
} SCDCMD_DMI_S;

typedef struct {
    int32_t cmdstat;     //!< ���������״̬
    int32_t freqKHz;              //!< ������Ƶ��
    int32_t ampPercent;          //!< ����������
    int32_t optingTemp;          //!< �������¶�
    int32_t reserved[11];  //total 60 Byte
} SCDCMD_LASER_S;

//! �豸���Ʋ���
typedef struct {
    SCDCMD_ENVIR_S envCtrl;      //! ��������/״̬
    SCDCMD_CAMERA_S cmrCtrl;      //! �������/״̬
    SCDCMD_SCANER_S scnCtrl;      //! ɨ��������/״̬
    SCDCMD_TURRET_S stgCtrl;      //! ת̨����/״̬
    SCDCMD_LASER_S lsrCtrl;      //! ����������/״̬
    SCDCMD_PROGRM_S prgCtrl;      //! ɨ����������/״̬ ��෶Χ���ز�����
    SCDCMD_TIMSYN_S synStat;      //! ʱ��ͬ��״̬
    SCDCMD_DMI_S dmiData;        //! DMI ����
    SCADA_DATAFUN_S storeData;     //���ݴ洢
    USBCMR_TRIG_S usbCmrData;
    SCDCMD_CAMERA_S pmCmrData;     //! palm�������/״̬
    SCDCMD_PALM_S pmDate;        //! palm ����״̬
    SCDCMD_PALMSTG_S pmStgData;     //! palm ת̨����
    int8_t reserve[244];                //! total 1KB
} SCADA_CONTROL_S;

typedef struct {
    SCDCMD_SCANER_S scnCtrl;      //! ɨ��������/״̬
    SCDCMD_TURRET_S stgCtrl;      //! ת̨����/״̬
    SCDCMD_LASER_S lsrCtrl;      //! ����������/״̬
    SCDCMD_PROGRM_S prgCtrl;      //! ɨ����������/״̬
} SCADA_CONFIGCTR_S;

typedef struct {
    SCADA_CONFIGCTR_S ctlPara[SCDSCAN_TYPE_COUNT]; //720Byte
    int8_t reserve[304];
} SCADA_DEFAULTCTR_S;

#pragma pack(pop)

#pragma pack(push, 4)
//IMP�ļ���ʽ_v3.1.0.txt
struct Imp_MetaData_S {
    SCADA_META_S DataHead;  //�豸��Ϣ(1KB)
    SCADA_CONFIG_S scada_config;  //ϵͳ������Ϣ(2KB)
    SCDCMD_ENVIR_S scada_env;    //ϵͳ״̬��Ϣ(2KB)
    int8_t revEnv[1988];
    SCADA_DEFAULTCTR_S scada_defCtrl; //�豸Ĭ�Ͽ��Ʋ�����Ϣ(1KB)
    SCADA_CONTROL_S scada_control;  //�豸���Ʋ���(1KB)
    int8_t reservedA[1024]; //(1KB)
    SCDCAL_ARRAY_S scada_calib; //ģ��У�����(2KB)
    ALGSC_ARRAY_S scada_algscA; //Ԥ����ģ��������Ϣ(4KB)
    RANGE_CALIB_S scada_rangeCal; //����Ҷȸ�����(64KB)
    int8_t reservedB[2052]; //(2KB)
};

#pragma pack(pop)

class __star_export Metadata : public detail::basic_message<uint16_t, Imp_MetaData_S> {
public:
    uint64_t dataId() const override;
};

}
}
}
}


#endif //__STAR_SDK_IMP_HEADER_H
