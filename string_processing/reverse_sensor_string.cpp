/*主要用途
传感器数据处理 - 反转摄像头、激光雷达等采集的原始数据序列
通信协议解析 - 处理网络传输中的字节序反转或协议字段反转
日志回放系统 - 逆向播放数据流时的时间戳或帧序列处理
图像处理流水线 - 某些图像格式需要行或列的逆序处理

CARLA相关场景
点云数据转换：不同传感器坐标系间的数据转换可能需要序列反转
消息队列处理：ROS消息或自定义协议中的数据顺序调整
回放功能：实现仿真数据的正向/反向播放时的时间线操作
调试工具：开发辅助工具中的数据显示或日志分析**/
class Solution {
public:
    void reverseString(vector<char>& s) {
        // 获取字符串的长度
        int n = s.size();
        
        // 使用双指针法反转字符串
        // left指针从0开始，right指针从n-1开始
        // 当left < right时，交换两个指针指向的字符
        // 然后left向右移动一位，right向左移动一位
        for(int left = 0, right = n - 1; left < right; ++left, --right) {
            // 交换left和right位置的字符
            swap(s[left], s[right]);
        }
    }
};
