#include "device_payg_logic.h"

int InvalidTokenCount = 0;

void UpdateDeviceStatusFromTokenValue(int TokenValue, int ActivationCount) {
    if(TokenValue == -1) {
        InvalidTokenCount++;
        UpdateInvalidTokenWaitingPeriod();
    } else {
        InvalidTokenCount = 0;
        if(TokenValue == COUNTER_SYNC_VALUE) {          // 计数同步值？！，不应该是TokenCount来吗。
            BlinkGreenLED(3); // We blink green twice to show that the token is good        绿灯闪烁两次，代表Token有效
        } else if(TokenValue == PAYG_DISABLE_VALUE) {           //关闭PAYGO输入吗？？
            PAYGEnabled = false;        //关闭
            BlinkGreenLED(5); // We blink green twice to show that the device is active forever    绿灯闪烁两次，代表设备永远处于激活状态
        } else {
            PAYGEnabled = true;             
            if(ActivationCount % 2) {           //判断TokenCount的奇偶
                SetTime(TokenValue);          //TokenCout为奇数，就更新时间
            } else {
                AddTime(TokenValue);          //为偶数，就在原本的时间上累加上去
            }
            BlinkGreenLED(2); // We blink green twice to show that the token is good      绿灯闪烁两次，代表令牌是好的
        }
        StoreActivationVariables(); // We store in every case   存储每一种情况
    }
}

void UpdateInvalidTokenWaitingPeriod() {
    uint32_t Now = GetTimeInSeconds();
    
    // We check that it does not become unbearably long
    if(InvalidTokenCount > 9) {
        InvalidTokenCount = 9;
    }
    
    
    TokenEntryLockedUntil = Now + pow(2, InvalidTokenCount)*60;
}

//允许输入密钥
bool TokenEntryAllowed() {
    if(TokenEntryLockedUntil > GetTimeInSeconds()) {
        return false;
    } else {
        return true;
    }
}


//添加天数
void AddTime(int ActivationValue) {
    uint32_t Now = GetTimeInSeconds();          //老惯例，先获取国际时间
    int NumberOfSecondsToActivate = (ActivationValue*3600*24) / TIME_DIVIDER;           //计算出多一共少秒
    
    if(ActiveUntil < Now) {        // 如果可用时间已经扣到负数了，就直接等于当前时间。
        ActiveUntil = Now;
    }
    

    /**
     * 把解码的时间添加上去，和原来的时间相加。
     */
    ActiveUntil += NumberOfSecondsToActivate; // We add the number of days (converted in seconds for to compare to our RTC time)
    //添加天数（与RTC时间进行比较）
}


//重新存储时间
void SetTime(int ActivationValue) {
    uint32_t Now = GetTimeInSeconds();          //得到当前时间吗？？？
    int NumberOfSecondsToActivate = (ActivationValue*3600*24) / TIME_DIVIDER;          //密钥的激活时间*一天多少秒，除于除法器，就是自己换算为算小时什么的。
    

    /*
    * 突然开智，上面获取的国际时间，就是为了和下面得到的秒相加，然后复制给支付系统的时间存储。
    * 然后每天获取一次时间为多少秒，在从里面剪掉
    */
    ActiveUntil = Now + NumberOfSecondsToActivate; // We set the number of days (converted in seconds for to compare to our RTC time)
    //设置天数（与RTC时间进行比较）
}

bool IsActive() {
    if(PAYGEnabled) {
        if(ActiveUntil > GetTimeInSeconds()) {
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}
