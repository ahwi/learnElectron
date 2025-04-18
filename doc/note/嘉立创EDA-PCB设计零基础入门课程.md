# 嘉立创EDA-PCB设计零基础入门课程







## 04-0 新建工程及LED灯模块电路原理图绘制

## 1. 新建工程

1. `文件-->新建-->工程 ` 工程名写 `GD32F103C8T6_最小系统`

2. 修改图纸大小：

![image-20240507184757964](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240507184757964.png)



**创建LED元件库**

1. 新建元件库：`文件-->新建-->元件库 `

   ![image-20240507185103997](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240507185103997.png)

2. 左下角可以看到创建的库：

   <img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240507185308484.png" alt="image-20240507185308484" style="zoom:80%;" />

3. 新建器件：`文件-->新建-->元件 `， 填写完名称和描述后，点击保存

   ![image-20240507185524233](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240507185524233.png)

4. 名称写R，描述去掉：

   <img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240507185713889.png" alt="image-20240507185713889" style="zoom:50%;" />



5. 调整网格尺寸：

   ![image-20240507223728498](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240507223728498.png)

6. 绘制矩形框

   <img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240507190240485.png" alt="image-20240507190240485" style="zoom:50%;" />



7. 绘制出相应的形状

   ![image-20240507223831978](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240507223831978.png)

用类似的方法创建LED灯

![image-20240507223920094](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240507223920094.png)

**绘制LED灯电路**

![image-20240507223957874](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240507223957874.png)

> 如果元器件的元件有更改，可以点击放置，会弹出是否更新的窗口，这时候点更新就可以把原理图里面旧的元器件更新过来了





## 04-7 原理图整理

![image-20240514224228365](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514224228365.png)

## 04-8 原理图DRC检测

`设计 --> 检查DRC`

![image-20240514224315199](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514224315199.png)

**设计规则**

设计规则可以更改检查DRC的相应规则

![image-20240514225009696](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514225009696.png)

![image-20240514225023220](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514225023220.png)

## 05-0 C0603封装绘制

### 0603封装绘制

0603的焊盘图

![image-20240514231343120](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514231343120.png)



`文件-->新建-->封装`

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514230253789.png" alt="image-20240514230253789" style="zoom:50%;" />



![image-20240514230415624](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514230415624.png)



设置画布属性：调成网格

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514230622256.png" alt="image-20240514230622256" style="zoom:50%;" />

放置单焊盘，并设置图层为顶层

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514230829446.png" alt="image-20240514230829446" style="zoom:50%;" />

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514230853949.png" alt="image-20240514230853949" style="zoom:50%;" />

设置焊盘形状与大小：

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514231124251.png" alt="image-20240514231124251" style="zoom:50%;" />

放置第二个焊盘

![image-20240514231209905](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514231209905.png)

设置两个焊盘的坐标：

`中心X`分别为`-0.8`和`+0.8`

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514231508896.png" alt="image-20240514231508896" style="zoom:50%;" />

**绘制丝印**

* 选择丝印层

* 选择折线
* 圆弧90°
* 线宽0.2mm（图中绘制错）

![image-20240514232135614](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514232135614.png)

绘制出图形：

![image-20240514233112335](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514233112335.png)

**阻焊层**

下图紫色的就是阻焊层：（紫色在覆盖绿油时，会把紫色的部分扣掉，把焊盘裸漏出来）

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514233201281.png" alt="image-20240514233201281" style="zoom:50%;" />

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514233357488.png" alt="image-20240514233357488" style="zoom:50%;" />

点击焊盘可以设置阻焊层的大小（使用自定义即可）

![image-20240514233433788](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514233433788.png)

至此，C0603的封装就画好了

### 封装管理器：设置对应的封装

选择封装管理器：

![image-20240514234109541](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514234109541.png)

勾选上C01~C20 (C18、C19除外)，选择C0603封装，点击更新

![image-20240514233954166](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240514233954166.png)

## 06-0 从原理图转到PCB

`设计 --> 更新/转换原理图到PCB`

![image-20240523221220603](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523221220603.png)

点击应用修改

![image-20240523221320584](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523221320584.png)



飞线层：

蓝色的线就是飞线，代表器件的引脚是相连的

![image-20240523221602736](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523221602736.png)

## 06-1 网络表概念解读

有些软件的原理图和PCB是分开的（不能一键转换），就需要先从原理图软件导出网络表（里面存储各个引脚的连接关系），然后再用PCB软件把网络关系导入进来。

其他略

## 06-2 板框绘制

`放置-->板框-->矩形`

![image-20240523222320786](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523222320786.png)



从原点处放置一个矩形

![image-20240523222407009](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523222407009.png)

点击画布，在`属性`中把单位切换成毫米

![image-20240523222659472](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523222659472.png)



把宽高设置成 `50*60 mm`，圆角半径设置成`5 mm`

![image-20240523223051327](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523223051327.png)

确认大小后锁定板框，避免误操作

![image-20240523224945178](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523224945178.png)

## 06-3 模块化预布局

准备将各个模块进行预布局

> 在原理图中，款选某个模块后，右键点击交叉布局，就可以切换到PCB视图，并且该模块的元器件是被选中的状态。
>
> 原理图中选中，直接切换到PCB视图，选中的器件也都是选中状态。

### 更改丝印位置及大小

`右击某个丝印 --> 查找 --> 查找全部`

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523224141652.png" alt="image-20240523224141652" style="zoom:50%;" />

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523224200299.png" alt="image-20240523224200299" style="zoom:50%;" />

`布局-->属性位置 --> 属性位置选为中间`

![image-20240523224314446](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523224314446.png)

![image-20240523224413337](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523224413337.png)

所有器件的丝印就都在中间了

![image-20240523224443104](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523224443104.png)

也可更改字体的线宽和高度 （视频中改为`线宽2mil 高度10mil`）

![image-20240523224605749](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523224605749.png)

> 后面为了方便焊接，应该把丝印改回来（个人觉得）



### 放置MCU

MCU通常放在中间

![image-20240523225857631](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523225857631.png)

### 晶振

晶振要靠近MCU

![image-20240523230113164](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240523230113164.png)



### 更新排针的封装库

编辑封装：`封装 --> 选着对应的库 --> 选中TDR-TH_20PIN --> 编辑封装`

<img src="assets/image-20240525223518145.png" alt="image-20240525223518145" style="zoom:33%;" />

把原点改成在排针中间：`放置-->画布原点-->从焊盘中央`

<img src="assets/image-20240525223722380.png" alt="image-20240525223722380" style="zoom: 33%;" />

在原理图中选中排针，点击封装

<img src="assets/image-20240525224053965.png" alt="image-20240525224053965" style="zoom: 33%;" />

`选择封装-->更新`

<img src="assets/image-20240525224200597.png" alt="image-20240525224200597" style="zoom: 33%;" />

另一个排针也同上面两步一样更新

更新PCB：`设计-->更新/转换原理图到PCB`

<img src="assets/image-20240525224434500.png" alt="image-20240525224434500" style="zoom:50%;" />

## 06-4 精细化布局

根据原理图及引脚连接关系，调整好元器件位置

<img src="assets/image-20240526165924642.png" alt="image-20240526165924642" style="zoom:50%;" />

可以在另一个窗口打开原理图，方便对照着修改：

<img src="assets/image-20240526170045381.png" alt="image-20240526170045381" style="zoom:50%;" />

## 07-0 设计规则设置

`设计-->设计规则`

<img src="assets/image-20240526170544424.png" alt="image-20240526170544424" style="zoom:50%;" />

`copperThickness1oz`与`copperThickness2oz`的区别：

布线生产出来是有厚度的，`copperThickness1oz`为1盎司，`copperThickness2oz`为2盎司即`copperThickness1oz`的两倍，一般情况下选择`copperThickness1oz`就好。

### 设置间距

![image-20240526171048552](assets/image-20240526171048552.png)

该页面可以设置导线到导线，导线到焊盘之间的间距，我们一般设置为`8mil`就可以。

<img src="assets/image-20240526171234336.png" alt="image-20240526171234336" style="zoom:50%;" />

元件到元件设置成`10mil`

![image-20240527211807004](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240527211807004.png)



### 设置导线宽度

<font color=blue>添加电源线的导线宽度：</font>

1. 可以先通过`PCB走线载流计算器`计算出需要的导线宽度：

   > https://www.eda365.com/article-12-1.html

   <img src="assets/image-20240526172327564.png" alt="image-20240526172327564" style="zoom:50%;" />

2. 设置默认的导线宽度：`设计规则`页面：`copperTickness1oz`

   ![image-20240527211341264](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240527211341264.png)

3. 添加导线宽度规则：`设计规则`页面：`物理-->导线`添加`power`选项

   ![image-20240526173506805](assets/image-20240526173506805.png)

4. 添加网络类：`设计-->网络类管理器-->添加一个“power”类，并把相关网络添加进来`

   ![image-20240526173006153](assets/image-20240526173006153.png)

   ![image-20240526173109318](assets/image-20240526173109318.png)

5. 设置power类对应的导线规则：

   `设计规则-->网络规则-->导线`将`power`类的规则设置为`power`

   <img src="assets/image-20240526173845907.png" alt="image-20240526173845907" style="zoom:50%;" />

   

### 设置差分

添加差分对：

`设计-->差分对管理器-->单机选择网络：在PCB图中选择USB的D+引脚`

![image-20240526181457352](assets/image-20240526181457352.png)

![image-20240526181849265](assets/image-20240526181849265.png)



选择`应用-->确认`

到设计规则页面，选择`差分对-->differentialPair`页面，设置线宽、间距等规则

![image-20240526182231653](assets/image-20240526182231653.png)

> 有个计算差分信号的工具：`si9000`
>
> 在高速板的设计中，应用较多

### 过孔尺寸

可以通过`PCB过孔载流计算器`计算需要的过孔尺寸

如下图：孔径12mil可以过1.8安培的电流

![image-20240526183300966](assets/image-20240526183300966.png)

设置`过孔外直径`为24mil，`过孔内直径`为12mil

> 一般设置过孔外直径为内直径的2倍

![image-20240526183507768](assets/image-20240526183507768.png)



> 补充知识：视频`18:33`秒
>
> 通过上面的计算器可知，一个12mil的过孔可以过1.8安培的电流，如果有2A的电流，可能就需要多个过孔来提高电流的承载能力。
>
> 疑问：难道不是提高孔径大小吗







## 07-1 PCB布线1

PCB布局原则：先从复杂的地方布线，一般先从MCU开始

`alt+w`布线的快捷键

设置`起始布线宽度`和`起始打孔尺寸`为跟随规则

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240527211635759.png" alt="image-20240527211635759" style="zoom:50%;" />

`shift+s`可以把丝印放到下一层，让走线看起来更清晰一点

![image-20240527213204813](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240527213204813.png)

**包地处理**

包地线宽一般是普通走线的2倍，这边是6mil的2倍，12mil

把`power`的规则改成最小12mil

![image-20240527214237291](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240527214237291.png)

进行包地：

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240527215134958.png" alt="image-20240527215134958" style="zoom:50%;" />



`alt+v`：在包地上打过孔

![image-20240527215533398](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240527215533398.png)

![image-20240527220246820](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240527220246820.png)

**电源**

把`power`的规则改成最小8mil

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240527224519230.png" alt="image-20240527224519230" style="zoom:50%;" />



修改`power`的导线线宽默认为20mil

![image-20240527230427832](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240527230427832.png)

### 07-2 PCB布线2

**电源线铺铜**

使用多边形铺铜

![image-20240528203347591](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528203347591.png)

设置铺铜方式为直连

![image-20240528203848896](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528203848896.png)

![image-20240528210633956](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528210633956.png)

**直连铺铜和发散铺铜的区别**

<font color=blue>直连铺铜</font>

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528204736503.png" alt="image-20240528204736503" style="zoom:50%;" />

<font color=blue>发散铺铜</font>

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528204647755.png" alt="image-20240528204647755" style="zoom:50%;" />

**电源部分画好之后的图**

![image-20240528211806180](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528211806180.png)

**差分对布线**

选择`差分对布线`进行布线，`差分对等长调节`进行长度的调节

![image-20240528214929936](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528214929936.png)

布线的效果：

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528214831770.png" alt="image-20240528214831770" style="zoom:50%;" />

### 07-3 PCB布线3

处理这种直角时，可以用圆弧90°进行过渡

![image-20240528231642961](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528231642961.png)

![image-20240528231704191](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528231704191.png)

移除回路选项设置为 否

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528231748825.png" alt="image-20240528231748825" style="zoom:50%;" />

### 07-4 铺铜

设置禁止铺铜区域：

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528232737180.png" alt="image-20240528232737180" style="zoom:50%;" />

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528232806056.png" alt="image-20240528232806056" style="zoom:50%;" />

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528233448184.png" alt="image-20240528233448184" style="zoom:50%;" />

两个晶振都设置禁止铺铜区域：

![image-20240528233609762](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528233609762.png)

**底层铺铜**





<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528233911410.png" alt="image-20240528233911410" style="zoom:50%;" />

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528234021719.png" alt="image-20240528234021719" style="zoom:50%;" />

<font color=blue>可以修改`设计规则`中的`网络间距`和`到边框/槽孔间距`</font>

![image-20240528234400929](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240528234400929.png)



## 07-5 DRC设计规则检查

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529210808556.png" alt="image-20240529210808556" style="zoom:50%;" />

## 07-6 优化与丝印调整

**添加过孔**

给板子多打点GND过孔

![image-20240529212532786](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529212532786.png)

**丝印调整**

`选中一个丝印-->右击查找-->查找全部`

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529212717865.png" alt="image-20240529212717865" style="zoom:50%;" />

线宽改成6mil，高度45mil

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529212843388.png" alt="image-20240529212843388" style="zoom:50%;" />

`布局-->属性位置-->属性位置：上边`

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529212910244.png" alt="image-20240529212910244" style="zoom:50%;" />

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529212930341.png" alt="image-20240529212930341" style="zoom:50%;" />

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529213144854.png" alt="image-20240529213144854" style="zoom:50%;" />

**添加泪滴**

`工具-->泪滴-->应用`

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529213414894.png" alt="image-20240529213414894" style="zoom:50%;" />



<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529213434627.png" alt="image-20240529213434627" style="zoom:50%;" />

泪滴的效果（有圆弧过渡）：

![image-20240529213633364](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529213633364.png)

![image-20240529213702292](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529213702292.png)

然后再重新铺铜和DRC检测



**调整丝印**

过滤中设置只选中`文本`和`元件属性`

![image-20240529221634009](嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529221634009.png)

调整完丝印后：

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529225105254.png" alt="image-20240529225105254" style="zoom:50%;" />

**关联3D模型封装**

略

## 07-7 导入图片

导入图片

<img src="嘉立创EDA-PCB设计零基础入门课程.assets/image-20240529225614677.png" alt="image-20240529225614677" style="zoom:50%;" />

导入图片到丝印层，就可以当作LOG之类的。



## 工具：

### PCB走线载流计算器

https://www.eda365.com/article-12-1.html

![image-20240526171827305](assets/image-20240526171827305.png)

### si9000 差分信号相关工具

![image-20240526182738199](assets/image-20240526182738199.png)



### PCB过孔载流计算器

https://www.eda365.com/article-11-1.html

![image-20240526183057541](assets/image-20240526183057541.png)

