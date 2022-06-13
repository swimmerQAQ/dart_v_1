## Acquirement
- data: Angle, Distance, Relative_position.
- freqency: Fast, Precise, In_order.
----
## data
 - pnp => distance
 > hardness[11000]
 - model => angle
 > hardness[11000]
 - model => relative position
 > hardness[11100]
 ----
 ## freqency
 - new_thread
 > hardness[11000]
 - upgrade_hardware
 > hardness[11110]
 ----
 ----
 ----
 ## accomplish
 - catch data
 ----
 > green_light + rotated_angle
 >-
 >>two main features

 > Detect
 >-
 >> Detect's ptr
 >>
 >>input <=> flat_bar's & two inflat_bars' ptr
 >>
 >>---------<=>green_dot's ptr
 >>
 >>invert image => **green light & angle bar**
----
 > Relative_position
 >-
 >> get relative position: distance angle rotation

> R_position
>- 
>>R_position's ptr 
>>
>>count in model !!! **work as ptr input the detect**
>>
>>using pnp mat or mathe model.
----

# 通讯协议
----
> 车组：飞镖
>
> 时间：2022.5.8
>
> 使用平台：树梅派zerow2 - stm32F4 之间串口通信
>
> 库：树梅派 -> wiring库 stm32F4 -> 串口
> 

> 协议主体如下：

# 符号

|.|功能|raspberry|stm43F4|
|:----:|:----:|:----:|:----:|
|'s'|start|115|'s'|
|'r'|receive|*|'r'|
|'-1'|compartment|无需接收|'-1'|
|‘o’|over|*|'o'|

> ## 模拟
>
> stmF4 -> 's'
>> 树梅派 发送'r' 意为接受成功
>>> stmF4 接收'r'并发送'r' 意为接受成功
>>>> 树梅派 **第二次** 接收'r' 开始 捕获图像
>>>>> 数据传输： 数值符号用'-1'隔开
>>>>>> 发送结束树梅派 发送‘o’
>>>>>>>stm32F4 接受'o', 树梅派 **第二次** 接收‘o’
>
> 一次交互结束

## 数据意义
- （在树梅派第二次接受’r‘后）
> model : 0 1 2 3 (其中一个)
>>0 无目标； 1 只有绿灯； 2 只有三角板； 3 匹配三角板和绿灯
>>> 除了第一种情况，其他都要读后面的数据
>>>> -1 距离 -1 yaw轴 -1 pitch轴 -1 （像素点）x坐标 -1 y坐标 -1
>>>>
>>>>注意： 最好是对-1计数， 时间允许
循环校验，因为yaw和pitch可能有-1度

