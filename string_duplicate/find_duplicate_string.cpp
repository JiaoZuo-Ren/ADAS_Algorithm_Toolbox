/*主要功能
通过文件内容（而非文件名）识别重复文件，并按内容分组返回文件路径。

CARLA应用场景
场景文件管理 - 检测重复的3D模型、纹理资源，优化存储

日志数据分析 - 识别重复的仿真日志，避免重复分析

数据集去重 - 清理自动驾驶训练数据中的重复图像/传感器数据

配置检查 - 发现重复的配置文件，确保实验配置一致性

缓存清理 - 识别并清理临时生成的重复中间文件*/
class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        // 创建一个哈希表，key是文件内容，value是包含该内容的文件完整路径列表
        unordered_map<string,vector<string>> m;
        
        // 遍历输入的每个路径字符串（每个字符串格式：目录路径 文件名1(内容1) 文件名2(内容2)...）
        for(string &s : paths){
            // 找到第一个空格，区分目录路径和文件名部分
            int start = s.find(' ');
            // 提取目录路径，并在末尾加上"/"
            string path = s.substr(0,start).append(1,'/');
            
            // 找到第一个"("的位置，表示文件内容的开始
            int leftBracket = s.find('(',start);
            
            // 循环处理当前字符串中的所有文件
            while(leftBracket != -1){
                // 提取文件名（从空格后到左括号前的内容）
                string fileName = s.substr(start + 1, leftBracket - start - 1);
                
                // 找到对应的右括号")"，表示文件内容结束
                int rightBracket = s.find(')',leftBracket);
                
                // 提取文件内容（括号内的内容），并添加到哈希表中
                // key: 文件内容，value: 添加完整路径（目录路径+文件名）
                m[s.substr(leftBracket + 1,rightBracket - leftBracket - 1)].emplace_back(path + fileName);
                
                // 更新start位置为右括号后一位，准备处理下一个文件
                start = rightBracket + 1;
                
                // 查找下一个左括号，如果没有则结束循环
                leftBracket = s.find('(',start);
            }
        }
        
        // 创建结果数组
        vector<vector<string>> result;
        
        // 遍历哈希表，找出重复文件（同一内容对应多个文件）
        for(auto &p : m){
            // 如果该内容对应的文件数>=2，说明有重复
            if(p.second.size() >= 2){
                // 将这些文件的路径数组添加到结果中
                result.emplace_back(p.second);
            }
        }
        
        // 返回所有重复文件的路径分组
        return result;
    }
};
