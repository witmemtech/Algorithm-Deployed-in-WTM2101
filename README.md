# 基于存内计算开发板WTM2101的算法部署



说明：WTM2101是首颗国际量产并商业化应用的存内计算芯片，本库围绕存内计算开发板WTM2101做算法部署教程。

算法部署实现Demo：



目录：

1. WTM2101 SDK

2. Tools

3. Witmem Studio

4.   Docker软件 

5. 机器学习算法部署

6. 语音识别算法部署

   



## WTM2101 X3板


WTMDK2101-X3是针对WTM2101 AI SOC设计的评估板，包含： 

（1）WTM2101核心板，即我们的存算芯片。

（2）和I/O 板：WTM2101运行需要的电源、以及应用I/O接口等。

![img](http://www.witintech.com/wladmin/kindeditor/attached/image/20231204/20231204220711_75537.png)

![img](http://www.witintech.com/wladmin/kindeditor/attached/image/20231204/20231204220748_82242.png)



## Mapper

witin_mapper是知存科技自研的用于神经网络映射的编译软件栈，可以将量化后的神经网络模型映射到WTM2101 MPU加速器上，是一种包括RiscV和MPU的完整解决方案，可以完成算子和图级别的转换和优化，将预训练权重编排到存算阵列中，并针对网络结构和算子给出存算优化方案，同时将不适合MPU运算的算子调度到CPU上运算，实现整网的调度，让神经网络开发人员高效快捷的将训练好的算法运行在WTM2101芯片上，极大缩短模型移植的开发周期并提高算法开发的效率。





## Project 



## Python



## Tools



## Witmem Studio 

Witmem Studio是由知存科技开发的一款全功能集成开发环境，包含客户识别的SDK推送功能，SDK包自动更新下载安装功能，内核自动识别语法高亮编辑器，面向不同功能的个性化工程创建功能，以及常规IDE所具有的项目工程管理，文件编辑、编译、调试等功能。



## Docker 软件

https://github.com/witmem/Witmem-Toolchain-WTM2101


## 算法部署基础步骤

***\实验环境搭建\**** 

***\模块⼀：软件包下载及环境搭建\**** 

***\步骤一：搭建docker、mappper环境：\****

①Linux下通过Docker直接下载，获取指令：

docker pull witin/toolchain:v001.000.034

②Window环境，可以通过docker desktop来使用docker:

1) 下载安装Docker desktop(win10或以上)：

[Docker Desktop: The #1 Containerization Tool for Developers | Docker](https://www.docker.com/products/docker-desktop/)

2) 通常需要更新WSL，下载链接如下，更新后需要重启生效

[旧版 WSL 的手动安装步骤 | Microsoft Learn](#step-4---download-the-linux-kernel-update-package)

3) Docker desktop 基本使用教程：

[Docker-desktop(Docker桌面版)——入门篇_dockerdesktop干嘛用的-CSDN博客](https://blog.csdn.net/m0_67393295/article/details/126327312)

4) Docker desktop通常默认安装在c:\Program File\docker，可以通过软连接的形式修改Docker安装路径：

[如何将Docker（Windows桌面版)自定义安装目录_自定义docker安装路径-CSDN博客](https://blog.csdn.net/qq_41467216/article/details/130501349)

5）在Docker desktop里，可以通过搜索获得witin_toolchain，我们需要的是034版本（ps:Hub反应慢可以开VPN获取，或者使用镜像路径，具体操作方式见3链接）

![img](file:///C:\Users\18475\AppData\Local\Temp\ksohtml22548\wps11.jpg) 

5) 测试：

①：管理员模式下打开命令行窗口

docker run -it --name XXXX witin/toolchain:v001.000.034

②：默认进入workspace目录下，可以进入witin_mapper下执行测试脚本：

cd witin_mapper

python3 tests/python/frontend/onnx/witin/wtm2101/precision/XXXX.py

![image-20240806175639165](https://github.com/user-attachments/assets/db2e8c20-e28b-4f9f-ba38-32cb548a06d5)


③：使用exit退出，再次进入可按如下操作：

④：通过docker ps -a获取容器id，然后打开进入容器
![image-20240806175659265](https://github.com/user-attachments/assets/3ef4aec9-9c88-449d-b73a-7079be18691b)


 

***步骤二：搭建IDE环境****

①预先下载安装包，下载安装

②默认安装路径，直接点击安装

③从主菜单的File->Open…菜单，或者点击工具栏的![image-20240806175707259](https://github.com/user-attachments/assets/19cd80d8-368c-4c35-a22e-55e7d7a3e3c3)
按钮，打开选择文件对话框，选择要打开的项目文件，即***.wmproject文件即可，点击【打开】按钮即可打开工程。如下图所示。

![image-20240806175757395](https://github.com/user-attachments/assets/aeaf086d-2514-4e24-a50c-6ddf29587f98)


 

***步骤三：其他需要安装的软件****

① 请确保安装以下环境：python, git, pytorch

 

***步骤四：下载训练数据****

① 最新数据集在软件安装包中



***动⼿实验： 基于WTM2101的算法部署****

***模块⼀：简介**** 

1、WTMDK2101-X3介绍

​	WTMDK2101-X3是针对WTM2101 AI SOC设计的评估板，包含：

（1） WTM2101核心板，即我们的存算芯片。

（2） 和I/O 板：WTM2101运行需要的电源、以及应用I/O接口等.

![image-20240806175807764](https://github.com/user-attachments/assets/f1818122-424e-47bb-a261-ca84eb24ce9c)


核心板示意图
![image-20240806175953745](https://github.com/user-attachments/assets/df1f9bbc-1a00-4309-b2e2-6c4dfa463e93)


 WTMDK2101-X3 I/O 板示意图

##### 2，训练数据集

***模块⼆：搭建算法训练工程，完成算法训练与量化\****

1. 模型训练工程搭建:

提供DNN和DNN_DEEP两种网络结构的示例，

***\步骤一：\配置python/config.py，参数释义见代码注释。

***\步骤二：\运行python/train.py，模型训练完毕后，在models/net_type文件夹下生成bestModel.pth，此即我们的模型权重。

***\步骤三：\运行python/onnx_converter.py，在models/net_type文件夹下生成bestModel.onnx。此步骤即完成原始模型到知存onnx格式模型的转换。



***模块三：算法模型转换

***1，Dcoker下 Mapper转换流程****

***步骤一：拷贝至指定文件夹

我们将mapper/input 拷贝至witin/toolchain:v001.000.034的指定文件夹下（通常为/home，需与gen_mapper.py文件里描述一致）

 

![image-20240806180155574](https://github.com/user-attachments/assets/8b729292-6a1f-495b-aad6-aa0a69784f3d)

 

***步骤二：在workplace witin_mapper下执行gen_mapper.py

docker start id

docker attach id

cd witin_mapper

python3 /home/mapper/input/gen_mapper.py

![image-20240806180205537](https://github.com/user-attachments/assets/2524d539-6388-411c-9355-135cc413e640)


 

***步骤三：在对应的output文件下获得输出

 
![image-20240806180212761](https://github.com/user-attachments/assets/5d724ed8-0f18-4cd2-8cd6-153c4f0cdf87)


 

 


***模块四：算法模型烧写

***步骤一：系统连接

进行模型烧录和开发时，我们需要将JTAG，核心板，NPU烧写板连接好，并打开开关，如系统连接示意图所示。

***步骤二：

![image-20240806180222235](https://github.com/user-attachments/assets/3cc17ad5-0330-446b-b642-58ba6cfb61a1)


系统连接示意图



 

***步骤三：跳线帽连接：

如跳线帽连接示意图所示，按照红框标注进行跳线连接。含义解释：

  

| 跳线 | 编号     | 跳帽连接 | 含义                                                        |
| ---- | -------- | -------- | ----------------------------------------------------------- |
| 1    | VIN      | VSPK     | Audio DAC 芯片供电，5V                                      |
| 2    | 3.3V     | AVDD     | WTM2101芯片模拟供电，3.3V                                   |
| 3    | 3.3V     | IOVDD    | WTM2101芯片I/O供电，3.3V                                    |
| 4    | 0.9/1.2V | DVDD     | 用 WTM2101BC 芯片时需接跳帽                                 |
| 5    | GND      | BOOT0    | 启动模式，SRAM启动                                          |
| 6    | 32K      | XTAL     | 晶振                                                        |
| 7    | RXD      | P17      | 串口                                                        |
| 8    | TXD      | P16      |                                                             |
| 9    | PERIV    | 3.3V     | QSPI Flash、数字麦克风、晶振供电，与 IOVDD 选择一致，即3.3V |
| 10   | P13      | WS       | I2S 功放的WS                                                |
| 11   | P12      | CK       | I2S 功放的CK                                                |
| 12   | P10      | SDO      | I2S 功放的SDO                                               |
| 13   | P05      | DMDIN    | 数字麦克风的Din                                             |
| 14   | P06      | DMCK     | 数字麦克风的CK                                              |

 

![image-20240806180353673](https://github.com/user-attachments/assets/985fac53-4cf9-464d-a532-e61801618417)


跳线帽连接示意图

 

***步骤四：

使用project/ WitinProgramTool_WTM2101下的WitinProgramTool.exe进行模型权重烧写。烧写时的开发板接线请参考其他文档。

 

***步骤五：烧写指令:

.\WitinProgramTool.exe -m init

.\WitinProgramTool.exe -m program -i XXXX\map.csv -k 2

其中XXXX为步骤2.（3）中生成的mapper/output/map

示例:

![image-20240806180415157](https://github.com/user-attachments/assets/e605daf2-acf9-4e22-b024-0fb8b4d5e764)



***模块五：算法模型在芯片运行推理

**步骤一：

从库中下载知存IDE Witmem Studio。

**步骤二：

生成的mapper/output/register.c放在project/Model，使用Witmem Studio打开project/Project/SES-RISCV/Demo.wmproject。

![image-20240806180429940](https://github.com/user-attachments/assets/02ff58f0-9837-4764-a71e-b55bfb940b6c)


**步骤三：Target->Download下载工程：
 

![image-20240806180434987](https://github.com/user-attachments/assets/1c5f9432-891c-49cb-ae79-e06a57949314)

 

注：本demo所用为x3开发板，所用串口GPIO为16,17。若是其他开发板，请根据情况修改串口。

 

**步骤四：

打开tools中的串口工具，设置波特率115200，查看准确率输出


![image-20240806180442453](https://github.com/user-attachments/assets/2d4f2338-075b-438c-9f26-a6a4d463e7f7)
 

***\*至此，我们完成了语音识别从训练到部署的全流程，本教程结束。\****





## 机器学习算法部署
![image-20240813194132450](https://github.com/user-attachments/assets/41c95aa7-4da2-42e8-94ec-01a8a5d80854)




## 语音识别算法部署

***\*AISHELL-WakeUp-1\*******\*数据集介绍\****

AISHELL-WakeUp-1数据集是中英文唤醒词语音数据库，命令词为“你好，米雅” “hi, mia”，语音数据库中唤醒词语音3936003条，1561.12小时，邀请254名发言人参与录制。录制过程在真实家居环境中，设置7个录音位，使用6个圆形16路PDM麦克风阵列录音板做远讲拾音(16kHz，16bit)、1个高保真麦克风做近讲拾音(44.1kHz，16bit)。此数据库可用于声纹识别、语音唤醒识别等研究使用。


Gitcode links:https://gitcode.com/m0_58966968/WITMEM-Algorithm-Deployed-in-WTM2101/overview 
