# Witmem Program Tool for WTM2101 V1.4.0.0

文件 | 描述
:--|:--
WitinProgramTool.exe|               供外部客户使用
WitinProgramTool_DEBUG.exe|         仅限内部使用（DEBUG版本）
LibOTA|                             OTA Library
LibNPU|                             NPU Library
JLink_x64.dll  |                    JLink DLL，由WitinProgramTool.exe调用
infer_DEBUG.py |                    查看烧写结果工具（仅限内部使用）
UserGuide.docx |                    公司内部用户使用说明
map_demo_1003_inx2_v3 |             示例网络

---
## 更新主要内容：
### WitinProgramTool（V1.4.0.0, Build 2023.08.09）:
1. 基于SDKv1.1.0.0开发
2. 底层优化，提高烧写速度和推理速度
3. LibNPU移除NPU_INFER_CONFIG()接口以避免混淆，仅使用NPU_INFER_CONFIG_6N_MHz(int N)。注意：NPU为24MHz时应为NPU_INFER_CONFIG_6N_MHz(4)
4. 使用建议：infer配置调整以提高推理速度，与V1.3.x.x可能存在兼容性问题，但烧写和推理速度均有优化，建议新项目以及使用新SDK开发的项目使用

## 更新主要内容：
### WitinProgramTool（V1.3.2.1, Build 2023.08.09）:
1. 修复个别芯片program结束出现“ERROR: DATA LOST!”的问题。
2. 更新LibNPU.h，修复个别芯片在pd_stage()后功耗异常问题。
3. 使用建议：与原V1.3.2.0兼容，建议基于V1.3.2.0项目（尤其是涉及OTA升级时）迁移至V1.3.2.1

## 更新主要内容：
### WitinProgramTool（V1.3.2.0, Build 2023.06.25）:
1. 提高可靠性，避免小概率芯片损坏
2. 更新LibOTA，增加wtmnpu_check_ota()接口查看OTA网络精度
3. LibNPU增加TRIM_DVDD_1p1v()和TRIM_DVDD_0p9v()接口
4. 使用建议：与原V1.3.1.0兼容，为避免芯片损坏，强烈建议基于V1.3.1.0项目（尤其是涉及OTA升级时）迁移至V1.3.2.0

## 更新主要内容：
### WitinProgramTool（V1.3.1.0, Build 2023.01.17）:
1. 取消WitinProgramTool_IEN.exe, 外部客户统一使用WitinProgramTool.exe
2. 更新LibNPU，模拟配置支持NPU频率以6MHz的整数倍调整[void NPU_INFER_CONFIG_6N_MHz(int N)]
3. 更新LibOTA，基于OTA工具 SPI/UART OTA: http://192.168.4.230:3000/WTM2101_tools/npu_network_ota_by_transfer_protocol
jlink OTA: http://192.168.4.230:3000/WTM2101_tools/WitmemOTATool_Jlink
4. 底层少量改动以优化可靠性
5. 支持json格式map文件


## 更新主要内容：
### WitinProgramTool（V1.3.0.0, Build 2022.12.07）:
1. 更新模拟配置，不再支持原1080,1090配置(移除-c参数)，消除AVDD电压变化影响
2. 提供LibNPU，供Demo工程使用，以调用NPU相关模拟配置
3. 更新LibOTA，优化使用逻辑，提供示例工程展示API使用
4. 支持多site并行，通过--spi,--jlink指定烧录器及jlink编号
5. 支持记录bootloader及map名称并读取(各8个字符，参见示例网络)

---
## 更新主要内容：
### WitinProgramTool（V1.2.0.0, Build 2022.09.08）:
1. ***重要：后续芯片（C版）务必使用v1.2.0.0及以后版本！强烈建议尽快将所有烧写迁移至本版本！***
2. 不再区分X2与X3版本Demo板(移除-x参数)，例如:原X2 Demo板在init时使用"-m init -x 2"，本次版本删除"-x 2" init 直接执行 -m init    
3. 更换工具版本不再自动执行init，需要手动执行-m init 或者-m init -c 1090
4. 去除ISEN连接,init时，去除force_init命令，使用init命令
5. 初次使用本版本时，需要执行-m init 或者-m init -c 1090
6. 其他版本内容：
1. 采用V1.0.9版本配置，具体使用方法：在init时使用"-c 1090"，demo工程中模拟配置添加：WRITE32(0x40002068, 0xac); WRITE16_NPU(0x0264, 0x8030);
2. 提供OTA Library, 支持--dframe xxx调整ota数据量及时间（目前推荐30）
3. 支持逐层调整infer平均次数（map目录中增加average.txt，每行一个数字[1,2,4],代表本层平均次数,default=2）

---
## 版本更新记录：
版本 | 日期 | 主要更新 | 示例网络单次烧录时间参考值(不含init)
:--|:--|:--|:--
1.4.0.0| 2023.08.09| SDKv1.1.0.0，速度优化| ~95s
1.3.2.1| 2023.08.09| bug修复| ~110s
1.3.2.0| 2023.06.25| 可靠性优化| ~110s
1.3.1.0| 2023.01.17| LibNPU支持NPU频率调整| ~100s
1.3.0.0| 2022.12.07| 更新模拟配置，使用trim| ~100s
1.2.0.0| 2022.09.08| 支持C版芯片| ~100s




