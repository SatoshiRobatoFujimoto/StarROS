/**
 * @author   lucb
 * @date     2019/12/31
 */

#ifndef __STAR_SDK_READER_H
#define __STAR_SDK_READER_H

#include <star/Star.h>
#include <star/Packet.h>

#include <star/utils/mutex.h>
#include <star/Configure.h>
#include <vector>

typedef struct _DecPara DecPara_S;

namespace ss {
class Stream;

namespace msg {
class Reader;
}

/**
 * ������
 */
class __star_export Reader {
private:
    constexpr static uint32_t ISF_FORMAT = 0x100000u;
    constexpr static uint32_t IMP_FORMAT = 0x200000u;
public:
    //���ݸ�ʽ
    constexpr static uint32_t ISF_VER_4     = ISF_FORMAT | 0x0400u;  /// ISF 4.0��ʽ
    constexpr static uint32_t ISF_VER_4_1   = ISF_FORMAT | 0x0410u;  /// ISF 4.1��ʽ��Ϊ��StageAngle��ISF 4.0
    constexpr static uint32_t ISF_VER_5     = ISF_FORMAT | 0x0500u;  /// ISF 5.0��ʽ
    constexpr static uint32_t IMP_VER_1     = IMP_FORMAT | 0x0100u;  /// IMP 1.0��ʽ��Ϊ�ɰ汾��IMP��ʽ���ļ�ͷΪIMP Header
    constexpr static uint32_t IMP_VER_3     = IMP_FORMAT | 0x0200u;  /// IMP 3.0��ʽ��Ϊ�¹滮��IMP��ʽ���ļ�ͷΪ�Ĵ�����

    //��������ݰ���@see Packet in Packet.h
    using Packets = Packet;

    /**
     * Ĭ�Ϲ��캯��
     */
    Reader();

    /**
     * ���캯�����ƶ���ȡ�����ݸ�ʽ
     * @param formatVersion ��ȡ�����ݸ�ʽ
     */
    explicit Reader(uint32_t formatVersion);

    ~Reader();

    /**
     * ��Reader��open�����󴴽�Decoder�������
     * @return �ɹ�����true��ʧ�ܷ���false
     */
    bool open();

    /**
     * ��ȡstream�����ݣ����Reader�Ѿ�����һ��Stream������ȹرվɵ�decoder����һ���µ�
     * @param stream Ҫ��ȡ��stream
     * @return �ɹ�����true��ʧ�ܷ���false
     */
    bool open(Stream* stream);

    /**
     * �ر�Reader���رպ�������´�
     */
    void close();

    /**
     * ��һ���µ�Stream������Ѿ�������Decoder�򲻻ᴴ���µ�
     * @param stream Ҫ��ȡstream
     * @return �ɹ�����true��ʧ�ܷ���false
     */
    bool openNewStream(Stream* stream);

    /**
     * �ж�stream�Ƿ��ȡ���������Ƿ���ڴ���
     * @return ���ļ���ȡ����β��Stream�����쳣�ر�ʱ������true�����򷵻�false
     */
    bool eof() const;

    /**
     * ��ת���ƶ���λ�ã�ֻ���ļ�������Ч
     * @param pos ָ����λ��
     * @return �ɹ��򷵻�true�����򷵻�false
     */
    bool seek(int64_t pos);

    /**
     * ��ȡ��ǰ��ȡ��λ�ã��ļ���Ϊ�ļ�ָ���λ�ã�����Ϊ�ۼƶ�ȡ��������
     * @return ��ȡ��λ��
     */
    int64_t tell() const;

    /**
     * ��ȡ��ǰ���Ĵ�С��ֻ���ļ�����Ч������������0
     * @return �ļ��������ļ��Ĵ�С����������0
     */
    int64_t size() const;

    /**
     * �����Ƿ�ʱ����ģʽ��������ʧЧ�������κ�ֵ����Ч
     * @param blockMode �Ƿ�ʹ������ģʽ���Ѿ���Ч
     */
    void setBlockMode(bool blockMode);

    /**
     * ���м���������������Ҫ�Ǵ���IMP�ļ������������
     * @param path �����·��
     * @param parameters ʹ��ѡ��
     */
    void openDebugs(const std::string& path, const cfg::DebugOutput& parameters);

    /**
     *  ���ý���ĸ�ʽ
     * @param formatVersion �����ʽ���μ���ʽ˵��
     */
    void setFormatVersion(uint32_t formatVersion);

    /**
     * ��ʼ¼��
     * @param stream д��¼�����ݵ�stream����stream���ú���reader�����û�����Ҫ�ͷ�
     * @return ��ʼ�ɹ��򷵻�true�����򷵻�false
     * @note ¼��֧��seek����
     */
    bool startRecord(Stream* stream);

    /**
     * ��ʼ¼��¼�����ݴ����ָ��·�����ļ���
     * @param path ָ�����ļ�·��
     * @return ��ʼ�ɹ��򷵻�true�����򷵻�false
     * @note ¼��֧��seek����
     */
    bool startRecord(const std::string& path);

    /**
     * ֹͣ¼�񣬱���¼�����ݣ��ͷ������Դ��
     */
    void stopRecord();

    /**
     * ��ȡ�ο���ʱ��������ڽ���ʱʱ����ļ��㣬��λus��һ��Ϊ�������ļ��ж�ȡ����ʱ��ֵ
     * @return �ο���ʱ���
     */
    int64_t timestamp() const;

    /**
     * ���òο���ʱ��������ڽ���ʱʱ����ļ���
     * @param lastSecond ���õ�ʱ�������λus��һ��Ϊ�������ļ��ж�ȡ����ʱ��ֵ
     */
    void setTimestamp(int64_t lastSecond);

#if 0
    void setMetadata(const ss::msg::Imp_MetaData_S& metadata);
	
    const ss::msg::Imp_MetaData_S& metadata() const;
    ss::msg::Imp_MetaData_S& metadata();
#endif
    bool waitMetadata(); //�ȴ�metadata��ȡ��ɣ����������������metadata����Ҫ���øú���
    bool waitMetadata(Configure& configure);
    void setMetadata(const Configure& metadata);

    void updateConfigure(Configure& configure) const;
	
    Packet getPacket();
    Packets getPackets();

protected:
    void setStream(Stream* stream);
    void waitReaderIdle();

private:
    uint32_t				        _format;
	mutable std::recursive_mutex	_reader_mutex;
    msg::Reader*		            _reader;
    bool                            _busy;
    int64_t                         _timestamp;
};

}

#endif //__STAR_SDK_READER_H
