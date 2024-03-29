# Gravity <font color="red">DEMO</font>

> **Gravity** Unified Simulation Platform  
> 架构&周期精确统一模拟平台<font color="red">（目前仅为 DEMO）</font>  
>   
  
## 1. 概述  
&emsp;&emsp;```开发中``` ```合理性验证中``` ```进度慢``` ```业余兴趣``` ```三天打鱼两天晒网```  
  
&emsp;&emsp;**Gravity Uni-Sim Platform** 旨在提供以下内容：  
- **统一架构设计建模框架**  
    - 类事件驱动
    - 面向 Zero-Copy 优化提供指导  
    - 统一化组织 **架构** & **行为** & **周期精确模拟**  
    - 不同建模形式间的统一差分测试、分析  
    - 不同建模形式间模块的快速切换  
- **用户交互与自动化**  
    - Gravity-Shell (grv-shell) 控制台  
    - 工程化管理  
    - tcl 自动化  
- **工程组织**  
    - 模块级编译拆分  
    - 编译拆分后的自动重新组合  
- **实用工具**  
    - 建模框架、接口的自动生成  
    - 建模设计的常用合理性测试  
    - RTL模块、虚拟模块的半自动化文档生成  
    - ~~Gem5 等模型库的自动化迁移~~   
- **性能分析工具**  
    - 基于图论的关键路径分析  
    - TIP & TEA  
- **计算机辅助测试**  
    - 差分测试接口  
    - ATPG 指导  
- **仿真加速**  
    - FPGA 联合模拟、仿真

&emsp;&emsp;*以上内容可能在开发过程中被删除，或可能增添新内容。*  


## 2. 架构设计建模框架 

### 2.1. 架构设计建模
&emsp;&emsp;对于架构建模，使用 ```Phase``` 和 ```Wavefront``` 进行建模，在形式上类似于**事件驱动建模**。  
&emsp;&emsp;将整个处理器模型描述为一个或多个波平面，```Phase``` 则为波平面内的某一个相位点，```Wavefront``` 则为波平面的某一个波前（波阵面）。而性能监视、分析、追踪可以通过在 ```Wavefront``` 上插入架构模拟不相关的监视点来完成。   

#### Phase
&emsp;&emsp;```Phase``` 表示处理器架构中的一个具体节点，在事件模型中则为负责**接受事件**、**发送事件**的对象。这一具体节点可以代表处理器中的某个流水级、某个架构部件、某个组合逻辑模块等。  

#### Wavefront  
&emsp;&emsp;```Wavefront``` 表示处理器架构中的某一个架构事件，或者某个逻辑上的信息平面、数据流平面，在模型中则表示为**某个具体的事件**对象。主要用于表示处理器架构中的数据通路。各个 ```Phase``` 之间应当且仅应当通过 ```Wavefront``` 进行逻辑交互、数据交换。    


### 2.2. 事件交互约定  
&emsp;&emsp;为了方便实现 Zero-Copy，并且保证代码的可维护性，以及各个模块间交互的正确性，我们需要明确以下几个规则：  
- 某个 ```Wavefront``` 内的变量定义可以为引用，但应在任何时候都保证引用有效（空引用也视为有效，但必须在逻辑上防止直接方位空引用）。
- 某个 ```Wavefront``` 若引用了其他的 ```Wavefront```，那么必须在每个时钟周期内将引用置为空。    
- 某个 ```Wavefront``` 对象的生命周期应该总是与产生它的 ```Phase``` 对象的声明周期一致。   
    - 这意味着 ```Wavefront``` 不是即用即分配的，而总与产生它的 ```Phase``` 共存。  
    - 在 ```Phase``` 对象被销毁后，```Wavefront``` 对象也不应该再有效。  
- 某个 ```Phase``` 对象的销毁应该总是要遵循以下条件：  
    - 如果该 ```Phase``` 已经产生过 ```Wavefront``` 且被发送到事件总线上，那么它至少经过一个完整的时钟周期（```ClockPosedge``` 与 ```ClockNegedge```）后才能被销毁。且在时钟周期后、销毁前不应该再发送任何 ```Wavefront```。   
    - 如果该 ```Phase``` 在时钟周期内没有再发送过 ```Wavefront```，那么可以立即销毁。  
    - ```Phase``` 销毁前应该取消所有 ```Wavefront``` 的收集路径。   
- 某个 ```Phase``` 内若保存了其收集的 ```Wavefront``` 的引用，那么必须在每个周期内将引用置为空。  
- 某个 ```Phase``` 内允许复制并保存收集到的 ```Wavefront```。但在 ```Wavefront``` 对象较大时不建议这么设计。    

