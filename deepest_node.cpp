/*这段代码在CARLA中可以用于空间覆盖优化和中心位置确定，具体包括：
最小覆盖区域 - 找到覆盖一组最远点的最小区域
关键枢纽定位 - 确定连接多个远距离位置的中心点
资源效率优化 - 用最少资源实现最大覆盖
层次化分析 - 理解复杂空间结构的深度特征
这是空间分析和优化决策的基础工具，特别适用于需要平衡覆盖范围和资源效率的场景，在自动驾驶的感知、规划和测试中都有重要应用。*/
class Solution {
public:
    pair<TreeNode*, int> f(TreeNode* root) {
        if (!root) {
            return {root, 0};
        }
        auto left = f(root->left);
        auto right = f(root->right);
        if (left.second > right.second) {
            return {left.first, left.second + 1};
        }
        if (left.second < right.second) {
            return {right.first, right.second + 1};
        }
        return {root, left.second + 1};
    }
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        return f(root).first;
    }
};
