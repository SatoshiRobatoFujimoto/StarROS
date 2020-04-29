/********************************************************************
 * $I
 * @Technic Support: <sdk@isurestar.com>
 * All right reserved, Sure-Star Coop.
 ********************************************************************/
#ifndef ICD_LIDAR_PRE_H
#define ICD_LIDAR_PRE_H
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "ICD_Common.h"
#pragma pack(2)

const int CPT_DELETE_LINE_COUNT = 2 ;  //��ʼʱɾ��ɨ���ߵĸ���
const int CPT_DELTETE_INDEX = 2;
const float CPT_DELTETE_RANGEMIN = 2;
const float CPT_DELTETE_RANGEMAX = 3;
const int CPT_DELETE_POINT_COUNT = 500 ; //һ��ɨ�������ٵ�ĸ���

const int  PR_FILE_NUM = 1024*2 ; //!< 2K���ļ�
const int  PRE_RING_NUM = 2 ;
const int DATA_POINT_COUNT =  0x10000 ; //��������Ϊ64K
const int DATA_POINT_COUNT_SMALL =  0x3E80 ; //��������Ϊ16K

const int IMP_SYNCWORD_COUNT = 8 ;
const int IMP_SYNCWORD = 0xA7 ;

//UTC TIME ECHO DATA
const unsigned short UTC_1ECHO_DATA = 0xEF01 ;
const unsigned short UTC_2ECHO_DATA = 0xEF02 ;
const unsigned short UTC_3ECHO_DATA = 0xEF03 ;
const unsigned short UTC_4ECHO_DATA = 0xEF04 ;
//LiDAR TIME ECHO DATA
const unsigned short LDT_1ECHO_DATA = 0xDF01 ;
const unsigned short LDT_2ECHO_DATA = 0xDF02 ;
const unsigned short LDT_3ECHO_DATA = 0xDF03 ;
const unsigned short LDT_4ECHO_DATA = 0xDF04 ;

const unsigned short ECHO_NUM_MARK = 0xFF ;
const int WEEK_SECOND_MAX = 604800;

typedef struct {
  char * buffAdd ;
  int buffSize ;
}PRE_BUFFER_S;

typedef enum {
  eDecodeOutNL, // means stop
  eDecodeOutDS, // data stream ring buffer only
  eDecodeOutFT, // save to text formate file only
  eDecodeOutFB, // save to binary formate file only
  eDecodeOutAll, // output all above formats
} IMP_DCOOPT_E ;

typedef struct _FilHeightPara{
    double minHeight;
    double maxHeight;
    _FilHeightPara(){
        minHeight = 0;
        maxHeight = 3500;
    }
}FilHeightPara_S;

typedef enum {
  ePreNULL = 0,
  ePreFile = 1,
  ePreRing = 2,
}PRE_OUTTYPE_E;

typedef struct RangeIntFilt{
    double R0;
    double  R1;
    double  R2;
    double  R3 ;
    double I0;
    double  I1;
    double  I2;
    double  I3;
    double  I4;
    double  I5;
    unsigned int PointFreqMin ;
    unsigned int   PointFreqMax;
    RangeIntFilt() {
        R0 = R1 = R2 =0 ;  R3 = 10000 ;
        I0 =  I1 = I2 = I3 = I4 = 0;  I5 = 8192;
        PointFreqMin=0;  PointFreqMax=600 ;
    }

}RANGE_ITNENSITY_FILT ;

typedef struct _fr_S {     //���롢ǿ���˲�ѡ��:  ���˷�Χ�ڵ�����
  float rngMin , rngMax ;  //!< �����С���ֵ
  int intMin, intMax ;     //!< ǿ����С���ֵ
  _fr_S () {
    rngMin = 1.0 ;
    rngMax = 3000.0 ;
    intMin = 0 ;
    intMax = 2047 ;
  }
} PRE_FltRInt_S ;

typedef struct _tr_S {//��Ч����ѡ��: ������Χ�ڵ�����
  float Rmin ,Rmax;   //!< �����С���ֵ
  _tr_S () {
    Rmin=1.0;
    Rmax=3000.0;
  }
} PRE_TR_S ;


typedef struct _fa_S {  //�Ƕ��˲�ѡ����˷�Χ�ڵ�����
  bool angleInvert;                        //by zhubing 2018.7.20
  double angleMin;
  double angleMax;
  double angleMin_filterAll;
  double angleMax_filterAll;
  double angleMin_filter[5];
  double angleMax_filter[5];
  double FreqMin_filter[3];
  double FreqMax_filter[3];
  double rangeMin_filter[3][3];
  double rangeMax_filter[3][3];
  double intensityMin_filter[3][3];
  double intensityMax_filter[3][3];
  _fa_S () {
    angleInvert = 0;               //by zhubing 2018.7.20
    angleMin = 0.0 ;
    angleMax = 360.0;
  }
} PRE_FltAngl_S ;

//�߶��˲�ѡ����˷�Χ�ڵ�����
typedef struct _fs_S {
  float altMin ;
  float altMax ;
  _fs_S() {
    altMin = 0;
    altMax = 3500;
  }
} PRE_FltSeaL_S ;



//�ݶ��˲�ѡ����˷�Χ�ڵ�����
typedef struct _grads_S {
  float   transverse_dis;
  size_t  horizontal_points;
  float   longitudinal_dis;
  size_t  vertical_points;

  _grads_S() {
    
  }
} PRE_FltGrads_S ;


typedef struct _imu_S {
  float utc2gps ; // (gps - utc)
  int xClcwise;   //X ��ת��-1 ˳ʱ�룬 1 ��ʱ��
  int yClcwise;   //Y ��ת��-1 ˳ʱ�룬 1 ��ʱ��
  int zClcwise;   //Z ��ת��-1 ˳ʱ�룬 1 ��ʱ��
  int zDirection; //Z ��ָ��1 ��,      -1 ��
  //���ý�(��λ: ��)
  double deltaR;  //Roll
  double deltaP;  //Pitch
  double deltaH;  //heading
  //ƽ����(��λ: mm)
  double deltaX; //IMU x����ƫ����
  double deltaY; //IMU y����ƫ����
  double deltaZ; //IMU z����ƫ����

  //��װ�Ƕ�(��λ: ��)
  double anlignX;
  double anlignY;
  double anlignZ;

  _imu_S() {
    utc2gps = 16 ;
    xClcwise = -1 ;
    yClcwise = -1 ;
    zClcwise = -1 ;
    zDirection = -1 ;
    deltaR=0;
    deltaP=0;
    deltaH=0;
    deltaX=0;
    deltaY=0;
    deltaZ=0;
	anlignX=0;
	anlignY=0;
	anlignZ=0;
  }
} PRE_IMU_S ;

typedef enum {
  eIMPDATA   =  0x1,
  eXYZIDATA   = 0x2,
  eARIDATA    = 0x4,
  eCRSDATA    = 0x8,
  eWUDDATA    = 0x10,
  eNARIDATA   = 0x12,
  eGEOXYZDAT  = 0x14,
  eCPTDATA    = 0x16,
  eSTDATA     = 0x18,
  ePLRDATA    = 0x20,
  eISSDATA    = 0x21,
  ePMISSDATA  = 0x22,
}DATA_TYPE_E;

typedef struct _of_f {
  bool isLas ;
  bool isXyz ;
  bool isXyzb ;
  bool isPlrt ;
  bool isPlrb ;
  bool isPtx ;
  bool isYsj ;
  bool isCrs ;
  bool isAgr ;
  bool isAgrb ;
  bool isCpt ;
 bool isRgp ;
 bool isGrid ;
  _of_f() {
   isLas=0;
   isXyz=0;
   isXyzb=0;
   isPlrt=0;
   isPlrb=0;
   isPtx=0;
   isYsj=0;
   isCrs=0;
   isAgr=0;
   isAgrb=0;
   isCpt=0;
   isRgp=0;
   isGrid=0 ;
  }
} PRE_OutFile_S ;

typedef struct _od_s {
   int ratio ;     //!< ������
   int viewAngle; //�ӳ��Ƕ� AP,TP ���� ��λ ��
   bool isTzero, isUTC ; //�����������UTCʱ�� T0 ʱ��
   bool is1Echo,is2Echo, is3Echo, is4Echo ; //����ز�����
   DATA_TYPE_E dataType ; //ʵʱ������������
   PRE_OUTTYPE_E ouputType ;
   float gridSize ;//��λ m
   bool isSlowdDtaSplit;//�����ݲ��
   _od_s() {
     ratio=1;
   viewAngle=100;
     isTzero=0;isUTC=0;
     is1Echo=1 ; is2Echo=1 ; is3Echo=1 ; is4Echo=1 ;
   dataType = eARIDATA ;
   ouputType = ePreFile ;
  gridSize = 1;
  isSlowdDtaSplit=true;
   }

} PRE_OutData_S ;

typedef struct _gps_s {

  float cMeridian; //���������߾��� ��λ��
  float B;  //γ�� ��λ��
  float L;   //���� ��λ��
  float H;  //�߶� ��λm
  _gps_s() {
  cMeridian=0.0;
  B=0.0;
  L=0.0;
  H=0.0;
  }
}PRE_CenterPoint_S;

typedef struct _ot_S {
  float Hs; //�豸�� ��λm
  float x0, y0,z0 ; //��������� ��λm
  float x1, y1,z1 ; //���ӵ����� ��λm
  float turnAngle;  //ת̨�Ƕ�  ��λ��
  _ot_S() {
  Hs=0.0;
  x0=0.0 ;
    y0=0.0;
    z0=0.0;
    x1=0.0;
    y1=0.0;
    z1=0.0;
  turnAngle=0.0;
  }
}PRE_BackCenter_S ;

typedef enum {
  WGS84      =0,
  BeiJing54  =1,
  XiAn80     =2,
  GJ2000 =3,
}EllipsoidType_E;

typedef enum  {
  UTM  =0,
  GUSS  =1,
  TM=2,
}ProjectionType_E;

typedef struct _gc_S{
  EllipsoidType_E ellipsolidtype;  //��������
  ProjectionType_E projectiontype; //ͶӰ����
  double CentralMeridian; //���������߾��� ��λ��
  double CentralLatitude; //ͶӰγ�� ��λ��
  bool projectFlag;      //XYZ �������
  _gc_S() {
  CentralMeridian=117.0;
  CentralLatitude=0.0;
  projectFlag = true ;
  }
}PRE_GeoProject_S;

typedef struct _SFileProcess {
  int filenum;        //ʣ��IMP�ļ����� 0~impCount
  int velocity;       //��ǰIMP�ļ����� 0~100
  _SFileProcess() {
    filenum=0;
    velocity=0;
  }
}FileProcess_S;

typedef struct  SbetRec{ //3*5*8+2*8 =136
  double ti;			///< ʱ�䣬��λ:����(time gps-sec. of week)
  double p[3];		///< γ�� ���� �߶� 24
  double wVel[3];		///< X�����ٶ� Y�����ٶ� Z�����ٶ� 24
  double rph[3];		///< roll, pitch, heading ,��λ:���� 24
  double w;			///< ���Ʒ�λ��
  double force[3];		///< X������ٶ� Y������ٶ� Z������ٶ� 24
  double aRate[3];		///< X������ٶ� Y������ٶ� Z������ٶ� 24
  SbetRec() {
    ti = 0.0;
    p[0] = 0.0;
    p[1] = 0.0;
    p[2] = 0.0;

    wVel[0] = 0.0;
    wVel[1] = 0.0;
    wVel[2] = 0.0;

    rph[0] = 0.0;
    rph[1] = 0.0;
    rph[2] = 0.0;
    w = 0.0;

    force[0] = 0.0;
    force[1] = 0.0;
    force[2] = 0.0;

    aRate[0] = 0.0;
    aRate[1] = 0.0;
    aRate[2] = 0.0;
  }
}SBET_Rec;

const int POS_COUNT_MAX = 0x8000 ;
typedef struct {
  char  sbetFile[FILENAME_MAX] ;                 //pos�ļ�·��
  SBET_Rec posData[POS_COUNT_MAX] ;
  int dataCount ;
}PRE_POS_S;

#define  RRE_VALIDR_MODLE     (0x1)   //��Ч����
#define  RRE_FILTRI_MODLE     (0x2)   //����Ҷ�
#define  RRE_FILTERA_MODLE    (0x4)   //�Ƕ�
#define  RRE_FILTERS_MODLE    (0x8)   //�߶�
#define  RRE_SAMPLE_MODLE     (0x10)  //����
#define  RRE_FILTGRADS_MODLE  (0x20)  //�ݶ��˲�

typedef struct {
  int funcSelect ;
  PRE_TR_S   tr ;         //��Ч�������
  PRE_FltRInt_S   fr ;     //����Ҷ��˲�
  PRE_FltAngl_S   fa ;     //�Ƕ��˲�
  PRE_FltSeaL_S   fs ;     //�߶��˲�
  PRE_FltGrads_S  fgs;     // �ݶ��˲�
  PRE_OutFile_S   op ;     //�������ļ����
  PRE_OutData_S   os ;     //��������˲�
} PRE_FILTER_S ;


#define  RRE_UTC_MODLE  (0x20)         //UTC��ֵģ��
#define  RRE_IMU_MODLE  (0x400)        //IMU
#define  RRE_CENTERPOINT_MODLE  (0x80) //ָ�������
#define  RRE_BACKCENTER_MODLE  (0x100) //���Ӷ���
#define  RRE_GEOPROJECT_MODLE  (0x200) //����ͶӰ

typedef struct {
  int funcSelect ;
  PRE_IMU_S   imuInfo ;         //IMU����
  PRE_CenterPoint_S  center;    //���е�λ�� ----UAָ������Զ���
  PRE_BackCenter_S  backcenter ; //���ӵ���е�λ��-----UA���Զ���
  PRE_GeoProject_S  geoproject;  //ͶӰ�������  --------AP/RA���Զ���
  PRE_POS_S  posSbet ;           //pos �켣����
} PRE_WSG_S ;

#define LIDAR_ECHO_NUM (4)
#define PRE_POINT_MAX (0x8000) //32KB
#define TSHORTPNT_HEAD (0xEF00)  //UTCʱ���ʶ
#define SHORTPNT_HEAD (0xDF00)   //T0ʱ���ʶ

typedef struct _shotHeadT{  //UTCʱ�����ݽṹ��
  unsigned short headFlag ;
  double time ;
  float scnAngle;           //����Ƕ�
  float stgAngle;           //ת̨����Ƕ�
  _shotHeadT() {
    scnAngle = stgAngle = 0 ;
    time = 0 ;
    headFlag = TSHORTPNT_HEAD ;
  }
} PRE_TSHOTHEAD_S ; //18

typedef struct _wudDATA{  //WUD UTCʱ�����ݽṹ��
  unsigned short headFlag ;
  double time ;
  unsigned int scnCount;           //����Ƕ�
  float range ;
  _wudDATA() {
    scnCount = 0 ;
    time = 0 ;
    headFlag = TSHORTPNT_HEAD ;
  }
} PRE_WUDDATA_S ;

typedef struct _shotRange { //�ز�����
  float range ;
  unsigned short uInt ;
  _shotRange() { range = 0 ; uInt = 0 ; }
}PRE_SHOTECHO_S; //6Byte

typedef struct {
  PRE_TSHOTHEAD_S ariHead ;
  PRE_SHOTECHO_S ariEcho[4] ;
}PRE_ARIPOINT_S;


const int SHOTPNT_ONE_SIZE = sizeof(PRE_SHOTECHO_S) + sizeof(PRE_TSHOTHEAD_S) ;
const int SHOTPNT_SIZE = sizeof(PRE_SHOTECHO_S)*LIDAR_ECHO_NUM + sizeof(PRE_TSHOTHEAD_S) ;
const int SHOTPNT_BUF_SIZE = SHOTPNT_SIZE*PRE_POINT_MAX ;
const int SHOTPNT_BUF_COUNT = 4;

typedef struct {
  PRE_SHOTECHO_S echoData[LIDAR_ECHO_NUM] ;
  int echoNum ;
}PRE_ECHODATA_S;

typedef struct _SHOTPNT_BUF {
  char shtPntFlow[SHOTPNT_BUF_SIZE] ;
  int bufSize ;
  _SHOTPNT_BUF() {
    bufSize = 0 ;
  }
}SHOTPNT_BUFFER_S;

typedef struct _SHOTPNT_RING{  //ʵʱ����
  SHOTPNT_BUFFER_S streamBuf[SHOTPNT_BUF_COUNT] ;
  int wrHead, rdTail ;
  _SHOTPNT_RING() { wrHead = rdTail = 0 ; }
} SHOTPNT_RING_S ;

typedef struct _BiGpsXYZ {
  double X;
  double Y;
  double Z;
  unsigned int m_uInt;
  double GPSTime;
  _BiGpsXYZ(){
    X= 0.0;
    Y = 0.0;
    Z = 0.0;
    m_uInt = 0;
    GPSTime = 0.0;
  }
}BiGpsXYZ;

typedef struct _rfansXyz {
  float X;
  float Y;
  float Z;
  unsigned short m_uInt;
  unsigned char laserId;
  float scnAng;
  unsigned int tZero;
  _rfansXyz(){
    X = 0.0;
    Y = 0.0;
    Z = 0.0;
    m_uInt = 0;
    laserId = 0;
  }
}RFANSXYZ_S;


#define TXYZIPNT_HEAD (0xCFCF)
#define XYZIPNT_HEAD (0xBFBF)
#define TSTPNT_HEAD 0xFFCF
#define STPNT_HEAD 0xFFFC

const  unsigned short UPDATA_FRAME_MASK = (0x8000);
const  unsigned short INTENSITY_VALUE_MASK = (0X1FFF);

const  unsigned short UPDATA_FRAME_BIT =15;
typedef struct _LSRXYZ {
  unsigned short headFlag ;
  float X;
  float Y;
  float Z;
  unsigned short m_uInt;  //15Bitλ Ϊ֡���±�ʶ��
  double GPSTime;
  _LSRXYZ(){
    X= 0.0;
    Y = 0.0;
    Z = 0.0;
    m_uInt = 0;
    GPSTime = 0.0;
  }
}LSRXYZ;

typedef struct _STDATA{
    unsigned short headFlag;
    unsigned int lineID;		//��¼ɨ�����ߺ�,��ɨ������תһ���ߺż�1)
    double time;	//��¼ɨ����ʱ��
    float distance;	//��¼ɨ���Ǽ���
    float hAngle;	//��¼ɨ����ˮƽ����
    float vAngle;	//��¼ɨ������ֱ����
    float x;
    float y;
    float z;
    unsigned short Intensity;//��¼ɨ����ǿ��
    _STDATA(){
        headFlag = STPNT_HEAD;
        lineID = 0;
        time = 0;
        distance = 0;
        hAngle = 0;
        vAngle = 0;
        x = 0;
        y = 0;
        z = 0;
        Intensity = 0;
    }
}STDATA;

typedef struct _xyzi_buffer{
  LSRXYZ dataXyzi[DATA_POINT_COUNT_SMALL];
  int bufSize ;
  _xyzi_buffer() {
    bufSize = 0 ;
  }
} XYZI_BUFFER_S;

typedef struct _xyzi_ring {
  XYZI_BUFFER_S dataPoints[PRE_RING_NUM] ;
  int wrHead, rdTail ;
  _xyzi_ring() {
    wrHead = 0 ;
    rdTail = 0 ;
  }
}XYZI_RINGBUFF_S;

const int FRAME_MIN_COUNT = 1000;
typedef struct {
  std::vector<LSRXYZ> xyzVectors[PRE_RING_NUM] ;
  int wrHead, rdTail ;
}XYZ_VECTOR_S;

#define  CRS_HEAD_FLAG (0xE7E7E7E7) //!< CRS��ʽ�������ݰ�ͷ��ʶ
#define  CRS_VERSION_FLAG (4)       //!< CRS��ʽ�汾��ʶ

//��������ϵͳʱ�䣬�����ڿ�ʼʱִ��ϵͳʱ��ͬ����
typedef struct  {
  unsigned short wYear;
  unsigned short wMonth;
  unsigned short wDayOfWeek;
  unsigned short wDay;
  unsigned short wHour;
  unsigned short wMinute;
  unsigned short wSecond;
  unsigned short wMilliseconds;
}CSYSTEMTIME , *PCSYSTEMTIME, LPCSYSTEMTIME;

//CRS ������������ͷ�ṹ
typedef struct _CRSHeader {
  unsigned int   packFlag ;    //!< ���ݰ���ʶ: 0xE7E7E7E7
  unsigned short versions ;    //!< �汾��
  unsigned short devNum ;      //!< �豸���
  unsigned int   serialNum ;   //!< ���к�
  unsigned char  devStaFlag ;  //!< �豸״̬��ʶ 0�����������쳣 �� 11 | 11 | 11(������״̬) | 11(ɨ����״̬)
  unsigned int   scanFrq ;     //!< ɨ��Ƶ��   ��λ RPS(ת/��)
  unsigned int   pointFrq ;    //!< ��Ƶ       ��λ Hz(��/��)
  unsigned int   angleRes ;    //!< �Ƕȷֱ��� ��λ ǧ��֮һ��
  uint_64   pulseNum ;    //!< DMI�������
  unsigned int   pointsCount ; //!< һ�����������ܵ���
  CSYSTEMTIME svrSysTime ;     //!< ����ɼ�ʱ�䣬��λʱ�䡣
}CRS_HEADER_S ;

//CRS �����ݽṹ
typedef struct _CRSPoint {
  //unsigned int Tstamp ;
  float angle ;               //!< ɨ��Ƕ�
  unsigned short range ;      //!< ��� ��λmm
  unsigned short intension ;  //!< ����ǿ��:
  _CRSPoint() {
    angle = 0 ;
    range = 0 ;
    intension = 0 ;
  }
}CRS_POINT_S ;

typedef struct _RGPPoint {
  unsigned int row ;
  unsigned int column ;
  float pointXYZ[3];
  unsigned int intensity ;
  _RGPPoint() {
    row = 0 ;
    column = 0 ;
    pointXYZ[0] = 0 ;
    pointXYZ[1] = 0 ;
    pointXYZ[2] = 0 ;
    intensity=0 ;
  }
}RGP_POINT_S ;

typedef struct {
  RGP_POINT_S dataPoints[DATA_POINT_COUNT] ;
}RGP_LINE_S ;

typedef struct {
  CRS_HEADER_S dataHead ;
  CRS_POINT_S dataPoints[DATA_POINT_COUNT] ;
}CRS_LINE_S ;


typedef struct _CRSRing {
  CRS_LINE_S dataLins[PRE_RING_NUM] ;
  int wrHead, rdTail , bufSize ;
  _CRSRing() {
    wrHead = 0 ;
    rdTail = 0 ;
    bufSize = 0 ;
  }
}CRS_RINGBUFF_S;

//CPT ������������ͷ�ṹ
typedef struct _CPTHeader {
  unsigned int   packFlag ;    //!< ���ݰ���ʶ: 0xE7E7E7E7
  unsigned short versions ;    //!< �汾��
  unsigned short devNum ;      //!< �豸���
  unsigned int   serialNum ;   //!< ���к�
  unsigned char  devStaFlag ;  //!< �豸״̬��ʶ 0�����������쳣 �� 11 | 11 | 11(������״̬) | 11(ɨ����״̬)
  unsigned int   scanFrq ;     //!< ɨ��Ƶ��   ��λ RPS(ת/��)
  unsigned int   pointFrq ;    //!< ��Ƶ       ��λ Hz(��/��)
  unsigned int   angleRes ;    //!< �Ƕȷֱ��� ��λ ǧ��֮һ��
  uint_64   pulseNum ;    //!< DMI�������
  unsigned int   pointsCount ; //!< һ�����������ܵ���
  CSYSTEMTIME svrSysTime ;     //!< ����ɼ�ʱ�䣬��λʱ�䡣
}CPT_HEADER_S ;

typedef struct {
  float m_fRange ;    	  ///<��������
  unsigned short m_uInt ; ///< intensity
}CPT_PULSE_S;

typedef struct {
  unsigned int m_tzero ; ///<
  int mpia_sel ;
  CPT_PULSE_S m_pulse[4]; ///<�ز�����
  double m_dAngleX;	 ///<���ɨ���
  double turnAngle ;   //ת̨�Ƕ�
} CPT_SHOT_S ;

typedef struct  {
  double X;		///< X����
  double Y;		///< Y����
  double Z;		///< Z����
} CPT_XYZ_S;

typedef struct {
  CPT_SHOT_S lasShot;
  double m_dGPSTime ;	///<GPSʱ��(��λ:����)
  CPT_XYZ_S m_pulse[4] ; ///<�����Ļز�����
} CPT_POINT_S ; // SHOTS_CALCOUT_S ;

typedef struct {
  CPT_HEADER_S dataHead;
  CPT_POINT_S dataPoints[DATA_POINT_COUNT];
}CPT_LINE_S ;



typedef struct _CPTRing {
  CPT_LINE_S dataLins[PRE_RING_NUM] ;
  int wrHead, rdTail , bufSize ;
  _CPTRing() {
    wrHead = 0 ;
    rdTail = 0 ;
    bufSize = 0 ;
  }
}CPT_RINGBUFF_S;

typedef struct _pre_outdata_ring {
  CRS_RINGBUFF_S *crsFlowPrt ;
  CPT_RINGBUFF_S *cptFlowPrt ;
  SHOTPNT_RING_S *shotPntRingPrt ;
}PRE_COORD_S ;

#ifndef LIDAR_HARDWARE
//liyp:���� PCI_lib.cpp ����ɱ������
#include <string>
#include <vector>
using namespace std;

typedef struct {
  vector<string> lasFilesPath ;
  int strIndex ;
  int stpIndex ;
}LAS_FILE_STRUCT ;
#endif


#pragma pack()
#endif
