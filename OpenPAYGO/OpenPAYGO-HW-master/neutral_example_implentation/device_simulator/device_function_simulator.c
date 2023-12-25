#include "device_function_simulator.h"
#include "getch.h"

// Device parameters (to be stored in Flash/EEPROM)     �豸�����洢��Flash
uint16_t TokenCount = 1; 
bool PAYGEnabled = true;                    // ʹ��PAYGO
uint32_t ActiveUntil = 0;                   // ��ֵ�뵽��ʱ�䣨Ŀǰ���ǰ����������,���Ǵ洢 ʱ��Ϊ�롣��
uint32_t TokenEntryLockedUntil = 0;         // ��Token����������ǰ
// WARNING: THIS SECRET KEY AND STARTING CODE IS ONLY HERE AS AN EXAMPLE AND SHOULD NEVER BE USED IN PRODUCTION
// ���棺�����Կ����������ֻ��һ��ʾ������Ӧ��������������ʹ�á�
 uint32_t StartingCode = 123456789;                                                                                          // ��������
//char SECRET_KEY[16] = {0xa2, 0x9a, 0xb8, 0x2e, 0xdc, 0x5f, 0xbb, 0xc4, 0x1e, 0xc9, 0x53, 0xf, 0x6d, 0xac, 0x86, 0xb1};       // ��Կ
char SECRET_KEY[16] = {...};


// This is just for displaying the activation status in the simulater WaitForTokenEntry function 
// ��ֻ��Ϊ����ģ����WaitForTokenEntry��������ʾ����״̬
extern bool IsActive(void);

void BlinkRedLED(int NumberOfBlinks) {              // �����˸ NumberOfBlinks ��
    printf("\nRed LED Blinked %d times!\n", NumberOfBlinks);    
}

void BlinkGreenLED(int NumberOfBlinks) {            // �̵���˸ NumberOfBlinks ��
    printf("\nGreen LED Blinked %d times!\n", NumberOfBlinks);
}

int GetKeyPressed() {                   //�õ���Կ
    char this_char = getch();
    switch (this_char) {
        case '*':
            return STAR_KEY;       // ���� -1 ��������Կ
            break;
            
        case '#':
            return HASH_KEY;       // ���� -2 ����������Կ
            break;
            
        default:
            return (int) (this_char - '0'); // this_char is now an int  ����int���͡�
            break;
    }
}

// ���ؼ������, ���� get
void LoadActivationVariables() {        
    // We load TokenCount   ����ToknCount
    // We load PAYGEnabled  ����PAYGEnabled
    // We load ActiveUntil  ����ActiveUntil
    // We load TokenEntryLockedUntil    ����TokenEntryLockedUntil
}


//�洢������������� set
void StoreActivationVariables() {
    // We store TokenCount
    // We store PAYGEnabled
    // We store ActiveUntil
    // We store TokenEntryLockedUntil
}

//��ȡʱ��
uint32_t GetTimeInSeconds() {
    return (uint32_t) time(NULL);
}
