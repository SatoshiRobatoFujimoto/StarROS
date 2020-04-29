/**
 * @author   lucb
 * @date     2020/3/20
 */

#ifndef __STAR_SDK_PCAP_H
#define __STAR_SDK_PCAP_H

#include <star/Star.h>
#include <star/Stream.h>

#include <string>

typedef struct pcap pcap_t;

namespace ss {

struct __bpf_insn {
    uint16_t	code;
    uint8_t 	jt;
    uint8_t 	jf;
    uint32_t    k;
};

struct __bpf_program {
    uint32_t bf_len;
    __bpf_insn* bf_insns;
};
	
class __star_export Pcap : public Stream {
public:
    Pcap();
    explicit Pcap(std::size_t head_size);
    explicit Pcap(const std::string& path);
    Pcap(const std::string& path, std::size_t head_size);

    /**
     * ��pcap�ļ�
     * @param path �ļ�·��
     * @return �ɹ��򷵻�true�����򷵻�false
     */
    bool open(const std::string& path);

    /**
     * Pcap���˹���ֻ��ȡָ���˿ڵ����ݰ�
     * @param port ָ���Ķ˿�
     * @return �ɹ��򷵻�true�����򷵻�false
     */
    bool filte(uint16_t port);

    /**
     * Pcap���˹���ֻ��ȡָ����IP��ַ�Ͷ˿ڵ����ݰ�
     * @param addr ָ����IP��ַ��Ϊxxx.xxx.xxx.xxx�ĵ��ʮ������ʽ
     * @param port ָ���Ķ˿�
     * @return �ɹ��򷵻�true�����򷵻�false
     */
    bool filte(const std::string& addr, uint16_t port);

    void close() override;

    ssize_t read(char* buffer, std::size_t length) override;

    ssize_t write(const char* buffer, std::size_t length) override;

    bool eof() override;

    bool good() override;

    bool seek(int64_t pos) override;

    int64_t tell() const override;

    int64_t size() const override;
	
private:
    pcap_t*         _pcap;
    bool            _eof;
    std::size_t     _head_size;
    int64_t         _size;
    int64_t         _total_size;
    __bpf_program   _filter;
    char            _errbuf[512];

	
};

}

#endif //__STAR_SDK_PCAP_H
