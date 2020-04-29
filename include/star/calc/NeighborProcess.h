#ifndef NEIGHBOR_PROCESS_H__
#define NEIGHBOR_PROCESS_H__

#define  CLOUD_BUFFER_SIZE (10)
#define  STDEV 0.01
#define  PRE_AVG_FIRST_INDEX (4) 
#define  LASER_ECHO_NUMBER (2) 

#include <star/Star.h>
#include <star/Shot.h>
#include <cmath>
#include <vector>




namespace ss {
namespace calc {

	struct ReviseOptions {
		//0��
		bool useTimeWindowFilter;
		bool useRangeIntensityWideFilter;
		bool useAngleFilter;
		bool useMultiEchoWideFilter;


		//1��
		//��·�궨��ʶ
		//bool useSingleLidarRevise;
		bool useSingleLidarRangeRevise;
		bool useSingleLidarWideRevise;
	//	bool useSingleLidarIntensityRevise;

		bool useRangeIntensityRevise;
		bool usePlusMultiCoefRevise;
		bool useRangeConstRevise;
		bool useRangeTempratureRevise;
		bool useMidFarCalibRevise;

		bool useLasifilter;  //��˿ģ��
		bool echo2filter;

		//2��
		bool useWideRangeRevise;
		bool useWideLaserRevise;
		bool useTrans12bitIntensity;

		//3��
		bool useTrans8bitIntensity;

		//�߼�
		bool useMirrosFlagFpga;
		bool useZeroAngleRevise;
		bool useCfansAngleRevise;		
		bool useSmoothRange; //��ݴ��� 
		bool useSmoothXY;  //��ݴ���XY
		bool useHomogenProcess;   //cfans���Ȼ�����
	};
const int  kRFANS_LASER_COUNT = 16;
//const int  ADR_D_LASI_PARA = 0x9200
//const int  REGISTER_INTERVAL = 4

#define ADR_D_LASI_PARA 0x9200
#define ADR_D_SUNNOISE_PARA 0x9224
#define ADR_D_SAWTOOTH_PARA 0x923C
#define REGISTER_INTERVAL4  4


struct LasiFilterPara {
	//�Ҷ�������ֵ
	int intensityFilt1;
	int intensityFilt2 ;
	float wideFilt;
	// ͬһ���������ڽ������
	float absAnglediff ;
	float rangediffMin  ;
	float rangediffMax ;
	float widediff ;
	float absRangediff;
	float bufferSize ;
};

struct SunNoiseFilterPara {
	//��������ľ�����ֵ
	float absRangediff;
	//��ͬ�������Ĳ���
	int laserNum;
	float rangeMax;
	float laserAbsRangediff;
	//˫�ز��ĻҶȺ�������ֵ
	int intensityVal;
	float wideVal;
};

struct SawToothFilterPara {
	//���ڵ�ľ�����ֵ
	float absRangediff;
	int bufferSize;
};

typedef enum {
    E_PreNeiborReady,
    E_PreNeiborStart,
    E_PreNeiborWorking,
} NEIGHBORHOOD_E;


typedef struct {
    SHOTS_CALCOUT_S ringB[CLOUD_BUFFER_SIZE];
    int wrHead;
    int rdTail;
    int pointnum;
    NEIGHBORHOOD_E avgState;
} neighborRing;

class __star_export NeighborProcess {
public:
	//NeighborProcess(size_t id = 0, bool need_wide = true);
	NeighborProcess(size_t id , bool need_wide, const std::vector<float>& gReviseMap);
	
	void init();
	//SHOTS_CALCOUT_S & getCurPoint();
	std::vector<size_t> & getNearIds(const SHOTS_CALCOUT_S & in_point);
	inline size_t getLastPos() { return last_pos_; }
	inline SHOTS_CALCOUT_S & getPoint(size_t pos) {
		return avgbuf_.ringB[pos];
	}

	int  HAvgProcess(SHOTS_CALCOUT_S & out_point, SHOTS_CALCOUT_S & in_point, const ReviseOptions& reviseOptions);
	double filterLasiNoise(neighborRing * avgbuf, SHOTS_CALCOUT_S & point);
	double filterSunNoise_sameLase_twoPoint(neighborRing* avgbuf, SHOTS_CALCOUT_S & point);
	static int filterSunNoise_differLaser(const SHOTS_CALCOUT_S & near_point, SHOTS_CALCOUT_S & in_point);

protected:	
	void initNearids(const SHOTS_CALCOUT_S & in_point);
	bool addNearid(int range, int max_val = 32);

	int  HAvgProcess(neighborRing * avgbuf, SHOTS_CALCOUT_S & out_point, SHOTS_CALCOUT_S & in_point, const ReviseOptions& reviseOptions);
	int  wirteAvgBuffer(neighborRing * avgbuf, SHOTS_CALCOUT_S &  point);
	int  readAvgBuffer(neighborRing * avgbuf, SHOTS_CALCOUT_S & point, const ReviseOptions& reviseOptions);
 
	bool filterByIntentWide(SHOTS_CALCOUT_S & mtPoint);
	bool filterlasiNoise_sameLaser(neighborRing * avgbuf,SHOTS_CALCOUT_S &mtPoint);
	bool filterSunNoise_sameLaser(neighborRing * avgbuf,SHOTS_CALCOUT_S &mtPoint);

	bool filterRangeSawTooth(neighborRing * avgbuf_smooth,SHOTS_CALCOUT_S & point);
	bool filterXYSawTooth(neighborRing * avgbuf_smooth,SHOTS_CALCOUT_S & point);
	//float calcMedian(float *a, int num) ;
	float calcMedian(std::vector<float> a, int num);

private:
	neighborRing         avgbuf_;
	neighborRing         avgbuf_smooth;
	size_t               id_;
	bool                 need_wide_;
	size_t               last_pos_;
	std::vector<size_t>  near_ids_;

	//�м����
	//std::vector<float>	 arrRange;
	//std::vector<float>	 arrX;
	//std::vector<float>	 arrY;
	
	LasiFilterPara m_lasiFiterPara;
	SunNoiseFilterPara m_sunNoiseFilterPara;
	SawToothFilterPara m_sawToothFilterPara;
};


}
}

#endif // CLOUD_PORCESS_H__