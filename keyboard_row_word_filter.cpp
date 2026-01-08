/*这段代码用于筛选可由键盘同一行字母打出的单词
核心功能
检查单词/字符串是否全部由键盘同一行字母组成，并过滤出符合条件的字符串。
CARLA应用场景
1. 命令行工具优化
快捷命令设计：为CARLA仿真控制台设计单手操作快捷键
命令别名生成：创建同一行字母组成的短命令，便于快速输入
2. 自动化测试脚本
测试用例过滤：筛选可以用键盘单行输入的测试数据
压力测试：模拟用户单手操作时的输入序列
错误注入测试：生成特定模式的错误输入
3. 用户界面辅助
可访问性设计：为有运动障碍的用户提供单行可输入的指令
平板/移动端适配：优化触摸屏虚拟键盘的输入体验
4. 安全与验证
输入验证：检测可能的键盘滚压测试（如"asdfgh"这类相邻键输入）
防暴力破解：识别同一行键位的常见密码模式
5. 日志与调试
日志关键字过滤：快速筛选特定模式的关键词
调试命令分类：按输入难度组织调试工具命令*/
class Solution {
public:
    vector<string> findWords(vector<string>& words) {
       vector<string> ans;
       string rowIdx = "12210111011122000010020202"; 
       for(auto & word : words){
          bool isValid = true;
          char idx = rowIdx[tolower(word[0]) - 'a'];
          for(int i = 1;i < word.size();++i)
          {
            if(rowIdx[tolower(word[i]) - 'a'] != idx){
                isValid = false;
                break;
            }
          }
          if(isValid){
                ans.emplace_back(word);
            }


       }
       return ans;
    }
};
