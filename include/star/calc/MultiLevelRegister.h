#ifndef __STAR_SDK_CALC_MULTI_LEVEL_REGISTER
#define __STAR_SDK_CALC_MULTI_LEVEL_REGISTER

#include <star/Star.h>
#include <star/calc/NeighborProcess.h>

#include <string>
#include <star/Configure.h>
#include <vector>
#include <set>

namespace ss {
namespace calc {

class __star_export MultiLevelRegister{
public:
  

    MultiLevelRegister();
    ~MultiLevelRegister() = default;

    void setup(const Configure& configure);

    int setTemperature(float temperature);
    bool set_intensity_params(std::vector<int>& intent,bool isdefault=true);

    //�༶���ݵĴ���Ĭ�ϣ�
    bool data_level_convert(SHOTS_CALCOUT_S* mtPoint);

    //----------------------0���㷨�����ˣ�-------------------------
    int filterTimeWindow(SHOTS_CALCOUT_S* mtPoint);         // ʱ�䴰�ڹ���
    int filterRangeIntensityWide(SHOTS_CALCOUT_S* mtPoint); // ����Ҷ��������
    int filterAngle(SHOTS_CALCOUT_S* mtPoint);              // �Ƕȹ���
    int filterMultiEchoWide(SHOTS_CALCOUT_S* mtPoint);      // ������ز��������Ӱ��

    //----------------------1���㷨���궨��-------------------------
    //��·�궨
	int reviseRange_singeLaser(SHOTS_CALCOUT_S *mtPoint);
	int reviseWide_singeLaser(SHOTS_CALCOUT_S *mtPoint);
	//int reviseIntensity_singeLaser(SHOTS_CALCOUT_S *mtPoint);	

	//��������
    int reviseRangeIntensity(SHOTS_CALCOUT_S* mtPoint);  //�Ҷȸ���������
    int revisePlusMultiCoef(SHOTS_CALCOUT_S* mtPoint);  //�ӳ�ϵ������
    int reviseRangeConst(SHOTS_CALCOUT_S* mtPoint);  //�ӳ�������
    int reviseRangeTemprature(SHOTS_CALCOUT_S* mtPoint);  //�����¶ȶԾ����Ӱ��
    int reviseMidFarCalib(SHOTS_CALCOUT_S *mtPoint) ; //��Զ��������

	//��˿���������
	int filterSunNoise_IntensityWide(SHOTS_CALCOUT_S* mtPoint); // ����Ҷ����� ����������
	bool filterPoint(size_t no, SHOTS_CALCOUT_S & in_point, const ReviseOptions& reviseOptions);
    //��������
    int reviseWideRange(SHOTS_CALCOUT_S *mtPoint);   //��������������Ӱ��
    int reviseWideLaser(SHOTS_CALCOUT_S *mtPoint);    //������������Ĳ���
    //ת��Ϊ12bit�Ҷ�
    int trans12bitIntensity(SHOTS_CALCOUT_S *mtPoint);

    //��λ��������CFans�Ƕȹ���
    int CalbZeroAngle(SHOTS_CALCOUT_S *mtPoint);

    //��ȡ������
    void findCFansMirrorNum_FPGA(SHOTS_CALCOUT_S *currshot);  //FPGA��ȡ
    void  findCFansMirrorNum_cfans(SHOTS_CALCOUT_S * mtPoint) ;    //��λ����ȡ

    //CFans ��Ե�Ƕȹ��ˣ��Ƕ�������
    void findCFansMirrorNum_cfans32(SHOTS_CALCOUT_S *currshot, bool flag);
    void findCFansMirrorNum_cfans128_v1_0(SHOTS_CALCOUT_S *currshot, bool flag);
    void findCFansMirrorNum_cfans128_v2_0(SHOTS_CALCOUT_S *currshot, bool flag);

    //��ȡ�Ƕ�����
    void findCFansAngleArea( SHOTS_CALCOUT_S *currshot);
    //CFans���ýǶȱ궨
    void reviseAngle(SHOTS_CALCOUT_S *currshot);
	//���Ȼ�����
	void HomogenizationProcess(SHOTS_CALCOUT_S* currshot);

    //----------------------2���㷨��ת8bit�Ҷȣ�-------------------------
    //12bit�Ҷ�ת��Ϊ8bit�Ҷ�
    unsigned short trans8bitIntensity(SHOTS_CALCOUT_S *mtPoint);

    //��˿��������㷨
    inline bool isNeedFilt() { return need_filt_; }
    inline void setFiltFlag(bool flag = true) { need_filt_ = flag; }
    bool reset();   //�������в���

    ReviseOptions& reviseOptions();
    const ReviseOptions& reviseOptions() const;
    void setReviseOptions(const ReviseOptions& reviseOptions);
	void setDefaultReviseOptions( int32_t data_grade);
	void setDefaultReviseOptions_singleCalib( int32_t data_grade);
protected:
   

private:
    std::vector<float> revise_map_;
    float temperature_;
    int intensity_duration_[6]{};
    float params_[10]{};

    std::vector<std::vector<NeighborProcess> >  cloud_procs_vec_;
    bool                                        need_filt_;
    ReviseOptions                               reviseOptions_{};
	
};

}
}

#endif //__STAR_SDK_CALC_MULTI_LEVEL_REGISTER
