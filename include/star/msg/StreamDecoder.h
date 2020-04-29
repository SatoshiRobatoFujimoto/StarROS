/**
 * @author   lucb
 * @date     2019/12/11
 */

#ifndef __STAR_SDK_DECODER_H
#define __STAR_SDK_DECODER_H

#include <star/Star.h>

#include <star/Stream.h>
#include <star/msg/Message.h>

#include <star/utils/circular_buffer.h>
#include <star/utils/mutex.h>

#include <system_error>

#include <new>
#include <map>

namespace ss {
namespace msg {

namespace detail {

class MsgBuilder {
public:
    virtual ~MsgBuilder() = default;

    virtual msg::Message& get() = 0;
};

template<typename _Msg>
class MsgBuilderImpl : public MsgBuilder {
public:
    msg::Message& get() override
    {
        new(&_storage)_Msg();
        return _storage;
    }

private:
    _Msg _storage;
};

}

/**
 * StreamDecoder ����������
 * @node ʹ�øö���ʱӦ����@see decode()�������ص�@see Message�������������
 */
class __star_export StreamDecoder {
public:
    StreamDecoder();

    virtual ~StreamDecoder();

    void setByteOrder(bool useNetworkByteOrder);

    /**
     * ������Ҫ����������������
     * Stream���������������StreamDecoder����
     * @param stream �µ�stream����
     */
    void setSourceStream(Stream* stream);

    void closeSourceStream();

    /**
     * ���������н���һ�����ݰ�
     * @return �����������ݰ�@see Message��ʧ�ܷ��ؿ�
     * @note ���ص����ݰ�����Ϊ��ʱ�����ַ��ָ��Ķ����ڴ���StreamDecoder����
     *          ����һ�ε���decode����������StreamDecoder�����ͷ�ʱ��
     *          ���صĵ�ַָ����ڴ���Դ���ͷš�
     */
    virtual const Message* read();

    //todo
    virtual ssize_t write(const Message* message);

    /**
     * ��ͬ��@see read();
     */
    virtual const Message* decode()
    {
        return read();
    }

    /**
     * ע��һ�����ݰ�����
     * @tparam _Msg ע������ݰ����ͣ�������@see Message��������
     * @param dataId ���ݰ���Ӧ��dataId
     * @return ע��ɹ��򷵻�true��ʧ�ܷ���false
     */
    template<typename _Msg>
    bool material(uint64_t dataId);

    /**
     * �ж��������Ƿ����
     * @return �����򷵻�true�����򷵻�false
     */
    bool eof() const;

    bool seek(int64_t pos);

    int64_t tell() const;

    int64_t size() const;

    /**
     * �ر�stream
     */
    void close();

    uint64_t totalByteCount() const;
    void resetTotalByteCount();

    double progress() const;

    virtual bool startRecord(Stream* stream);
    virtual void stopRecord();

protected:
    /**
     * ���������н���һ�����ݰ�
     * @return �����������ݰ�@see Message��ʧ�ܷ��ؿ�
     * @note ���ص����ݰ�����Ϊ��ʱ��ַ��ָ��Ķ����ڴ���StreamDecoder����
     *          ����һ�ε���decode����������StreamDecoder�����ͷ�ʱ��
     *          ���ص�������ָ����ڴ���Դ���ͷš�
     */
    virtual const Message* decodeMessage() = 0;

    /**
     * �����ȡһ�����ݰ����ú�����һ��ӿں���@see doDecode()�е���
     * @param dataId ���������н���������dataId
     * @return �������������ݰ�@see Message��ʧ�ܷ��ؿ�
     * @note ���ص����ݰ�����Ϊ��ʱ�����������ڵ���һ�ε���decode����������
     */
    const Message* decodeWithDataId(uint64_t dataId);

    std::size_t readStream(void* buffer, std::size_t length);

    bool underflow();

    virtual bool writeRecordHeader(Stream* stream) = 0;

protected:
    using buffer_type       = utils::circular_buffer<uint8_t>;
    using builder_map_type  = std::map<uint64_t, detail::MsgBuilder*>;
    Stream*                     _stream;
    Stream*                     _recordStream;
    buffer_type                 _buffer;
    builder_map_type            _builders;
    std::size_t                 _min_size;
    std::size_t                 _max_size;
    uint8_t                     _temp[8192];
    uint8_t                     _write_buffer[8192];
    utils::buffer_reader*       _reader;
    bool                        _closed;
    bool                        _byteSwap;
    uint64_t                    _totalByteCount;
    uint64_t                    _tell;
    uint64_t                    _size;
    // mutable std::mutex          _streamMutex;
};

template<typename _Msg>
bool StreamDecoder::material(uint64_t dataId)
{
    detail::MsgBuilder* builder = new detail::MsgBuilderImpl<_Msg>();
    auto ret = _builders.insert(std::make_pair(dataId, builder));
    if (!ret.second) {
        delete builder;
        return false;
    }
    if (_min_size > _Msg::min_size()) {
        _min_size = _Msg::min_size();
    }
    if (_max_size < _Msg::max_size()) {
        _max_size = _Msg::max_size();
    }
    return true;
}

}
}

#endif //__STAR_SDK_DECODER_H
