#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "device_parameters.h"      // �豸����
#include "device_simulator/device_function_simulator.h"  // �豸����ģ����
#include "device_payg_logic.h"  // �豸֧���߼�
#include "opaygo_decoder/opaygo_decoder.h"  // ֧��������

//�ȴ������ź�
uint64_t WaitForTokenEntry() {
    uint64_t TempToken = 0;
    bool NoToken = true;       
    int LastKey;    // ������Կ
    
    // ֻҪû����Կ�Ͳ��ϵ�ѭ��
    while(NoToken) {
        LastKey = GetKeyPressed();

       
        if(LastKey == STAR_KEY) {    //�����⵽�� * �����룬��ƾ���˸
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
        TempToken += GetKeyPressed()*pow(10, (TOKEN_LENGTH-1)-i);               //�õ��������Կ
    }
    return TempToken;
}


// Main PAYG loop   ��PAYGѭ��
int main(int argc, const char * argv[]) {
    printf("Welcome to the OPAYGO Device Simulator\n");     // ��ӭ����OPAYFGO�豸ģ������
    // �ڵȴ� * �ַ���ʼ��¼������ �����¸ð������谴ENTE����ģ�������ܹ�����IN ���� # ���鿴�豸����״̬����
    printf("We're waiting for the * character to start recording the key presses. \n(You need to press ENTER after the key presses for the simulator to work)\n(Press the '#' key to see the device activation status)\n\n");
    
    LoadActivationVariables(); // We load the activation variables  ���ؼ��������
    
    uint64_t InputToken;        // ��ʼ���洢������Կ�ı���
    while(1) {
        // We wait for a token to be entered    �ȴ����� token��
        InputToken = WaitForTokenEntry();
        printf("\n(Token entered: %llu)", InputToken);          // ��ʾ�������롣
        
        // We get the activation value from the token       �����л�ȡ�����롣
        int TokenValue = GetActivationValueFromToken(InputToken, &TokenCount, StartingCode, SECRET_KEY);        // �������Ƽ����롣 �������������Կ����Կ�������������롢��Կ
        printf("\n(Activation Value from Token: %d)", TokenValue); // Activation Value found in the token       // ��ʾ���Ƽ����롣
        printf("\n(Count: %d)\n", TokenCount); // Count found in the token                                      // ��ʾ��token���ҵ��ļ�����
        
        // We update the PAYG mode (ON or OFF) and the PAYG timer based on the activation value     //���ݼ���ֵ����PAYGģʽ��ON��OFF����PAYG��ʱ����
        UpdateDeviceStatusFromTokenValue(TokenValue, TokenCount);       //�����豸״̬����ֵ��Դ�������ToKen��������
    }
    
    return 0;
}

