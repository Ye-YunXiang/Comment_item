#include "device_function_simulator.h"
#include "getch.h"

// Device parameters (to be stored in Flash/EEPROM)     设备参数存储在Flash
uint16_t TokenCount = 1; 
bool PAYGEnabled = true;                    // 使能PAYGO
uint32_t ActiveUntil = 0;                   // 充值码到期时间（目前都是按天来计算的,但是存储 时间为秒。）
uint32_t TokenEntryLockedUntil = 0;         // 在Token输入上锁以前
// WARNING: THIS SECRET KEY AND STARTING CODE IS ONLY HERE AS AN EXAMPLE AND SHOULD NEVER BE USED IN PRODUCTION
// 警告：这个密钥和启动代码只是一个示例，不应该在生产环境中使用。
 uint32_t StartingCode = 123456789;                                                                                          // 启动代码
//char SECRET_KEY[16] = {0xa2, 0x9a, 0xb8, 0x2e, 0xdc, 0x5f, 0xbb, 0xc4, 0x1e, 0xc9, 0x53, 0xf, 0x6d, 0xac, 0x86, 0xb1};       // 密钥
char SECRET_KEY[16] = {...};


// This is just for displaying the activation status in the simulater WaitForTokenEntry function 
// 这只是为了在模拟器WaitForTokenEntry函数中显示激活状态
extern bool IsActive(void);

void BlinkRedLED(int NumberOfBlinks) {              // 红灯闪烁 NumberOfBlinks 次
    printf("\nRed LED Blinked %d times!\n", NumberOfBlinks);    
}

void BlinkGreenLED(int NumberOfBlinks) {            // 绿灯闪烁 NumberOfBlinks 次
    printf("\nGreen LED Blinked %d times!\n", NumberOfBlinks);
}

int GetKeyPressed() {                   //得到密钥
    char this_char = getch();
    switch (this_char) {
        case '*':
            return STAR_KEY;       // 返回 -1 ，启动密钥
            break;
            
        case '#':
            return HASH_KEY;       // 返回 -2 结束输入密钥
            break;
            
        default:
            return (int) (this_char - '0'); // this_char is now an int  返回int类型。
            break;
    }
}

// 加载激活变量, 就是 get
void LoadActivationVariables() {        
    // We load TokenCount   加载ToknCount
    // We load PAYGEnabled  加载PAYGEnabled
    // We load ActiveUntil  加载ActiveUntil
    // We load TokenEntryLockedUntil    加载TokenEntryLockedUntil
}


//存储激活变量，就是 set
void StoreActivationVariables() {
    // We store TokenCount
    // We store PAYGEnabled
    // We store ActiveUntil
    // We store TokenEntryLockedUntil
}

//获取时间
uint32_t GetTimeInSeconds() {
    return (uint32_t) time(NULL);
}
