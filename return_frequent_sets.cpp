//这段代码用于统计二叉树中所有子树和的出现频率，并返回出现最频繁的子树和。
/*CARLA应用场景
1. 场景图属性分析
cpp
// 分析场景中不同区域/子场景的属性统计
// 例如：每个区域内的车辆总数、行人密度、障碍物数量等
class SceneAnalyzer {
    // 统计每个子区域的总属性值
    // 找出最常见的区域属性组合
};
2. 传感器覆盖范围统计
cpp
// 分析传感器检测区域的覆盖统计
// 统计不同子树区域的检测点数、信号强度总和
class SensorCoverage {
    // 找出最常见检测模式的区域
    // 优化传感器布局和参数设置
};
3. 路网分区流量分析
cpp
// 将道路网络组织成树状结构
// 统计每个子路网区域的流量总和
// 找出流量模式最相似的路网分区
class TrafficFlowAnalyzer {
    // 分析哪些道路区域具有相似的交通流量特征
    // 用于交通预测和路线规划
};
4. 行为模式聚类
cpp
// 分析车辆/行人行为树的子树和
// 统计行为序列的累积得分
// 找出最常见的行为模式
class BehaviorAnalyzer {
    // 识别高频出现的行为组合
    // 用于异常行为检测和行为预测
};*/
class Solution {
private:
    // 1. 添加 cnt 的定义
    unordered_map<int, int> cnt;
    int maxCnt = 0;
    // 2. 修复递归函数
    int dfs(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        // 计算子树和
        int sum = node->val + dfs(node->left) + dfs(node->right);
        // 统计该和出现的次数
        cnt[sum]++;
        // 更新最大出现次数
        maxCnt = max(maxCnt, cnt[sum]);
        return sum;
    }
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        // 清空之前的结果（重要：因为Solution可能被多次使用）
        cnt.clear();
        maxCnt = 0;
        // 计算所有子树和
        dfs(root);
        // 收集出现次数等于maxCnt的子树和
        vector<int> ans;
        for (auto& [s, c] : cnt) {
            if (c == maxCnt) {
                ans.emplace_back(s);
            }
        }
        return ans;
    }
