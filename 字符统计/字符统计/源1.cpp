#include<iostream>
using namespace std;
struct Chinese
{
    char                 chr1Chinese[2]; //����ռ2���ֽڵĿռ䣬��Ϊ��֪����ռ2���ֽڣ����Բ���Ҫ����һ���ֽڱ��������
    int                  intApearTimes;  //�����ֳ��ֵĴ���
    struct Chinese* next;           //ָ����һ���ڵ�
};
class ChineseCache //�����ַ�����
{
private:
    Chinese* stcCacheHead;  //�����׵�ַ
    Chinese* stcCacheCur;   //���浱ǰ�Ĳ���λ�ã�һ��ָ��β����ÿ������һ���ڵ㣬��Ҳ�����ƶ�һ����λ

    void AddCache(const char* chr1Chinese);

public:
    ChineseCache();
    ~ChineseCache();

    void AddApearTimes(const char* chr1Chinese);
    void ShowAllCache();
};
ChineseCache::ChineseCache()
{
    stcCacheHead = NULL;
}
ChineseCache::~ChineseCache()
{
    //�ͷŻ���
    if (stcCacheHead)
    {
        Chinese* ChineseTemp;
        while (stcCacheHead)
        {
            ChineseTemp = stcCacheHead;
            stcCacheHead = stcCacheHead->next;
            delete ChineseTemp;
        }
    }
}
void ChineseCache::AddCache(const char* chr1Chinese) //����һ�����ֵĻ���ռ䡣chr1Chinese:һ�������ַ�����һ������
{
    int loop;
    if (stcCacheHead)
    {/*
      Chinese* ChineseNew;
      ChineseNew = new Chinese;
      stcCacheCur->next = ChineseNew;      //����һ���ڵ����½ڵ���������
      stcCacheCur = ChineseNew;            //����¼��ǰ����λ�õı�ǣ������½ڵ��λ��
      */
      //�������ú��������һ��������ѭ��ʱЧ�ʱ���������Ը�
        stcCacheCur->next = new Chinese;
        stcCacheCur = stcCacheCur->next;
        stcCacheCur->intApearTimes = 0;
    }
    else //����ǵ�һ�����ӻ���
    {
        stcCacheCur = stcCacheHead = new Chinese;
        stcCacheCur->intApearTimes = 0;     //�����ֳ��ֵĴ�����ʼ��Ϊ0���Ա���������ۼ�����
    }
    //�������ṩ�ĺ��ֻ�������������ַ�����chr1Test[2]���������Ϊ���С�
    //��ô�ڼ�����ڲ���2��Ԫ�ص�ֵ�ֱ�Ϊ��chr1Test[0] == -42��chr1Test[1] == -48
    for (loop = 0; loop < 2; loop++)
        stcCacheCur->chr1Chinese[loop] = chr1Chinese[loop];
    stcCacheCur->next = NULL;
}
void ChineseCache::AddApearTimes(const char* chr1Chinese)
{
    bool bMatch = false; //�Ƿ����β���ƥ�䣬�ڻ������Ƿ��ҵ��ú���*chr1Chinese��
    if (stcCacheHead)
    {
        Chinese* chn;
        //�ҳ��������������ͬ�ĺ��֣�����ҵ���¶�������1
        for (chn = stcCacheHead; chn; chn = chn->next)
        {
            //��Ϊchn��Աchr1Chineseû�н��������ʶ�����ʹ��strcmp����
            //���Ҵ˴�����򵥣�������Ҫ���ÿ⺯�������Ӹ���
            if (chn->chr1Chinese[0] == chr1Chinese[0] && chn->chr1Chinese[1] == chr1Chinese[1])
            {
                chn->intApearTimes++;
                bMatch = true; //�ҵ�Ŀ�꣬���Ϊ��
                break;
            }
        }
        //���û��ƥ�䵽Ҫ��ѯ�ĺ��֣��򽫸ú������ӵ�������
    }
    if (bMatch == false)
    {
        AddCache(chr1Chinese);
        stcCacheCur->intApearTimes++;
    }
}
void ChineseCache::ShowAllCache()
{
    if (stcCacheHead)
    {
        Chinese* ChnTemp;
        char chn[3] = "";
        for (ChnTemp = stcCacheHead; ChnTemp; ChnTemp = ChnTemp->next)
        {
            //��ΪChnTemp->chr1Chineseû�н����������Բ���ʹ��cout���
            //��Ҫ������2���ֽ����ϵ��ַ����������
            chn[0] = ChnTemp->chr1Chinese[0], chn[1] = ChnTemp->chr1Chinese[1];
            cout << chn << "  " << "����: " << ChnTemp->intApearTimes << endl;
        }
    }
}
class EnglishCache //Ӣ����ĸ����
{
    //������֪Ӣ����ĸֻ��26�������Կ���˳���ṹ�洢֮������������
private:
    //ĳ����ĸ���ֵĴ�����0��25��ʾA��Z�������ִ�Сд
    //���int1ApearTimes[2]��ֵ����4�����ʾ��ĸC������4��
    int          int1ApearTimes[26];

public:
    EnglishCache();
    void AddApearTimes(char letter);
    void ShowAllCache();
};
EnglishCache::EnglishCache()
{
    int loop;
    for (loop = 0; loop < 26; loop++)
        int1ApearTimes[loop] = 0;
}
void EnglishCache::AddApearTimes(char letter)
{
    int loop;
    for (loop = 0; loop < 26; loop++)
        //�����ִ�Сд
        if (65 + loop == letter || 97 + loop == letter)
        {
            int1ApearTimes[loop] ++;
            break;
        }
}
void EnglishCache::ShowAllCache()
{
    int loop;
    char ch;
    for (loop = 0; loop < 26; loop++)
    {
        if (int1ApearTimes[loop])
        {
            ch = 65 + loop;
            cout << ch << "  " << "����: " << int1ApearTimes[loop] << endl;
        }
    }
}
void StatisticsCharacter(const char* str)
{
    int intChnCount = 0, intEngCount = 0;//���ġ�Ӣ���ַ����ֵ��ܴ���
    ChineseCache ChnCache;
    EnglishCache EngCache;
    while (*str)
    {
        //�������дif (*str >= 65 && *str <= 90 || *str >= 97 && *str <= 122) //�ж��Ƿ�Ϊ��ĸ������Ϊ����
        //�����Ա����š�����ַ������б����ţ���ô���ѱ�e799bee5baa6e78988e69d8331333337616466����ſ������ġ�����û�в��ô��㷨��
        if (*str < 0) //����Ǻ��֣������ڼ������ʵ��ֵΪ����
        {
            ChnCache.AddApearTimes(str);
            intChnCount++;
            str += 2; //����ռ2���ֽڣ�����һ��Ҫ��2���ֽ�
        }
        else //�����Ӣ����ĸ
        {
            EngCache.AddApearTimes(*str);
            intEngCount++;
            str++;
        }
    }
    EngCache.ShowAllCache();
    ChnCache.ShowAllCache();
    cout << "english ��Ӣ���ַ���: " << intEngCount << endl;
    cout << "chinese �������ַ���: " << intChnCount << endl;
}
int main()
{
    char string[1000];
    cout << "1.Ӣ����ĸ�����ִ�Сд��2.�벻Ҫ����ո񣬷���ո��������ַ���������" << endl << endl;
    cout << "�������ַ���" << endl;
    cin >> string;
    ::StatisticsCharacter(string);
}