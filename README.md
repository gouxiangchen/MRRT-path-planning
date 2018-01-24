# MRRT-path-planning
2D robot path planning using MRRT algorithm 

# 说明

#### 实现的是MRRT（multiple RRT） 算法，多树搜索，本算法实现的是双树搜索，即从起点和终点同时生长搜索树（红树与黑树），当两树相遇时连接，其算法特点与RRT基本相似，可以相互对照。

#### 本来是老师实验室移动机器人需要的一种路径规划算法，实际并未在机器人上跑过，最终是整理成了一篇评价各个算法的论文

#### 后续将发出其他的路径规划算法

#### 想要运行的话，需要opencv2的支持，本人在VS2010 + opencv2 的环境下是测试过的

#### 运行结果示意也包含在其中了，MRRT.jpg是运行的结果，fr079_binary.jpg也是一个经典的benchmark，slam建图得到

#### 代码挺丑陋的，仅供参考，有部分注释

#### 联系 Author：陈狗翔 zhixinc@buaa.edu.cn