#include "opaygo_decoder.h"

// 得到Token计算激活码
int GetActivationValueFromToken(uint64_t InputToken, uint16_t *LastCount, uint32_t StartingCode, unsigned char SECRET_KEY[16]) {

#ifdef RESTRICTED_DIGIT_SET_MODE        //受限位数设置模式
    InputToken = ConvertFromFourDigitToken(InputToken);
#endif

    // 开机密码基准 = 得到Token基准 （开机密码）
    uint16_t StartingCodeBase = GetTokenBase(StartingCode);

    // Token基准 = 得到Token基准（输入的Token）
    uint16_t TokenBase = GetTokenBase((uint32_t)InputToken);

    // 当前的Token = 放入基准Token（开机代码，Token基准）
    uint32_t CurrentToken = PutBaseInToken(StartingCode, TokenBase);

    uint32_t MaskedToken;   // 加密密钥初始化
    int MaxCountTry;        // 最大计数
    int MinCountTry;        // 最小计数

    // 计算结果 = 译码基准（启动密码基准， Token基准。）
    int Value = DecodeBase(StartingCodeBase, TokenBase);

    if(Value == COUNTER_SYNC_VALUE) {   // 同步计算结果
        MaxCountTry = *LastCount + MAX_TOKEN_JUMP_COUNTER_SYNC;
        MinCountTry = *LastCount - MAX_TOKEN_JUMP;
    } else {
        MaxCountTry = *LastCount + MAX_TOKEN_JUMP;
        MinCountTry = *LastCount;
    }

    for (int Count=0; Count <= MaxCountTry; Count++) {
        MaskedToken = PutBaseInToken(CurrentToken, TokenBase);
        if(MaskedToken == InputToken && Count > MinCountTry) {
            *LastCount = Count;
            return Value;
        }
        CurrentToken = GenerateOPAYGOToken(CurrentToken, SECRET_KEY);       // 产生OpenPAYGO的密钥
    }

    return -1;
}
