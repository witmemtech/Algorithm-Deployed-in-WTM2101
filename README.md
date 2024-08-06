# 【基于存内计算芯片开发板验证语音识别】 训练手册

[WTM2101 Speech Recognition Video ](https://www.youtube.com/watch?v=jOrEGvNcjF0)

## ⽬录 

### 实验环境搭建 

模块一：软件包下载及环境搭建

### 动⼿实验： 简单语音识别系统开发

模块⼀：简介 
模块⼆：搭建算法训练工程，完成算法训练与量化 
模块三：算法模型转换
模块四：算法模型烧写
模块五：算法模型在芯片运行推理



## 实验环境搭建 

#### 模块⼀：软件包下载及环境搭建 

##### 步骤一：搭建docker、mappper环境：

①Linux下通过Docker直接下载，获取指令：
docker pull witin/toolchain:v001.000.034
②Window环境，可以通过docker desktop来使用docker:
1)下载安装Docker desktop(win10或以上)：
Docker Desktop: The #1 Containerization Tool for Developers | Docker
2)通常需要更新WSL，下载链接如下，更新后需要重启生效
旧版 WSL 的手动安装步骤 | Microsoft Learn
3)Docker desktop 基本使用教程：
Docker-desktop(Docker桌面版)——入门篇_dockerdesktop干嘛用的-CSDN博客
4)Docker desktop通常默认安装在c:\Program File\docker，可以通过软连接的形式修改Docker安装路径：
如何将Docker（Windows桌面版)自定义安装目录_自定义docker安装路径-CSDN博客
5）在Docker desktop里，可以通过搜索获得witin_toolchain，我们需要的是034版本（ps:Hub反应慢可以开VPN获取，或者使用镜像路径，具体操作方式见3链接）

<img width="416" alt="image" src="https://github.com/user-attachments/assets/da638008-ab9f-40a9-804f-43f1a306b702">


5)测试：
①：管理员模式下打开命令行窗口
docker run -it --name XXXX witin/toolchain:v001.000.034
②：默认进入workspace目录下，可以进入witin_mapper下执行测试脚本：
cd witin_mapper
python3 tests/python/frontend/onnx/witin/wtm2101/precision/XXXX.py

<img width="416" alt="image" src="https://github.com/user-attachments/assets/4884b6c3-4656-46fb-9faa-e16b6bda9b38">


③：使用exit退出，再次进入可按如下操作：
④：通过docker ps -a获取容器id，然后打开进入容器

<img width="416" alt="image" src="https://github.com/user-attachments/assets/93ff000e-63f6-4785-80d3-c85e368e7e02">


##### 步骤二：搭建IDE环境

①预先下载安装包，下载安装
②默认安装路径，直接点击安装
③从主菜单的File->Open…菜单，或者点击工具栏的按钮，打开选择文件对话框，选择要打开的项目文件，即***.wmproject文件即可，点击【打开】按钮即可打开工程。如下图所示。

<img width="284" alt="image" src="https://github.com/user-attachments/assets/0e4c9285-9f73-4a62-b2ee-72e7d9fb43f8">


##### 步骤三：其他需要安装的软件

① 请确保安装以下环境：python, git, pytorch

##### 步骤四：下载训练数据

① 最新数据集在软件安装包中







## 动⼿实验： 简单语音识别系统开发

### 模块⼀：简介 

##### 1、WTMDK2101-X3介绍

​	WTMDK2101-X3是针对WTM2101 AI SOC设计的评估板，包含：
（1）WTM2101核心板，即我们的存算芯片。
（2）和I/O 板：WTM2101运行需要的电源、以及应用I/O接口等.

<img width="115" alt="image" src="https://github.com/user-attachments/assets/3093ebf9-97bd-4d89-88ca-5251d39ba137">


​                                                                                                            核心板示意图

<img width="438" alt="image" src="https://github.com/user-attachments/assets/73b4cbb4-d1cb-4a8c-8210-2c23060df1a5">


​                                                                                         WTMDK2101-X3 I/O 板示意图

##### 2, AISHELL-WakeUp-1数据集介绍

AISHELL-WakeUp-1数据集是中英文唤醒词语音数据库，命令词为“你好，米雅” “hi, mia”，语音数据库中唤醒词语音3936003条，1561.12小时，邀请254名发言人参与录制。录制过程在真实家居环境中，设置7个录音位，使用6个圆形16路PDM麦克风阵列录音板做远讲拾音(16kHz，16bit)、1个高保真麦克风做近讲拾音(44.1kHz，16bit)。此数据库可用于声纹识别、语音唤醒识别等研究使用。

本demo以该数据集为例，用不同网络结构展示模型训练及移植过程。













### 模块⼆：搭建算法训练工程，完成算法训练与量化

##### 1.模型训练工程搭建:  

本demo提供DNN和DNN_DEEP两种网络结构的示例，网络结构如下，本教程以DNN为例。

<img width="271" alt="image" src="https://github.com/user-attachments/assets/146cd4a7-6ea6-4bad-bd0a-48903a5e8fe0">


​                                                                                                                DNN

步骤一：配置python/config.py，参数释义见代码注释。
步骤二：运行python/train.py，模型训练完毕后，在models/net_type文件夹下生成bestModel.pth，此即我们的模型权重。
步骤三：运行python/onnx_converter.py，在models/net_type文件夹下生成bestModel.onnx。此步骤即完成原始模型到知存onnx格式模型的转换。

### 







### 模块三：算法模型转换

##### 1，Dcoker下Mapper转换流程

步骤一：拷贝至指定文件夹
我们将mapper/input 拷贝至witin/toolchain:v001.000.034的指定文件夹下（通常为/home，需与gen_mapper.py文件里描述一致）

<img width="416" alt="image" src="https://github.com/user-attachments/assets/11228a38-6d26-42c7-be11-2d984b498cf2">


步骤二：在workplace\witin_mapper下执行gen_mapper.py
docker start id
docker attach id
cd witin_mapper
python3 /home/mapper/input/gen_mapper.py

<img width="416" alt="image" src="https://github.com/user-attachments/assets/306d8038-def2-4fb7-93ba-3ea94a6306f5">



步骤三：在对应的output文件下获得输出

<img width="258" alt="image" src="https://github.com/user-attachments/assets/d9878464-c7b7-4f51-9c0d-e2f5106dcc07">




### 模块四：算法模型烧写

步骤一：系统连接：
进行模型烧录和开发时，我们需要将JTAG，核心板，NPU烧写板连接好，并打开开关，如系统连接示意图所示。

步骤二：

<img width="317" alt="image" src="https://github.com/user-attachments/assets/0865db7b-90a4-4e34-b0da-25a064425409">


​                                                                                                                系统连接示意图



步骤三：跳线帽连接：
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

<img width="387" alt="image" src="https://github.com/user-attachments/assets/92eac91c-9c3b-4d35-a010-63db60109ba1">


​                                                                                                  跳线帽连接示意图

步骤四：
使用project/ WitinProgramTool_WTM2101下的WitinProgramTool.exe进行模型权重烧写。烧写时的开发板接线请参考其他文档。

步骤五：烧写指令: 
.\WitinProgramTool.exe -m init
.\WitinProgramTool.exe -m program -i XXXX\map.csv -k 2
其中XXXX为步骤2.（3）中生成的mapper/output/map
示例:

<img width="378" alt="image" src="https://github.com/user-attachments/assets/0d693e08-5723-46eb-aa8b-f6ed5f582b1e">








### 模块五：算法模型在芯片运行推理

步骤一：
从官网下载知存IDE Witmem Studio。
步骤二：
生成的mapper/output/register.c放在project/Model，使用Witmem Studio打开project/Project/SES-RISCV/Demo.wmproject。

<img width="149" alt="image" src="https://github.com/user-attachments/assets/14ee2290-0b35-4db4-bd75-b3dac2097420">

步骤三：Target->Download下载工程：

<img width="248" alt="image" src="https://github.com/user-attachments/assets/6908d7e7-a1f9-4671-a4cc-37c1b5cc3e8d">


注：本demo所用为x3开发板，所用串口GPIO为16,17。若是其他开发板，请根据情况修改串口。

步骤四：
打开tools中的串口工具，设置波特率115200，查看准确率输出


​		<img width="300" alt="image" src="https://github.com/user-attachments/assets/556e7b06-f641-4a77-a6e8-fed0c539d448">


###                至此，我们完成了语音识别从训练到部署的全流程，本教程结束。
