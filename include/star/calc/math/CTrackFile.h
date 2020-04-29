#include <cstdio>
#include <cstdint>
#include <vector>

namespace ss {
namespace calc {
namespace math {

class CTrackFile {
public:
    struct SBET_Rec { //3*5*8+2*8 =136
        double ti;			///< ʱ�䣬��λ:����(time gps-sec. of week)
        double p[3];		///< γ�� ���� �߶� 24
        double wVel[3];		///< X�����ٶ� Y�����ٶ� Z�����ٶ� 24
        double rph[3];		///< roll, pitch, heading ,��λ:���� 24
        double w;			///< ���Ʒ�λ��
        double force[3];		///< X������ٶ� Y������ٶ� Z������ٶ� 24
        double aRate[3];		///< X������ٶ� Y������ٶ� Z������ٶ� 24
    };

    typedef struct {
        SBET_Rec headInfo ;
        SBET_Rec tailInfo ;
        //double pageHeadTime ;
        //double pageTailTime ;
        uint32_t  pageStartOffset;
        uint32_t  pageSize ;
        int count ;
    }TRACK_PAGEINFO_S ;

    typedef struct {
        std::vector<TRACK_PAGEINFO_S> pageList ;
        double trackHeadTime ;
        double trackTailTime ;
        int currentIndex ;
    }TRACK_PAGE_LIST;

public:
    CTrackFile() ;
    ~CTrackFile() ;
    int setIndexFromTime(double mtTime) ;
    SBET_Rec getCurPosInfo() ;
    SBET_Rec getNextPosInfo() ;
    int LoadFile(const char* mtFileName) ;
    bool fileIsOpen() ;
    int CloseFile() ;

protected:
    int setCount(int mtCount ) ;
    int getCount() ;
    double PreTime() ;
    double CurTime() ;
    double nextTime() ;
    //double getHeadTime() ;
    //double getTailTime() ;
    int indexToNext() ;
    int setCurIndex(int mtIndex) ;
    int getIndexFromTime(double mtTime) ;
    double getTimeFromIndex(int mtIndex) ;
    SBET_Rec getInfoFromIndex( int mtIndex );
    void setDataBaseAddress(SBET_Rec *mtAdd) ;
    bool switchPage(int mtIndex);
    //test(int argc, char *argv[] );
private:
    SBET_Rec *m_infoGroup ;
    size_t m_count;
    int m_curIndex ;
    FILE *m_impfileHdl;
    bool m_fileIsOpen ;
    // void * m_imppvFile ;
    TRACK_PAGE_LIST m_trackInfo ;
};

}
}
}
