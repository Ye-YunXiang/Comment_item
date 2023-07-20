#include "opaygo_decoder.h"

// �õ�Token���㼤����
int GetActivationValueFromToken(uint64_t InputToken, uint16_t *LastCount, uint32_t StartingCode, unsigned char SECRET_KEY[16]) {

#ifdef RESTRICTED_DIGIT_SET_MODE        //����λ������ģʽ
    InputToken = ConvertFromFourDigitToken(InputToken);
#endif

    // ���������׼ = �õ�Token��׼ ���������룩
    uint16_t StartingCodeBase = GetTokenBase(StartingCode);

    // Token��׼ = �õ�Token��׼�������Token��
    uint16_t TokenBase = GetTokenBase((uint32_t)InputToken);

    // ��ǰ��Token = �����׼Token���������룬Token��׼��
    uint32_t CurrentToken = PutBaseInToken(StartingCode, TokenBase);

    uint32_t MaskedToken;   // ������Կ��ʼ��
    int MaxCountTry;        // ������
    int MinCountTry;        // ��С����

    // ������ = �����׼�����������׼�� Token��׼����
    int Value = DecodeBase(StartingCodeBase, TokenBase);

    if(Value == COUNTER_SYNC_VALUE) {   // ͬ��������
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
        CurrentToken = GenerateOPAYGOToken(CurrentToken, SECRET_KEY);       // ����OpenPAYGO����Կ
    }

    return -1;
}
