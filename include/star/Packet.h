/**
 * @author   lucb
 * @date     2020/1/18
 */

#ifndef __STAR_SDK_PACKETS_H
#define __STAR_SDK_PACKETS_H

#include <vector>
#include <star/Shot.h>

namespace ss {

struct Packet {
    using Points = std::vector<LasShot_S>; //todo ʹ��object_pool��list�����ڴ濽��
    using Synchrons = std::vector<PosPPS_S>;
    // using GPSPackets = std::vector<scd::GPS>;
    // using IMUPackets = std::vector<scd::IMU>;

    Points points;
    Synchrons fast_synchrons;
    Synchrons slow_synchrons;
};

}
#endif //__STAR_SDK_PACKETS_H
