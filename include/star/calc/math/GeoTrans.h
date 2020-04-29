#ifndef __STAR_SDK_CALC_MATH_GEO_TRANS_H
#define __STAR_SDK_CALC_MATH_GEO_TRANS_H

#include <star/Star.h>

namespace ss {
namespace calc {
namespace math {

class __star_export CGeoTrans {
public:
    CGeoTrans(void);

    ~CGeoTrans(void);

    double m_a, m_f;

    // [��B ��L ���뾭L0 �ݳ���(dx=0) �᳣��(dy=500000) ��ֱ��X ��ֱ��Y]
    void BLToXY(double B, double L, double CentL, double dx, double dy, double& x, double& y);

    // [��ֱ��X ��ֱ��Y ���뾭L0 �ݳ���(dx=0) �᳣��(dy=500000) ��B ��L ]
    void XYToBL(double X, double Y, double CentL, double dx, double dy, double& B, double& L);

    double dms2rad(double x);

    double rad2dms(double x);

    bool MatrixInversion_General(double* a, int n);

    bool MatSAT(double* a, int m);

    bool MatSAT(double* a, double* at, int m, int n);

    void Zero(double* p, int n);

    bool MatrixMulti(double* a, double* b, double* c, int m, int n, int l);

    bool MatrixSub(double* a, double* b, double* c, int m, int n);

    //��ָ��������ʸ����ΪX/Z������ϵ��ԭ����ϵ����ת����R
    bool CalRM(double* R, double* X, double* Z);

    //(B L)==>(X Y Z)
    void CalEarthCentXY(double* XYZ, double B, double L);

    //��֪P�� ƽ���ϵ�һ��O��ƽ�浥λ����������P��ƽ��Ĵ�������
    void CalVPF(double* XYZ, double* P, double* O, double* N);

    //�ߵ���Ӱ����ϵͳ��6����ת����
    //�ߵ���������ϵb���񸨹ߵ�����ϵbp;��������ϵn����������ϵe����˹����ϵnp��
    //�������ϵE����ռ�����ϵB;
    //double Tbpb[9],CBbp[9],CEB[9],TnpE[9],Tnnp[9],Cbn[9];
    void CalTMat(double* Tbpb, double* TnpE);

    void CalIMU(double* R, double roll, double pitch, double yaw);

    void CalCMR(double* R, double omg, double phi, double kap);

    void CalGassMat(double* R, double Lgk, double B0, double L0, double B, double L);

    void CalErrMat(double* R, double ex, double ey, double ez);

    void CEB_ANGLE(double* R, double& omg, double& phi, double& kap);

    void Cnb_ANGLE(double* R, double& rol, double& pit, double& yaw);

    void NormalAngle(double& p, double& o, double& k);

    double NRAngle(double rad);

    void RRx(double* R, double angle);

    void RRy(double* R, double angle);

    void RRz(double* R, double angle);

    //����ϵͳ���� ͳһ��λΪ���� �ȣ� X������������ԼӴ��ţ������ȥ���˴���
    void SetCoorSysType(int ty = 84, bool inip = true);

    void SetL0(double L0, double HX = 500000, double ZX = 0); //���������߼�ƽ�Ʋ�������
    double GetL0(double LL, int ty = 3);

    void LB2XY(double L, double B, double& X, double& Y);//ͳһΪ������ ������
    void XY2LB(double X, double Y, double& L, double& B); //
    void Z54D84(double L0, double X54, double Y54, double H54, double& L, double& B, double& H);

    void Z80D84(double L0, double X80, double Y80, double H80, double& L, double& B, double& H);

    void L54D84(double L0, double L54, double B54, double H54, double& L, double& B, double& H);

    void L80D84(double L0, double L80, double B80, double H80, double& L, double& B, double& H);

    void LB84XY80(double L0, double L, double B, double H84, double& X, double& Y, double& H);

    void Xyz2Lbh(double X, double Y, double Z, double& L, double& B, double& H);

    void Lbh2Xyz(double L, double B, double H, double& X, double& Y, double& Z);

    double rangle(double L, double B); //��������������

protected:
    void CalEP();//�����Ӧ�����ڲ�����

private:
    double mL0, m_dZX, m_dHX; //���������ߣ����� ����ƽ��ZX=0 ����ƽ��HX=500000)
    double mRC, EE;// ����ڶ�ƫ����
    double CC1, CC2, CC3, CC4; //�����м����
    double d2r, r2d; //��ת����ϵ�� �� ����ת��ϵ��
    double TT, TE, TC;//ת������

    double DX80_84, DY80_84, DZ80_84, DX54_84, DY54_84, DZ54_84;
};

}
}
}


#endif //__STAR_SDK_CALC_MATH_GEO_TRANS_H
