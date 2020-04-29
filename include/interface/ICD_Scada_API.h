/********************************************************************
 * $I
 * @Technic Support: <sdk@isurestar.com>
 * All right reserved, Sure-Star Coop.
 ********************************************************************/
#ifndef ICD_SCADA_API_H_
#define ICD_SCADA_API_H_
#include "ICD_Common.h"
#include "ICD_LiDAR_API.h"
#include "ICD_UsbCamera.h"
#include <istoolkit/icnLiDARAPI.h>
#include "ICD_LiDAR_PRE.h"

#pragma pack(2)
typedef enum {
  eScadaPci ,
  eScadaNet ,
  eScadaUrt ,
  eScadaSim ,
  eScdSimDa ,
  eScdSimIm ,
  eScadaUsb ,
  eScadaUDP,  //udpRfans
  eScadaUdpPalm,
  eScadaGrdUdp, //v+AP �����ն�
  eScadaSN,//starnavi
} SCADA_TYPE_E ;

typedef enum {
  eDevCmdIdle = 0,
  eDevCmdWork ,
  eDevCmdSimu ,
  eDevCmdBreak ,
  eDevCmdReset ,
  eDevCmdAsk , //��ѯָ��
} SCDEV_CMD_E ;

typedef enum {
  eNoMode  = 0,
  eFarMode ,
  eNearMode
} SCADA_RANGE_S ;

typedef enum{           //�ַ����ѽ�����ϢID
  eRevMsgLaser   = 0x01,
  eRevMsgScanner = 0x02,
  eRevMsgEnv     = 0x04,
  eRevMsgProgam  = 0x08,
  eRevMsgPCM     = 0x10,
  eRevMsgPDT     = 0x20,
  eRevMsgPST     = 0x40,
  eRevMsgHeader  = 0x80,
  eRevFinish     = 0xFF
}SCDID_MESREV_E;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                           ������
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
const int SCDLSR_POWR_DFLT = 100 ;          //!< ����������Ĭ��ֵ��100%
const int SCDLSR_POWR_MIN  = 50 ;
const int SCDLSR_POWR_MAX  = 100 ;
const int SCDLSR_FREQ_DFLT = 200 ;         //!< ������Ƶ��Ĭ��ֵ��200KHz
const int SCDLSR_FREQ_MIN  = 30 ;
const int SCDLSR_FREQ_MAX  = 500 ;         //!< 500 kHz

//! laser
typedef struct {
  SCDEV_CMD_E cmdstat ;     //!< ���������״̬
  int freqKHz;              //!< ������Ƶ��
  int ampPercent ;          //!< ����������
  int optingTemp ;          //!< �������¶�
  int reserved[11] ;  //total 60 Byte
} SCDCMD_LASER_S;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                            ɨ����
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ��תģʽ
typedef enum {
  eScanPlusPosA,            //!< ����λ��ģʽ, ������ת
  eScanPlusPosR,            //!< ���λ��ģʽ, ������ת
  eScanMinusPosA,           //!< ����λ��ģʽ, ������ת
  eScanMinusPosR,           //!< ���λ��ģʽ, ������ת
  eScanPlusSpeed,           //!< �ٶ�ģʽ, ������ת
  eScanMinuSpeed            //!< �ٶ�ģʽ, ������ת
} SCDSCN_MODE_E;

// ɨ����ת��״̬
typedef enum {
  standReady = 0x0 ,  //׼��״̬
  eScanStand = 0x1 ,  //ת��״̬
  eScanError = 0x2,
}SCDSCN_STATE_E ;

const int SCDSCN_SPEED_DFLT     = 1800;       //!< ����ٶ�Ĭ��ֵ��1800
const int SCDSCN_SPEED_MIN      = 0;
const int SCDSCN_SPEED_MAX      = 6000;

//! scanner
typedef struct{
  SCDEV_CMD_E cmdstat ;
  SCDSCN_MODE_E mode ;
  float angSpeed ;           //!< depends on SCDSCN_MODE_E
  unsigned short roistr[4], roistp[4] ;
  unsigned int speedCount ;   //ɨ����count
  SCDSCN_STATE_E speedState ;  //ɨ����ת��״̬
  int grade;
  short reserved[10] ;  //total 60 Byte
} SCDCMD_SCANER_S;

//! motor hardValue
typedef struct{
  unsigned int spdTmpc ;
  unsigned int amcSpdCount ;
  unsigned int amcCrcValue ;
  int reserved[54] ; //total 60 Byte
} SCDMACH_SCANER_S;



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                            ת  ̨
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ����Ĭ��ֵ
const int SCDSTG_ANGLE_MIN    = 0;
const int SCDSTG_ANGLE_MAX    = 360;
const float SCDSTG_SPEED_MIN = 0.5 ;   // degree/sec
const float SCDSTG_SPEED_MAX = 3.0 ;   // degree/sec
const float SCDSTG_SPEED_DFLT = 3.0 ;  // degree/sec

//!< AMC���״̬
typedef enum {
  eAMCRdy = 0x0 ,
  eAMCRst,
  eAMCRsted,
  eAMCSpeedup,    //�ٶȼ���ģʽ
  eAMCSpdWork,      //�ٶȼ���
  eAMCJogo,       //
  eAMCPst ,       //λ��ģʽ
  eAMCPsted ,     //λ��ģʽ���
  eAMCCtnPsted ,  //����λ��ģʽ���
  eAMCWaitScaner,
  eAMCNxtPst,
  eAMCError,
  eAMCSetSpeed,
  eAMCCheckSpeed,
  eAMCUpdataFilter,
} SCDAMC_STATUS_E ;

//!< ת̨��״̬
typedef enum {
  eTurretNormal     = 0x0,
  eTurretReadyArea  = 0x1,
  eTurretSpeedArea  = 0x2,
  eTurretScanArea   = 0x3,
  eTurretStopArea   = 0x4,
  eTurretReadyPos   = 0x5,
  eTurretTrigePos   = 0x6,
  eTurretWorkePos   = 0x7,
  eTurretStopPos    = 0x8,
  eTurretCheckError = 0xE,
  eTurretSystemBusy = 0xF,
  eTurretWaitScaner,
  eTurretCmrTirgOk,
  eTurretPCChkError,
} SCDTURRET_MISTATE_E ;

//!< ת̨��״̬
typedef enum {
  eTurretInit     = 0x1,
  eTurretHold     = 0x2,
  eTurretDisable  = 0x3,
  eTurretRun      = 0x4,
  eTurretError    = 0x5,
} SCDTURRET_MASTATE_E ;

typedef struct {
  SCDTURRET_MISTATE_E currMiStat ;
  SCDTURRET_MASTATE_E currMaStat ;
}SCDBCD_MOTORSTATE_S;

const float TRIGGER_IMAGE_SPEED = 1; //DPS
//! turret
typedef struct{
  SCDEV_CMD_E cmdstat ;
  SCDTURRET_MODE_E mode ;
  float angSpeed ;
  float strAngle , stpAngle;          //!< ������ʼ�Ƕ�
  float currAng ;                     //!< ��ǰ�Ƕ�
  unsigned short roistr[4], roistp[4] ;
  SCDTURRET_MISTATE_E currMiStat ;
  SCDTURRET_MASTATE_E currMaStat ;
  int reserved[3] ;  //total 60 Byte
} SCDCMD_TURRET_S;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                            �������
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
typedef struct{
  SCDEV_CMD_E cmdstat ;
  SCDSCN_MODE_E mode ;//��ת����
  float angle;//ת���Ƕ�
  float currAng;//��ǰ�Ƕ� ����λ�ñ�������ǰ�Ƕ�
  int reserved[11] ; //total 60 Byte
}SCDCMD_STEPMOTOR_S;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                            ��   ��
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//! �豸��������
typedef struct {
  GPS_TYPE_E gpsType ;      //!< GPS����Ĭ��ֵ��eGpsTrimble
  unsigned int utcTime ;    //!< ������ʱ
  unsigned int utcSec ;     //!< UTC����
  bool pps ;               //!< PPS�ź� 0 :���ź�   ���㣺���ź�
  unsigned char satelliteCount ;    //!< gps ���Ǹ���
  unsigned char imuAmSign ;         //!< IMU �����쳣�����ź� 0: �ޱ����ź�  ���㣺�б���
  unsigned char imuDataState  ;     //!< IMU ���ݴ���״̬ 0: ����ֹͣ����  ���㣺���ݴ���
  float fGPSx ;             //!< γ��
  float fGPSy ;             //!< ����
  float fGPSz ;             //!< ����
  float temp[2];            //!< �¶�
  float hemi[2];            //!< ʪ��
  short altitude ;          //!< �߶�
  unsigned short airspeed ; //!< ����
  float incX ;              //!< inclinometer X
  float incY ;              //!< inclinometer Y
  float compassAng;         //!< ָ����Ƕ�
} SCDCMD_ENVIR_S  ;

// added by zhubing 2020.2.17
typedef struct  
{
	double mf_h;
	double mf_v;
	double mf_Dcol;
	float  _mf_freq;
	float _mf_cycle;
	char reserved[28]; // total 60 Byte
}SCDCMD_MF_S;


// ����Ĭ��ֵ
const int     SCDCMR_TIMER_MIN = 0;
const int     SCDCMR_TIMER_MAX = 6553;
const int     SCDCMR_TIME_DFLT = 4000;     //!< ʱ���ع�Ĭ��ֵ��4000ms
const int     SCDCMR_ANGLE_MIN = 0;
const int     SCDCMR_ANGLE_MAX      = 360;
const int     SCDCMR_ANGLE_DFLT     = 180; //!< �Ƕ��ع�Ĭ��ֵ��180��
const int     SCDCMR_ANGLOFFST_DFLT = 0;   //!< �Ƕ�ƫ��Ĭ��ֵ��0

//Ĭ��ֵΪ�� ʹ��lidar.cfg�е����ò���
const int     SCDCMR_DMI_ENCODER = 0 ;    //!< DMI����������
const float     SCDCMR_DMI_CIRCUM = 0 ;  //!< DMI �ܳ�

const int CMR_A_INDEX = 0;
const int CMR_B_INDEX = 1;

#define CMR_NUMBER 6 // 1 trige + 6 flash
typedef struct {
  SCDEV_CMD_E cmdStat ;        //!< �������
  SCDCMR_MODE_E triggerMode ;  //!< �ع�ģʽ
  int interval ;               //!< ʱ��/�Ƕ� ���
  int angOffset ;              //!< �Ƕ�ƫ��
  unsigned int msgCount;       //!< ������
  unsigned int flashCount[CMR_NUMBER] ;
  unsigned int trigCount ;

  float strAngle , stpAngle;   //!< ������ʼ�Ƕ�
  int reserved[1] ;            // total 60 Byte
} SCDCMD_CAMERA_S ;


//!< USB�����������ICD_UsbCamera.h ��ת�Ƶ����ﶨ�壬���ͷ�ļ�����������

const float USBCMR_EXPVALUE_DEF = 2000.0f;
const int USBCMR_A_INDEX = 0 ;
const int USBCMR_B_INDEX = 1 ;
typedef struct {
  SCDEV_CMD_E cmdStat ;         //!< USB�������
  SCDCMR_MODE_E triggerMode ;   //!< �ع�ģʽ
  float  currAngle ;            //!< ��ǰת̨trigger�Ƕ�
  float itvAngle ;              //!< �ع����Ƕ�
  float strAngle , stpAngle;    //!< ������ʼ�Ƕ�
  bool trigger[USBCmr_MAXNUMBER] ;
  float expValues[USBCmr_MAXNUMBER] ; //�ع�ʱ��
  unsigned short grayValue[USBCmr_MAXNUMBER] ; //�Ҷ�ֵ
  short reserved[11] ;    //total 60 Byte
} USBCMR_TRIG_S ;

typedef struct {
  bool pps;           //!< PPS�ź�
  bool utc;           //!< UTC�ź�
  bool gps;           //!< GPS�ź�
  char reservedA[1] ; //total 60 Byte
  unsigned int tZero ;
  CSYSTEMTIME syncTime ;
  char reserved[36] ; //total 60 Byte
} SCDCMD_TIMSYN_S ;

//palm ���ݴ������
typedef struct {
  SCDEV_CMD_E cmdStat ;         //���ݴ���ʹ��
  SCDEV_CMD_E imuState ;        //imu���ݴ��

  SCDEV_CMD_E gpsState ;        //gps���ݴ��

  unsigned int dmiMileage ;    //dmi ����� ��λm

  GPS_TYPE_E gpsType ;       //GPS����
  unsigned int utcTime ;    //UTCʱ����
  unsigned int utcYMDH;   //UTC������ʱ
  unsigned short stateCount;  //������
  unsigned short ppsSign  ;   //!< PPS�ź�  0 :���ź�   1�����ź�
  unsigned short imuUtcSync ;    //imu UTCʱ��ͬ�� 0 :δͬ��   1��ͬ��
  unsigned short imuDataState ;  //imu ���ݴ���״̬ 0: ����ֹͣ����  ���㣺���ݴ���
  unsigned short gpsDataSate ;  //gps ���ݴ���״̬ 0: ����ֹͣ����  ���㣺���ݴ���
  unsigned short switchStat;    //����״̬
  unsigned int issDataSize;
  char reserved[16] ; //total 60 Byte
}SCDCMD_PALM_S ;

//palm ת̨ģʽ
typedef enum {
  eStageSpeed,  //�ٶ�ģʽ
  eStageAngle,  //�Ƕ�ģʽ
}SCDMODE_PALMSTG_E;

//palm ת̨����
typedef enum {
  eStagePlus ,  //��
  eStageMinus,  //��
}SCDDIRE_PALMSTG_E;

//palm ת̨
typedef struct {
  SCDEV_CMD_E cmdStat ;        //ת̨ʹ��
  SCDMODE_PALMSTG_E mode ;     //ת̨����ģʽ
  float speed ;                //�Ƕ�(��)/�ٶ�(dps)
  float angle ;                //ת���Ƕ�
  SCDDIRE_PALMSTG_E dire ;     //����
  float pulseAng ;             //ÿ�������Ӧ�ĽǶ�
  SCDEV_CMD_E cmrStat ;        //���ʹ��
  float crtAngle ;               //��ǰת���Ƕ�
  char reserved[28] ;          //!<total 60 Byte
}SCDCMD_PALMSTG_S ;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                           ���ݲɼ�
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#define MPMODE_REVISE_RANGE (120)  //!< MPģʽ�����ӵ����� ��λm
typedef enum {
  eProgrmModeNon = 0 ,
  eProgrmModeMP = 1 ,
}SCDMODE_PROGRAM_E;

#define ROI_NUMBER (2)

typedef enum {
  eNetFlow = 0x01,
  eDeviceSave = 0x02 ,
  ePCSave = 0x04 , //?
  eUSBSave = 0x08,
  eMemorySave = 0x10,
}SCDMODE_DATAPLACE_S;

typedef struct {             //ͬʱ�������ݲɼ�ģʽ0
  SCDEV_CMD_E cmdstat ;
  ECHO_TYPE_E m_eEcho ;      //!< �ز�ģʽ
  int rangemin, rangeMax ;   //!< meters
  SCDMODE_PROGRAM_E mpMode ;
  unsigned short isNetFlow ; //storageSetup()->setup 1�����豸��PC��PAD���洢��2: �豸�洢��8: U�̴洢
  short roiSstr[ROI_NUMBER], roiSstp[ROI_NUMBER] ;
  short roiTstr[ROI_NUMBER], roiTstp[ROI_NUMBER] ;
  unsigned short itvWorkTime ;   //�豸�������ʱ�� ��λ��
  char reserved[6] ;             //!<total 60 Byte
  LiDARImp_Action_E fileState ;
  DATA_TYPE_E dataType ;       //storageSetup()->setup
  SCDSCAN_TYPE_E scanMode ;    //����Զģʽ
  unsigned short resetSign ;    //����RW �������
} SCDCMD_PROGRM_S ;


//! �Ĵ�������
typedef struct {
  unsigned int regAddr;          //!< �Ĵ�����ַ
  unsigned int regValue;         //!< �Ĵ�������
  int reserved[13] ;             //!<total 60 Byte
} SCDCMD_REGIST_S;



typedef struct {
  LDRPROG_STAT_E state ;
  unsigned short vol, amp ;       //!< ������ѹ������
  unsigned short humidA ;         //!< ʪ��A
  unsigned short tempA;           //!< �¶�A
  unsigned short humidB;          //!< ʪ��B
  unsigned short tempB;           //!< �¶�B
  unsigned short altitude ;       //!< �����߶�
  unsigned int tdcaFact ;        //!< ����ϵ��A  FPGA �Ĵ�������  liyp
  unsigned int tdcbFact ;        //!< ����ϵ��B  FPGA �Ĵ�������  liyp
  unsigned short mSet ;           //!< ���ز�����ϵ��  FPGA �Ĵ������� liyp
  char reserved[32] ;             //!<total 60 Byte
} SCADA_STATE_S;

typedef struct {
  SCDEV_CMD_E cmdstat ;
  int reserve[14] ;  //total 60 Byte
} SCADA_POST_S ;

//!< FPGA ״̬���
typedef struct {
  unsigned char hardState ;    //!< T0����
  unsigned char packState ;  //!< ���ݴ��
  unsigned char tranState ;  //!< ���ݴ���
  unsigned char simuState ;  //!< �������ģʽ
  int reserve[14] ;  //total 60 Byte
} SCADA_FPGA_STATE ;


const SCDMODE_DATAPLACE_S SCDCMD_STRGPLACE_DFLT = eNetFlow ;
const DATA_TYPE_E SCDCMD_STRGTYPE_DFLT = eIMPDATA ;

typedef struct {
  SCDEV_CMD_E cmdstat ;
  SCDMODE_DATAPLACE_S storePlace ; //���ݴ洢λ��
  DATA_TYPE_E storeType ;          //���ݴ洢����
  int reserve[12] ;  //totao 60 Byte
} SCADA_DATAFUN_S ;

typedef struct {
  SCDEV_CMD_E cmdstat ;
  int dmiEncoder ;             //!< DMI ����������
  float dmiCircum ;            //!< DMI �ܳ� m
  int dmiSelect ;
  int reserve[11] ;  //totao 60 Byte
} SCDCMD_DMI_S ;

typedef struct {
  DEVICE_TYPE_E  deviceType; //�豸����
  unsigned int   deviceRev;     //!< �豸���
  int mpiaMode;
  int nRangScopeMin,  nRangScopeMax;            //!< scan distances ��m �ף�
  int	nLaserFreqMin,    nLaserFreqMax;            //!< e.g (50 - 300))Frequence (KHz)
  int nLaserPowerMin,   nLaserPowerMax;           //!< e.g Min(51%) (���ʵ�λ %��
  int fScannerSpeedMin, fScannerSpeedMax;         //<! rpm
  float fStageSpeedMin, fStageSpeedMax;           //!< ת̨�ٶȱ߽�
  int cmrCount;                                   //!< �����������
  int reserve[1] ;  //totao 60 Byte
} SCDCFG_LIMIT_S;
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// *                           �豸״̬
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
const bool SCDCMD_PPS_DFLT = false;         //!< PPS�ź�Ĭ��ֵ�����ź�
const bool SCDCMD_UTC_DFLT = false;         //!< UTC�ź�Ĭ��ֵ�����ź�
const bool SCDCMD_CMR_DFLT = false;         //!< Shutter�ź�Ĭ��ֵ�����ź�
const bool SCDCMD_GPS_DFLT = false;         //!< GPS�ź�Ĭ��ֵ�����ź�

//! ��Ϣ��ʽ
//! liyp���ṹ���С�ı�ʱ�����޸� MSG_BUFFER_SIZE ��С
typedef struct cmdRpt{
  LiDAR_MSGID_E cmdId;               //!< �����
  int isAsk ;
  union {
    SCADA_STATE_S    statData ;      //! �豸״̬
    SCDCMD_ENVIR_S   envData ;       //! ��������/״̬
    SCDCMD_CAMERA_S  cmrData ;       //! �������/״̬
    SCDCMD_SCANER_S  scnData ;       //! ɨ��������/״̬
    SCDCMD_TURRET_S  stgData ;       //! ת̨����/״̬
    SCDCMD_LASER_S   lsrData ;       //! ����������/״̬
    SCDCMD_PROGRM_S  prgData ;       //! ɨ����������/״̬
    SCDCMD_TIMSYN_S  synData ;       //! ʱ��ͬ��״̬
    SCDCMD_REGIST_S  regData ;       //! �Ĵ�����д
    USBCMR_CTRL_S    umrData ;       //! USB�������/״̬
    USBCMR_TRIG_S    umrTrig ;       //! USB����ع�
    SCDCMD_STEPMOTOR_S stepMtoData ; //! �����������/״̬
    LiDAR_DATAINFO_S infoData;       //! ʵʱ���ݲɼ���Ϣ
    SCADA_FPGA_STATE fpgaData ;      //! FPGA״̬
    SCADA_DATAFUN_S  storageData ;   //! �洢��ʽ
    SCDCMD_DMI_S     dmiData ;        //! DMI ����
    SCDCMD_CAMERA_S  pmCmrData ;     //! palm�������/״̬
    SCDCMD_PALM_S    pmDate ;        //! palm ����״̬
    SCDCMD_PALMSTG_S pmStgData ;     //! palm ת̨����
    SCDCFG_LIMIT_S   limitData ;
// added by zhubing 2020.2.17
	SCDCMD_MF_S		 mfData;
    char msgstream[60] ;
  };
  cmdRpt() {
    isAsk = false ;
    cmdId = eMsgSoftCk ;
  }
} SCADA_CMDRPT_U ;

#define SCADA_CMD_COUNT (32)
typedef struct _CMDRPTS{
  SCADA_CMDRPT_U cmds[SCADA_CMD_COUNT] ;
  int count ;
  _CMDRPTS(){
    count = 0 ;
  }
}SCADA_CMDRPTS_S ;

//! �豸���Ʋ���
typedef struct {
  SCDCMD_ENVIR_S      envCtrl ;      //! ��������/״̬
  SCDCMD_CAMERA_S     cmrCtrl ;      //! �������/״̬
  SCDCMD_SCANER_S     scnCtrl ;      //! ɨ��������/״̬
  SCDCMD_TURRET_S     stgCtrl ;      //! ת̨����/״̬
  SCDCMD_LASER_S      lsrCtrl ;      //! ����������/״̬
  SCDCMD_PROGRM_S     prgCtrl ;      //! ɨ����������/״̬ ��෶Χ���ز�����
  SCDCMD_TIMSYN_S     synStat ;      //! ʱ��ͬ��״̬
  SCDCMD_DMI_S        dmiData ;        //! DMI ����
  SCADA_DATAFUN_S     storeData ;     //���ݴ洢
  USBCMR_TRIG_S       usbCmrData;
  SCDCMD_CAMERA_S     pmCmrData ;     //! palm�������/״̬
  SCDCMD_PALM_S       pmDate ;        //! palm ����״̬
  SCDCMD_PALMSTG_S    pmStgData ;     //! palm ת̨����
  char reserve[244] ;                //! total 1KB
} SCADA_CONTROL_S ;



typedef struct {
  SCDCMD_SCANER_S     scnCtrl ;      //! ɨ��������/״̬
  SCDCMD_TURRET_S     stgCtrl ;      //! ת̨����/״̬
  SCDCMD_LASER_S      lsrCtrl ;      //! ����������/״̬
  SCDCMD_PROGRM_S     prgCtrl ;      //! ɨ����������/״̬
} SCADA_CONFIGCTR_S ;

typedef struct {
  SCADA_CONFIGCTR_S ctlPara[SCDSCAN_TYPE_COUNT] ; //720Byte
  char reserve[304] ;
}SCADA_DEFAULTCTR_S ;

///  ��ʴ�����Э����ض���

#define CMD_MODE_DISTANCE_NEAR 0x01
#define CMD_MODE_DISTANCE_MIDL 0x02
#define CMD_MODE_DISTANCE_FARR 0x03
#define CMD_SCAN_SPEED 0x06
#define CMD_TURRET_SPEED 0x08
#define CMD_TURRET_WORKMODE 0x09
#define CMD_TURRET_RESSET 0x03
#define CMD_LIDAR_START 0x00
#define CMD_LIDAR_STOP 0x01
#define CMD_CMR_START 0x02
#define CMD_CMR_STOP 0x03
#define CMD_TURRET_RESET 0X04
#define CMD_TURRET_RESET_STOP 0X05//006δ���
#define CMD_CMR_ANGLE_INTERVAL 0x06
#define CMD_CMR_ANGLE_BEGIN 0x07 //Э��δ˵��
#define CMD_CMR_ANGLE_END 0x08
#define CMD_LASER_MODE 0x03

#define STATE_TYPE_MIN_DISTANCE		0x08 //�����С����
#define STATE_TYPE_MAX_DISTANCE		0x09 //���������
#define STATE_TYPE_MIN_REFLECT		0x0A //��С����ǿ��
#define STATE_TYPE_MAX_REFELEC		0x10 //�����ǿ��
#define STATE_TYPE_TRANS_RATE		0x0B //��������
#define STATE_TYPE_DATA_TOTAL		0x0C //��������
#define STATE_TYPE_TEMPERATURE		0x0F //�¶�

enum UartScreenStatus{
	US_IDLE,
	US_INIT,
	US_LASER_STATUS_WAITING,
	US_SCANER_STATUS_WAITING,
	US_TURRET_STATUS_WAITING,
	US_LASER_MODE_WAITING,
	US_SCAN_SPEED_WAITING,
	US_TURRET_SPEED_WAITING,
	US_TURRET_MODE_WAITING,
	US_CMR_AGL_BEGIN_WAITING,
	US_CMR_AGL_INTV_WAITING,
	US_CMR_AGL_END_WAITING,
	US_WORKING
};

enum UartDeviceType {
	UART_TYPE_NONE,
	UART_TYPE_LIDAR,
	UART_TYPE_CMR,
	UART_TYPE_TURRET_RESET
};

enum UartTurretMode {
	UART_TURRET_MODE_CNTU,
	UART_TURRET_MODE_180D,
	UART_TURRET_MODE_360D
};

enum LaserStatus {
	LASER_STATUS_IDLE,
	LASER_STATUS_WORKING,
	LASER_STATUS_SIMU
};

enum ScanerStatus {
	SCANER_STATUS_IDLE,
	SCANER_STATUS_WORKING
};

enum TurretStatus {
	TURRET_STATUS_IDLE,
	TURRET_STATUS_WORKING
};

struct UartSceenParam {
	UartDeviceType deviceType;
	//device mode
	LaserStatus laserStatus;
	ScanerStatus scanerStatus;
	TurretStatus turretStatus;
	// lidar 
	SCDSCAN_TYPE_E distanceMode; // ����Զ
	char scanSpeed[8];
	char turretSpeed[8];
	bool turretReseting;
	UartTurretMode turretMode;//continue, 180, 360
	//cmr
	int cmrAglBegin;
	int cmrAglEnd;
	int cmrAglIntv;
};


#pragma pack()
#endif
