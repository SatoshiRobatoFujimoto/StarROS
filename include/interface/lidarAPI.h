/********************************************************************
 * $I
 * @Technic Support: <sdk@isurestar.com>
 * All right reserved, Sure-Star Coop.
 ********************************************************************/
#ifndef SS_LIDAR_API_H_
#define SS_LIDAR_API_H_

#include "ICD_LiDAR_API.h"
#include "ICD_LiDAR_TSK.h"
#include "ICD_Scada_API.h"
#include "ICD_UsbCamera.h"
//#include "ICD_LiDAR_PRE.h"
//added by zhubing 2020.1.3
#ifndef _WINDOWS
	#include "../navigator/include/ssNavigator.h"
	#include "../navigator/include/nav_ccoordconvert.h"
	#include "../navigator/include/nav_datatype.h"
#endif // !WINDOWS

class CUsbCamera ;
class CScada ;
class CLidarConfig ;
class IdataHandle ;
class CLifetime ;
class CLidarReporter ;
class CPalmMode ;
class CStrPtcTool ;
class CSvrSocket ;
class CNavSerial ;
class CdataCom ;

#if defined(_MSC_VER)
#ifdef LIDARAPI_EXPORTS
#define LIDAR_API_DLL __declspec(dllexport)
#else //LIDARAPI_EXPORTS
#define LIDAR_API_DLL __declspec(dllimport)
#endif //LIDARAPI_EXPORTS
#else //defined(_MSC_VER)
#define LIDAR_API_DLL
#endif //defined(_MSC_VER)
// added by zhubing 2020.2.13
#define PI 3.1415926

class LIDAR_API_DLL CLidarAPI {
  private:
    //<! LiDAR State
    LDRPROG_STAT_E m_eprogstat;
    LDRPROG_STAT_E cmrScanSta_;
    GPSMSG_RINGBUF_S m_gpsMsgRing ;
    SHOTS_RINGBUF_S shotsRing_;		//!< for lidar data collecting
    IMAGE_RINGBUF_S imageRing_[USBCmr_MAXNUMBER]; //һ�����һ��ring Buffer���첽�¼�����(�ص�����)���д���
    MESSG_RINGBUF_S messgRing_;   //!< for GUI message box
    CFG_RINGBUF_S   m_serverCfgRing_ ;    //buf
    CFG_RINGBUF_S   m_clientCfgRing_ ;    //�����ļ���Ϣbuf
    SLOW_RINGBUF_S slowRing_ ;    //������Buffer
    STRMSG_RINGBUF_S strRprtRing_ ; //�ַ������buf
	//FILE *fp_test;
	//int buf_full;
	
    int m_camNeedCnt;
    int m_imgCnt;
    int preCmrCount;
    bool m_cmrIsTrige ;   // ����������� 
    int cmrCount ; //debug
    CScada *s_scada;
    CLidarConfig *s_config;
	//added by zhubing 2020.1.3
#ifndef _WINDOWS
	Point_S m_pStart_;
	Point_S	m_pNext_;
	CNavigator *tmpNavigator_;
	double	m_fSumDis_;
	SCDCMD_CAMERA_S tmpCamera;
	void cameraRangeTrigger(Pilot_S &data);
#endif
    //<! Camera
    CUsbCamera * _usbCmr;
    //USBCMR_CTRL_S usbCmrCtrl_[USBCmr_MAXNUMBER];   //!< �����������
   // USBCMR_TRIG_S usbTrig_;

    LiDAR_DATAINFO_S curData_; //!< ʵʱ��ʾ���� liyp
    
    SCADA_POST_S posDataStat_ ; //!< pos ״̬ liyp

    CLifetime            *_lidarLife  ;       //!< �ϵ�ʱ���¼
    CLidarReporter       *_lidarRecord ;	    //!< ���������¼
    unsigned short       reportItv_ ;         //!< ���ʱ��
    LiDAR_STAT_E         lidarCfgStat_ ;      //!< lidarConfig ���ܼ�¼
    CPalmMode *_m_palmMode ;                  //!< palm ����ģ��
    SCADA_TYPE_E m_scada ; //scadaType
    LiDAR_TYPE_E m_lidar;
    
    bool m_openLidar ;                  //The LIDAR is Opened.
    int m_cmfFlashCount ;
    CStrPtcTool *_mPtcTool ;
    bool m_dataFlwRun ;  //��ʼ��fast ring buffer �ź�
    bool m_dataTrans;
    int m_StgMsgUp ;
    int m_StgMsgCount ;
    LDRPROG_STAT_E m_cmdSpinStat ;
    LDRPROG_STAT_LIST m_cmdStatList ;

    LDRFILE_STAT_LIST m_fileCtrlList ;
    CSvrSocket *_svrSock ;
    CdataCom *_m_svrUrt ;
    CStrPtcTool *_m_strCmdHnd ;
    CStrPtcTool *_m_strMsgHnd ; 
    time_t m_StartTime ;  //��ʼ�ɼ�����ʱ��
    time_t m_StopTime ;   //�����ɼ�����ʱ��
    LDRPROG_STAT_E m_slAtuoCtrlStatus;
    UartScreenStatus m_usStatus;// uart screen�Ĺ���״̬
    UartSceenParam m_usParam;
  private:
    void impDataCtrl(SCDCMD_PROGRM_S progPara_) ;
    
    void initUsbCamera( ) ;
    void initScada(SCADA_TYPE_E mtscada ) ;
    void initPalm();
  public:
    //<! 
    CLidarAPI(SCADA_TYPE_E scada_e=eScadaNet,LiDAR_TYPE_E mtlidar=eLidarGui);
    ~CLidarAPI() ;
    static CLidarAPI* getInstance() ;
    LiDAR_TYPE_E getLidarType();
    SCADA_TYPE_E getScadaType();

    /*** (1) for receiving commands from up-side controller ***/
    int cmdHandle(SCADA_CMDRPT_U & cmd) ;
    int cmdRprt(SCADA_CMDRPT_U & cmdrcv) ;
    
// added by zhubing 2020.3.19
	//void getMF_Parameter(double &tmp_h, double &tmp_v, double &tmp_Drol, double &tmp_Draw,bool &tmp_mf_falg);
	void setMF_Parameter(float tmp_mf_num_, bool tmp_mf_flag, float tmp_mf_freq_);
    /*** (2) for SCADA Hardware communicating ***/
    int openLidar(char *ip );
    int closeLidar(void);
    int pingLidar(void);

    //<! start up a scanning production
    LDRPROG_STAT_E prodStart(LiDAR_RoiProg_S * roids=NULL);
    //<! stop the scanning procedure
    LDRPROG_STAT_E prodStop();
    //<! take a break, stop laser firing or simu
    LDRPROG_STAT_E prodBreak();

    int dtaRecvHandle() ;
    int msgHandle(SCADA_CMDRPT_U mtMsgs) ;
    int msgRecvHandle() ;
    int systemDateTimeUpdate();
    int msgRecv(char * _mt_msgBuff, int mt_msgSize ) ;
	int gpsmsgRecv(char * _mt_msgBuff, int mt_msgSize);
    int slwdtaRecvHandle() ;  //������������
	int navmsgHandle();//added by zhubing 2020.1.3
	int mfModeDateHandle();//added by zhubing 2020.2.13
// added by zhubing 2020.2.14
	int init_cycle(double m_high, double m_dot_max, double m_view);

    /*** (3) share the ring buffers ***/
    //<! 
    SHOTS_RINGBUF_S * shotsOut() { return &shotsRing_; }
    //<! 
    IMAGE_RINGBUF_S * imageOut() { return imageRing_; }
    //<! 
    MESSG_RINGBUF_S * messgOut() { return &messgRing_; }
    
    CFG_RINGBUF_S * serverCfgRingOut() { return &m_serverCfgRing_ ; } 
    CFG_RINGBUF_S * clientCfgRingOut() { return &m_clientCfgRing_ ; } 
   
    SLOW_RINGBUF_S * slwRingOut() { return &slowRing_ ;}   //���������ڴ��ַ
    STRMSG_RINGBUF_S * strMsgRingOut() { return &strRprtRing_ ;}  //�ַ�����Ϣ�����ڴ��ַ
    CLidarConfig * ldrCfgOut() {return s_config; } 
    
    LDRFILE_STAT_LIST * fileCtrlListOut() {return &m_fileCtrlList; }
    /*** (4) .... ***/
    //<! usb camera options
    int usbCmrOpen();
    int usbCmrClose();

    //<! read and write the camera config parameters
    int usbCmrRead(USBCMR_CTRL_S * usbcmrPara);
    int usbCmrWrite(USBCMR_CTRL_S usbcmrPara);
    int usbCmrSetupTrig(USBCMR_TRIG_S usbTrigSetup );
    int usbCmrTrig(USBCMR_TRIG_S usbCmrTrig); // take a picture 

    int usbCameraCtrl(USBCMR_TRIG_S mt_usbCmrPara) ;
    int usbCameraRprt(USBCMR_TRIG_S *_mt_usbCmrPara) ;

    LDRPROG_STAT_E usbCameraScanStart(USBCMR_TRIG_S mt_usbCmrPara) ;
    LDRPROG_STAT_E usbCameraScanStop();


    /*** (5) .... *****/
    //<! used for data header packaging, for CssTask and IDataHandle
    //fileType: 0:�ַ���  1:������
    int lidarLoadCfg(char * fname , int fileType=0 ) ;
    int lidarLoadCfg(CScada * scada, char * fname , int fileType=0) ;
    int lidarDumpCfg() ;
    
    char * getImpHead() ;
    int packImpHead(char * buf, int size=IMP_HEADER_SIZE) ;
    int packTskRecd(char * buf) ;

    int packConfig() ;  
    int depackConfig(const char * buf) ;
    
    int spinMachine() ;
    int spinCmrTrigger() ;
    int initSlowRing() ;
    int initFastRing() ;

    /* delete by dengbj
    //int pipeMsgIn(char* msg);
    //int pipeMsgIn(SCADA_CMDRPT_U cmdrpt);
    */
  public:
    //Advanced Usage
    
    int ctrlParaRprt(SCADA_CONTROL_S *ctrRpt ) ;
    // including enable the dma
    int progCtrl(SCDCMD_PROGRM_S prgCmd);
    int progSetup(SCDCMD_PROGRM_S progPara) ;
    int progRprt(SCDCMD_PROGRM_S * prgRpt);
    
    //device control, add by dengbj
    int envirCtrl(SCDCMD_ENVIR_S envirPara);
    int envirSetup(SCDCMD_ENVIR_S envirPara);
    int envirRprt(SCDCMD_ENVIR_S *envirReport);
    
    int laserCtrl(SCDCMD_LASER_S laserPara);
    int laserSetup(SCDCMD_LASER_S laserPara);
    int laserRprt(SCDCMD_LASER_S *laserReport);
    
    int scanerCtrl(SCDCMD_SCANER_S scanerPara);
    int scanerSetup(SCDCMD_SCANER_S scanerPara);
    int scanerRprt(SCDCMD_SCANER_S *scanRprt);
    int scanerDriver(bool strStat ) ;
    
    int cameraCtrl(SCDCMD_CAMERA_S cameraPara);
    int cameraSetup(SCDCMD_CAMERA_S cameraPara);
    int cameraRprt(SCDCMD_CAMERA_S *cmrRprt);
    int cameraPosTrig();                        // add for nav by dengbj
		    
    int turretCtrl(SCDCMD_TURRET_S turretPara);
    int turretSetup(SCDCMD_TURRET_S turretPara);
    int turretRprt(SCDCMD_TURRET_S *turretReport);
    int turretWaitScaner();
    int turretStatProcess() ;
    
    //<! access the register directly  
    int regWrite(SCDCMD_REGIST_S reg);
    int regRead(SCDCMD_REGIST_S *reg);

    void setStationNbr(unsigned short nbr);
    
    int configRprt(LiDAR_CFGFILE_S *config); //! �����ļ����ݷ���
 
    LiDAR_DATAINFO_S* dataInfoOut();
    int dataInfoRprt( LiDAR_DATAINFO_S *_mt_Info ) ;
    int dataInfoSetup( LiDAR_DATAINFO_S mt_Info ) ;

    LDRPROG_STAT_E cameraScanStart(SCDCMD_CAMERA_S mt_cmrPara); 
    LDRPROG_STAT_E cameraScanStop(); //! ֹͣ��������ع�

    int posCtrl(SCADA_POST_S posPara_ ) ;     //!< pos �������ݿ���
    int posRprt(SCADA_POST_S * _posPara ) ;   //!< pos ���ݴ���״̬����

    int fpgaStatRprt(SCADA_FPGA_STATE * _fpgaStaPara) ; //!< FPGA ״̬���


    LiDAR_STAT_E getLidarConfigStat( void ) ;  //!<liyp����ȡ�����ļ�����״̬


    int impFileStateCtrl(LiDARImp_Action_E impPara ) ;

    int searchUsbRegister() ;
    #ifdef _WINDOWS
    //palm ����ģ�����
    int palmTranCtrl(SCDCMD_PALM_S mt_palmPata_) ;
    int palmTranRprt(SCDCMD_PALM_S *_mt_palmPara) ;
    
    int palmCmrCtrl(SCDCMD_CAMERA_S mt_cmrPara) ;
    int palmCmrRprt(SCDCMD_CAMERA_S *_mt_cmrState) ;

    int palmStgCtrl(SCDCMD_PALMSTG_S mt_stgPara) ;
    int palmStgRprt(SCDCMD_PALMSTG_S *_mt_stgPara) ;

    int palmReadRegister(SCDCMD_REGIST_S *_mt_reg) ;
    int palmWriteRegister(SCDCMD_REGIST_S mt_reg) ;
    int palmDataDirSetup(char * _mt_Path ) ;
    int palmDataHandle() ;
    int palmPing();
#endif
    unsigned int issFileSizeRprt() ;
    int dmiSetup(SCDCMD_DMI_S mt_para) ;
    int dmiRprt(SCDCMD_DMI_S *_mt_para) ;
    
    int strCmdSent(char *_mt_msg, int mt_size ) ;
    LDRPROG_STAT_E lidarMachStateRprt() { return m_eprogstat ; }

    int askLidarState() ;
    bool imageCollectRprt() ;  //����Ӱ��ɼ�״̬
    bool imageWiFiTransfer() ;

    int scanParaRprt(SCADA_DEFAULTCTR_S *defPara ) ;
    int testImpHeadDump() ;

    int syncTimeCtrl(SCDCMD_TIMSYN_S mtTime) ;

    int storageSetup(SCADA_DATAFUN_S mtPara) ;
    int storageCtrl(SCADA_DATAFUN_S mtPara) ;
    int storageRprt(SCADA_DATAFUN_S *mtPara) ;

    void msgRingHangle(void) ;
    void strMsgHangle(void) ;
    int  msgAutoRprt() ;
    CSvrSocket * getSvrSocket() ;
    void checkDataChannel() ;
    int svcCmdflow() ;
    void initLidar(LiDAR_TYPE_E mtlidar) ;

    void msgSent(unsigned char *mtMsg, int mtMsgSize, LiDAR_MSGID_E mtMsgId ) ;

    int limitParaRprt(SCDCFG_LIMIT_S *mtPara) ; //�豸Ӳ���������Ʒ�Χ

    void setupSimuPath(char *mtDir);
    int intervalWork();
    void scadaPing();
    bool issFileIsOpen() ;
	bool serialScreenCommandHandle(void *mtComMsg, size_t size, char* mtStrCmd);
	int sendScada2UartCmd(const unsigned char* cmd, size_t size);
	int  getUartCmdValue(void* cmdStr, size_t size, unsigned char* data);
	int updateserialScreenInfo();
	void uartScreenStateReportCmd(unsigned char type, void*cmd);  
	void setupLaserStrCmd(char *buf);

public:
	void getTemp(float &tempA,float &tempB);
	void setTemp(float tempA,float tempB);

 private:
	 //added by zhubing 2020.2.13
	 //�û��������
	 double m_high;				//����
	 double m_v_fight;			//�����ٶ�
	 double m_density_col;		//������ܶ�
	 double m_density_row;		//������ܶ�

	 //�豸�ڲ�����
	 int m_number_mirror;        //��������
	 double m_view;				//�ӳ���
	 double m_fpga_clk;			//FPGAʱ��Ƶ��

	 //��ʼ������
	 double m_groundview;		//�����ӳ��ǿ��
	 int m_v_motor;				//���ת��
	 double m_dot_max;			//����Ƶ
	 double m_cycle_tmp;			//����ӳ����µ���С��Ҫ��������
	 int m_cycle;				//��ǰ��������
	 int m_view_angle_div;		//�ǶȻ���������<50��
	 int m_div;					//��i���Ƕ�����ķ�Ƶ����ֵ
	 double m_th_div;			//������Ƶ����ֵ�ı߽磬ȡֵ��Χ(0.2~0.4)
	 double m_T0_T0_disti;		//��i���Ƕ����������T0����ֵ
	 double m_max_meas_disti;	//��i���Ƕ����������ʱֵ
	 double m_mid_meas_disti;	//��i���Ƕ��������С��ʱֵ
	 double m_min_meas_disti;	//��i���Ƕ�����Ĳ�ʱֵ��ֵ
	 int m_err_mfi;				//��i���Ƕ������mf����״̬
	 double m_c;					//�����й��� 2.99e8m/s

	 //���㺽���漰����
	 double m_time;				//ʱ��
	 double m_scale_time;		//��ʱ���
	 unsigned int m_hsdiv;		//
	 unsigned int m_mset;		//

	 float _tempA;
	 float _tempB;
	 bool  tcp_flag;
// added by zhubing 2020.2.15
	 SCDCMD_MF_S _mf_parameter;
	 bool   _mf_flag;
	 float  _m_pulse;
// added by zhubing 2020.2.17
	 bool  _mf_open_flag;
	 bool  _mf_run_flag;
};
#endif
  
