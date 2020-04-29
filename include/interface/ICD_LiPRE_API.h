/********************************************************************
 * $I
 * @Technic Support: <sdk@isurestar.com>
 * All right reserved, Sure-Star Coop.
 ********************************************************************/
#ifndef ICD_LIPRE_API_H
#define ICD_LIPRE_API_H
#include "ICD_LiDAR_PRE.h"

#pragma pack(2)
#ifndef RFAN_DEVICE
     #define IMPFILE_EXTNAME "/*.imp"
#else
     #define IMPFILE_EXTNAME "/*.isf"
#endif

#define ISSFILE_EXTNAME "/*.iss"
#define EXTNAME_SIZE (strlen(ISSFILE_EXTNAME) )

typedef enum {
  eApRealTm = 0,//real-time process
  eApAftwards,//afterwards process
  eRaRealTm,
  eRaAftwards,
  eUrRealTm,
  eUrAftwards,
  eTpRealTm,
  eTpAftwards,
  eAKRealTm,
  eAKAftwards,
} WORK_FLOW_E;

typedef enum {
  eIMPDIR = 0,
  eISSDIR = 1,
}LiPRE_DIRTYPE_E;

typedef struct lsrPoint {
  float range[LIDAR_ECHO_NUM];             //�ز����� 0~3echo
  float scnAngle;                          //����Ƕ�
  float stgAngle;                          //ɨ�����Ƕ�   
  unsigned short uInt[LIDAR_ECHO_NUM];		 //�ز�ǿ��
} LSRPOINT_S ;

typedef enum {
  eDataNormal,
  eDataAllZero,
  eDataLargeZero,
  eDataFrameFinished,
}PRE_DATASTATE_E;

typedef enum
{
  eLaser0 = 0x1,
  eLaser1 = 0x2,
  eLaser2 = 0x4,
  eLaser3 = 0x8,
  eLaser4 = 0x10,
  eLaser5 = 0x20,
  eLaser6 = 0x40,
  eLaser7 = 0x80,
  eLaser8 = 0x100,
  eLaser9 = 0x200,
  eLaser10 = 0x400,
  eLaser11 = 0x800,
  eLaser12 = 0x1000,
  eLaser13 = 0x2000,
  eLaser14 = 0x4000,
  eLaser15 = 0x8000,
  elaserALL = 0xFFFF,
}RFANS_LASERNUM_E;

typedef struct {
  LSRPOINT_S pntData[PRE_POINT_MAX];
  int pntCount ;
  PRE_DATASTATE_E dataState;
  unsigned int utcSec ; //UTCʱ�䣬����
}PRE_POINTS_S;

typedef struct _ih_s {
	bool imphead;
	_ih_s() {
     imphead=0;
	}
}PRE_ImpHead_S ;

typedef struct _rc_S {
  bool b_rc;   //�Ҷȸ���  ģ�鹦��ѡ�� 
  bool b_coor; //�������ѡ��  ģ�鹦��ѡ�� 
  bool b_invert; //�Ƕ����䷴��ѡ��by zhubing 2018.7.20
  double p1_A;
  double p2_A;
  double p1_B;
  double p2_B;
  double rangecorr[2048]; 
  double rangecorrB[2048]; 
  _rc_S() {
  b_rc=0;
  b_coor=0;
  b_invert=0;  //by zhubing 2018.7.20
  p1_A=1.0;
  p2_A=0.0;
  p1_B=1.0;
  p2_B=0.0;

  }
}PRE_RCoor_S ;

typedef struct  Meteotic {
  double WaterVapPressure; //ˮ����ѹ
  double dRelMoisture;    //���ʪ��
  double Temperature;   //�¶�
  double Perssure;  //��ѹ
  double cofR;   //����˳�������
}Meteotic_s;

typedef struct _Dec{
  bool isOutT0Stage;
  bool isOutT0Inclt;
  bool isOutPackageNo;
  bool isOutT0Pos;
  bool isOutARI;
  bool isOutT0Cmr;
  bool isEnvir;
  bool isOutT0RF;
  bool isOutAMCW;
  bool isOutPC;
  bool isOutGPS;
  bool isOutIMU;
  _Dec(){
    isOutT0Stage=0;
    isOutT0Inclt=0;
    isOutPackageNo=0;
    isOutT0Pos=0;
    isOutARI=0;
    isOutT0Cmr=0;
    isEnvir=0;
    isOutT0RF = 0;
    isOutAMCW = 0;
    isOutPC = 0;
    isOutGPS = 0;
    isOutIMU = 0;
  }
} Pre_Dec_S;

typedef struct _grid_S{
  double gridSize ;
  double flightVel ;
  _grid_S() {
    gridSize=1.0;
    flightVel=5.0 ;
  }
}GRID_S;

typedef struct _gui_S {   //lidarPre �ӿ����ò���
  PRE_ImpHead_S  ih;      //�Ƿ��imp�ļ�ͷ�����ò���
  PRE_FILTER_S  filter;   //����������˲�
  PRE_RCoor_S rs;         //�����У����
  PRE_WSG_S wgs84;        //����������
  Pre_Dec_S dec;          //�����Щ�����ļ�
  GRID_S grid ;
} PRE_CONTROL_S ;

#pragma pack()

#endif