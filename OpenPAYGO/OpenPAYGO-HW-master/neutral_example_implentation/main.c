#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "device_parameters.h"      // 设备参数
#include "device_simulator/device_function_simulator.h"  // 设备功能模拟器
#include "device_payg_logic.h"  // 设备支付逻辑
#include "opaygo_decoder/opaygo_decoder.h"  // 支付编码器

//等待输入信号
uint64_t WaitForTokenEntry() {
    uint64_t TempToken = 0;
    bool NoToken = true;       
    int LastKey;    // 最后的密钥
    
    // 只要没有密钥就不断的循环
    while(NoToken) {
        LastKey = GetKeyPressed();

       
        if(LastKey == STAR_KEY) {    //如果检测到了 * 的输入，红灯就闪烁
            if(TokenEntryAllowed()) {      
                NoToken = false;
            } else {
                BlinkRedLED(1);
                printf("\nToken entry locked for %d seconds", TokenEntryLockedUntil-GetTimeInSeconds());
            }
        } else if(LastKey == HASH_KEY) {
            if(IsActive()) {
                BlinkGreenLED(1);
                printf("\nTime Left: %d seconds", ActiveUntil-GetTimeInSeconds());
            } else {
                BlinkRedLED(1);
            }
        }
    }
    for(int i=0; i<TOKEN_LENGTH; i++) {
        // We add the last key pressed to the token (as integer) if needed
        TempToken += GetKeyPressed()*pow(10, (TOKEN_LENGTH-1)-i);               //得到输入的密钥
    }
    return TempToken;
}


// Main PAYG loop   主PAYG循环
int main(int argc, const char * argv[]) {
    printf("Welcome to the OPAYGO Device Simulator\n");     // 欢迎来到OPAYFGO设备模拟器。
    // 在等待 * 字符开始记录按键。 （按下该按键后需按ENTE键，模拟器才能工作）IN （按 # 键查看设备激活状态）。
    printf("We're waiting for the * character to start recording the key presses. \n(You need to press ENTER after the key presses for the simulator to work)\n(Press the '#' key to see the device activation status)\n\n");
    
    LoadActivationVariables(); // We load the activation variables  加载激活变量。
    
    uint64_t InputToken;        // 初始化存储输入密钥的变量
    while(1) {
        // We wait for a token to be entered    等待输入 token。
        InputToken = WaitForTokenEntry();
        printf("\n(Token entered: %llu)", InputToken);          // 显示令牌输入。
        
        // We get the activation value from the token       令牌中获取激活码。
        int TokenValue = GetActivationValueFromToken(InputToken, &TokenCount, StartingCode, SECRET_KEY);        // 计算令牌激活码。 参数：输入的密钥、密钥计数、启动代码、密钥
        printf("\n(Activation Value from Token: %d)", TokenValue); // Activation Value found in the token       // 显示令牌激活码。
        printf("\n(Count: %d)\n", TokenCount); // Count found in the token                                      // 显示在token中找到的计数。
        
        // We update the PAYG mode (ON or OFF) and the PAYG timer based on the activation value     //根据激活值更新PAYG模式（ON或OFF）和PAYG计时器。
        UpdateDeviceStatusFromTokenValue(TokenValue, TokenCount);       //更新设备状态，数值来源于上面的ToKen计算结果。
    }
    
    return 0;
}

