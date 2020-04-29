/********************************************************************
 * $I
 * @Technic Support: <sdk@isurestar.com>
 * All right reserved, Sure-Star Coop.
 ********************************************************************/
#ifndef ICD_LIDAR_API_H_
#define ICD_LIDAR_API_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ICD_LiPRE_API.h"
#include "ICD_LiDAR_PRE.h"
#pragma pack(2)
#include <time.h>
const int IMP_HEADER_SIZE = 0x14000;    //IMP�ļ�ͷ��С 80KB

const int END_LEFT_SIZE = 0xA00000;    //IMP�ļ�ͷ��С 131KB

const char LIDAR_IPADDR_DFLT[] = "192.168.0.188" ;  //!< Ĭ��IP��192.168.0.188
const char LIDAR_IPADDR_WIFI[] = "192.168.10.1" ;   //!< ���߿��� IP��192.168.10.1
const char RFANS_IPADDR_DFLT[] = "224.0.0.1" ;  //!< Ĭ��IP��192.168.0.188
const int LIDAR_MSGPORT = 2008;  //��Ϣ���ݶ˿�
const int LIDAR_PNTPORT = 2009;  //�����ݶ˿�
const int LIDAR_IMGPORT = 2011;  //ͼ�����ݶ˿�
const int LIDAR_SLWPORT = 2012;  //�����ݶ˿�
const int LIDAR_UDPPORT = 2013;  //UDP CMD �˿�

//added by zhubing for getGPS INFO
const int LIDAR_GPSPORT = 2020;  //�������ݴ���˿�

const int RFANS_DATA_UDPPORT = 2014 ;
const int RFANS_CMD_UDPPORT = 2015;

const int LIDAR_GPSMSG_UDPPORT = 2016;  //�˿�


const int SCADA_UDP_CPORT = 2017 ;// ����UDP�˿ں�

const int NET_SLOW_TIMEOUT = 1000 ; //΢��
const int CHNL_OPEN_ID = 7 ;        //socket
const int IMPFILE_CLOSE_COUNT = 50 ;
const int Y_M_D_SIZE = 9; //size of year,month ,day string; including
const int H_M_S_SIZE = 7; //hour, minute,second string; including 0

static const int DATA_FILE_SIZE = 0x8000000; // 128 * 1024 * 1024 =128M Bytes
static const int USBDATA_FILE_SIZE = 0x40000000; // 128 * 1024 * 1024 =1GM Bytes
static const int SLOWDATA_SIZE = 0x100000;  // 1M Bytes
static const int SLOW_FILE_SIZE = 0x20000000;  // 512M Bytes

typedef enum {
  eAPilot = 0 ,
  eRAngle,
  eUArm,
  eTPilot,
  eAK,
  eRFans,
  eSL,
  eCFans,
  eUT = 8 ,
	IRA,
} DEVICE_TYPE_E;

typedef enum {     //!<�ز�����
  eEchoAll = 0,
  eEchoOne = 1,    //!< 1�ز�
  eEchoTwo = 2,    //!< 2�ز�
  eEchoTri = 4,    //!< 3�ز�
  eEchoFor = 8,    //!< 4�ز�
} ECHO_TYPE_E ;

const int SCDSCAN_TYPE_COUNT = 3 ;

typedef enum {     //!<ɨ��ɼ�����
  eScanNear = 0,   //!< ������ģʽ
  eScanMiddle = 1, //!< ����ģʽ
  eScanMiddleFar = 2, //!< ��Զ����ģʽ
  eScanFar = 3,    //!< Զ����ģʽ
} SCDSCAN_TYPE_E ;

typedef enum {               //!< ����ع�ģʽ
  eCmrTimerNero,             //!< ʱ���ع�, ����λ����
  eCmrTimerZero,             //!< ʱ���ع�, ����λ����
  eCmrAngleNero,             //!< �Ƕ��ع�, ����λ����
  eCmrAngleZero,             //!< �Ƕ��ع�, ����λ����
  eCmrPosnNero,              //!< λ���ع�, ����λ����
  eCmrPosnZero,              //!< λ���ع�, ����λ����
  eCmrRangeNero,             //!< �����ع�, ����λ����
  eCmrRangeZero,             //!< �����ع�, ����λ����
} SCDCMR_MODE_E;


typedef enum {             //!< ת̨����ģʽ
  eTurretReset     = 0x00, //!< ����
  eTurretContinue  = 0x01, //!< ����ģʽ
  eTurretArea      = 0x02, //!< ����ģʽ
  eTurretPosition  = 0x04, //!< λ��ģʽ
  eTurretNextTrige = 0x08, //!< ��һ���ع��
  eTurretStop      = 0x10, //!< ֹͣ
  eTurretSearch    = 0x20, //!< ��ѯ
} SCDTURRET_MODE_E ;

typedef enum {        //GPS����
  eGpsApplanix = 0,
  eGpsTrimble=1 ,
  eGpsNoval=2 ,
  eGpsJavat=3 ,
  eGpsNmea = 4,
  eGpsGsof = 5,
  eGPSInpps = 6,
} GPS_TYPE_E ;



typedef enum {//��λ���Ŀ���ģʽ
  eLidarNet ,  // Acting as Server, accept cmd from Ethernet
  eLidarGui ,  // controlling the LiDAR through GUI
  eLidarUrt ,  // Acting as Server, accept cmd from Uart
  eDataSave ,  // for Data Handle: Save locally
  eDataFlow ,  // for Data Handle: Transfer through Net
  eLidarNetAndUrt,
  eLidarFlyUrt,
} LiDAR_TYPE_E ;

typedef enum {
  eFileStay, // no action to file handler
  eFileNew,
  eFileRenew,
  eFileClose,
  eFileCloseAll,
  eFileImpClose,
  eFileIssClose,
} LiDARImp_Action_E ;



/********** Structures ***********/
const int LiDAR_SHOTBUF_SIZE = 0x40000 ;  //256KB
const int LiDAR_RINGBUF_NUM = 1024;       //���󻺴�Ϊ256MB

const int LiDAR_SHOTBUF_MINI_SIZE = 0x8000 ; //32KB ÿ��ɨ���� 3000 ���㣬��һ�ز����ݴ�С���� 54KB
const int LiDAR_RINGBUF_MINI_NUM = 8192;     //32KB*8192 = 256MB

const int LiDAR_CALC_RINGBUF_NUM = 256;
typedef struct { //for PCI DMA, 256 MBytes in total
  int wrHead, rdTail ,bfSize;
  char * buffer[LiDAR_RINGBUF_NUM]; //[LiDAR_RINGBUF_SIZE] ;
  int ROW,COLUMN ; //liyp �ڴ����֯��ʽPCI interface: 1024*256KB; USB interface:8192*32KB
  int readCount ;    //һ�ζ�buffer�ĸ���
} SHOTS_RINGBUF_S ;

inline int SHOTS_RINGBUF_COUNT(SHOTS_RINGBUF_S *mtRingBuff) {
  int tmpCount = 0;
  if (mtRingBuff->wrHead > mtRingBuff->rdTail) {
    tmpCount = mtRingBuff->wrHead - mtRingBuff->rdTail;
  } else if (mtRingBuff->wrHead < mtRingBuff->rdTail){
    tmpCount = mtRingBuff->ROW - mtRingBuff->rdTail + mtRingBuff->wrHead;
  }
  return tmpCount ;
}

const int SLOW_RINGBUF_SIZE = 0x80000;//1MB
const int SLOW_READ_SIZE = 0x4000 ; //16KB
const int SLOW_WRITE_SIZE = 0x40000 ; //256KB
const int SLW_DATA_RDCOUNT = 16 ;

const int SLOW_READ_SIZE_1K = 0x400; //1KB

typedef struct {
  int wrHead, rdTail;
  char buffer[SLOW_RINGBUF_SIZE];
} SLOW_RINGBUF_S ;
const unsigned int IMPHEAD_SYN_WORD = 0xA7A7A7A7;
const unsigned int IMG_SYN_WORD = 0xF9F9F9F9 ;
const unsigned int JPG_SYN_WORD = 0xFAFAFAFA ;
const unsigned int CMPIMG_SYN_WORD = 0xF8F8F8F8 ;
typedef struct {
  unsigned int synWord ;
  unsigned short cmrNo ;
  unsigned int imgSize ;
  float currAngle ;
} USBCMR_IMGHEADER_S ;

// buffer size

const int USBCmr_MAXNUMBER = 2 ;

const int IMG_WIDTH = 2592;
const int IMG_HEIGHT = 1944;
const int IMG_YUYBITS = 16;
const int IMG_SIZEFIX = 40;
const int IMG_HEAD_SIZE = 54 ;

const int IMG_SIZEMAX = sizeof(USBCMR_IMGHEADER_S) + (IMG_WIDTH*IMG_HEIGHT*3) +IMG_HEAD_SIZE ;


//const int CAMERA_IMGRBUF_SIZE = IMG_SIZEMAX ;
const int CAMERA_IMGRBUF_SIZE = 15*1024*1024 ;

const int CAMERA_RINGBUF_NUM = 2 ;
const int JPG_BUFFER_SIZE = (512*1024)  ;

typedef struct {
  int wrHead, rdTail , bfSize;
  int BUFFER_MAX_SIZE ;
  char * buffer[CAMERA_RINGBUF_NUM]; //
} IMAGE_RINGBUF_S ;

const int MSG_BUFFER_SIZE = 68;
typedef struct {
  int wrHead, rdTail ;
  char msgArray[LiDAR_RINGBUF_NUM][MSG_BUFFER_SIZE] ; //64 > sizeof(SCADA_CMDRPT_U)
} MESSG_RINGBUF_S ;

const int GPMSG_BUFFER_SIZE = 1024;

typedef struct {
  int wrHead, rdTail ;
  struct {
    char gpsMsg[GPMSG_BUFFER_SIZE] ;
    unsigned short msgSize ;
  } msgArray [LiDAR_RINGBUF_NUM];
} GPSMSG_RINGBUF_S ;

inline int LDRPROG_GPSMSG_RING_WRITE(GPSMSG_RINGBUF_S* msgRing ,char *mtMsg,int size) {
  char *tmpWrtMsg = NULL ;
  if( msgRing ) {
    tmpWrtMsg = msgRing->msgArray[msgRing->wrHead].gpsMsg ;
    memset(tmpWrtMsg, 0, GPMSG_BUFFER_SIZE) ;
    msgRing->msgArray[msgRing->wrHead].msgSize = 0 ;
    memcpy(tmpWrtMsg, mtMsg, size) ;
    msgRing->msgArray[msgRing->wrHead].msgSize = size ;
    msgRing->wrHead = (msgRing->wrHead+1) % LiDAR_RINGBUF_NUM ;
  }
  return size ;
}

inline int LDRPROG_GPSMSG_RING_READ(GPSMSG_RINGBUF_S *msgRing , char *mtReadMsg, int size)  {
  char *tmpMsg = NULL ;
  if(msgRing) {
    if(msgRing->wrHead !=  msgRing->rdTail) {
    tmpMsg = msgRing->msgArray[msgRing->rdTail].gpsMsg ;
    size = msgRing->msgArray[msgRing->rdTail].msgSize ;
    memcpy(mtReadMsg, tmpMsg, size) ;
    msgRing->rdTail = (msgRing->rdTail+1)% LiDAR_RINGBUF_NUM ;
    } else {
    size = 0 ;
    }
  }
  return size ;
}

inline int LDRPROG_GPSMSG_RING_INIT(GPSMSG_RINGBUF_S *msgRing) {
  if( msgRing ) {
  memset(msgRing, 0, sizeof(GPSMSG_RINGBUF_S) ) ;
  }
  return 0 ;
}

typedef enum {
  eLidarProgError ,
  eLidarProgStandBy ,
  eLidarProgReady ,
  elidarProgPre ,
  eLidarProgEnvir , //
  eLidarProgCamera=5 , //
  eLidarProgMotor , //
  eLidarProgStage , //
  eLidarProgLaser , //
  eLidarProgStart , //
  eLidarProgAction=10 ,  // eLidarProgReady <-> eLidarProgAction
  eLidarCmrScaning ,  // eLidarProgReady <-> eLidarCmrScaning
  eLidarCmrWaitImg1 ,
  eLidarCmrWaitImg2 ,
  eLidarCmrTrigOK,
  eLidarStopAll,
  eLidarProgBreak,
  eLidarCmrInit ,
  eLidarCmrInited ,
  eLidarCmrFinished,
  eLidarUCmrInit,
  eLidarUCmrScaning,
  eLidarUCmrWaiting,
  eLidarUCmrFinished,
  eLidarCheckStagStop,
  eLidarUCmrTrigger,
  eLidarCmrTrigger,
} LDRPROG_STAT_E ;

typedef enum
{
  eUsbDiskBreak,
  eUsbDiskInsert,
}LDRUSB_STATE_E;

typedef enum {
  eDFrameReady,
  eDFrameFinished,
  eDFrameReadChange,
}SL_DFRAME_E;

//�豸״̬����
typedef struct {
  LDRPROG_STAT_E lsrState ;
  float  nRangeScopeMin_;
  float  nRangeScopeMax_ ;       //ʱ�䴰��
  int    nReflectMin_;
  int    nReflectMax_ ;          //����ķ���ǿ��(0, 2047)��
  float  fDataCollectSpeed_ ;    //���� KB/s;
  double fDataTotal_ ;           //�������� KB
  unsigned int   curImpSize_ ;           //��ǰIMP��С KB
  int scadaFlag_ ;               //����ͳ�Ƶ�λ�ã� 1:��λ��ͳ�ƣ�0����λ��ͳ��
  PRE_DATASTATE_E dataState;     //����״̬
  unsigned int diskSize ;        //���̿ռ�ʣ���С
  LDRUSB_STATE_E usbDiskStat;    //
  SL_DFRAME_E frameState;
  int reserve[2] ;               //total 60 Byte
} LiDAR_DATAINFO_S ;

/*
    �ַ���Э��
*/
#define PARA_STR_LENGTH (64) //��������
#define CMD_STR_LENGTH (1024) //�ַ������

#define DEV_MODE_HEAD "m"       //�豸(����/ת̨/���/������ҵ)ģʽ
#define DEV_FREQ_HEAD "freq"     //�豸(ת̨/ɨ����)�ٶ�
#define DEV_ROIS_HEAD "rois"     //�豸ɨ��������ROI
#define DEV_ROIT_HEAD "roit"     //�豸ת̨�������ROI
#define DEV_REPORT_HEAD "a"       //����

//������
#define LSR_RUN_HEAD "LSR_RUN"
#define LSR_STP_HEAD "LSR_STP"
#define LSR_ASK_HEAD "LSR_ASK"

#define LSR_FREQ_HEAD   DEV_FREQ_HEAD  //!< ����ƽ��
#define LSR_POWER_HEAD  "power" //!< ���⹦��
#define LSR_SIMU_HEAD  "simu"  //!< ����ģʽ

//ɨ����
#define SCN_RUN_HEAD "SCN_RUN"
#define SCN_STP_HEAD "SCN_STP"
#define SCN_ASK_HEAD "SCN_ASK"

#define SCN_COUNT_HEAD "scncnt"   //!< ���ת����Ȧ��
#define SCN_STEADY_HEAD "scnstdy" //!< ����ٶ�ת��״̬

#define SCN_SPD_HEAD "rpm"        //!< ɨ�����ٶ�

//ת̨���
#define STG_RUN_HEAD "STG_RUN"
#define STG_STP_HEAD "STG_STP"
#define STG_ASK_HEAD "STG_ASK"

#define STG_CURANG_HEAD "angle"
#define STG_SPD_HEAD    "dps"          //!< ת̨�ٶ�
#define STG_MODE_HEAD DEV_MODE_HEAD  //!< ת̨ģʽ

//���ݲɼ���ҵ
#define TSK_RUN_HEAD "TSK_RUN"
#define TSK_STP_HEAD "TSK_STP"
#define TSK_BRK_HEAD "TSK_BRK"
#define TSK_ASK_HEAD "TSK_ASK"

#define TSK_MIN_HEAD      "min"           //!< ��С���
#define TSK_MAX_HEAD      "max"           //!< �����
#define TSK_RANGE_HEAD    "range"           //!< ���
#define TSK_ECHO_HEAD     "echo"          //!< �ز�����
#define TSK_MP_HEAD       DEV_MODE_HEAD   //!< mpģʽ
#define TSK_NETFLOW_HEAD  "netflow"       //!< ������
#define TSK_ROIS_HEAD     DEV_ROIS_HEAD   //!< ɨ��Ƕ�ROI
#define TSK_ROIT_HEAD     DEV_ROIT_HEAD   //!< ת̨�Ƕ�ROI
#define TSK_SYNCTIME_HEAD "syct"          //!< ͬ��ʱ����Ϣ��ʽ
#define TSK_RESETSIGN_HEAD "rsts"         //!< �����ź�����
#define TSK_DTYPE_HEAD     "dtype"       //!< ��������
#define TSK_ITVWTIME_HEAD   "itvtime"      //!< �������ʱ��



//�������
#define CMR_RUN_HEAD "CMR_RUN"
#define CMR_STP_HEAD "CMR_STP"
#define CMR_ASK_HEAD "CMR_ASK"

#define CMR_MODE_HEAD DEV_MODE_HEAD  //���ģʽ
#define CMR_ROI_HEAD DEV_ROIT_HEAD   //�Ƕ�ROI
#define CMR_ITV_HEAD DEV_FREQ_HEAD   //�������

//����USB���
#define UCM_RUN_HEAD "UCM_RUN"
#define UCM_STP_HEAD "UCM_STP"
#define UCM_ASK_HEAD "UCM_ASK"

#define UCM_MODE_HEAD DEV_MODE_HEAD //���ģʽ
#define UCM_ROI_HEAD DEV_ROIT_HEAD  //�Ƕ�ROI
#define UCM_A_HEAD "cmra"           //���A ����
#define UCM_B_HEAD "cmrb"           //���B ����
#define UCM_AEXP_HEAD "expa"           //���A �ع�ֵ
#define UCM_BEXP_HEAD "expb"           //���B �ع�ֵ

// added by zhubing 2020.2.17
// MF ��������
#define MF_RUN_HEAD "MF_RUN"
#define MF_H_HEAD     "h"             //!< ����
#define MF_V_HEAD     "v"             //!< �����ٶ�
#define MF_DCOL_HEAD     "Dcol"       //!< �����ܶ�
#define MF_DROW_HEAD     "Draw"       //!< �����ܶ�
#define MF_PULSES_HEAD   "Pulse"       //!< ��������
#define MF_FREQ_HEAD   "Frequency"       //!< ��Ƶ

//���ݴ洢����
#define STORAGE_RUN_HEAD "SRG_RUN"  //!< �洢����
#define STORAGE_ASK_HEAD "SRG_ASK"  //!< �洢��ѯ

//AK�豸���ڿ��ƣ�����ͨ��lidar.cfg �ļ���ȡ
#define LDR_STR_HEAD "LDR_START"  //!< ����ɨ��
#define LDR_STP_HEAD "LDR_STOP"   //!< ֹͣɨ��
#define LDR_BRK_HEAD "LDR_BREAK"  //!< ��ͣɨ��

//DMI
#define DMI_RUN_HEAD "DMI_RUN"   //!< DMI��������
#define DMI_ASK_HEAD "DMI_ASK"   //!< DMI������ѯ

#define DMI_CODE_HEAD "code"     //!< dmi ����������
#define DMI_CIRC_HEAD "circ"     //!< DMI �����ܳ�

//PALM���
#define PCM_RUN_HEAD "PCM_RUN" //����palm ���
#define PCM_STP_HEAD "PCM_STP" //ֹͣpalm ���
#define PCM_ASK_HEAD "PCM_ASK" //��ѯpalm ���

//PALM ���ݴ���
#define PDT_RUN_HEAD "PDT_RUN" //����palm ���ݲɼ�
#define PDT_STP_HEAD "PDT_STP" //ֹͣ palm ���ݲɼ�
#define PDT_ASK_HEAD "PDT_ASK" //��ѯ palm ״̬


//PALM RTת̨
#define PST_RUN_HEAD "PST_RUN" //����palm ת̨
#define PST_STP_HEAD "PST_STP" //ֹͣpalm ת̨
#define PST_ASK_HEAD "PST_ASK" //ֹͣpalm ת̨

#define PST_RES_HEAD "res"    //ÿ�������Ӧ�ĽǶ�
#define PST_ANTI_HEAD "anti"   //Ĭ��Ϊ�����򣬴�"-anti"Ϊ������
#define PST_ANGLE_HEAD "pangle"
#define PST_CURANG_HEAD "curang"  //palm ת̨��ǰ�Ƕ�

#define LDR_ASK_HEAD "LDR_ASK" //�豸״̬��ѯ
#define ENV_ASK_HEAD "ENV_ASK" //����״̬��ѯ
#define CFG_ASK_HEAD "CFG_ASK" //�豸������Ϣ��ѯ
//
/**
            ״̬
**/
#define LDR_RPT_HEAD "LDR_RPT"    //!< �豸״̬����
#define LSR_RPT_HEAD "LSR_RPT"    //!< ������
#define SCN_RPT_HEAD "SCN_RPT"    //!< ɨ����
#define STG_RPT_HEAD "STG_RPT"    //!< ת̨
#define CMR_RPT_HEAD "CMR_RPT"    //!< ����������
#define UCM_RPT_HEAD "UCM_RPT"    //!< ����USB���
#define TSK_RPT_HEAD "TSK_RPT"    //!< ���ݲɼ���ҵ
#define ENV_RPT_HEAD "ENV_RPT"    //!< ���� ״̬
#define DMI_RPT_HEAD "DMI_RPT"    //!< ���� ״̬

#define PCM_RPT_HEAD "PCM_RPT"    //!< PALM �������
#define PDT_RPT_HEAD "PDT_RPT"    //!< PALM���ݴ���
#define CFG_RPT_HEAD "CFG_RPT"    //!< ������Ϣ����


/**
            ״̬����
**/
#define CMR_TCOUNT_HEAD "tc"	//palm�����������
#define CMR_FLASH1_HEAD "f1"	//palm���1��������
#define CMR_FLASH2_HEAD "f2"	//palm���2��������
#define CMR_FLASH3_HEAD "f3"	//palm���3��������
#define CMR_FLASH4_HEAD "f4"	//palm���4��������
#define CMR_FLASH5_HEAD "f5"	//palm���5��������
#define CMR_FLASH6_HEAD "f6"	//palm���6��������
#define DMI_COUNT_HEAD "dmiCount"	//dmi �����
#define IMU_SYNC_HEAD "imuSync"	//imu ʱ��ͬ���ź�
#define IMU_DATA_HEAD "imuData"	//imu ���ݴ���
#define IMU_WARN_HEAD "imuwarn"	//imu ����
#define GPS_DATA_HEAD "gpsData"	//gps ���ݴ���
#define GPS_TYPE_HEAD "gpsType"	//gps����
#define UTC_YMD_HEAD  "utc"	//utcʱ��
#define UTC_SEC_HEAD  "sutc"	//utcʱ��
#define SATE_COUNT_HEAD "sate"	//������
#define PPS_SYNC_HEAD "pps"	//pps�ź�
#define GPS_X_HEAD "gpsx"	//γ��
#define GPS_Y_HEAD "gpsy"	//����
#define GPS_Z_HEAD "gpsz"	//����
#define INCY_X_HEAD "incx"	//�����x��
#define INCY_Y_HEAD "incy"	//�����y��
#define TEMP_A_HEAD "tempA"	//�¶ȴ�����A
#define TEMP_B_HEAD "tempB"	//�¶ȴ�����B
#define HEMI_A_HEAD "hemiA"	//ʪ�ȴ�����A
#define HEMI_B_HEAD "hemiB"	//ʪ�ȴ�����B
#define AIR_HEIGHT_HEAD "altitude"	//��ѹ�߶�
#define AIR_SPEED_HEAD "airspeed"	//����
#define RANGE_MIN_HEAD "rangMin"	//������Сֵ
#define RANGE_MAX_HEAD "rangMax"	//�������ֵ
#define REF_MIN_HEAD "refMin"	//ǿ����Сֵ
#define REF_MAX_HEAD "refMax"	//ǿ�����ֵ
#define DATA_SPEED_HEAD "dataSpeed"	//���ݲɼ�����
#define DATA_TOTAL_HEAD "dataTotal"	//��������
#define IMP_SIZE_HEAD "impSize"	//��ǰIMP��С
#define CMR_COUNT_HEAD "cmrc"	//������
#define CMR_TRGA_HEAD "trigerA"	//���A ����ʱ��
#define CMR_TRGB_HEAD "trigerB"	//���B ����ʱ��
#define CMR_FLASHA_HEAD "flashA"	//���A shutter�ź�ʱ��
#define CMR_FLASHB_HEAD "flashB"	//���B shutter�ź�ʱ��
#define STATE_POWUP_HEAD "powup"	//�ϵ�
#define STATE_READY_HEAD "ready"	//׼��
#define STATE_ERROR_HEAD "error" // ����״̬
#define STATE_WORKING_HEAD "working"	//����
#define STATE_STOPED_HEAD "stoped"	//ֹͣ
#define STATE_PAUSE_HEAD "pause"	//��ͣ
#define STATE_SICK_HEAD "sick"	//����״̬
#define STATE_INIT_HEAD "init"	//ת̨��ʼ��
#define STATE_FIXING_HEAD "fixing"	//ת̨��λ��
#define STATE_FIXED_HEAD "fixed"	//ת̨��λ���
#define STATE_POSEND_HEAD "stpposm"	//ת̨λ��ģʽ����
#define STR_IMU_HEAD "strimu"	//imu ���ݲɼ�
#define STR_GPS_HEAD "strgps"	//gps ���ݲɼ�
#define STP_IMU_HEAD "stpimu"	//ֹͣimu���ݲɼ�
#define STP_GPS_HEAD "stpgps"	//ֹͣgps���ݲɼ�

#define LIDAR_STATE_HEAD "state"  //״̬
#define LIDAR_FLAG_HEAD "flag"  //״̬
#define LIDAR_DATA_HEAD "data"  //״̬
#define LIDAR_FRAME_HEAD "frame"  //״̬

#define DEVICE_TYPE_HEAD "deviceType"
#define DEVICE_REV_HEAD "deviceRev"
#define FREQ_MIN_HEAD "freqMin"
#define FREQ_MAX_HEAD "freqMax"
#define POWER_MIN_HEAD "powerMin"
#define POWER_MAX_HEAD "powerMax"
#define SCNSPEED_MIN_HEAD "scnSpdMin"
#define SCNSPEED_MAX_HEAD "scnSpdMax"
#define STGSPEED_MIN_HEAD "stgSpdMin"
#define STGSPEED_MAX_HEAD "stgSpdMax"
//#define CMR_COUNT_HEAD "cmrCount"
#define MPIA_MODE_HEAD "mpiaMode"

#define DATA_BUTTON_HEAD "enDataBtn"  //palm���ݲɼ�����ʹ��

#define CMD_START_CHAR  '<'
#define CMD_STOP_CHAR   '>'
#define CMD_START_STRING  "<"
#define CMD_STOP_STRING  ">"
#define PARA_START_STRING "-"
#define PARA_VALUE_STRING  "="

#pragma pack()
#endif
