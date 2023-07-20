#include "device_payg_logic.h"

int InvalidTokenCount = 0;

void UpdateDeviceStatusFromTokenValue(int TokenValue, int ActivationCount) {
    if(TokenValue == -1) {
        InvalidTokenCount++;
        UpdateInvalidTokenWaitingPeriod();
    } else {
        InvalidTokenCount = 0;
        if(TokenValue == COUNTER_SYNC_VALUE) {          // ����ͬ��ֵ��������Ӧ����TokenCount����
            BlinkGreenLED(3); // We blink green twice to show that the token is good        �̵���˸���Σ�����Token��Ч
        } else if(TokenValue == PAYG_DISABLE_VALUE) {           //�ر�PAYGO�����𣿣�
            PAYGEnabled = false;        //�ر�
            BlinkGreenLED(5); // We blink green twice to show that the device is active forever    �̵���˸���Σ������豸��Զ���ڼ���״̬
        } else {
            PAYGEnabled = true;             
            if(ActivationCount % 2) {           //�ж�TokenCount����ż
                SetTime(TokenValue);          //TokenCoutΪ�������͸���ʱ��
            } else {
                AddTime(TokenValue);          //Ϊż��������ԭ����ʱ�����ۼ���ȥ
            }
            BlinkGreenLED(2); // We blink green twice to show that the token is good      �̵���˸���Σ����������Ǻõ�
        }
        StoreActivationVariables(); // We store in every case   �洢ÿһ�����
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

//����������Կ
bool TokenEntryAllowed() {
    if(TokenEntryLockedUntil > GetTimeInSeconds()) {
        return false;
    } else {
        return true;
    }
}


//�������
void AddTime(int ActivationValue) {
    uint32_t Now = GetTimeInSeconds();          //�Ϲ������Ȼ�ȡ����ʱ��
    int NumberOfSecondsToActivate = (ActivationValue*3600*24) / TIME_DIVIDER;           //�������һ������
    
    if(ActiveUntil < Now) {        // �������ʱ���Ѿ��۵������ˣ���ֱ�ӵ��ڵ�ǰʱ�䡣
        ActiveUntil = Now;
    }
    

    /**
     * �ѽ����ʱ�������ȥ����ԭ����ʱ����ӡ�
     */
    ActiveUntil += NumberOfSecondsToActivate; // We add the number of days (converted in seconds for to compare to our RTC time)
    //�����������RTCʱ����бȽϣ�
}


//���´洢ʱ��
void SetTime(int ActivationValue) {
    uint32_t Now = GetTimeInSeconds();          //�õ���ǰʱ���𣿣���
    int NumberOfSecondsToActivate = (ActivationValue*3600*24) / TIME_DIVIDER;          //��Կ�ļ���ʱ��*һ������룬���ڳ������������Լ�����Ϊ��Сʱʲô�ġ�
    

    /*
    * ͻȻ���ǣ������ȡ�Ĺ���ʱ�䣬����Ϊ�˺�����õ�������ӣ�Ȼ���Ƹ�֧��ϵͳ��ʱ��洢��
    * Ȼ��ÿ���ȡһ��ʱ��Ϊ�����룬�ڴ��������
    */
    ActiveUntil = Now + NumberOfSecondsToActivate; // We set the number of days (converted in seconds for to compare to our RTC time)
    //������������RTCʱ����бȽϣ�
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
