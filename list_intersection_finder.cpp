/*核心功能
找到两个链表中第一个相同的节点（内存地址相同）。
CARLA应用场景
1. 传感器数据融合
多传感器时间戳对齐：不同传感器（激光雷达、摄像头、雷达）的数据流链表，找到时间同步的交点
数据流合并点检测：多个数据源在某个时间点开始共享相同数据
2. 仿真状态追踪
车辆轨迹交叉分析：两辆车的历史轨迹链表，找到路径交叉点
事件链关联查找：不同事件序列（如交通违规、事故）找到共同的触发节点
3. 资源管理优化
共享资源检测：多个模块是否共享相同的资源节点（如内存池、缓冲区）
内存泄漏排查：检测不同对象链表是否意外共享节点
4. 回放系统调试
多日志流对齐：不同组件的日志链表，找到需要同步的时间点
状态恢复点查找：仿真回放中多个状态序列的共享恢复点
5. 网络通信分析
消息流合并检测：多个数据包流在某个节点开始共享内容
协议解析优化：找到不同解析路径的共同头部节点*/
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode *>visited;
        ListNode *temp = headA;
        while(temp != nullptr){
            visited.insert(temp);
            temp = temp->next;
        }
        temp = headB;
        while(temp != nullptr){
            if(visited.count(temp)){
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};
