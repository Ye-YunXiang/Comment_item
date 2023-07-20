# 通用例程解析

> 本文档为通用的例程介绍，用于嵌入单片机。

## 文档结构介绍

本目录下包含了一堆文件，名字都看不懂。。。

不怕！现在就对每个文档名字进行翻译！（英语太垃圾了，背背背！）

- **device_simulator**  *设备模拟器*
  - device_function_simulator.c  *设备功能模拟*          这里就存储了设备等待各种信息
  - device_function_simulator.h
  - getch.c  *获取字符函数*
  - getch.h
- **opaygo_decoder**  *OpenPAYGO解码器*
  - **extended**  *扩展*
    - opaygo_core_extended.c  *核心扩展*
    - opaygo_core_extended.h
    - opaygo_decoder_extended.c  *解码器扩展*
    - opaygo_decoder_extended.h
  - opaygo_core.c  *核心*
  - opaygo_core.h
  - opaygo_decoder.c  *解码器*
  - opaygo_decoder.h
  - opaygo_value_utils.c  *重要功能*
  - opaygo_value_utils.h
  - restricted_digit_set_mode.c  *有限的数字写入模块*
  - restricted_digit_set_mode.h
  - siphash.c
  - siphash.h
- **文件**
  - device_parameters.h  *设备参数*
  - device_payg_logic.c  *设备支付逻辑*
  - device_payg_logic.h
  - main.c
  
## 文件深介绍

