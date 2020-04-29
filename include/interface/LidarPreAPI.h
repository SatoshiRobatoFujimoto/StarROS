/********************************************************************
 * $I
 * @Technic Support: <sdk@isurestar.com>
 * All right reserved, Sure-Star Coop.
 ********************************************************************/
/*     IMP�ļ����㹦��ʹ�ò���   
  
  1.���ý������(setup)
     
  2.��ʼ����(calcStart)

  3.��ȡ�������(getProgress)

  4.ֹͣ����(calcStop)
*/

/*     ʵʱ���㹦��ʹ�ò���             
  1.���ý������(setup)

  2.��ʼ����(calcRun)

*/



#ifndef _LIDARPREAPI_H
#define _LIDARPREAPI_H

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>

//#include <io.h>

#include "ICD_LiDAR_PRE.h"
#include "ICD_LiDAR_API.h"

#if defined(_MSC_VER)
#ifdef LIDARPRE_EXPORTS
#define LIDAR_PRE_DLL __declspec(dllexport)
#else //LIDARPRE_EXPORTS
#define LIDAR_PRE_DLL __declspec(dllimport)
#endif //LIDARPRE_EXPORTS
#else //defined(_MSC_VER)
#define LIDAR_PRE_DLL
#endif //defined(_MSC_VER)

class CLidarPre ;

class LIDAR_PRE_DLL CLidarPreAPI {
public:
  CLidarPreAPI( ) ;
  ~CLidarPreAPI() ;

  /**
  * @brief �����������
  * @_mt_preCtr ���������
  * @mt_deviceTyp: �豸����,����(�����豸:eUArm)
  */
  bool setup(DEVICE_TYPE_E mt_deviceTyp, PRE_FILTER_S mt_prePara,PRE_WSG_S *mt_wsgPara=NULL ) ; 

  /**
  * @brief �ļ�������ȷ���
  * @_mt_process: ���ؽ������
  * @return ��
  */
  bool getProgress(FileProcess_S *_mt_process );

  /**
  * @brief IMP�ļ����� 
  * @mt_rawFiles_ ��IMP�ļ��б�,���ļ��ɼ�ʱ��˳������
  * @_mt_strOutPath ��   �������Ŀ¼
  * @return :  false: �ļ�����Ϊ�㡣
  */
  bool calcStart( std::vector<std::string> mt_rawFiles_, char *_mt_strOutPath, PRE_WSG_S *_mt_wsgPara) ;	

  bool calcStop() ;

  /**
  * @brief ʵʱ����
  * @_mt_headInfo ��ͷ��Ϣ�� HeadSize = 80KB
  * @_mt_fastFlow ������������ַ
  * @mt_flowSize  :  ����������С��512KB >= mt_flowSize
  * @_mt_wsgPara  :  ���������� value = NULL �豸�������,��֮���������㡣
  * @__outResult  :  �����������
  * @return��
  */
  
  bool calcRun(PRE_BUFFER_S *_mt_fastFlw, PRE_COORD_S *_outResult, PRE_BUFFER_S *_mt_headInfo , PRE_WSG_S *_mt_wsgPara) ;	
  
private:
  
};

#ifdef __cplusplus
extern "C"
{
#endif
  LIDAR_PRE_DLL bool CSetup(DEVICE_TYPE_E mt_deviceTyp, PRE_FILTER_S mtPrePara,PRE_WSG_S *mtWsgPara=NULL) ;
  LIDAR_PRE_DLL bool CCalcStart( std::vector<std::string> mt_rawFiles_, char * _mt_strOutPath, PRE_WSG_S *_mt_wsgPara) ;
  LIDAR_PRE_DLL bool CCalcStop() ;
  LIDAR_PRE_DLL bool CCalcRun( PRE_BUFFER_S *_mt_fastFlw, PRE_COORD_S *_outResult, PRE_BUFFER_S *_mt_headInfo , PRE_WSG_S *_mt_wsgPara) ;
  LIDAR_PRE_DLL bool CGetProgress(FileProcess_S *_mt_process) ;
  LIDAR_PRE_DLL void CInitPre() ;
  LIDAR_PRE_DLL void CClearPre() ;
  LIDAR_PRE_DLL void CDecodeProcess() ;
  LIDAR_PRE_DLL void CCalcProcess() ;
#ifdef __cplusplus
}
#endif


#endif
