/********************************************************************
       Author:		           ZQW	
       File Name:	           TerrRasFile
	   File Type:	           h
       Created Date:	       2011/12/7
	   Created Time:	       13:06      
*********************************************************************/
#ifndef TerrRasFile_h_ZQW_2011_12_7_13_06_DEF
#define TerrRasFile_h_ZQW_2011_12_7_13_06_DEF

#pragma   warning(disable:4786)
#pragma   warning(disable:4251)
#pragma   warning(disable:4089)
#pragma   warning(disable:4996)
#pragma   warning(disable:4099)

#ifndef TerrRasFile_LIB 
   #define TerrRasFile_LIB _declspec(dllimport)
   #ifdef _DEBUG
      #pragma comment(lib,"TerrRasFileD.lib")
      #pragma message("Automatically linking with TerrRasFileD.lib")
   #else
      #pragma comment(lib,"TerrRasFile.lib")
      #pragma message("Automatically linking with TerrRasFile.lib")
   #endif
#endif

typedef int (__stdcall *ProgressFunc)(double dfComplete, const char *pszMessage, void *pProgressArg);

#ifndef    _RGBTABLE
#define    _RGBTABLE
typedef struct tagRGBTABLE
{ 
	BYTE    Red;
	BYTE    Green;
	BYTE    Blue;
	BYTE    Resv;
}RGBTABLE,*PRGBTABLE;
#endif

//////////////////////////////////////////////////////////////////////////
//֧��ȫ��GDAL��ʽ�Լ������Զ���դ�����£�
//BMP;ECW;EIR;ENVI;ERS;GIF;GTIFF;JPEG;PNG;XYZ;AATGrid��;
//Transform[0]: topLeft x;
//Transform[1]: w-e pixel resolution;
//Transform[2]: rotation, 0 if image is "North up";
//Transform[3]: topLeft y;
//Transform[4]: rotation, 0 if image is "North up";
//Transform[5]: n-s pixel resolution;
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//BOOL ReadRange (int nLevel,int nFileSX,int nFileSY,int nFileXSize,int nFileYSize,void *pBuffer,int nReadXSize,int nReadYSize,int nBufXSize,int nBufYSize,int *pBandList,int nBandNum,BMPFormat eF=BIP);
//BOOL WriteRange(int nLevel,int nFileSX,int nFileSY,int nFileXSize,int nFileYSize,void *pBuffer,int nWriteXSize,int nWriteYSize,int nBufXSize,int nBufYSize,int *pBandList,int nBandNum,BMPFormat eF=BIP);
//IO�ӿ�˵����
//nLevel: ��ǰ��д��������������������0���㣬ԭʼӰ��Ϊ��0�㣻
//nFileSX,nFileSY:��Ҫ�����ļ����кź��кţ�
//nFileSY,nFileYSize:��Ҫ������ļ���Χ��
//pBuffer:��Ҫ��д�ڴ��׵�ַ������ƫ�����ڵ���ǰ���ƫ�Ƽ��㣻
//nReadXSize,nReadYSize:���ļ��������ڴ��С,����ʵ���ڴ治��ȣ�Ҳ�����ļ���Χ����ȣ�
//nBufXSize,nBufYSize:ʵ���ڴ��С��
//pBandList: �ļ�����,������1���㣻
//nBandNum:������Ŀ��
/////////////////////////////////////////////////////////////////////////

class TerrRasFile_LIB CRasterFile
{
public:
	enum OpenModes{modeREAD=0,modeWRITE=1/*,modeREADWRITE=2,*/};	
	enum PIXELTYPE{
		PIXEL_Unknown  = 0, /*! Unknown or unspecified type */
		PIXEL_Byte     = 1, /*! Eight bit unsigned integer */
		PIXEL_UInt16   = 2, /*! Sixteen bit unsigned integer */
		PIXEL_Int16    = 3, /*! Sixteen bit signed integer */
		PIXEL_UInt32   = 4, /*! Thirty two bit unsigned integer */
		PIXEL_Int32    = 5, /*! Thirty two bit signed integer */ 
		PIXEL_Float32  = 6, /*! Thirty two bit floating point */
		PIXEL_Float64  = 7, /*! Sixty four bit floating point */ 
		PIXEL_CInt16   = 8, /*! Complex Int16 */
		PIXEL_CInt32   = 9, /*! Complex Int32 */
		PIXEL_CFloat32 = 10,/*! Complex Float32 */ 
		PIXEL_CFloat64 = 11,/*! Complex Float64 */
	};	
	//���ش洢��ʽ;
	enum BMPFormat 
	{ 
		BSQ = 0, // BAND
		BIP = 1, // PIXEL
		BIL = 2, // LINE
	};

public:	
	//Raster tools;
	static void                GDALInitial();
	static int                 GetGDALVersion();
	static void                Geo2Raster(const double *pTransform,double *x,double *y);
	static void                Raster2Geo(const double *pTransform,double *x,double *y);
	static void                StatisticRaster(const char* lpstrFilePath,double *MinVal,double *MaxVal,double *MeanVal=NULL,double *StdDev=NULL);
	static void                InitTransform(double *pTrasnform);	
	static void                InitColorTab(RGBTABLE *pRgbTab,int nItemCount=256);
	static void                SetNodataVal(const char* lpstrPath,double dfNodataVal);
	
	//Gdal tools;
	static int                 GeneratorCnt(const char* pszSrcFilename,const char *pszDstFilename,double dfInterval,BOOL bIgnoreNoData=FALSE);
	static int                 GeneratorQvs(int argc, char ** argv);
	static int                 TranslateFile(int argc, char ** argv);

public:	
	//��д�ӿڣ�
	BOOL                       Open(const char* lpstrFilePath,OpenModes nOpenMode=modeREAD);	
	BOOL                       Create(const char* lpstrFilePath,int nCol,int nRow,int nBand,double* dTransform, 
		                              PIXELTYPE pixType=PIXEL_Byte,const char* strCode="GTiff",const char* projWKT=NULL, 
									  bool bTiled=false,bool bCompress=false,const char* strTieSize="128",const char* strCompress="LZW");	
	
	BOOL                       IsOpen(){return m_bOpen;};	
	void                       Close();
	
	BOOL                       ReadRange (int nLevel,int nFileSX,int nFileSY,int nFileXSize,int nFileYSize,void *pBuffer,int nReadXSize,int nReadYSize,int nBufXSize,int nBufYSize,int *pBandList,int nBandNum,BMPFormat eF=BIP);
	BOOL                       WriteRange(int nLevel,int nFileSX,int nFileSY,int nFileXSize,int nFileYSize,void *pBuffer,int nWriteXSize,int nWriteYSize,int nBufXSize,int nBufYSize,int *pBandList,int nBandNum,BMPFormat eF=BIP);

public:
	//������Ϣ�ӿڣ�
	const char*                GetLastError();
	char*                      GetFilePath(){return m_strFilePath;};
	int                        GetBandNum(){return m_nBandNum;};
	PIXELTYPE                  GetPixelType(){return m_stPixelType;};
	int                        GetPixelBits(){return m_nPixBits;};
	int                        GetPixelBytes();
	int                        GetCols(int nLevel=0);
	int                        GetRows(int nLevel=0);
	PRGBTABLE                  GetColorTab(){return m_ColorTab;};
	char*                      GetProjection(){return m_strProjection;};
	double*                    GetTransform(){return m_Transform;};
	char*                      GetRasterPath(){return m_strFilePath;};
	double                     GetZMinimum(){return m_MinValue;};
	double                     GetZMaximum(){return m_MaxValue;};
	double                     GetInvalidData(){return m_InvalidValue;};

	//�ֿ�ֲ�ӿڣ�
	BOOL                       IsTiled();     
	int                        GetTileCols(); 
	int                        GetTileRows(); 
	int                        GetXTileSize();
	int                        GetYTileSize();
	int                        GetLevels();  

	CRasterFile();
	virtual ~CRasterFile();

protected:	
	BOOL                       m_bOpen;	
	char                       m_strFilePath[512];
	char                       m_strProjection[512];
	double                     m_Transform[6];	
	int                        m_nCols,m_nRows;
	int                        m_nBandNum,m_nPixBits;
	int                        m_nBlkXSize,m_nBlkYSize;
	int                        m_nLevels;

	PIXELTYPE                  m_stPixelType;
	RGBTABLE                   m_ColorTab[256];
	double                     m_MinValue,m_MaxValue;
	double                     m_InvalidValue;
	OpenModes				   m_OpenModes;

private:
	void*					   m_pImage;
};

#endif // TerrRasFile_h__
