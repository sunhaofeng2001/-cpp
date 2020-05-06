#include<iostream>
using namespace std;
struct Chinese
{
    char                 chr1Chinese[2]; //文字占2个字节的空间，因为已知汉字占2个字节，所以不需要增加一个字节保存结束符
    int                  intApearTimes;  //该文字出现的次数
    struct Chinese* next;           //指向下一个节点
};
class ChineseCache //中文字符缓存
{
private:
    Chinese* stcCacheHead;  //缓存首地址
    Chinese* stcCacheCur;   //缓存当前的操作位置，一般指向尾部，每次增加一个节点，它也随着移动一个单位

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
    //释放缓存
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
void ChineseCache::AddCache(const char* chr1Chinese) //增加一个汉字的缓存空间。chr1Chinese:一个中文字符，即一个汉字
{
    int loop;
    if (stcCacheHead)
    {/*
      Chinese* ChineseNew;
      ChineseNew = new Chinese;
      stcCacheCur->next = ChineseNew;      //将上一个节点与新节点连接起来
      stcCacheCur = ChineseNew;            //将记录当前操作位置的标记，移至新节点的位置
      */
      //以下作用和上面代码一样，但在循环时效率比上面代码稍高
        stcCacheCur->next = new Chinese;
        stcCacheCur = stcCacheCur->next;
        stcCacheCur->intApearTimes = 0;
    }
    else //如果是第一次增加缓存
    {
        stcCacheCur = stcCacheHead = new Chinese;
        stcCacheCur->intApearTimes = 0;     //该文字出现的次数初始化为0，以便后续进行累加运算
    }
    //将参数提供的汉字缓存起来，如果字符数组chr1Test[2]保存的数据为“中”
    //那么在计算机内部它2个元素的值分别为：chr1Test[0] == -42，chr1Test[1] == -48
    for (loop = 0; loop < 2; loop++)
        stcCacheCur->chr1Chinese[loop] = chr1Chinese[loop];
    stcCacheCur->next = NULL;
}
void ChineseCache::AddApearTimes(const char* chr1Chinese)
{
    bool bMatch = false; //是否与形参相匹配，在缓存中是否找到该汉字*chr1Chinese。
    if (stcCacheHead)
    {
        Chinese* chn;
        //找出缓存中与参数相同的汉字，如果找到则将露面次数加1
        for (chn = stcCacheHead; chn; chn = chn->next)
        {
            //因为chn成员chr1Chinese没有结束符，故而不能使用strcmp函数
            //而且此处运算简单，更不需要调用库函数，增加负担
            if (chn->chr1Chinese[0] == chr1Chinese[0] && chn->chr1Chinese[1] == chr1Chinese[1])
            {
                chn->intApearTimes++;
                bMatch = true; //找到目标，标记为真
                break;
            }
        }
        //如果没有匹配到要查询的汉字，则将该汉字增加到缓存中
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
            //因为ChnTemp->chr1Chinese没有结束符，所以不能使用cout输出
            //需要借助有2个字节以上的字符数组来输出
            chn[0] = ChnTemp->chr1Chinese[0], chn[1] = ChnTemp->chr1Chinese[1];
            cout << chn << "  " << "数量: " << ChnTemp->intApearTimes << endl;
        }
    }
}
class EnglishCache //英文字母缓存
{
    //由于已知英文字母只有26个，所以可用顺序表结构存储之，而不是链表。
private:
    //某个字母出现的次数。0到25表示A到Z，不区分大小写
    //如果int1ApearTimes[2]的值等于4，则表示字母C出现了4次
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
        //不区分大小写
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
            cout << ch << "  " << "数量: " << int1ApearTimes[loop] << endl;
        }
    }
}
void StatisticsCharacter(const char* str)
{
    int intChnCount = 0, intEngCount = 0;//中文、英文字符出现的总次数
    ChineseCache ChnCache;
    EnglishCache EngCache;
    while (*str)
    {
        //如果这样写if (*str >= 65 && *str <= 90 || *str >= 97 && *str <= 122) //判断是否为字母，否则为汉字
        //则会忽略标点符号。如果字符串中有标点符号，那么将把标e799bee5baa6e78988e69d8331333337616466点符号看成中文。所以没有采用此算法。
        if (*str < 0) //如果是汉字，汉字在计算机内实际值为负数
        {
            ChnCache.AddApearTimes(str);
            intChnCount++;
            str += 2; //汉字占2个字节，所以一次要跑2个字节
        }
        else //如果是英文字母
        {
            EngCache.AddApearTimes(*str);
            intEngCount++;
            str++;
        }
    }
    EngCache.ShowAllCache();
    ChnCache.ShowAllCache();
    cout << "english 总英文字符数: " << intEngCount << endl;
    cout << "chinese 总中文字符数: " << intChnCount << endl;
}
int main()
{
    char string[1000];
    cout << "1.英文字母不区分大小写。2.请不要输入空格，否则空格后的所有字符将被舍弃" << endl << endl;
    cout << "请输入字符串" << endl;
    cin >> string;
    ::StatisticsCharacter(string);
}