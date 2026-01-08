/*核心功能
用户管理：每个用户有一个关注列表和推文列表。
发布推文：用户可以发布推文，每个用户只保存最近的10条推文（可配置）。
关注/取消关注：用户可以关注或取消关注其他用户。
获取消息流：获取用户以及其关注者的最近推文，按时间倒序排列（最新的在前）。
在CARLA中的潜在应用
1. 多智能体通信
每个智能体（车辆）可以发布自己的状态（位置、速度、事件等）作为“推文”。
其他智能体可以关注它，从而获取其状态更新，用于协同决策（如车队行驶、交通流协调）。
2. 事件和状态广播
当发生交通事件（事故、施工、拥堵）时，相关智能体可以发布事件信息，关注者可以及时获取并调整行为。
交通基础设施（如交通灯、路侧单元）也可以作为“用户”发布状态变化，被车辆关注。
3. 数据记录和回放
每个智能体的推文列表可以记录其历史状态，用于回放和分析。
可以获取某个智能体及其关注者的最新状态，用于仿真监控和调试。
4. 协同感知
智能体可以通过关注其他智能体来扩展感知范围，形成协同感知网络。
例如，一辆车可以通过关注其他车辆来获取盲区信息。
5. 仿真实验管理
在仿真实验中，可以定义不同的关注关系来模拟信息传播模式（如广播、多播、单播）。
通过调整关注关系，可以研究不同通信拓扑对整体系统性能的影响。
代码特点在CARLA中的优势
时间戳管理：每个推文都有唯一递增的时间戳，可以准确排序，适合仿真中的时间敏感操作。
内存效率：每个用户只保存最近的10条推文，避免内存无限增长，适合长时间仿真。
快速查询：使用哈希表存储用户和推文时间戳，查询和更新效率高，适合实时仿真。
灵活的关注关系：使用集合存储关注者，可以快速添加和删除关注关系。*/
class Twitter {
    struct Node {
        unordered_set<int> followee;
        list<int> tweet; 
    };
    int recentMax, time;
    unordered_map<int, int> tweetTime;
    unordered_map<int, Node> user;
    
public:
    Twitter() {
        time = 0;
        recentMax = 10;
        // user.clear();  // ❌ 不需要，user是新建的，本身就是空的
    }
    
    void init(int userId) {
        user[userId].followee.clear();
        user[userId].tweet.clear();
    }
    
    void postTweet(int userId, int tweetId) {
        if(user.find(userId) == user.end()) {
            init(userId);
        }
        if(user[userId].tweet.size() == recentMax) {
            user[userId].tweet.pop_back();
        }
        user[userId].tweet.push_front(tweetId);
        tweetTime[tweetId] = ++time;
    }
    
    vector<int> getNewsFeed(int userId) {
        // 如果用户不存在，初始化
        if(user.find(userId) == user.end()) {
            init(userId);
            return {};  // 新用户没有推文
        }
        
        // 使用最小堆（优先队列）获取最近的推文
        using TweetInfo = pair<int, int>;  // (时间戳, 推文ID)
        priority_queue<TweetInfo, vector<TweetInfo>, greater<TweetInfo>> minHeap;
        
        // 辅助函数：将推文添加到堆中
        auto addTweetsToHeap = [&](list<int>& tweets) {
            int count = 0;
            for(int tweetId : tweets) {
                if(count >= recentMax) break;
                
                minHeap.push({tweetTime[tweetId], tweetId});
                if(minHeap.size() > recentMax) {
                    minHeap.pop();  // 保持堆大小为recentMax
                }
                ++count;
            }
        };
        
        // 添加用户自己的推文
        addTweetsToHeap(user[userId].tweet);
        
        // 添加关注者的推文
        for(int followeeId : user[userId].followee) {
            if(followeeId == userId) continue;
            addTweetsToHeap(user[followeeId].tweet);
        }
        
        // 从堆中提取结果（最新的在前）
        vector<int> ans;
        while(!minHeap.empty()) {
            ans.push_back(minHeap.top().second);
            minHeap.pop();
        }
        
        // 反转，让最新的在前面
        reverse(ans.begin(), ans.end());
        return ans;
    }
    
    void follow(int followerId, int followeeId) {
        if(user.find(followerId) == user.end()) {
            init(followerId);
        }
        if(user.find(followeeId) == user.end()) {
            init(followeeId);
        }
        user[followerId].followee.insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        if(user.find(followerId) == user.end()) {
            return;  // 用户不存在，直接返回
        }
        user[followerId].followee.erase(followeeId);
    }
};
